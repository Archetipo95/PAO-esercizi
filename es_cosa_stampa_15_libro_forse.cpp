#include <iostream>
using namespace std;

class A {
protected:
	int x;
public:
	A(int k=0) : x(k) {cout << "A("<<k<<") ";}
	~A() { cout << "~A ";}
	operator double() const { cout << "operator double() "; return x;}
};

class B : public A {
public:
	static A a;
	const A& a2;
	B(int k=3, const A &a3=0) : A(k), a2(a3) {cout << "B() ";}
	B(const B &b) : a2(b) {cout << a2 << " ";}
	~B() { cout <<"~B ";}
	A F(A a = A() ) { return a; }
};
A B::a(1);

int main() {
	
	A a(2); cout << "UNO\n";//A(1) A(2) UNO
	B b; cout << "DUE\n";//A(0) A(3) B() ~A DUE
	B b2(a); cout << "TRE\n";//A(0) operator double() A(2) B() ~A TRE
	B b3(a,a); cout << "QUATTRO\n";//operator double() A(2) B() QUATTRO
	B b4=b3; cout << "CINQUE\n";//A(0) operator double() 2 CINQUE
	b.F(); cout << "SEI\n";//A(0) ~A ~A ~A SEI
	b.F(3); cout << "SETTE\n";//A(3) ~A ~A ~A SETTE
	//~B ~A ~B ~A ~B ~A ~B ~A ~A ~A
	return 0;
}