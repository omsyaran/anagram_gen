// gonna do the new anagram genarator

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

// stack part is here
class stack
{
public:
	struct stacknode
	{
		char value;	// value inside the stack is char
		stacknode* next;	// points to the next node
	};
	stacknode* stacktop; // points to the top of the stack
	stack(); // comstructor
	~stack(); // destructor
	void push(char); // masukkan data
	void pop(char&); // keluarkan data
	bool is_empty(); // check if the stack is empty or not
	string show_stack()const; // shows the values 
	void copyr(stack&);
};

stack::stack()
{
	stacktop = nullptr;
}

stack::~stack()
{
	stacknode* deleter;
	while (stacktop != nullptr) // while got element inside thr stack
	{
		deleter = stacktop;
		stacktop = stacktop->next;
		delete deleter;
	}
}

void stack::push(char input)
{
	stacknode* newnode = nullptr;
	newnode = new stacknode;
	newnode->value = input;

	if (is_empty())
	{
		stacktop = newnode;
		newnode->next = nullptr;
	}
	else
	{
		newnode->next = stacktop;
		stacktop = newnode;
	}
}

void stack::pop(char& input)
{
	stacknode* temp = nullptr;

	if (is_empty())
	{
		cout << "\nTHE STACK IS EMPTY MY FRIEND.." << endl;
	}
	else
	{
		input = stacktop->value;
		temp = stacktop->next;
		delete stacktop;
		stacktop = temp;
	}

}

bool stack::is_empty()
{
	// stack is empty if stacktop is empty
	bool checker = false;
	if (stacktop == nullptr)
		checker = true;

	return checker;
}

string stack::show_stack()const
{
	stacknode* displayer;
	displayer = stacktop;
	string collecter;
	while (displayer)
	{
		collecter = collecter + displayer->value;
		displayer = displayer->next;
	}

	return collecter;
}

void stack::copyr(stack& new_stack)
{
	stacknode* copier1 = stacktop;
	char input;
	while (copier1)
	{
		input = copier1->value;
		new_stack.push(input);
		copier1 = copier1->next;
	}
}


// queue part is here
class qnode {
public:
	char value;
	qnode* next;

	qnode(char input)
	{
		value = input;
		next = nullptr;
	}
};

class qlist {
private:
	qnode* front;
	qnode* rear;
	int num_node;
public:
	qlist();
	~qlist();
	void enqueue(char);
	void dequeue();
	bool is_empty()const;
	void display()const;
	char get(int); // insert the node place tht u want to retrive
};

qlist::qlist()
{
	front = nullptr;
	rear = nullptr;
	num_node = 0;
}

qlist::~qlist()
{
	qnode* deleter1 = front;
	qnode* deleter2 = nullptr;
	while (deleter1 != nullptr)
	{
		deleter2 = deleter1->next;
		delete deleter1;
		deleter1 = deleter2;
	}
}

bool qlist::is_empty()const
{
	bool checker = true;
	if (num_node > 0)
		checker = false;

	return checker;
}

void qlist::dequeue()
{
	qnode* deleter = front;
	if (is_empty())
		cout << "\n\nThe list is empty!";
	else
	{
		deleter = front;
		front = front->next;
		delete deleter;
		num_node--;
	}
}

void qlist::enqueue(char input)
{
	qnode* newnode = nullptr;
	newnode = new qnode(input);
	if (is_empty())
	{
		front = newnode;
		rear = newnode;
	}
	else
	{
		rear->next = newnode;
		rear = newnode;
	}
	num_node++;
}

void qlist::display()const
{
	qnode* displayer;
	displayer = front;
	while (displayer) {
		cout << displayer->value << " ";
		displayer = displayer->next;
	}
}

void swap(char& a, char& b)
{
	char temp;
	temp = a;
	a = b;
	b = temp;
}

char qlist::get(int place)
{
	qnode* getter = front;
	for (int i = 0; i < place; i++)
	{
		getter = getter->next;
	}
	return (getter->value);
}


// ganti value kat tempat yang sama....
void swap_value(char a, char& b)
{
	b = a;
}

