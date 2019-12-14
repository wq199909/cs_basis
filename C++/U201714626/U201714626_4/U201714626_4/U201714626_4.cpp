#include<cstdio>
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include "U201714626_4.h"
using namespace std;
ofstream out;

/*
* 栈函数定义
*/
STACK::STACK(int m) : max(m), elems(new int[m]) {
	pos = 0;
}
STACK::STACK(const STACK&s) : max(s.max), elems(new int[s.max]), pos(s.pos) {
	for (int i = 0; i < s.pos; i++) {
		STACK::elems[i] = s.elems[i];
	}
}
STACK::STACK(STACK&&s) : max(STACK::max), elems(s.elems), pos(s.pos) {
	*((int **)&(s.elems)) = nullptr;
	*((int *)&(s.max)) = 0;
	s.pos = 0;
}
STACK::operator int() const {
	return pos;
}
int STACK::operator[] (int x) const {
	return elems[x];
}
STACK& STACK::operator<<(int e) {
	if (pos >= max) {
		this->~STACK();

	}
	else {
		*(elems + pos) = e;
		pos++;
	}
	return (*this);
}
STACK& STACK::operator>>(int &e) {
	if (pos == 0) {
		cout << "栈为空";
	}
	else {
		e = *(elems + pos - 1);
		pos -= 1;
	}
	return (*this);
}
STACK& STACK::operator=(const STACK&s) {
	pos = s.pos;
	*((int *)&(s.max)) = s.max;
	int *arr = new int[s.max];
	for (int i = 0; i < this->size(); i++) {
		arr[i] = s.elems[i];
	}
	this->~STACK();
	*(int **)(&elems) = arr;
	return (*this);
}
STACK &STACK::operator=(STACK&&s) {
	*((int **)&(elems)) = s.elems;
	pos = s.pos;
	*((int *)&(max)) = s.max;
	*((int **)&(s.elems)) = 0;
	*((int *)&(s.max)) = 0;
	s.pos = 0;
	return (*this);
}
int STACK::size() const {
	return max;
}
void STACK::print() const {
	if (k == 1) {
		for (int i = 0; i < pos; ++i) {
			out << elems[i] << "  ";
		}
		out << flush;
	}
	else {
		for (int i = pos - 1; i >= 0; --i) {
			out << elems[i] << "  ";
		}
		out << flush;
	}
}
STACK::~STACK() {
	if (elems != 0) {
		delete[]elems;
		*(int **)(&elems) = 0;
	}
}

/*
* 队列函数定义
*/
QUEUE::QUEUE(int m) :STACK(m), s(m) {};
QUEUE::QUEUE(const QUEUE&q) : s(q.s), STACK(q) {};
QUEUE::QUEUE(QUEUE&&s) :s(s.s), STACK(s) {};
QUEUE::operator int() const {
	return STACK::operator int() + this->s.operator int();
}
int QUEUE::full() const {
	return (STACK::operator int() == STACK::size() && this->s.operator int() != 0) ? 1 : 0;
}
int QUEUE::operator[ ] (int x) const {
	if (x >= s.operator int()) {
		return STACK::operator[](s.operator int() - (x - STACK::operator int()) - 1);
	}
	return STACK::operator[](x);
}
QUEUE& QUEUE::operator<<(int e) {
	if (STACK::operator int() == STACK::size() && s.operator int() == 0) {
		int ele;
		while (STACK::operator int() > 0) {
			STACK::operator>>(ele);
			s.operator<<(ele);
		}
	}
	STACK::operator<<(e);
	return (*this);
}
QUEUE& QUEUE::operator>>(int &e) {
	if (s.operator int() == 0) {
		int ele;
		while (STACK::operator int() > 0) {
			STACK::operator>>(ele);
			s.operator<<(ele);
		}
	}
	s.operator>>(e);
	return (*this);
}
QUEUE&  QUEUE::operator=(const QUEUE&q) {
	STACK::operator=(q);
	s.operator=(q.s);
	return (*this);
}
QUEUE& QUEUE::operator=(QUEUE&&q) {
	STACK::operator=(q);
	s.operator=(q.s);
	q.~QUEUE();
	return (*this);
}
void QUEUE::print() const {
	k = -1;
	s.print();
	k = 1;
	STACK::print();
}
QUEUE::~QUEUE() {
	STACK::~STACK();
	s.~STACK();
}

bool Utils::convertToInt(const std::string &s, int &out) {
	using namespace std;

	try {
		out = stoi(s);
	}
	catch (invalid_argument i) {
		return false;
	}
	catch (out_of_range o) {
		return false;
	}
	return true;
}

bool Utils::isPrime(const int a) {
	if (a <= 1)
		return false;

	int i;
	for (i = 2; i * i <= a; i++)
		if (a % i == 0)
			return false;
	return true;
}

