#include<iostream>
#include<fstream>
#include<typeinfo>

using namespace std;

class C { public: virtual ~C() {} };

//Creare questa in modo che stampi correttamente
template <typename T1, typename T2>
bool Fun(T1* t1, T2& t2) {
    if(typeid(t1) == typeid(C*)) return false;
    return typeid(t1) == typeid(&t2);
}

int main() {
    ifstream f("pippo");
    fstream g("pluto"), h("zagor");
    iostream* p = &h;
    C c1,c2;
    cout << Fun(&cout,cin) << endl; // stampa: 0
    cout << Fun(&cout,cerr) << endl; // stampa: 1
    cout << Fun(p,h) << endl; // stampa: 0
    cout << Fun(&f,*p) << endl; // stampa: 0
    cout << Fun(&g,h) << endl; // stampa: 1
    cout << Fun(&c1,c2) << endl; // stampa: 0
}
