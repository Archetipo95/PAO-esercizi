// Programma 4
#include <iostream>

using namespace std;

class A {
    private:
    int z;
    public:
    ~A() {cout << "Ad ";}
};

class B {
    public:
    A* p;
    A a;
    ~B() {cout << "Bd ";}
};

class C {
    public:
    static B s;
    int k;
    A a;
    ~C() {cout << "Cd ";}
};

B C::s=B();

int main()
{
    C c1; cout << "UNO\n";
    C c2; cout << "DUE\n";
    C c3; cout << "TRE\n";
    
    return 0;
}

/*
Bd Ad UNO
DUE
TRE
Cd Ad Cd Ad Cd Ad Bd Ad 
*/