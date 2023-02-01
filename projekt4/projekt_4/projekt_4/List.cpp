#include "List.h"

List::List() {}
void List::Add_head(int key) {
	Node* tmp = new Node;
	tmp->key = key;
	if (this->head == NULL) { 
		this->head = tmp;
		this->tail = tmp;
		return;
	}
	else if()
	tmp->next = this->head;
	tmp->prev = this->tail;
	this->head = tmp;
}
void List::Add_tail(int key) {
	Node* tmp = new Node;
	tmp->key = key;
	tmp->next = this->head;
	tmp->prev = this->tail;
	this->tail = tmp;
}
void List::Rem_head() {
	Node* tmp = this->head;
	this->head = this->head->next;
	this->tail->next = this->head;
	this->head->prev = this->tail;
	delete tmp;
}
void List::Rem_tail() {
	Node* tmp = this->tail;
	this->tail = this->tail->prev;
	this->tail->next = this->head;
	this->head->prev = this->tail;
	delete tmp;
}

void List::Add_after(int i, int key) {
	Node* tmp = this->head;
	for (int j = 0; j < i; j++) { tmp = tmp->next; }
	Node* tmp2 = new Node;
	tmp2->key = key;
	tmp2->next = tmp->next;
	tmp2->prev = tmp;
	tmp->next->prev = tmp2;
	tmp->next = tmp2;
}
void List::Rem_ind(int i) {
	Node* tmp = this->head;
	for (int j = 0; j < i; j++) { tmp = tmp->next; }
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	delete tmp;
}

int List::get_head() { return this->head->key; }
int List::get_tail() { return this->tail->key; }
int List::get_ind(int i) {
	Node* tmp = this->head;
	for (int j = 0; j < i; j++) { tmp = tmp->next; }
	return tmp->key;
}