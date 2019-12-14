#include"U201714626_1.h"
#include<cstdio>
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
using namespace std;
ofstream out;

int main(int argc, char *argv[]) {
	string ID(argv[0]);
	out.open(ID + ".txt");
	STACK *p = new STACK;
	bool is_valid = true;
	for (int i = 1; i<argc; i++) {
		string commond(argv[i]);
		if (commond == "-S") {
			int max_size = atoi(argv[++i]);
			initSTACK(p, max_size);
			out << "S  " << size(p) << "  ";
		}
		else if (commond == "-I") {
			out << "I  ";
			while (i < argc - 1 && is_valid) {		// 这里-1不能少 
				if (isdigit(argv[i + 1][0])) {
					int num = atoi(argv[++i]);
					p = push(p, num);
					if (!p) is_valid = false;
				}
				else break;
			}
			if (!is_valid) {
				out << "E";
				break;
			}
			print(p);
		}
		else if (commond == "-O") {
			out << "O  ";
			int out_num = atoi(argv[++i]);
			while (out_num-- > 0 && is_valid) {
				int temp;
				p = pop(p, temp);		// 表示不保存出栈元素内容 
				if (!p) is_valid = false;
			}
			if (!is_valid) {
				out << "E";
				break;
			}
			print(p);
		}
		else if (commond == "-C") {
			out << "C  ";
			STACK *t = new STACK;
			initSTACK(t, *p);
			destroySTACK(p);
			p = t;
			print(p);
		}
		else if (commond == "-A") {
			out << "A  ";
			STACK *t = new STACK;
			int max_size = atoi(argv[++i]);
			initSTACK(t, max_size);
			t = assign(t, *p);
			if (!t) is_valid = false;
			destroySTACK(p);
			if (!is_valid) {
				out << "E";
				break;
			}
			p = t;
			print(p);
		}
		else if (commond == "-N") {
			out << "N  " << howMany(p) << "  ";
		}
		else if (commond == "-G") {
			out << "G  ";
			int pos = atoi(argv[++i]);
			if (pos >= p->max) {
				out << "E";
				is_valid = false;
				break;
			}
			out << getelem(p, pos) << "  ";
		}
	}
	out.close();
	return 0;
}

void initSTACK(STACK *const p, int m) {
	p->max = m;
	p->elems = (int *)malloc(m * sizeof(int));
	p->pos = 0;
	return;
}

void initSTACK(STACK *const p, const STACK&s) {
	initSTACK(p, s.max);
	for ((p->pos) = 0; (p->pos) < s.pos; (p->pos)++) {
		p->elems[p->pos] = s.elems[p->pos];
	}
	return;
}

int  size(const STACK *const p) {
	return p->max;
}

int  howMany(const STACK *const p) {
	return p->pos;
}

int  getelem(const STACK *const p, int x) {
	return (p->elems)[x];
}

STACK *const push(STACK *const p, int e) {
	if (p->pos < p->max) {
		(p->elems)[(p->pos) ++] = e;
		return p;
	}
	else {
		destroySTACK(p);
		return nullptr;
	}
}

STACK *const pop(STACK *const p, int &e)
{
	if (p->pos == 0) {
		destroySTACK(p);
		return nullptr;
	}
	else {
		p->pos--;
		e = (p->elems)[(p->pos)];
		return p;
	}
}

STACK *const assign(STACK*const p, const STACK&s) {
	initSTACK(p, s);
	return p;
}

void print(const STACK*const p)
{
	for (int i = 0; i<p->pos; i++)
		out << (p->elems)[i] << "  ";
	return;
}
void destroySTACK(STACK*const p)
{
	delete[] p->elems;
	delete p;
	return;
}