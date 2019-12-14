#include "U201714626_2.h"
#include<cstdio>
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
using namespace std;
ofstream out;

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
	for (int i = 0; i < pos; ++i) {
		out << elems[i] << "  ";
	}
	out << flush;
}
STACK::~STACK() {
	if (elems != 0) {
		delete[]elems;
		*(int **)(&elems) = 0;
	}
}


int main(int argc, char *argv[]) {
	string ID(argv[0]);
	out.open(ID + ".txt");
	STACK* p = new STACK(1);
	bool is_valid = true;
	for (int i = 1; i < argc; i++) {
		string commond(argv[i]);
		if (commond == "-S") {
			int max_size = atoi(argv[++i]);
			p = new STACK(max_size);
			out << "S  " << p->size() << "  ";
		}
		else if (commond == "-I") {
			out << "I  ";
			while (i < argc - 1 && is_valid) {		// 这里-1不能少 
				if (isdigit(argv[i + 1][0])) {
					int num = atoi(argv[++i]);
					if (p->operator int() == p->size()) {
						is_valid = false;
						break;
					}
					*p = p->operator<<(num);
					if (!p) is_valid = false;
				}
				else break;
			}
			if (!is_valid) {
				out << "E";
				break;
			}
			p->print();
		}
		else if (commond == "-O") {
			out << "O  ";
			int out_num = atoi(argv[++i]);
			while (out_num-- > 0 && is_valid) {
				int temp;
				if (p->operator int() == 0) {
					is_valid = false;
					break;
				}
				*p = p->operator>>(temp);		// 表示不保存出栈元素内容 
			}
			if (!is_valid) {
				out << "E";
				break;
			}
			p->print();
		}
		else if (commond == "-C") {
			out << "C  ";
			STACK *t = new STACK(*p);
			p->~STACK();
			p = t;
			p->print();
		}
		else if (commond == "-A") {
			out << "A  ";
			STACK *t;
			int max_size = atoi(argv[++i]);
			t = new STACK(max_size);
			t = new STACK(*p);
			if (!t) is_valid = false;
			p->~STACK();
			if (!is_valid) {
				out << "E";
				break;
			}
			p = t;
			p->print();
		}
		else if (commond == "-N") {
			out << "N  " << p->operator int() << "  ";
		}
		else if (commond == "-G") {
			out << "G  ";
			int pos = atoi(argv[++i]);
			if (pos >= p->size()) {
				out << "E";
				is_valid = false;
				break;
			}
			out << p->operator[](pos) << "  ";
		}
	}
	out.close();
	return 0;
}
