#include <iostream>
using namespace std;

class Z { 
public: 
	Z(int x) {}
};

class A { 
public:
	void f(int) {cout << "A::f(int) "; f(true);} 
	virtual void f(bool) {cout <<"A::f(bool) ";} 
	virtual A* f(Z) {cout <<"A::f(Z) "; f(2); return this;} 
	A() {cout <<"A() "; }
};

class C: virtual public A { 
public:
	C* f(Z){cout <<"C::f(Z) "; return this;}
	C() {cout <<"C() "; } 
};

class B: virtual public A { 
public:
	void f(const bool&){cout<< "B::f(const bool&) ";} 
	void f(const int&){cout<< "B::f(const int&) ";} 
	virtual B* f(Z) {cout <<"B::f(Z) "; return this;} 
	virtual ~B() {cout << " ̃B ";}
	B() {cout <<"B() "; } 
};
		
class D: public B { 
public:
	virtual void f(bool) const {cout <<"D::f(bool) ";} 
	B* f(Z) {cout << "D::f(Z) "; return this;} 
	~D() {cout <<" ̃D ";} 
	D() {cout <<"D() "; }
};
		
class E: public D, public C { 
public:
			
	void f(bool){cout<< "E::f(bool) ";} 
	E* f(Z){cout <<"E::f(Z) "; return this;} 
	E() {cout <<"E() "; } 
	~E() {cout <<" ̃E ";}
}; 

int main(){

	cout << "***************** DEFAULT *****************" << endl;
	B* pb=new B; C* pc = new C; D* pd = new D; E* pe = new E; A *pa1=pb, *pa2=pc, *pa3=pd, *pa4=pe; B *pb1=pe;
	cout << endl << "*****************+++++++++*****************" << endl;

	//E* puntE = new E;	cout << endl;		//	A() B() D() C() E() 
	//D* puntD = new D;	cout << endl;		//	A() B() D()
	//pa3->f(3);			cout << endl;		//	A::f(int) A::f(bool)  Perchè D::f(bool) è marchiata costante
	//pa4->f(3);			cout << endl;		//	A::f(int) E::f(bool) 
	//pb1->f(true);		cout << endl;		//	B::f(const bool&) 
	//pa4->f(true);		cout << endl;		//	E::f(bool)
	//pa2->f(Z(2));		cout << endl;		//	C::f(Z)
	//pa4->f(Z(2));		cout << endl;		//	E::f(Z)
	//pb->f(3);			cout << endl;		//	B::f(const int&)
	//pc->f(3);			cout << endl;		//  C::f(Z)
	//(pa4->f(Z(3)))->f(4);	cout << endl;	//	E::f(Z) A::f(int) E::f(bool) 
	//(pc->f(Z(3)))->f(4);	cout << endl;	//	C::f(Z) C::f(Z) 
	//delete pa4;			cout << endl;		// 
	//delete pd;			cout << endl;		// ~D ~B dovrebbe stampare A ma non ha ridefinito il distruttore


}