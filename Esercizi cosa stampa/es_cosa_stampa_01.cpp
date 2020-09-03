#include "iostream"

using namespace std;

class A {
    private:
        void h() {cout << "A::h ";}
    public:
        virtual void g() {cout << "A::g ";}
        virtual void f() {cout << "A::f ";g(); h();}
        void m() {cout << "A::m ";g(); h();}
        virtual void k() {cout << "A::k ";g(); h(); m();}
        A* n() { cout << "A::n "; return this;}
};

class B : public A{
    private:
        void h() {cout << "B::h ";}
    public: 
        virtual void g() {cout << "B::g ";}
        void m() {cout << "B::m ";g(); h();}
        void k() {cout << "B::k ";g(); h(); m();}
        B* n() { cout << "B::n ";return this;}
};

int main() {
    B* b = new B(); A* a = new B();
    b->f(); cout << "\n";
    b->m(); cout << "\n";
    b->k(); cout << "\n";
    a->f(); cout << "\n";
    a->m(); cout << "\n";
    a->k(); cout << "\n";
    (b->n())->g(); cout << "\n";
    (b->n())->n()->g(); cout << "\n";
    (a->n())->g(); cout << "\n";
    (a->n())->m(); cout << "\n";
}



/*
A::f B::g A::h 
B::m B::g B::h 
B::k B::g B::h B::m B::g B::h 
A::f B::g A::h 
A::m B::g A::h 
B::k B::g B::h B::m B::g B::h 
B::n B::g 
B::n B::n B::g 
A::n B::g 
A::n A::m B::g A::h 
*/