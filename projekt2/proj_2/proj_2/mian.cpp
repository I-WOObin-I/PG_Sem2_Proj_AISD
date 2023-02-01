#include <iostream> 

using namespace std;

struct Node {
    int key = NULL;
    Node* link = NULL;
};

struct List {
    Node* beg = NULL;
    Node* end = NULL;
    Node* act = NULL;
    Node* a_p = NULL;
};

Node* Xor(Node* prev, Node* next) {
    return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(prev) ^ reinterpret_cast<uintptr_t>(next));
}

void Actual(List* L) {
    //cout << "L.act: " << L->act->key << endl;
    if (L->act == NULL) { cout << "NULL" << endl; return; }
    cout << L->act->key << endl;
}
void Next_print(List* L) {
    if (L->act == NULL) { cout << "NULL" << endl; return; } // 0 //
    else if (L->act == L->a_p) { cout << L->act->key << endl; return; } // 1 //
    else if (L->act->link == L->a_p) { // 2 //
        Node* tmp = L->act;
        L->act = L->a_p;
        L->a_p = tmp;
        cout << L->act->key << endl;
        return;
    }
    Node* A_N = Xor(L->act->link, L->a_p);
    L->a_p = L->act;
    L->act = A_N;
    cout << L->act->key << endl;
}
void Prev_print(List* L) {
    if (L->act == NULL) { cout << "NULL" << endl; return; }
    else if (L->act == L->a_p) { cout << L->act->key << endl; return; }
    else if (L->act->link == L->a_p) {
        Node* tmp = L->act;
        L->act = L->a_p;
        L->a_p = tmp;
        cout << L->act->key << endl;
        return;
    }
    Node* P_P = Xor(L->a_p->link, L->act);
    L->act = L->a_p;
    L->a_p = P_P;
    cout << L->act->key << endl;
}

void Add_beg(List* L, int key) {
    if (L->beg == NULL) {               // PUSTA LISTA //
        Node* N = new Node;
        N->key = key;
        L->beg = N;
        L->a_p = N;
        L->act = N;
        L->end = N;
    }
    else if (L->beg == L->end) {        // LISTA 1 ELEM //
        Node* N = new Node;
        N->key = key;
        N->link = L->end;
        L->end->link = N;
        L->beg = N;
        L->a_p = N;
    }
    else {
        Node* B_N = Xor(L->beg->link, L->end);
        Node* E_P = Xor(L->end->link, L->beg);
        if (L->beg->link == L->end) { B_N = L->end; E_P = L->beg; } // LISTA 2 ELEM //
        Node* N = new Node;
        N->key = key;
        N->link = Xor(L->end, L->beg);
        L->beg->link = Xor(N, B_N);
        L->end->link = Xor(N, E_P);
        if (L->beg == L->act) { L->a_p = N; }
        L->beg = N;
    }
}
void Add_end(List* L, int key) {
    if (L->beg == NULL) {           // LISTA PUSTA //
        Node* N = new Node;
        N->key = key;
        L->beg = N;
        L->a_p = N;
        L->act = N;
        L->end = N;
    }
    else if (L->beg == L->end) {    // LISTA 1 ELEM //
        Node* N = new Node;
        N->key = key;
        N->link = L->beg;
        L->beg->link = N;
        L->end = N;
        L->a_p = N;
    }
    else {
        Node* B_N = Xor(L->beg->link, L->end);
        Node* E_P = Xor(L->end->link, L->beg);
        if (L->beg->link == L->end) { B_N = L->end; E_P = L->beg; } // LISTA 2 ELEM //
        Node* N = new Node;
        N->key = key;
        N->link = Xor(L->end, L->beg);
        L->beg->link = Xor(N, B_N);
        L->end->link = Xor(N, E_P);
        if (L->end == L->a_p) { L->a_p = N; }
        L->end = N;
    }
}
void Add_act(List* L, int key) {
    if (L->beg == NULL) {           // LISTA PUSTA //
        Node* N = new Node;
        N->key = key;
        L->beg = N;
        L->a_p = N;
        L->act = N;
        L->end = N;
    }
    else if (L->beg == L->end) {    // LISTA 1 ELEM //
        Node* N = new Node;
        N->key = key;
        N->link = L->beg;
        L->beg->link = N;
        L->end = N;
        L->a_p = N;
    }
    else {
        Node* A_N = Xor(L->act->link, L->a_p);
        Node* P_P = Xor(L->a_p->link, L->act);
        if (L->beg->link == L->end) { A_N = L->a_p; P_P = L->act; } // LISTA 2 ELEM //
        Node* N = new Node;
        N->key = key;
        N->link = Xor(L->a_p, L->act);
        L->act->link = Xor(N, A_N);
        L->a_p->link = Xor(N, P_P);
        if (L->act == L->beg) { L->beg = N; }
        L->a_p = N;
    }
}

