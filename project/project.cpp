#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Queue;
class linkedlistPhone;

class PhoneNode
{
public:
	string brand, model, processor;
	int ram, rom, battery, numberofphone;
	float camera, screen, price;
	PhoneNode *next; //indicate next node
};

class Phone
{
private:
	string brand, model, processor;
	int ram, rom, battery, numberofphone;
	float camera, screen, price;

public:
	Phone();												 //sets default value of all the attributes.
	void input(ifstream &infile);							 //set the value of the attributes from data file
	int getRam() const { return ram; }						 //return the value of ram
	int getRom() const { return rom; }						 //return the value of rom
	int getBattery() const { return battery; }				 //return the value of battery
	float getCamera() const { return camera; }				 //return the value of camera
	float getScreen() const { return screen; }				 //return the value of screen
	float getPrice() const { return price; }				 //return the value of price
	string getModel() const { return model; }				 //return the value of model
	string getBrand() const { return brand; }				 //return the value of Brand
	string getProcessor() const { return processor; }		 //return the value of processor
	int getNumberofPhone() const { return numberofphone; }	 //return the value of numberofphone
	void setNumberofPhone(int num) { numberofphone += num; } //set the value of numberofphone
	void printDetails() const;								 //print details of the phone
	~Phone() {}
};

class ShopOwner
{
public:
	ShopOwner() {}
	void sortMobile(Phone phone[], int count);				 // sort the phone obj array based on model number
	void quickSort(Phone phone[], int first, int last);		 // sort the phone obj array using quick sort technique
	int partition(Phone phone[], int first, int last);		 // determine and return the partition point for quick sort
	int *orderPhone(Phone phone[], int count, int &tracker); //search if any phone has less that 10 numberofohone and add numofphone from use input
	void recieveStock(Phone phone);							 // print changed numberofphone from orderPhone() function
	~ShopOwner() {}
};

class Customer
{
private:
	string customerName;

public:
	Customer() {}
	void getName();																	 // take input from user and store it to customerName
	int searchModel(Phone phone[], int count, string searchitemstr, Queue &queue);	 //search for specific model of phone from all phones
	int searchPrice(Phone phone[], int count, float searchitemfloat, Queue &queue);	 //search for specific price phone from all phones
	int searchRam(Phone phone[], int count, int searchitemint, Queue &queue);		 //search for specific ram phone from all phones
	int searchRom(Phone phone[], int count, int searchitemint, Queue &queue);		 //search for specific rom phone from all phones
	int searchBattery(Phone phone[], int count, int searchitemint, Queue &queue);	 //search for specific battery phone from all phones
	int searchScreen(Phone phone[], int count, float searchitemfloat, Queue &queue); //search for specific screen phone from all phones
	int searchingMenu(Phone phone[], int count, Queue &queue);						 //give user a menu to search for a specific phone
	void buyPhone(PhoneNode &node);													 // reduce numberofphone by 1 of searched phone
	void getReceipt(linkedlistPhone list);											 //print customer and phone details
	~Customer() {}
};

class Queue
{
private:
	int front, back;
	Phone *item;

public:
	void createQueue() //set the initial value
	{
		front = 0;
		back = -1;
		item = new Phone[100];
	}
	bool isEmpty() { return bool(back < front); } //check if Queue is empty
	bool isFull() { return bool(back == 99); }	  //check if Queue is full
	Phone getFront() { return item[front]; }	  //return the first value of queue
	Phone getBack() { return item[back]; }		  //return the last value of queue
	void destroyQueue() { delete[] item; }		  // delete all the item values of queue
	void enQueue(Phone phone)					  // insert a Phone class object into queue
	{
		if (isFull())
			cout << "Can not enQueue. Queue is already full." << endl;
		else
		{
			back++;
			item[back] = phone;
		}
	}
	void deQueue() // deQueue the first element of queue
	{
		if (isEmpty())
			cout << "Queue is already empty." << endl;
		else
		{
			front++;
		}
	}
};

class linkedlistPhone
{
private:
	PhoneNode *head, *tail;

public:
	linkedlistPhone();							  //set initial value for head and tail.
	void insertPhone(Phone phone);				  //insert a node into linked list by taking a Phone object
	void insertPhone(PhoneNode node);			  //insert a node into linked list by taking a PhoneNode object
	bool isEmpty() { return bool(head == NULL); } //check if linked list is empty
	void displayList();							  // display all the values of all the nodes in the linked list
	void deletePhone(int x);					  //delete a node from linked list
	PhoneNode FindNode(int x = 1);				  // find a node from linked list based on index value
	void destroyLinkedList();					  // delete all the nodes in linked list
};

