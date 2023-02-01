#pragma once
#include <iostream>

using namespace std;

class List {
private:
	struct Node {
		int key = 0;
		Node* prev = NULL;
		Node* next = NULL;
	};
	
	int n = 0;
	Node* head = NULL;
	Node* tail = NULL;

public:
	List() {};
	void Add_head(int key) {};
	void Add_tail(int key) {};
	void Rem_head() {};
	void Rem_tail() {};

	void Add_after(int i, int key) {};
	void Rem_ind(int i) {};

	int get_head() {};
	int get_tail() {};
	int get_ind(int i) {};
};