#include <iostream>

using namespace std;

int main() {
int i;
char c;
int depth=0;
while(true) {
    cin>>i;
    //if(c=='(') { depth++; }
    //else if(c==')') { depth--;}
    if(cin.fail()) {
        cin.clear();
        if(cin.peek() == '(') { depth++; cout<<"("<<endl;}
        if(cin.peek() == ')') { depth--; cout<<")"<<endl;}
        cin.ignore();
        cout<<"d: "<<depth<<endl;
    }
    else { cout<<i<<endl; }
}
( ( ( 1 2 ) 3 ( 4 ) 5 ( 6 7 ) ) 8 ( ( 9 ) 10 ( 11 ) ))


return 0;
}