void Del_beg(List* L) {
    if (L->beg == NULL) { return; } // 0 //
    else if (L->beg == L->end) { delete L->beg; L->beg = NULL; L->a_p = NULL; L->act = NULL; L->end = NULL; return; } // 1 //
    else if (L->beg->link == L->end) { delete L->beg; L->beg = L->end; L->a_p = L->end; L->act = L->end; return; } // 2 //
    else {
        Node* B_N = Xor(L->beg->link, L->end);
        if (Xor(B_N->link, L->beg) == L->end) {     // LISTA 3 ELEM //
            if      (L->beg == L->act)  { L->act = L->end; L->a_p = B_N; }
            else if (L->beg == L->a_p)  { L->a_p = L->end;  }
            B_N->link = L->end;
            L->end->link = B_N;
            delete L->beg;
            L->beg = B_N;
        }
        else {
            Node* N_N = Xor(B_N->link, L->beg);
            Node* E_P = Xor(L->end->link, L->beg);
            if      (L->beg == L->act) { L->act = L->end; L->a_p = E_P; }
            else if (L->beg == L->a_p) { L->a_p = L->end; }
            L->end->link = Xor(E_P, B_N);
            B_N->link = Xor(L->end, N_N);
            delete L->beg;
            L->beg = B_N;
        }
    }
}
void Del_end(List* L) {
    if (L->beg == NULL) { return; } // 0 //
    else if (L->beg == L->end) { delete L->beg; L->beg = NULL; L->a_p = NULL; L->act = NULL; L->end = NULL; return; } // 1 //
    else if (L->beg->link == L->end) { delete L->end; L->end = L->beg; L->a_p = L->beg; L->act = L->beg; return; }      // 2 //
    else {
        Node* E_P = Xor(L->end->link, L->beg);
        if (Xor(E_P->link, L->end) == L->beg) {     // 3 //
            if      (L->end == L->act) { L->act = E_P; L->a_p = L->beg; }
            else if (L->end == L->a_p) { L->a_p = E_P; }
            E_P->link = L->beg;
            L->beg->link = E_P;
            delete L->end;
            L->end = E_P;
        }
        else {
            Node* P_P = Xor(E_P->link, L->end);
            Node* B_N = Xor(L->beg->link, L->end);
            if      (L->end == L->act) { L->act = E_P; L->a_p = P_P; }
            else if (L->end == L->a_p) { L->a_p = E_P; }
            E_P->link = Xor(P_P, L->beg);
            L->beg->link = Xor(E_P, B_N);
            delete L->end;
            L->end = E_P;
        }
    }
}
void Del_act(List* L) {
    if (L->beg == NULL) { return; } // 0 //
    else if (L->beg == L->end)       { delete L->beg; L->beg = NULL; L->a_p = NULL; L->act = NULL; L->end = NULL; return; } // 1 //
    else if (L->beg->link == L->end) { delete L->act; L->act = L->a_p; L->beg = L->a_p; L->end = L->a_p;          return; } // 2 //
    else {
        Node* A_N = Xor(L->act->link, L->a_p);
        if      (L->act == L->beg) { L->beg = A_N;      }
        else if (L->act == L->end) { L->end = L->a_p;   }
        if (Xor(A_N->link, L->act) == L->a_p) { // 3 //
            L->a_p->link = A_N;
            A_N->link = L->a_p;
            delete L->act;
            L->act = L->a_p;
            L->a_p = A_N;
        }
        else {
            Node* N_N = Xor(A_N->link, L->act);
            Node* P_P = Xor(L->a_p->link, L->act);
            L->a_p->link = Xor(P_P, A_N);
            A_N->link = Xor(N_N, L->a_p);
            delete L->act;
            L->act = L->a_p;
            L->a_p = P_P;
        }
    }
}
void Del_val(List* L, int key) {
    Node* P_P;
    Node* A_P = L->end;
    Node* ACT = L->beg;
    Node* A_N;
    Node* N_N;
    bool is_end = false;
    for(;;)  {
        if (L->beg == NULL) { return; } // 0 //
        else if (L->beg == L->end) {    // 1 //
            if (L->beg->key == key) { delete L->beg; L->beg = NULL; L->a_p = NULL; L->act = NULL; L->end = NULL; return; }
            else { return; }
        }
        else if (L->beg->link == L->end) { // 2 //
            if (L->beg->key == key && L->end->key == key) { delete L->beg; delete L->end; L->beg = NULL; L->a_p = NULL; L->act = NULL; L->end = NULL; }
            else if (L->beg->key == key) { delete L->beg; L->beg = L->end; L->a_p = L->end; L->act = L->end; }
            else if (L->end->key == key) { delete L->end; L->end = L->beg; L->a_p = L->beg; L->act = L->beg; }
            return;
        }
        if (is_end) { break; }
        if (ACT == L->end) { is_end = true; }
        //cout << "DEL: " << ACT->key << endl;
        if (ACT->key == key) {
            A_N = Xor(ACT->link, A_P);
            if (Xor(A_N->link, ACT) == A_P) { // 3 //
                A_P->link = A_N;
                A_N->link = A_P;
                if      (ACT == L->act) { L->act = A_P; L->a_p = A_N; }
                else if (ACT == L->a_p) { L->a_p = A_P; }
                if      (ACT == L->beg) { L->beg = A_N; }
                else if (ACT == L->end) { L->end = A_P; }
                delete ACT;
                continue;
            }
            else {
                N_N = Xor(A_N->link, ACT);
                P_P = Xor(A_P->link, ACT);
                A_P->link = Xor(P_P, A_N);
                A_N->link = Xor(A_P, N_N);
                if      (ACT == L->act) { L->act = A_P; L->a_p = P_P; }
                else if (ACT == L->a_p) { L->a_p = A_P; }
                if      (ACT == L->beg) { L->beg = A_N; }
                else if (ACT == L->end) { L->end = A_P; }
                delete ACT;
                ACT = A_N;
                continue;
            }

        }
        else {
            A_N = Xor(ACT->link, A_P);
            A_P = ACT;
            ACT = A_N;
            continue;
        }
    }
}

