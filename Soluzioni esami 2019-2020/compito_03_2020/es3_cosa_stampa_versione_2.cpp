// Esercizio "cosa stampa"

#include <iostream>
using namespace std;

class A {
public:
    virtual void f() const {cout <<" A::f ";}
    virtual void h() {cout <<" A::h "; m();}
    virtual void k() {cout <<" A::k "; f();}
    void m() {cout <<" A::m "; f();}
    virtual A* n() {cout <<" A::n "; return this;}
};

class B: public A {
public:
    virtual void f() const {cout <<" B::f ";}
    void h() {cout <<" B::h "; A::n();}
    virtual void m() {cout <<" B::m "; f();}
    A* n() {cout <<" B::n "; return this;}
};

class E: public B {
public:
    B* n() {cout <<" E::n "; return this;}
protected:
    void r() {cout <<" E::r ";}
public:
    void m() {cout <<" E::m "; f(); r();}
};

class D: public A {
public:
    virtual void f() {cout <<" D::f ";}
    void h() const {cout <<" D::h "; h();}
    void m() {cout <<" D::m "; h(); f();}
};

int main() {
    A* q1 = new E(); 
    A* q2 = new B(); 
    A* q3 = new D(); 
    B* q4 = new E(); 
    const A* q5 = new D();

    //q1->h();    cout<<"\n";
    //q2->k();    cout<<"\n";
    //q3->h();    cout<<"\n";
    //q4->m();    cout<<"\n";
    //q4->h();    cout<<"\n";
    //(q3->n())->n()->f();    cout<<"\n";
    //(q4->n())->m();    cout<<"\n";
    //(q5->n())->f();    cout<<"\n";
    //(dynamic_cast<B*>(q1))->m();    cout<<"\n";
    //(static_cast<D*>(q2))->h();    cout<<"\n";

    return 0;
}


/*
 B::h  A::n 
 A::k  B::f 
 A::h  A::m  A::f 
 E::m  B::f  E::r 
 B::h  A::n 
 A::n  A::n  A::f 
 E::n  A::m  B::f
 errore compilazione
 E::m  B::f  E::r 
 errore runtime
*/


