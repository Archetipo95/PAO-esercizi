#include "iostream"

using namespace std;

class C { 
    public: 
        int x; 
        void f() { x=1; }
};

class D: public C { 
    public: 
        int y; 
        void f() { C::f(); y=2; }
};

int main() { 
    C c; D d; 
    c.f(); 
    d.f(); 
    cout << c.x << endl; 
    cout << d.x << " " << d.y;
}

/*
1
1 2
*/