#pragma once
#include <iostream>

using namespace std;

struct Node {
	int key = NULL;
	Node* next = NULL;
	Node* prev = NULL;
	Node() {}
	Node(int key) : key(key) {}
	Node(int key, Node* prev, Node* next) : key(key), prev(prev), next(next) {}
};
struct Qlist {
	Node* head = NULL;
	Node* tail = NULL;
	Node* frst = NULL;
	Node* last = NULL;
};

void add_beg(Qlist* L, int key) {
	if (L->head == NULL) {				// 0 //
		L->head = new Node(key);
		L->tail = L->head;
		L->head->next = L->head; L->head->prev = L->head;
	}
	else {
		L->head = new Node(key, L->tail, L->head);
		L->head->next->prev = L->head;
		L->head->prev->next = L->head;
	}
}
void add_end(Qlist* L, int key) {
	if (L->head == NULL) {				// 0 //
		L->head = new Node(key);
		L->tail = L->head;
		L->head->next = L->head; L->head->prev = L->head;
	}
	else {
		L->tail = new Node(key, L->tail, L->head);
		L->tail->next->prev = L->tail;
		L->tail->prev->next = L->tail;
	}
}
void del_beg(Qlist* L) {
	if (L->head == NULL) { return; }
	else if (L->head == L->tail) {		// 1 //
		delete L->head;
		L->head = NULL; L->tail = NULL; L->frst = NULL; L->last = NULL;
	}
	else {
		L->tail->next = L->head->next;
		L->head->next->prev = L->tail;
		Node* tmp = L->head->next;
		if (L->head == L->last) { L->last = L->last->next; }
		if (L->head == L->frst) { L->frst = L->frst->prev; }
		delete L->head;
		L->head = tmp;
	}
}
void del_end(Qlist* L) {
	if (L->head == NULL) { return; }
	else if (L->head == L->tail) {		// 1 //
		delete L->head;
		L->head = NULL; L->tail = NULL; L->frst = NULL; L->last = NULL;
	}
	else {
		L->head->prev = L->tail->prev;
		L->tail->prev->next = L->head;
		Node* tmp = L->tail->prev;
		if (L->tail == L->last) { L->last = L->last->next; }
		if (L->tail == L->frst) { L->frst = L->frst->prev; }
		delete L->tail;
		L->tail = tmp;
	}
}
void print_f(Qlist* L) {
	if (L->head == NULL) { cout << "NULL" << endl; }
	else {
		Node* tmp = L->head;
		for (;;) {
			if (tmp == L->tail) { cout << tmp->key << endl; break; }
			cout << tmp->key << " ";
			tmp = tmp->next;
		}
	}
}
void print_b(Qlist* L) {
	if (L->head == NULL) { cout << "NULL" << endl; }
	else {
		Node* tmp = L->tail;
		for (;;) {
			if (tmp == L->head) { cout << tmp->key << endl; break; }
			cout << tmp->key << " ";
			tmp = tmp->prev;
		}
	}
}
void l_size(Qlist* L) {
	if (L->head == NULL) { cout << "0" << endl; }
	else {
		Node* tmp = L->head;
		int c = 0;
		for (;;) {
			if (tmp == L->tail) { cout << c + 1 << endl; break; }
			c++;
			tmp = tmp->next;
		}
	}
}