// ---------------------------------------------------------------------------------------------------
// class Phone member function definition
// ---------------------------------------------------------------------------------------------------

Phone::Phone() // set default value
{
	brand = model = processor = " ";
	ram = rom = battery = numberofphone = 0;
	camera = screen = price = 0;
}

void Phone::input(ifstream &infile) // set value from file
{
	infile >> brand >> model >> processor >> ram >> rom >> battery >> camera >> screen >> price >> numberofphone;
}

void Phone::printDetails() const //       print phone specification
{

	cout << "Brand: " << brand << endl;
	cout << "Model No.: " << model << endl;
	cout << "Display: " << screen << " inch" << endl;
	cout << "Chipset: " << processor << endl;
	cout << "Mamory RAM: " << ram << " GB" << endl;
	cout << "Mamory ROM: " << rom << " GB" << endl;
	cout << "Camera: " << camera << " MP" << endl;
	cout << "Battery: " << battery << " mah" << endl;
	cout << "Price: " << price << " RM" << endl
		 << endl;
}

// ---------------------------------------------------------------------------------------------------
// class ShopOwner member function definition
// ---------------------------------------------------------------------------------------------------

void ShopOwner::sortMobile(Phone phone[], int count) // sort the phone array object based on model number
{
	int first = 0;
	quickSort(phone, first, count);
}

void ShopOwner::quickSort(Phone phone[], int first, int last) // function for quick sort
{
	int cut;
	if (first < last)
	{
		cut = partition(phone, first, last);
		quickSort(phone, first, cut);
		quickSort(phone, cut + 1, last);
	}
}

int ShopOwner::partition(Phone phone[], int first, int last) // determine the partition index for quick sort
{
	string pivot;
	Phone temp;
	int loop, cutPoint, bottom, top;
	pivot = phone[first].getModel(); // identify pivot
	bottom = first;
	top = last;
	loop = 1; //always TRUE

	while (loop)
	{
		while ((phone[top].getModel().compare(pivot)) > 0)
		{
			top--;
		}
		while ((phone[bottom].getModel().compare(pivot)) < 0)
		{
			bottom++;
		}
		if (bottom < top)
		{
			// change pivot place
			temp = phone[bottom];
			phone[bottom] = phone[top];
			phone[top] = temp;
		}
		else
		{
			loop = 0; //loop false
			cutPoint = top;
		}
	} // end while
	return cutPoint;
}

int *ShopOwner::orderPhone(Phone phone[], int count, int &tracker) // check if any phone model has less that 10 phones
{
	int num, *index = new int[100];
	for (int i = 0; i < count; i++)
	{
		if (phone[i].getNumberofPhone() < 10)
		{
			cout << "How many phone set want to order of " << phone[i].getModel() << " model ?? \n=> ";
			cin >> num;
			phone[i].setNumberofPhone(num);
			index[tracker] = i;
			tracker++;
		}
	}
	if (tracker == 0)
		cout << "No phone need to order." << endl
			 << endl;
	return index;
}

void ShopOwner::recieveStock(Phone phone) // print the ordered phone details
{
	cout << "Brand: " << phone.getBrand() << endl;
	cout << "Model: " << phone.getModel() << endl;
	cout << "Updated Number of handset: " << phone.getNumberofPhone() << endl
		 << endl;
}

// ---------------------------------------------------------------------------------------------------
// class Customer member function definition
// ---------------------------------------------------------------------------------------------------

void Customer::getName() // get the customer name from keyboard
{
	cout << "Enter customer name: ";
	cin.ignore();
	getline(cin, customerName);
}

int Customer::searchModel(Phone phone[], int count, string searchitemstr, Queue &queue) //search a phone based on model number and store in Queue object
{
	int index = 0;
	for (int p = 0; p < count; p++)
	{
		if (searchitemstr == phone[p].getModel())
		{
			queue.enQueue(phone[p]);
			index++;
		}
	}

	return index;
}