void Print_for(List* L) {
    if (L->beg == NULL) { cout << "NULL" << endl; return; } // 0 //
    else if (L->beg == L->end) { cout << L->beg->key; } // 1 //
    else if (L->beg->link == L->end) { cout << L->beg->key << " " << L->end->key; } // 2 //
    else {
        Node* tmp = L->beg;
        //cout << "L.beg: " << L->beg->key << endl;
        Node* tmp2 = L->end;
        //cout << "L.end: " << L->end->key << endl;
        Node* tmp3;
        for (;;) {
            cout << tmp->key << " ";
            if (tmp == L->end) { break; }
            tmp3 = tmp;
            tmp = Xor(tmp->link, tmp2);
            tmp2 = tmp3;
        }
    }
    cout << endl;
}
void Print_back(List* L) {
    if (L->beg == NULL) { cout << "NULL" << endl; return; } // 0 //
    else if (L->beg == L->end) { cout << L->beg->key; } // 1 //
    else if (L->beg->link == L->end) { cout << L->end->key << " " << L->beg->key; } // 2 //
    else {
        Node* tmp = L->end;
        //cout << "L.end: " << L->end->key << endl;
        Node* tmp2 = L->beg;
        //cout << "L.beg: " << L->beg->key << endl;
        Node* tmp3;
        for (;;) {
            cout << tmp->key << " ";
            if (tmp == L->beg) { break; }
            tmp3 = tmp;
            tmp = Xor(tmp->link, tmp2);
            tmp2 = tmp3;
        }
    }
    cout << endl;
}
void Print_stats(List* L) {
    cout << "L.beg: " << L->beg->key << " ";
    cout << "L.a_p: " << L->a_p->key << " ";
    cout << "L.act: " << L->act->key << " ";
    cout << "L.end: " << L->end->key << " ";
    cout << endl;
}
void Del_nodes(List* L) {
    if (L->beg == NULL) { return; } // 0 //
    else if (L->beg == L->end) { delete L->beg; } // 1 //
    else if (L->beg->link == L->end) { delete L->beg; delete L->end; } // 2 //
    else {
        Node* tmp = L->beg;
        //cout << "L.beg: " << L->beg->key << endl;
        Node* tmp2 = L->end;
        //cout << "L.end: " << L->end->key << endl;
        Node* tmp3;
        Node* tmp4;
        for (;;) {
            tmp4 = tmp;
            if (tmp == L->end) { delete tmp; break; }
            tmp3 = tmp;
            tmp = Xor(tmp->link, tmp2);
            tmp2 = tmp3;
            delete tmp4;
        }
    }
    cout << endl;
}