int main(int argc, char *argv[]) {
	using namespace std;
	using namespace Utils;

	// if argc is 1, run dancer problem, else run tests
	if (argc == 1) {
		int menNum, womenNum, m, f;
		//> get men number
		while (true) {
			cout << "Please enter the number of gentlemans: " << flush;
			cin >> menNum;
			if (cin.eof() || cin.bad()) {
				continue;
			}
			else if (cin.fail()) {
				cout << "--> Input not recognized." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else if (!isPrime(menNum)) {
				cout << "--> This is not a prime number." << endl;
			}
			else
				break;
		}
		//> get women number
		while (true) {
			cout << "Please enter the number of laydies: " << flush;
			cin >> womenNum;
			if (cin.eof() || cin.bad()) {
				continue;
			}
			else if (cin.fail()) {
				cout << "--> Input not recognized." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else if (!isPrime(womenNum)) {
				cout << "--> This is not a prime number." << endl;
			}
			else if (womenNum == menNum) {
				cout << "--> The number of laydies must be unequal with the number of gentlemans." << endl;
			}
			else
				break;
		}
		//> get m
		while (true) {
			cout << "Please enter m (1 <= m <= number of gentlemans): " << flush;
			cin >> m;
			if (cin.eof() || cin.bad()) {
				continue;
			}
			else if (cin.fail()) {
				cout << "--> Input not recognized." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else if (m <= 0 || m > menNum) {
				cout << "--> m out of range" << endl;
			}
			else
				break;
		}
		//> get f
		while (true) {
			cout << "Please enter f (1 <= f <= number of ladies): " << flush;
			cin >> f;
			if (cin.eof() || cin.bad()) {
				continue;
			}
			else if (cin.fail()) {
				cout << "--> Input not recognized." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else if (f <= 0 || f > womenNum) {
				cout << "--> f out of range" << endl;
			}
			else
				break;
		}

		// create QUEUE
		QUEUE queueMen(2 * menNum + 1), queueWomen(2 * womenNum + 1);
		for (int i = 0; i < menNum; ++i)
			queueMen << i + 1;
		for (int i = 0; i < womenNum; ++i)
			queueWomen << i + 1;

		int currentMan, currentWoman, counter = 1;
		while (1) {
			queueMen >> currentMan;
			queueWomen >> currentWoman;
			if (currentMan == m && currentWoman == f) {
				cout << "==> m and f met at round " << counter << endl;
				break;
			}
			queueMen << currentMan;
			queueWomen << currentWoman;
			++counter;
		}
		return 0;
	}
	else {
		// arguments
		string arg;
		int number;

		// queue for test
		QUEUE *queue = nullptr;

		// file to write
		ofstream outFile;
		outFile.open("U201514898_6.TXT");

		auto coutBackup = cout.rdbuf();
		cout.rdbuf(outFile.rdbuf());

#define CHECK_IF_LAST_ARG if (i == argc - 1){ \
            cerr << "paramter not found after: " << arg << endl; \
            return 1; \
        }

		try {
			for (int i = 1; i < argc; ++i) {
				arg = string(argv[i]);
				if (arg == "-S" || arg == "-s") {
					CHECK_IF_LAST_ARG;

					arg = string(argv[++i]);
					if (!convertToInt(arg, number)) {
						cerr << "Error: cannot convert " << arg << " to int" << endl;
						return 1;
					}

					queue = new QUEUE(number);
					cout << "S  " << number;
				}
				else if (arg == "-I" || arg == "-i") {
					cout << "I";

					for (++i; i < argc; ++i) {
						arg = string(argv[i]);
						// until there's noting to covert
						if (!convertToInt(arg, number)) {
							break;
						}
						(*queue) << number;
					}
					if (i != argc)
						--i;

					if (int(*queue)) {
						cout << "  ";
						queue->print();
					}
				}
				else if (arg == "-O" || arg == "-o") {
					CHECK_IF_LAST_ARG

						cout << "O";
					arg = string(argv[++i]);
					if (!convertToInt(arg, number)) {
						cerr << "Error: cannot convert " << arg << " to int" << endl;
						return 1;
					}

					int garbage;
					for (int j = 0; j < number; ++j) {
						(*queue) >> garbage;
					}

					if (int(*queue)) {
						cout << "  ";
						queue->print();
					}

				}
				else if (arg == "-C" || arg == "-c") {
					QUEUE *newQueue = new QUEUE(*queue);
					queue = newQueue;

					cout << "C";
					if (int(*queue)) {
						cout << "  ";
						queue->print();
					}
				}
				else if (arg == "-A" || arg == "-a") {
					CHECK_IF_LAST_ARG

						arg = string(argv[++i]);
					if (!convertToInt(arg, number)) {
						cerr << "Error: cannot convert " << arg << " to int" << endl;
						return 1;
					}

					QUEUE *newQueue = new QUEUE(number);
					*newQueue = *queue;
					queue = newQueue;

					cout << "A";
					if (int(*queue)) {
						cout << "  ";
						queue->print();
					}

				}
				else if (arg == "-N" || arg == "-n") {
					cout << "N  " << int(*queue);

				}
				else if (arg == "-G" || arg == "-g") {
					CHECK_IF_LAST_ARG

						arg = string(argv[++i]);
					if (!convertToInt(arg, number)) {
						cerr << "Error: cannot convert " << arg << " to int" << endl;
						return 1;
					}

					cout << "G  " << (*queue)[number];

				}
				else {
					cerr << "Wrong parameter: " << arg << endl;
					return 1;
				}

				if (i != argc - 1)
					cout << "  ";
			}
		}
		catch (logic_error error) {
			cout << "  E" << endl;
			return 1;
		}
		cout.rdbuf(coutBackup);
		outFile.close();
		return 0;
	}
}