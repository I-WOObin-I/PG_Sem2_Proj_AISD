#include <iostream>

using namespace std;

struct Node {
    int key;
    Node *link;
};

struct List {
    Node* beg;
    Node* end;
    Node* act;
    Node* a_p;
};

Node* Xor(Node* prev, Node* next) {
    return reinterpret_cast<Node *>(reinterpret_cast<uintptr_t>(prev) ^ reinterpret_cast<uintptr_t>(next));
}

int Actual(List L) {
    return L->act->key;
}

void Next_print(List L) {
    L->act = Xor (L->act->link, L->a_p);
    cout<<L->act->key<<endl;
}

void Prev_print() {
    L->act = Xor (L->act->link, L->a_n);
    cout<<L->act->key<<endl;
}

Node* Insert(List L, Node* A_P, Node* Act, int key) {
    Node* P_P = Xor(A_P->link, Act);
    Node* A_N = Xor(Act->link, A_P);
    Node* N = new Node;
    N->key = key;
    N->link = Xor(A_P, Act);
    Act->link = Xor(N, A_N);
    A_P->link = Xor(N, P_P);
    return N;
}

void Add(List L, int key, int mode) {
    // mode 0 - add at the beginnig
    // mode 1 - add at the end
    // mode 2 - add before actual
    if      (mode == 0)
        L->beg = Insert(L, L->end, L->beg, key);
    else if (mode == 1)
        L->end = Insert(L, L->end, L->beg, key);
    else if (mode == 2)
        L->a_p = Insert(L, L->a_p, L->act, key);
}

Node* Rem(List L, Node* A_P, Node* Act, int key) {
    Node* A_N = Xor(Act->link, A_P);
    Node* N_N = Xor(A_N->link, Act);
    Node* P_P = Xor(A_P->link, Act);

}

void Del(List L, int key, int mode) {
    // mode 0 - del the beginnig
    // mode 1 - del the end
    // mode 2 - del the actual
    if      (mode == 0)
    else if (mode == 1)
    else if (mode == 2)
}

void Del_beg() {
    Node* tmp2 = Xor(L->beg->link, L->end);
    Node* tmp3 = Xor(L->end->link, L->beg);
    Node* tmp4 = Xor(L->beg, tmp2->link);
    delete L->beg;
    L->beg = tmp2;
    L->beg->link = Xor(L->end, tmp4);
    L->end->link = Xor(tmp2, tmp3);
    delete L->beg;
    L->beg = tmp2;
}

void Del_end() {
    Node* tmp2 = Xor(L->beg->link, L->end);
    Node* tmp3 = Xor(L->end->link, L->beg);
    Node* tmp5 = Xor(L->end, tmp3->link);
    L->beg
}

void Del_val() {

}

void Del_act() {

}

void Print_for(List L) {
    Node* tmp = L->beg;
    Node* tmp2 = L->end;
    for(;;) {
        cout<<tmp->key<<" ";
        if(tmp == L->end) { break; }

    }
}

void Print_back() {

}

int main() {









    return 0;
}