bool Comp(char inp[], const char str[]) {
    bool out = true;
    for (int i = 0 ;; i++) {
        if (str[i] == '*') { break; }
        if (inp[i] != str[i]) { out = false; break; }
    }
    return out;
}
int Menu(char inp[]) {
    if      (Comp(inp, "ACTUAL*"        ))  { return 1; }
    else if (Comp(inp, "NEXT*"          ))  { return 2; }
    else if (Comp(inp, "PREV*"          ))  { return 3; }
    else if (Comp(inp, "ADD_BEG*"       ))  { return 4; }
    else if (Comp(inp, "ADD_END*"       ))  { return 5; }
    else if (Comp(inp, "ADD_ACT*"       ))  { return 6; }
    else if (Comp(inp, "DEL_BEG*"       ))  { return 7; }
    else if (Comp(inp, "DEL_END*"       ))  { return 8; }
    else if (Comp(inp, "DEL_VAL*"       ))  { return 9; }
    else if (Comp(inp, "DEL_ACT*"       ))  { return 10; }
    else if (Comp(inp, "PRINT_FORWARD*" ))  { return 11; }
    else if (Comp(inp, "PRINT_BACKWARD*"))  { return 12; }
    else if (Comp(inp, "print-stats*"   ))  { return 13; }
    else                                    { return 0; }
}

int main() {
    List* L = new List;
    char inp[14];
    int menu, key;
    while (!cin.eof()) {
        cin >> inp;
        //cout << inp << endl;
        menu = Menu(inp);
        switch (menu) {
        case 1:
            //cout << "actual" << endl;
            Actual(L);
            break;
        case 2:
            //cout << "next" << endl;
            Next_print(L);
            break;
        case 3:
            //cout << "prev" << endl;
            Prev_print(L);
            break;
        case 4:
            //cout << "add beg" << endl;
            cin >> key;
            Add_beg(L, key);
            break;
        case 5:
            //cout << "add end" << endl;
            cin >> key;
            Add_end(L, key);
            break;
        case 6:
            //cout << "add act" << endl;
            cin >> key;
            Add_act(L, key);
            break;
        case 7:
            //cout << "del beg" << endl;
            Del_beg(L);
            break;
        case 8:
            //cout << "del end" << endl;
            Del_end(L);
            break;
        case 9:
            //cout << "del val" << endl;
            cin >> key;
            Del_val(L, key);
            break;
        case 10:
            //cout << "del act" << endl;
            Del_act(L);
            break;
        case 11:
            //cout << "print for" << endl;
            Print_for(L);
            break;
        case 12:
            //cout << "print back" << endl;
            Print_back(L);
            break;
        case 13:
            //cout << "print back" << endl;
            Print_stats(L);
            break;
        case 0:
            //cout << "???" << endl;
            break;
        }
    }
    Del_nodes(L);
    delete L;
    

    return 0;
}