// when the word length is 4........got 24 combinations
void panjang34(string s)
{
	// openeing filename
	fstream outfile;
	outfile.open("4or3huruf.txt", ios::out);

	// file part above this...

	int length = s.length(); // the length of the string is found
	qlist qlist1; // created a queue
	stack stack1, stack2;// created stack1,stack2

	int place1 = s.length() - 2;
	int place2 = s.length() - 1;
	int sets;

	// sets = 1 for 3 huruf
	// sets = 3 for 4 huruf
	// sets = 4 for 5 huruf , currently should be 12


	if (s.length() == 2 || s.length() == 3)
		sets = 1;
	else
		sets = 3;


	for (int z = 0; z < sets; z++)// main guy outside
	{
		cout << "\n\nTHE CURRENT STRING VALUE IS :  " << s << endl;
		for (int j = 0; j < length; j++)
			qlist1.enqueue(s[j]); // 1234 sdh masuk dlm queue
		for (int k = 0; k < length; k++)
		{
			for (int i = 0; i < length; i++)
			{
				stack1.push(qlist1.get(i));	// 1234 sdh masuk dlm stack1
			}
			stack1.copyr(stack2);
			outfile << stack1.show_stack() << "\n"; 					// save the value into the linked list first  
			cout << endl;
			outfile << stack2.show_stack() << "\n";			// save the value into the linked list first
			qlist1.dequeue();
			qlist1.enqueue(s[k]);
			stack1.~stack();	// clears the stack...,use intialize stack...to make things clear...
			stack2.~stack();	// clears the stack...,use intialize stack...to make things clear...
			cout << "\n" << endl;
		}
		if (s.length() == 4)
		{
			for (int j = 0; j < length; j++)	// emptying the queue, all of it
				qlist1.dequeue();
			swap(s[place1], s[place2]);	// from 2,3 it goes to 1,2...kurang by satu..
			place1--;
			place2--;
		}
	}
	outfile.close();

}


// for words with 5 huruf , will have 120 combinations
void panjang5(string huruf5)
{
	// bukak filename

	fstream outfile;
	outfile.open("5huruf.txt", ios::out);

	// file part above this...




	string huruf4;
	int size = huruf5.length();

	for (int i = 1; i < size; i++) // huruf4 is created, "bcde" 
		huruf4 = huruf4 + huruf5[i];

	string newhuruf4 = huruf4;	// a copy of huruf4....newhuruf4 = 1234

	for (int j = 0; j < size; j++)	//size = 5
	{

		int length = huruf4.length(); // the length of the string is found
		qlist qlist1; // created a queue
		stack stack1, stack2;// created stack1,stack2

		int place1 = huruf4.length() - 2;
		int place2 = huruf4.length() - 1;
		int sets = 3;

		for (int z = 0; z < sets; z++)// main guy outside
		{
			cout << "\n\nTHE CURRENT STRING VALUE IS :  " << huruf4 << endl;
			for (int j = 0; j < length; j++)
				qlist1.enqueue(huruf4[j]); // 1234 sdh masuk dlm queue
			for (int k = 0; k < length; k++)	// 4 times loop
			{
				for (int i = 0; i < length; i++)
				{
					stack1.push(qlist1.get(i));	// 1234 sdh masuk dlm stack1
				}
				stack1.copyr(stack2); // get reverse version of 1234

				string dummy1;
				dummy1 = huruf5[j];
				dummy1 = dummy1 + stack1.show_stack();
				//outfile << dummy1 << "\n";

				cout << endl;

				string dummy2;
				dummy2 = huruf5[j];
				dummy2 = dummy2 + stack2.show_stack();
				//outfile << dummy2 << "\n";

				qlist1.dequeue();
				qlist1.enqueue(huruf4[k]); // keluar(keluar) then masuk balik (belakang)..
				stack1.~stack();	// clears the stack...,use intialize stack...to make things clear...
				stack2.~stack();	// clears the stack...,use intialize stack...to make things clear...
				cout << "\n" << endl;
			}

			for (int j = 0; j < length; j++)	// emptying the queue, all of it
				qlist1.dequeue();
			swap(huruf4[place1], huruf4[place2]);	// from 2,3 it goes to 1,2...kurang by satu..
			place1--;
			place2--;
		}
		if (j <= 3) // tukarq huruf4 set
		{
			swap_value(huruf5[j], newhuruf4[j]);	// utk 0123
			huruf4 = newhuruf4;
			outfile << huruf4 << endl;
		}

	}

	outfile.close();


}


