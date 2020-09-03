#include "iostream"

using namespace std;

template<class T> class D; // dichiarazione incompleta

template<class T1, class T2> 
class C { 
    friend class D<T1>; 
    private: 
        T1 t1; 
        T2 t2;
};

template<class T> 
class D { 
    public: 
        void m() {C<T,T> c; cout << c.t1 << c.t2;} 
        void n() {C<int,T> c; cout << c.t1 << c.t2;} 
        void o() {C<T,int> c; cout << c.t1 << c.t2;} 
        void p() {C<int,int> c; cout << c.t1 << c.t2;} 
        void q() {C<int,double> c; cout << c.t1 << c.t2;}
        void r() {C<char,double> c; cout << c.t1 << c.t2;} 
};

/*
Compila o non compila?

(1) int main() { D<char> d; d.m(); } Yes
(2) int main() { D<char> d; d.n(); } No
(3) int main() { D<char> d; d.o(); } Yes
(4) int main() { D<char> d; d.p(); } No
(5) int main() { D<char> d; d.q(); } No
(6) int main() { D<char> d; d.r(); } Yes
*/