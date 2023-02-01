#include <iostream>
#include <list>

using namespace std;

struct Node {
	int* keys;
	Node** kids;
	int n = 0, k = 0;
	bool is_leaf = true;
	Node(int t) {
		keys = new int[2 * t - 1];
		kids = new Node* [2 * t];
		for (int i = 0; i < 2 * t; i++) { this->kids[i] = NULL; }
	}
	~Node() {
		delete[] keys;
		if(is_leaf == false) { delete[] kids; }
	}
};
struct B_tree {
	Node* root = NULL;
	int T = 0;
	int minKeys = 0, maxKeys = 0;
	B_tree(int t) {
		this->T = t;
		this->minKeys = t - 1;
		this->maxKeys = 2 * t - 1;
	}
};

void pn(Node* node) {
	//for (int i = 0; i < node->n; i++) { cout << node->keys[i] << " "; }
	//cout << endl;
}

void Insert_V(Node* node, int key) {
	int i;
	for (i = 0; i < node->n; i++) {
		if (node->keys[i] > key) { break; }
	}
	for (int j = node->n - 1; j >= i; j--) {
		node->keys[j + 1] = node->keys[j];
	}
	node->keys[i] = key;
	node->n++;
}
void Insert_K(Node* node, Node* kid) {
	if (kid == NULL) { return; }
	int i;
	int key = kid->keys[0];
	for (i = 0; i < node->n; i++) {
		if (node->keys[i] > key) { break; }
		if (i == node->n - 1) { i++; break; }
	}
	for (int j = node->n; j >= i; j--) {
		node->kids[j + 1] = node->kids[j];
	}
	node->kids[i] = kid;
	node->k++;
}

Node* Split(B_tree* btree, Node* parent, Node* node) {
	//cout << "Split" << endl;
	Node* tmp = new Node(btree->T);
	int middle = btree->T - 1;
	for (int i = btree->maxKeys - 1; i > middle; i--) {
		Insert_V(tmp, node->keys[i]);
		Insert_K(tmp, node->kids[i]);
		node->kids[i] = NULL;
	}
	Insert_K(tmp, node->kids[node->n]);
	node->kids[node->n] = NULL;
	pn(tmp);
	if (node == btree->root) {
		Node* newroot = new Node(btree->T);
		Insert_V(newroot, node->keys[middle]);
		newroot->kids[0] = node;
		newroot->kids[1] = tmp;
		newroot->is_leaf = false;
		btree->root = newroot;
		pn(btree->root);
	}
	else {
		Insert_V(parent, node->keys[middle]);
		Insert_K(parent, tmp);
		pn(parent);
	}
	node->n = middle;
	pn(node);
	if (node->is_leaf == false) { tmp->is_leaf = false; }
	return tmp;
}
void Add_V(B_tree* btree, Node* parent, Node* node, int key) {
	//cout << "ADD" << endl;
	if (node->n >= btree->maxKeys) {
		int tmp_v = node->keys[btree->T - 1];
		Node* tmp = Split(btree, parent, node);
		if(key>tmp_v) { Add_V(btree, parent, tmp, key); }
		else { Add_V(btree, parent, node, key); }
		return;
	}
	if (node->is_leaf == true) {
		Insert_V(node, key);
		pn(node);
	}
	else {
		int i;
		for (i = 0; i < node->n; i++) {
			if (node->keys[i] > key) { break; }
			if (i == node->n - 1) { i++; break; }
		}
		Add_V(btree, node, node->kids[i], key);
	}
}

void Find_V(B_tree* btree, Node* node, int key) {
	int i;
	for (i = 0; i < node->n; i++) {
		if (node->keys[i] == key) { cout << key << " +" << endl; return; }
		if (node->keys[i] > key) { break; }
		if (i >= node->n - 1) { i++; break; }
	}
	if (node->kids[i] == NULL) { cout << key << " -" << endl; }
	else { Find_V(btree, node->kids[i], key); }
}
void Print(B_tree* btree, Node* node) {
	for (int i = 0; i < node->n; i++) {
		if (node->kids[i] != NULL) { Print(btree, node->kids[i]); }
		cout << node->keys[i]<<" ";
	}
	if (node->kids[node->n] != NULL) { Print(btree, node->kids[node->n]); }
}

Node* Load(B_tree* btree) {
	//cout << "load" << endl;
	Node* node = new Node(btree->T);
	int key;
	while (true) {
		cin >> key;
		if (cin.fail() == true) {
			cin.clear();
			if (cin.peek() == '(') { cin.ignore(); Insert_K(node, Load(btree)); }
			if (cin.peek() == ')') { cin.ignore(); return node; }
		}
		else {
			Insert_V(node, key);
		}
	}
}
void Save(B_tree* btree, Node* node) {
	cout << "( ";
	for (int i = 0; i < node->n; i++) {
		if (node->kids[i] != NULL) { Save(btree, node->kids[i]); }
		cout << node->keys[i] << " ";
	}
	if (node->kids[node->n] != NULL) { Save(btree, node->kids[node->n]); }
	cout << ") ";
}

void Write(B_tree* btree, Node* node, int gap) {
	cout << endl;
	for (int i = 0; i < gap; i++) { cout << "\t"; }
	for (int i = 0; i < node->n; i++) {
		cout << node->keys[i] << " ";
	}
	for (int i = 0; i < node->n; i++) {
		if (node->kids[i] != NULL) { Write(btree, node->kids[i], gap+1); }
	}
	if (node->kids[node->n] != NULL) { Write(btree, node->kids[node->n], gap+1); }
}

void delete_tree(B_tree* btree, Node* node) {
	if (node->is_leaf == false) {
		for (int i = 0; i < node->k; i++) {
			if (node->kids[i] != NULL) { delete_tree(btree, node->kids[i]); }
		}
	}
	delete node;
}

int main() {
	B_tree* btree = new B_tree(3);
	char inp;
	int key;
	while (!cin.eof()) {
		cin >> inp;
		switch (inp) {
		case 'I':
			cin >> key;
			delete btree;
			btree = new B_tree(key);
			break;
		case 'A':
			cin >> key;
			if (btree->root != NULL) { Add_V(btree, btree->root, btree->root, key); }
			else {
				btree->root = new Node(btree->T);
				Insert_V(btree->root, key);
			}
			break;
		case '?':
			cin >> key;
			if (btree->root == NULL) { cout << key << " -" << endl; }
			else { Find_V(btree, btree->root, key); }
			break;
		case 'P':
			if (btree->root == NULL) { cout << endl; }
			else { Print(btree, btree->root); }
			cout << endl;
			break;
		case 'L':
			cin >> key;
			btree->T = key;
			cin >> inp;
			btree->root = Load(btree);
			break;
		case 'S':
			cout << btree->T << endl;
			Save(btree, btree->root);
			cout << endl;
			break;
		case 'W':
			Write(btree, btree->root, 0);
			cout << endl;
			break;
		default: break;
		}
	}


	delete_tree(btree, btree->root);
	return 0;
}