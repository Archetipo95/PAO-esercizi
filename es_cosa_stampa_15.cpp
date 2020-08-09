#include <iostream>

using namespace std;

class A {
protected: 
    virtual void r() {cout<<" A::r ";}
public:
    virtual void g() const {cout <<" A::g ";} 
    virtual void f() {cout <<" A::f "; g(); r();} 
    void m() const {cout <<" A::m "; g();}
    virtual void k() {cout <<" A::k "; r(); m(); } 
    virtual A* n() {cout <<" A::n "; return this;}
};

class B: public A { 
protected:
    void r() const {cout<<" B::r ";}
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
    B* n() {cout <<" D::n "; A::r(); return this;} 
    void m() {cout <<" D::m "; g(); r();}
    void k() {cout <<" D::k "; A::n();}
};

class C: public A {
protected:
    void r() {cout <<" C::r ";}
public:
    virtual void g() {cout <<" C::g ";}
    void m() {cout <<" C::m "; g(); r();}
    void k() const {cout <<" C::k "; k();}
    C* n() {cout <<" C::n "; return this;} 
};

class E: public A {
private: 
    virtual void r() {cout<<" E::r ";}
public:
    void g() const {cout <<" E::g ";} 
    void f() {cout <<" E::f "; g(); r();} 
    virtual void m() {cout <<" E::m "; g();}
    void k() {cout <<" E::k "; r(); m(); } 
    A* n() {cout <<" E::n "; return this;}
};

class F: public E {
public:
    void r() {cout<<" F::r ";}
    F* n() {cout <<" F::n "; return this;}
};

int main()
{
    A* p1 = new B(); 
    A* p2 = new D(); 
    A* p3 = new C(); 
    B* p4 = new B(); 
    const A* p5 = new C();
    B* p6 = new D();
    A* p7 = new F();
    
    //p1->r();
    //p1->k();
    //p3->n();
    //p2->f();
    //p5->g();
    //(p3->n())->m();
    //p3->k();
    //p7->n()->g();
    //(dynamic_cast<A*>(p6))->f();
    //(static_cast<A*>(p6))->g();
    //(dynamic_cast<A*>(p6))->g();
    //(dynamic_cast<B*>(p6))->k();
    //dynamic_cast<E*>(p7)->r();
    //(dynamic_cast<C*>(p3))->r();
    //(dynamic_cast<D*>(p1))->k();
    //(p4->n())->m();
    //p3->f();
    //p2->m();
    //(p5->n())->g();
    //(p6->n())->m();
    //p5->m();
    //((p6->n())->n())->g();
    //(dynamic_cast<E*>(p7)->n())->g();
    //static_cast<E*>(p7)->r();
    //(dynamic_cast<D*>(p6))->m();
    //static_cast<B*>(p6)->g();          //
    //(dynamic_cast<D*>(p1))->m();
    //static_cast<C*>(p1)->g();
    //(dynamic_cast<C*>(p6))->g();
    //(dynamic_cast<B*>(p1))->m();
    //(dynamic_cast<A*>(p2))->k();
    //(p3->n())->n()->g();
    //(static_cast<A*>(p6))->f();
    //(static_cast<D*>(p1))->k();         //
    //(static_cast<D*>(p1))->m();
    //(dynamic_cast<A*>(p3))->r();
    //(static_cast<B*>(p2))->k();
    //static_cast<F*>(p7)->r();
    //(static_cast<C*>(p2))->k();      //
    //(dynamic_cast<C*>(p2))->k();       //
    //(const_cast<A*>(p5)->n())->g();
    //dynamic_cast<F*>(p7)->r();
    //(dynamic_cast<C*>(p6)->n())->g();
    //(dynamic_cast<C*>(p1)->n())->g();

    return 0;
}

