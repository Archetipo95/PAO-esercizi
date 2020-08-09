#include <iostream>
#include <string>

using namespace std;

class S {
public:
    string s;
    S(string t) : s(t) {}
};

class N {
private:
    S x;
public:
    N* next;
    N(S t, N* p) : x(t), next(p) { cout << "N2 ";}
    ~N() { if(next) delete next; cout << x.s + "~N ";}
};

class C {
    N* pointer;
public:
    C() : pointer(nullptr) {}
    ~C() { delete pointer; cout << "~C ";}
    void F(string t1, string t2 = "pippo") {
        pointer = new N(S(t1), pointer);
        pointer = new N(t2, pointer);
    }
};

int main() {
    C* p = new C; cout << "UNO\n";
    p->F("pluto", "paperino"); p->F("topolino"); cout << "DUE\n";
    delete p; cout << "TRE\n";
}



//Attenzio che su if di ~N non ci sono le parentesi
/*
Uno
N2 N2 N2 N2 Due
pluto~N paperino~N topolino~N pippo~N ~C Tre
*/
//si crea una coda pluto->paperino->topolino->pippo->nullptr