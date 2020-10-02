// Esercizio "cosa stampa"

#include <iostream>
using namespace std;

class A {
protected: 
    virtual void r() {cout<<" A::r ";}
public:
    virtual void g() const {cout <<" A::g ";} 
    virtual void f() {cout <<" A::f "; g(); r();} 
    void m() {cout <<" A::m "; g(); r();}
    virtual void k() {cout <<" A::k "; r(); m(); } 
    virtual A* n() {cout <<" A::n "; return this;}
};

class B: public A { 
public:
    virtual void g() const {cout <<" B::g ";}
    virtual void m() {cout <<" B::m "; g(); r();}
    void k() {cout <<" B::k "; A::n();}
    A* n(){cout <<" B::n "; return this;}
};

class D: public B { 
protected:
    void r() {cout <<" D::r ";} 
public:
    B* n() {cout <<" D::n "; return this;} 
    void m() {cout <<" D::m "; g(); r();}
};

class C: public A {
protected:
    void r() {cout <<" C::r ";}
public:
    virtual void g() {cout <<" C::g ";}
    void m() {cout <<" C::m "; g(); r();}
    void k() const {cout <<" C::k "; k();}
};

int main()
{
    A* p1 = new D(); 
    A* p2 = new B(); 
    A* p3 = new C(); 
    B* p4 = new D(); 
    const A* p5 = new C();
    
    //p1->k(); 
    //p2->f();
    //p2->m();
    //p3->k();
    //p3->f();
    //p5->g();
    //(p3->n())->m();
    //(p3->n())->n()->g();
    //(p4->n())->m();
    //(p5->n())->g();
    //(dynamic_cast<B*>(p1))->m();
    //(static_cast<C*>(p2))->k();   errore runtime

    return 0;
}

/*
B::k  A::n 
A::f  B::g  A::r 
A::k  C::r  A::m  A::g  C::r 
A::f A::g C::r
A::g
A::n  A::m  A::g  C::r 
A::n  A::n  A::g 
D::n  A::m  B::g  D::r 
errore compilazione
D::m  B::g  D::r 
errore runtime
*/