int Customer::searchPrice(Phone phone[], int count, float searchitemfloat, Queue &queue) // search a phone based on price and store in Queue object
{
	int index = 0;
	for (int p = 0; p < count; p++)
	{
		if (searchitemfloat == phone[p].getPrice())
		{
			queue.enQueue(phone[p]);
			index++;
		}
	}

	return index;
}

int Customer::searchRam(Phone phone[], int count, int searchitemint, Queue &queue) // search a phone based on ram size and store in Queue object
{
	int index = 0;
	for (int p = 0; p < count; p++)
	{
		if (searchitemint == phone[p].getRam())
		{
			queue.enQueue(phone[p]);
			index++;
		}
	}

	return index;
}
int Customer::searchRom(Phone phone[], int count, int searchitemint, Queue &queue) // search a phone based on rom size and store in Queue object
{
	int index = 0;
	for (int p = 0; p < count; p++)
	{
		if (searchitemint == phone[p].getRom())
		{
			queue.enQueue(phone[p]);
			index++;
		}
	}

	return index;
}
int Customer::searchBattery(Phone phone[], int count, int searchitemint, Queue &queue) // search a phone based on battery size and store in Queue object
{
	int index = 0;
	for (int p = 0; p < count; p++)
	{
		if (searchitemint == phone[p].getBattery())
		{
			queue.enQueue(phone[p]);
			index++;
		}
	}

	return index;
}

int Customer::searchScreen(Phone phone[], int count, float searchitemfloat, Queue &queue) // search a phone based on screen size and store in Queue object
{
	int index = 0;
	for (int p = 0; p < count; p++)
	{
		if (searchitemfloat == phone[p].getScreen())
		{
			queue.enQueue(phone[p]);
			index++;
		}
	}

	return index;
}

void Customer::buyPhone(PhoneNode &node) // buy the searched phone and reduce number of phone by one
{
	node.numberofphone = node.numberofphone - 1;
}

void Customer::getReceipt(linkedlistPhone list) // print the receipt of the customer
{
	cout << "\n----------Receipt----------" << endl
		 << endl;
	cout << "-----Customer Details-----" << endl;
	cout << "Customer's Name: " << customerName << endl
		 << endl;
	cout << "-----Phone Specification-----" << endl;
	list.displayList();
}

int Customer::searchingMenu(Phone phone[], int count, Queue &queue) // searching menu
{
	string searchitemstr;
	int searchitemint, index, choice;
	float searchitemfloat;
	char choose;
B:
	system("CLS");
	cout << "a. Model \nb. Feature \nc. Price " << endl
		 << endl;
	cout << "Enter your choice [1-3]: ";
	cin >> choose;
	if (choose == 'a' || choose == 'A')
	{
		cout << endl;
		cout << "Enter Model Name: ";
		cin >> searchitemstr;
		cout << endl;
		index = searchModel(phone, count, searchitemstr, queue);
	}
	else if (choose == 'b' || choose == 'B')
	{
	C:
		system("CLS");
		cout << "Which feature you want to search?" << endl;
		cout << "1. Ram\n2. Rom\n3. Battery\n4. Screen" << endl
			 << endl;
		cout << "Enter your choice [1-4]: ";
		cin >> choice;
		if (choice == 1)
		{
			cout << endl;
			cout << "Enter Ram Size: ";
			cin >> searchitemint;
			cout << endl;
			index = searchRam(phone, count, searchitemint, queue);
		}
		else if (choice == 2)
		{
			cout << endl;
			cout << "Enter Rom Size: ";
			cin >> searchitemint;
			cout << endl;
			index = searchRom(phone, count, searchitemint, queue);
		}
		else if (choice == 3)
		{
			cout << endl;
			cout << "Enter Battery Size: ";
			cin >> searchitemint;
			cout << endl;
			index = searchBattery(phone, count, searchitemint, queue);
		}
		else if (choice == 4)
		{
			cout << endl;
			cout << "Enter Screen Size: ";
			cin >> searchitemfloat;
			cout << endl;
			index = searchScreen(phone, count, searchitemfloat, queue);
		}
		else
		{
			cout << "\nWrong Input. Please choose the correct Option." << endl;
			cout << "<< Press any key to continue >>";
			cin.ignore();
			cin.get();
			goto C;
		}
	}
	else if (choose == 'c' || choose == 'C')
	{
		cout << endl;
		cout << "Enter price of the phone: ";
		cin >> searchitemfloat;
		cout << endl;
		index = searchPrice(phone, count, searchitemfloat, queue);
	}
	else
	{
		cout << "\nWrong Input. Please choose the correct Option." << endl;
		cout << "<< Press any key to continue >>";
		cin.ignore();
		cin.get();
		goto B;
	}
	return index;
}

