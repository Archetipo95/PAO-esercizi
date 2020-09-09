// Esercizio "cosa stampa"

#include <iostream>
using namespace std;

class B {
protected:
    virtual void h() {cout <<" B::h ";}
public:
    virtual void f() {cout << " B::f "; g(); h();}
    virtual void g() const {cout <<" B::g ";}
    virtual void k() {cout << " B::k "; h(); m();}
    void m() {cout <<" B::m "; g(); h();}
    virtual B* n() {cout<< " B::n"; return this;}
};

class D : public B {
protected:
    void h() {cout <<" D::h ";}
public:
    virtual void g() {cout << " D::g ";}
    void k() const {cout << " D::k "; k();}
    void m() {cout << " D::m "; g(); h();}
};

class C: public B {
public:
    virtual void g() const {cout<<" C::g ";}
    void k() {cout<<" C::k "; B::n();}
    virtual void m() {cout << " C::m "; g(); h();}
    B* n() {cout <<" C:.n "; return this;}
};

class E: public C {
protected:
    void h() {cout<<" E::h ";}
public:
    void m() {cout<<" E::m "; g(); h();}
    C* n() {cout <<" E:.n "; return this;}
};

const B* p1 = new D(); B* p2 = new C(); B* p3 = new D(); C* p4 = new E(); B* p5 = new E();
int main()
{
    // p1->g(); cout << endl;
    // (p1->n()->g());
    // p2->f(); cout<<endl;
    // p2->m(); cout<<endl;
    // (static_cast<D*>(p2))->k();
    // p3->k(); cout<<endl;
    // p3->f(); cout<<endl;
    // (p3->n())->m(); cout<<endl;
    // (p3->n())->n()->g(); cout<<endl;
    // (static_cast<C*>(p3->n()))->g(); cout<<endl;
    // p4->m(); cout<<endl;
    // p4->k(); cout<<endl;
    // (p4->n())->m(); cout<<endl;
    // p5->g(); cout<<endl;
    // p5->k(); cout<<endl;
    // (dynamic_cast<C*>(p5))->m(); cout<<endl;
}
