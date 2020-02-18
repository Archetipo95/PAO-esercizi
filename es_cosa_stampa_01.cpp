#include "iostream"

using namespace std;

class A {
    private:
        void h() {cout << "A::h";}
    public:
        virtual void g() {cout << "A::g";}
        virtual void f() {cout << "A::f";g(); h();}
        void m() {cout << "A::m";g(); h();}
        virtual void k() {cout << "A::k";g(); h(); m();}
        A* n() { cout << "A::n"; return this;}
};

class B : public A{
    private:
        void h() {cout << "B::h";}
    public: 
        virtual void g() {cout << "B::g";}
        void m() {cout << "B::m";g(); h();}
        void k() {cout << "B::k";g(); h(); m();}
        B* n() { cout << "B::n";return this;}
};

int main() {
    B* b = new B(); A* a = new B();
    //b->f(); //A::f B::g A::h //cerca f() in b, non c'è, controlla in A, TS A* e TD B*, invoca l'ovveraid B::g(), chiamo A::h perchè in B è privata e non la vedo (in più non è virtual in A, se era publica in B)
    //b->m(); // B::m B::g B::h
    //b->k(); //B::k B::g B::h B::m B::g B::h
    //a->f(); //A::f B::g A::h
    //a->m(); // A::m B::g A::h
    //a->k(); // B::k B::g B::h B::m B::g B::h
    //(b->n())->g();  // B::n B::g  
    //(b->n())->n()->g(); //B::n B::n B::g
    //(a->n())->g(); // A::n B::g ATTENZIONE n() non è virtual
    //(a->n())->m();  // A::n A::m B::g A::h
}