// ---------------------------------------------------------------------------------------------------
// class linkedlistPhone member function definition
// ---------------------------------------------------------------------------------------------------

linkedlistPhone::linkedlistPhone()
{
	head = NULL;
	tail = NULL;
}

void linkedlistPhone::insertPhone(Phone phone) //insert a node into linked list by taking a Phone object
{
	PhoneNode *newNode;
	newNode = new PhoneNode;

	newNode->brand = phone.getBrand();
	newNode->model = phone.getModel();
	newNode->processor = phone.getProcessor();
	newNode->ram = phone.getRam();
	newNode->rom = phone.getRom();
	newNode->battery = phone.getBattery();
	newNode->camera = phone.getCamera();
	newNode->screen = phone.getScreen();
	newNode->price = phone.getPrice();
	newNode->numberofphone = phone.getNumberofPhone();

	if (isEmpty())
	{
		newNode->next = NULL;
		head = newNode;
		tail = newNode;
	}
	else
	{
		newNode->next = NULL;
		tail->next = newNode;
		tail = newNode;
	}
}

void linkedlistPhone::insertPhone(PhoneNode node) //insert a node into linked list by taking a PhoneNode object
{
	PhoneNode *newNode;
	newNode = new PhoneNode;

	newNode->brand = node.brand;
	newNode->model = node.model;
	newNode->processor = node.processor;
	newNode->ram = node.ram;
	newNode->rom = node.rom;
	newNode->battery = node.battery;
	newNode->camera = node.camera;
	newNode->screen = node.screen;
	newNode->price = node.price;
	newNode->numberofphone = node.numberofphone;

	if (isEmpty())
	{
		newNode->next = NULL;
		head = newNode;
		tail = newNode;
	}
	else
	{
		newNode->next = NULL;
		tail->next = newNode;
		tail = newNode;
	}
}

void linkedlistPhone::displayList() // display all the values of all the nodes in the linked list
{
	PhoneNode *currNode = new PhoneNode;
	currNode = head;
	int i = 1;
	if (isEmpty())
		cout << "Linked List is Empty." << endl;
	else
	{
		while (currNode)
		{
			cout << i++ << "." << endl;
			cout << "Brand: " << currNode->brand << endl;
			cout << "Model No.: " << currNode->model << endl;
			cout << "Display: " << currNode->screen << " inch" << endl;
			cout << "Chipset: " << currNode->processor << endl;
			cout << "Mamory RAM: " << currNode->ram << " GB" << endl;
			cout << "Mamory ROM: " << currNode->rom << " GB" << endl;
			cout << "Camera: " << currNode->camera << " MP" << endl;
			cout << "Battery: " << currNode->battery << " mah" << endl;
			cout << "Price: " << currNode->price << " RM" << endl
				 << endl;

			currNode = currNode->next;
		}
	}
}

void linkedlistPhone::deletePhone(int x) //delete a node from linked list
{
	PhoneNode *currNode = new PhoneNode;
	PhoneNode *prevNode = new PhoneNode;
	currNode = head;
	int index = 1;
	while (index != x)
	{
		prevNode = currNode;
		currNode = currNode->next;
		index++;
	}
	if (index == x)
	{
		prevNode->next = currNode->next;
		delete currNode;
	}
}

PhoneNode linkedlistPhone::FindNode(int x) // find a node from linked list based on index value
{
	PhoneNode *currNode = new PhoneNode;
	currNode = head;
	PhoneNode final;
	int index = 1;
	while (index != x)
	{
		currNode = currNode->next;
		index++;
	}
	if (index == x)
	{
		final = *currNode;
	}
	return final;
}

void linkedlistPhone::destroyLinkedList() // delete all the nodes in linked list
{
	PhoneNode *currNode = new PhoneNode;
	PhoneNode *nextNode = new PhoneNode;
	currNode = head;
	while (currNode != NULL)
	{
		nextNode = currNode->next;
		delete currNode;
		currNode = nextNode;
	}
	head = NULL;
	tail = NULL;
}