// for words with 6 huruf , will have 720 combinations
void panjang6(string huruf6) // str is huruf6 now...ingat
{

	// openeing filename

	fstream outfile;
	outfile.open("6huruf.txt", ios::out);

	// file part above this...

	string huruf5;
	for (int i = 1; i < 6; i++)
		huruf5 = huruf5 + huruf6[i];	// created huruf5 from huruf6 which is 23456

	string newhuruf5 = huruf5;	// a copy of huruf5.. 23456
	string nhuruf4,nhuruf5; // 2 more copiers, holders

	nhuruf5 = newhuruf5; // nhuruf5 = 23456 -> 13456 -> 12456 -> 12356 -> 12346 -> 12345 (4)
	
	
	// masuk dlm for loop.....

	for (int w = 0; w < 6; w++)  // for huruf6 utk masuk
	{
		// nhuruf4 = 3456 -> 2456 -> 2356 -> 2346 -> 2345 (3) this is for 23456

		string huruf4;
		for (int i = 1; i < 5; i++) // 
			huruf4 = huruf4 + huruf5[i];	// created huruf4 from huruf5
		string newhuruf4 = huruf4;	// a copy of huruf4..  3456
		nhuruf4 = newhuruf4;
		cout << "\nNHURUF4 : " << nhuruf4 << endl;

		for (int j = 0; j < 5; j++) // for huruf5 utk masuk first
		{
			int length = huruf4.length(); // length = 4
			qlist qlist1; // created a queue
			stack stack1, stack2;// created stack1,stack2
			int place1 = huruf4.length() - 2;
			int place2 = huruf4.length() - 1;
			int sets = 3;

			for (int z = 0; z < sets; z++)// main guy outside
			{
				for (int j = 0; j < length; j++)
					qlist1.enqueue(huruf4[j]); // huruf4 masuk dlm queue
				for (int k = 0; k < length; k++)
				{
					for (int i = 0; i < length; i++)
						stack1.push(qlist1.get(i));	// huruf4 masuk dlm stack1
					
					stack1.copyr(stack2);	// huruf4 kena reversed

					string dummy1;
					dummy1 = huruf6[w];
					dummy1 = dummy1 + huruf5[j];
					dummy1 = dummy1 + stack1.show_stack();
					outfile << dummy1 << "\n";

					string dummy2;
					dummy2 = huruf6[w];
					dummy2 = dummy2 + huruf5[j];
					dummy2 = dummy2 + stack2.show_stack();
					outfile << dummy2 << "\n";


					qlist1.dequeue();
					qlist1.enqueue(huruf4[k]);
					stack1.~stack();	// clears the stack...,use intialize stack...to make things clear...
					stack2.~stack();	// clears the stack...,use intialize stack...to make things clear...
				}

				for (int j = 0; j < length; j++)	// emptying the queue, all of it
					qlist1.dequeue();

				swap(huruf4[place1], huruf4[place2]);	// from 2,3 it goes to 1,2...kurang by satu..
				place1--;
				place2--;
			}
			if (j < 4)	// creates huruf4 new one for me...
			{
				swap_value(newhuruf5[j], nhuruf4[j]);	// nhuruf4 will get new string for huruf4
				huruf4 = nhuruf4;
				//outfile << huruf4 << endl;
			}
		}

		if (w < 5 )	// creates huruf5 new one for me...
		{
			// do this sequence 0,2,3,4
			// utk nhuruf5 = 23456 -> 13456 -> 12456 -> 12356 -> 12346 -> 12345 (4)
			if (w == 1)
			{
				swap_value(huruf6[w], nhuruf5[w]);
				swap_value(huruf6[w+1], nhuruf5[w+1]);
			}
			else
			{
				swap_value(huruf6[w], nhuruf5[w]);
			}
			huruf5 = nhuruf5;
			cout << "\nHuruf5 : " << huruf5 << endl;

		}


	}


	outfile.close();


}




// the main juice man
int main()
{

	string input = "oms";
	if (input.length() == 3 || input.length() == 4)
		panjang34(input);
	if (input.length() == 5)
		panjang5(input);
	if (input.length() == 6)
		panjang6(input);		

	cout << "\n";
	system("pause");
}