void push(Qlist* L, int key) {
	if (L->head == NULL) {				// 0 //
		L->head = new Node(key);
		L->tail = L->head;
		L->frst = L->head;
		L->last = L->head;
		L->head->next = L->head; L->head->prev = L->head;
	}
	else if (L->frst == NULL) {
		L->frst = L->tail;
		L->last = L->tail;
		L->frst->key = key;
	}
	else {
		if (L->last->prev == L->frst) {
			Node* tmp = new Node(key, L->frst, L->last);
			L->frst->next = tmp;
			L->last->prev = tmp;
			if (L->last == L->head) { L->head = tmp; }
			L->last = tmp;

		}
		else {
			L->last = L->last->prev;
			L->last->key = key;
		}
	}
}
void pop(Qlist* L) {
	if (L->frst == NULL) { cout << "NULL" << endl; }
	else if (L->frst == L->last) {
		cout << L->frst->key << endl;
		L->frst = NULL;
		L->last = NULL;
	}
	else {
		cout << L->frst->key << endl;
		L->frst = L->frst->prev;
	}
}
void print_q(Qlist* L) {
	if (L->frst == NULL) { cout << "NULL" << endl; }
	else {
		Node* tmp = L->frst;
		for (;;) {
			if (tmp == L->last) { cout << tmp->key << endl; break; }
			cout << tmp->key << " ";
			tmp = tmp->prev;
		}
	}
}
void q_size(Qlist* L) {
	if (L->frst == NULL) { cout << "0" << endl; }
	else {
		Node* tmp = L->frst;
		int c = 0;
		for (;;) {
			if (tmp == L->last) { cout << c + 1 << endl; break; }
			c++;
			tmp = tmp->prev;
		}
	}
}
void gar_s(Qlist* L) {
	if (L->head == NULL) { return; }
	else {
		if (L->frst == NULL) {
			Node* tmp = L->tail;
			for (;;) {
				if (tmp == L->head) { tmp->key = 0; break; }
				tmp->key = 0;
				tmp = tmp->prev;
			}
		}
		else {
			Node* tmp = L->last->prev;
			for (;;) {
				if (tmp == L->frst) { break; }
				tmp->key = 0;
				tmp = tmp->prev;
			}
		}
	}
}
void gar_h(Qlist* L) {
	if (L->head == NULL) { return; }
	else {
		if (L->frst == NULL) {
			Node* tmp = L->tail;
			for (;;) {
				if (tmp == L->head) { del_end(L); break; }
				tmp = tmp->prev;
				del_end(L);
			}
		}
		else {
			Node* tmp = L->last->prev;
			Node* tmp2;
			for (;;) {
				if (tmp == L->frst) { break; }
				tmp->next->prev = tmp->prev;
				tmp->prev->next = tmp->next;
				tmp2 = tmp;
				tmp = tmp->prev;
				delete tmp2;
			}
		}
	}
}

void Print_stats(Qlist* L) {
	cout << "L.beg: " << L->head->key << " ";
	cout << "L.a_p: " << L->tail->key << " ";
	cout << "L.act: " << L->frst->key << " ";
	cout << "L.end: " << L->last->key << " ";
	cout << endl;
}
bool Comp(char inp[], const char str[]) {
	bool out = true;
	for (int i = 0;; i++) {
		if (str[i] == '*') { break; }
		if (inp[i] != str[i]) { out = false; break; }
	}
	return out;
}
int Menu(char inp[]) {
	if (Comp(inp, "ADD_BEG*")) { return 1; }
	else if (Comp(inp, "ADD_END*")) { return 2; }
	else if (Comp(inp, "DEL_BEG*")) { return 3; }
	else if (Comp(inp, "DEL_END*")) { return 4; }
	else if (Comp(inp, "PRINT_FORWARD*")) { return 5; }
	else if (Comp(inp, "PRINT_BACKWARD*")) { return 6; }
	else if (Comp(inp, "PUSH*")) { return 7; }
	else if (Comp(inp, "POP*")) { return 8; }
	else if (Comp(inp, "PRINT_QUEUE*")) { return 9; }
	else if (Comp(inp, "COUNT*")) { return 10; }
	else if (Comp(inp, "GARBAGE_SOFT*")) { return 11; }
	else if (Comp(inp, "GARBAGE_HARD*")) { return 12; }
	else if (Comp(inp, "SIZE*")) { return 13; }
	else if (Comp(inp, "print-stats*")) { return 14; }
	else { return 0; }
}

int main() {
	Qlist* L = new Qlist;
	char inp[14];
	int menu, key;
	while (!cin.eof()) {
		cin >> inp;
		menu = Menu(inp);
		switch (menu) {
		case 1:
			cin >> key;
			add_beg(L, key);
			break;
		case 2:
			cin >> key;
			add_end(L, key);
			break;
		case 3:
			del_beg(L);
			break;
		case 4:
			del_end(L);
			break;
		case 5:
			print_f(L);
			break;
		case 6:
			print_b(L);
			break;
		case 7:
			cin >> key;
			push(L, key);
			break;
		case 8:
			pop(L);
			break;
		case 9:
			print_q(L);
			break;
		case 10:
			q_size(L);
			break;
		case 11:
			gar_s(L);
			break;
		case 12:
			gar_h(L);
			break;
		case 13:
			l_size(L);
			break;
		case 14:
			Print_stats(L);
			break;
		case 0:
			break;
		}
	}


	return 0;
}