int main()
{
	string name; // string vatiable to store the name of the customer.
	int user, inputcounter = 0, tracker = 0, index, *orderphone, x;
	Phone *phone;
	phone = new Phone[100]; // dynamic allocation of phone object array
	orderphone = new int[100];
	ifstream infile("PhoneFile.txt"); // open the "PhoneFile.txt" file to take input
	if (!infile)					  // check if "PhoneFile.txt" file is opened.
	{
		cout << "Error" << endl;
		cout << "Can not open the file" << endl;
		return 0;
	}
	while (!(infile.eof())) // read value from file
	{
		phone[inputcounter].input(infile);
		inputcounter++;
	}
	inputcounter = inputcounter - 1;
	infile.close(); // close the "PhoneFile.txt" file
	int choose;
	ShopOwner shopowner;   //ShopOwner class object
	Customer customer;	   //Customer class object
	Queue queue;		   //Queue class object
	Phone *p = new Phone;  //dynamic allocation of Phone class object p
	linkedlistPhone list;  //linkedlistPhone object declaration for storing buying list nodes
	linkedlistPhone list2; //linkedlistPhone object declaration for storing searching and queue nodes
	PhoneNode node;		   //PhoneNode object declaration for storing the buying phone node
A:
	system("CLS");
	cout << "Welcome to Smartphone Selling System" << endl;
	cout << "Enter as a," << endl
		 << endl;
	cout << "1.Shop Owner \n2.Customer\n3.Exit " << endl
		 << endl;
	cout << "Enter your choice [1-3]: ";
	cin >> user;

	if (user == 1) // Shop Owner menu
	{
	D:
		system("CLS");
		cout << "Shop Owner Menu" << endl
			 << endl;
		cout << "1. Sort the phone based on the phone model " << endl;
		cout << "2. Order phone " << endl;
		cout << "3. Receive stock " << endl;
		cout << "4. Detail information for a phone. " << endl;
		cout << "5. Back" << endl
			 << endl;
		cout << "Enter your choice [1-5]: ";
		cin >> choose;
		switch (choose)
		{
		case 1: //sort the phone object array
		{
			system("CLS");
			shopowner.sortMobile(phone, inputcounter);
			cout << "Phone list has been sorted based on the phone model number." << endl
				 << endl;
			cout << "New Phone List," << endl;
			for (int i = 0; i < inputcounter; i++)
			{
				phone[i].printDetails();
			}
			cout << "<< Press any key to go back >>";
			cin.ignore();
			cin.get();
			goto D;
			break;
		}

		case 2: // order phone if any model has less then 10 phones
		{
			system("CLS");
			orderphone = shopowner.orderPhone(phone, inputcounter, tracker);
			cout << "<< Press any key to to go back >>" << endl;
			cin.ignore();
			cin.get();
			goto D;
			break;
		}

		case 3: // shows which phones have been ordered
		{
			system("CLS");
			if (tracker != 0)
			{
				cout << "Recieved Stock" << endl;
				for (int i = 0; i < tracker; i++)
				{
					shopowner.recieveStock(phone[(orderphone[i])]);
				}
			}
			else
			{
				cout << "No stock recieved " << endl;
			}
			cout << "<< Press any key to go back >>";
			cin.ignore();
			cin.get();
			goto D;
			break;
		}
		case 4: //search a phone and show the deatils of that phone
		{
			system("CLS");
			cout << "Search Phone" << endl;
			queue.createQueue();
			index = customer.searchingMenu(phone, inputcounter, queue);
			if (index == 0)
			{
				cout << "Search Item not found." << endl;
			}
			else
			{

				for (int i = 0; i < index; i++)
				{
					*p = queue.getFront();
					queue.deQueue();
					p->printDetails();
					cout << endl;
				}
			}
			queue.destroyQueue();
			cout << "<< Press any key to go back >>";
			cin.ignore();
			cin.get();
			goto D;
			break;
		}
		case 5: // check if user put wrong input
			goto A;
		default:
		{
			cout << "\nWrong Input. Please choose the correct Option." << endl;
			cout << "<< Press any key to continue >>";
			cin.ignore();
			cin.get();
			goto D;
		}
		}
	}
	else if (user == 2) //Customer Menu
	{
		system("CLS");
		customer.getName();

	E:
		system("CLS");
		cout << "Customer Menu" << endl
			 << endl;
		cout << "1. Search phone " << endl;
		cout << "2. Buy phone " << endl;
		cout << "3. Recipt " << endl;
		cout << "4. Back" << endl
			 << endl;
		cout << "Enter your choice [1-4]: ";
		cin >> choose;
		switch (choose)
		{
		case 1: //search for phone and show the details of the phone
			system("CLS");
			queue.createQueue();
			index = customer.searchingMenu(phone, inputcounter, queue);
			if (index == 0)
			{
				cout << "Search Item not found." << endl;
			}
			else
			{
				for (int i = 0; i < index; i++)
				{
					cout << i + 1 << "." << endl;
					*p = queue.getFront();
					list2.insertPhone(queue.getFront());
					queue.deQueue();
					p->printDetails();
					cout << endl;
				}
			}
			cout << "<< Press any key to go back >>";
			cin.ignore();
			cin.get();
			goto E;
			break;
		case 2: // buy the searched phone
			system("CLS");
			if (index == 0)
			{
				cout << "No Phone has been searched" << endl;
				cout << "<< Press any key to go back >>";
				cin.ignore();
				cin.get();
				goto E;
			}

			cout << "-----Phone Specification-----" << endl;
			list2.displayList();
			if (index == 1)
			{
				node = list2.FindNode(index);
				customer.buyPhone(node);
			}

			else
			{
				cout << "Enter the number of phone you want to buy form [1-" << index << "] :";
				cin >> x;
				node = list2.FindNode(x);
				customer.buyPhone(node);
			}

			cout << node.brand << " " << node.model << " has been added to buying list." << endl
				 << endl;
			list.insertPhone(node);
			list2.destroyLinkedList();
			char ch;
			cout << "Do you want to buy another phone?(Y/N) :";
			cin >> ch;
			while (ch == 'Y')
			{
				queue.destroyQueue();
				queue.createQueue();
				index = customer.searchingMenu(phone, inputcounter, queue);
				if (index == 0)
				{
					cout << "Search Item not found." << endl;
				}
				else
				{
					for (int i = 0; i < index; i++)
					{
						cout << i + 1 << "." << endl;
						*p = queue.getFront();
						list2.insertPhone(queue.getFront());
						queue.deQueue();
						p->printDetails();
						cout << endl;
					}

					if (index == 1)
					{
						node = list2.FindNode();
						customer.buyPhone(node);
					}

					else
					{
						cout << "Enter the number of phone you want to buy form [1-" << index << "] :";
						cin >> x;
						node = list2.FindNode(x);
						customer.buyPhone(node);
					}

					cout << node.brand << " " << node.model << " has been added to buying list." << endl
						 << endl;
					list.insertPhone(node);
					list2.destroyLinkedList();
				}
				cout << "Do you want to buy another phone?(Y/N) :";
				cin >> ch;
			}
			system("CLS");
			cout << "Do u want to delete any item from buying list?(Y/N):";
			cin >> ch;
			while (ch == 'Y')
			{
				cout << "Your current buying list," << endl;
				list.displayList();
				cout << "Enter the number of phone you want to delete :";
				cin >> x;
				list.deletePhone(x);
				cout << endl
					 << "Phone is deleted from buying list." << endl
					 << endl;
				cout << "Do u want to delete any item from buying list?(Y/N):";
				cin >> ch;
			}
			cout << "<< Press any key to go back >>";
			cin.ignore();
			cin.get();
			goto E;
			break;
		case 3: // get receipt of the brought phone
			system("CLS");
			customer.getReceipt(list);
			cout << "<< Press any key to go back >>";
			cin.ignore();
			cin.get();
			goto E;
			break;
		case 4: // check if user put wrong input
			goto A;
			break;
		default:
		{
			cout << "\nWrong Input. Please choose the correct Option." << endl;
			;
			cout << "<< Press any key to continue >>";
			cin.ignore();
			cin.get();
			goto E;
		}
		}
	}
	else if (user == 3) // close the program
	{
		cout << "Thanks for using the App...\nSee you again" << endl;
		goto F;
	}

	else // check if user put wrong input
	{
		cout << "\nWrong Input. Please choose the correct Option." << endl;
		cout << "<< Press any key to continue >>";
		cin.get();
		goto A;
	}
F:
	system("pause");
	return 0;
}