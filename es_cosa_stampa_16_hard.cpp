#include <iostream>

using namespace std;

class A {
protected:
    int x;
public:
    A(int k=0): x(k) { cout << "A(" << x << ") ";}
    ~A() { cout << "~A()";}
    operator double() const { cout << "op double(" << x << ") "; return x;}
};

class B: public A {
public:
    static A a;
    const A &a2;
    A F(A a=A()) { return a;}
    B(int k=3, const A& a3=7) : A(k), a2(a3) { cout << "B() ";}
    ~B() { cout << "~B()";}
    B(const B &b) : a2(b) { cout << a2 << " ";}
};

A B::a(1);

int main() {
    //A a(1); cout << "UNO\n";
    //B b; cout << "DUE\n";
    //B b2(a); cout << "TRE\n";
    //B b3(a,a); cout << "QUATTRO\n";
    //B b4=b3; cout << "CINQUE\n";
    //b.F(); cout << "SEI\n";
    //b.F(2); cout << "SETTE\n";

    cout << "FINE\n";
}


/*
A(1) A(1) UNO
A(7) A(3) B() ~A()DUE
A(7) op double(1) A(1) B() ~A()TRE
op double(1) A(1) B() QUATTRO
A(0) op double(1) 1 CINQUE
A(0) ~A()~A()~A()SEI
A(2) ~A()~A()~A()SETTE
FINE
~B()~A()~B()~A()~B()~A()~B()~A()~A()~A()

*/