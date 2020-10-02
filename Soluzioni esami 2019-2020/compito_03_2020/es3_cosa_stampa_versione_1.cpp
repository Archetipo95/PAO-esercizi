// Esercizio "cosa stampa"

#include <iostream>
using namespace std;

class A {
public:
    virtual void f() const {cout <<" A::f ";}
    virtual void g() {cout <<" A::g "; m(); }
    virtual void h() {cout <<" A::h "; f();}
    void m() {cout <<" A::m "; f();}
    virtual A* n() {cout <<" A::n "; return this;}
};

class B: public A {
public:
    virtual void f() const {cout <<" B::f ";}
    void g() {cout <<" B::g "; A::n();}
    virtual void m() {cout <<" B::m "; f();}
    A* n() {cout <<" B::n "; return this;}
};

class D: public B {
public:
    B* n() {cout <<" D::n "; return this;}
protected:
    void r() {cout <<" D::r ";}
public:
    void m() {cout <<" D::m "; f(); r();}
};

class C: public A {
public:
    virtual void f() {cout <<" C::f ";}
    void g() const {cout <<" C::g "; g();}
    void m() {cout <<" C::m "; g(); f();}
};

int main() {
    A* q1 = new D(); 
    A* q2 = new B(); 
    A* q3 = new C(); 
    B* q4 = new D(); 
    const A* q5 = new C();

    //q1->f();
    //q1->g();
    //q2->h();
    //q2->m();
    //q3->g();
    //q3->h();
    //q4->m();
    //q4->g();
    //(q3->n())->m();
    //(q3->n())->n()->f();
    //(q4->n())->m();
    //(q5->n())->f();
    //(dynamic_cast<B*>(q1))->m();
    //(static_cast<C*>(q2))->g();
    //(static_cast<B*>(q3->n()))->f();

    return 0;
}



