#include<cstdio>
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include "U201714626_3.h"
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
	* ((int **)&(elems)) = s.elems;
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
	else{
		for (int i = pos-1; i >= 0; --i) {
			out << elems[i] << "  ";
		}
		out << flush;
	}
}
STACK::~STACK() {
	if (elems!=0) {
		delete[]elems;
		*(int **)(&elems) = 0;
	}
}

/*
* 队列函数定义
*/
QUEUE::QUEUE(int m) :s1(m), s2(m) {};
QUEUE::QUEUE(const QUEUE&q) :s1(q.s1), s2(q.s2) {};
QUEUE::QUEUE(QUEUE&&q) : s1(q.s1), s2(q.s2) {};
QUEUE::operator int() const {
	return s1.operator int() + s2.operator int();
}
int QUEUE::full() const {
	if (s1.operator int() == s1.size() && s2.operator int() > 0) {
		return 1;
	}
	return 0;
}
int QUEUE::operator[ ] (int x) const {
	if (x >= s2.operator int()) {
		return s1.operator[](s2.operator int() - (x - s1.operator int()) - 1);
	}
	return s2.operator[](x);
}
QUEUE& QUEUE::operator<<(int e) {
	if (s1.operator int() == s1.size() && s2.operator int() == 0) {
		int ele;
		while (s1.operator int() > 0) {
			s1.operator>>(ele);
			s2.operator<<(ele);
		}
	}
	s1.operator<<(e);
	return (*this);
}
QUEUE& QUEUE::operator>>(int &e) {
	if (s2.operator int() == 0) {
		int ele;
		while (s1.operator int() > 0) {
			s1.operator>>(ele);
			s2.operator<<(ele);
		}
	}
	s2.operator>>(e);
	return (*this);
}
QUEUE&  QUEUE::operator=(const QUEUE&q) {
	s1.operator=(q.s1);
	s2.operator=(q.s2);
	return (*this);
}
QUEUE& QUEUE::operator=(QUEUE&&q) {
	s1.operator=(q.s1);
	s2.operator=(q.s2);
	q.~QUEUE();
	return (*this);
}
void QUEUE::print() const{
	k = -1;
	s2.print();
	k = 1;
	s1.print();
}
QUEUE::~QUEUE() {
	s1.~STACK();
	s2.~STACK();
}

int main(int argc, char *argv[]) {
	string ID(argv[0]);
	out.open(ID + ".txt");
	QUEUE* p = NULL;
	bool is_valid = true;
	for (int i = 1; i<argc; i++) {
		string commond(argv[i]);
		if (commond == "-S") {
			int max_size = atoi(argv[++i]);
			p = new QUEUE(max_size);
			out << "S  " << max_size << "  ";
		}
		else if (commond == "-I") {
			out << "I  ";
			while (i < argc - 1 && is_valid) {		// 这里-1不能少 
				if (isdigit(argv[i + 1][0])) {
					int num = atoi(argv[++i]);
					if (p->full()) {
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
			QUEUE *t = new QUEUE(*p);
			p->~QUEUE();
			p = t;
			p->print();
		}
		else if (commond == "-A") {
			out << "A  ";
			QUEUE *t;
			int max_size = atoi(argv[++i]);
			t = new QUEUE(max_size);
			t = p;
			if (t == nullptr) is_valid = false;
			if (!is_valid) {
				out << "E";
				break;
			}
			QUEUE *&tt = t;
			p = tt;
			p->print();

		}
		else if (commond == "-N") {
			out << "N  " << p->operator int() << "  ";
		}
		else if (commond == "-G") {
			out << "G  ";
			int pos = atoi(argv[++i]);
			if (p->full()) {
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