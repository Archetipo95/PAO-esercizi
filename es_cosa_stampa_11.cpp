#include <iostream>
using std::cout;

class Z {

public: Z(int x) {}

};

class A {

public:

void f(int){cout << "A::f(int) ";}

virtual void f(bool){cout <<"A::f(bool) ";}

virtual void f(Z){cout <<"A::f(Z) ";}

};

class B: virtual public A {

public:

void f(const bool&){cout<< "B::f(const bool&) ";}

void f(const int&){cout<< "B::f(const int&) ";}

};

class C: virtual public A {

public:

virtual void f(Z){cout <<"C::f(Z) ";}

};

class D: public B, public C {

public:

virtual void f(int*){cout<< "D::f(int*) ";}

void f(int&){cout <<"D::f(int&) ";}

};

class E: public D {

public:

void f(Z){cout <<"E::f(Z) ";}

};

int main(){
	
	B* pb=new B; C* pc = new C; D* pd = new D; 
	E* pe = new E; A *pa1=pb, *pa2=pc, *pa3=pd, *pa4=pe; C *pc1=pe;

	(dynamic_cast<B*>(pa1))->f(1); 		// B::f(const int&)
	(dynamic_cast<B*>(pa1))->f(true); 	// B::f(const bool&)
	pa1->f(true);						// A::f(bool)
	pa2->f(1);							// A::f(int)
	(dynamic_cast<C*>(pa2))->f(1);      // C::f(Z)
	// (dynamic_cast<E*>(pa2))->f(1);   ERRORE RUN-TIME
	(dynamic_cast<C*>(pa3))->f(0);		// C::f(Z)
	(dynamic_cast<D*>(pa3))->f(0);		// D::f(int*)
	pa4->f(1);							// A::f(int)
	(dynamic_cast<C*>(pa4))->f(1);		// E::f(Z)
	pc1->f(1);							// E::f(Z)
	(static_cast<E*>(pc1))->f(1);		// E::f(Z)
	(static_cast<A*>(pc1))->f(1);		// A::f(int)


}	




