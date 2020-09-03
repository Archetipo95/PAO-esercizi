#include "iostream"

using namespace std;

class C {
public:
    int a[2];
    C(int x = 0, int y = 1) {
        a[0] = x;
        a[1] = y;
        cout << "C(" << a[0] << "," << a[1] << ") ";
    }
};

class D {
private:
    C c1;
    C *c2;
    C &cr;
public:
    D() : c2(&c1), cr(c1) { cout << "D() "; }
    D(const D &d) : cr(c1) { cout << "Dc "; }
    ~D() { cout << "~D "; }
};

class E {
public:
    static C cs;
};

C E::cs;

int main() {
    C c;
    cout << "UNO" << endl;
    C x(c);
    cout << x.a[0] << " " << x.a[1] << " DUE" << endl;
    D d = D();
    cout << "TRE" << endl;
    E e;
    cout << "QUATTRO" << endl;
}

/*
C(0,1) C(0,1) UNO
0 1 DUE
C(0,1) D() C(0,1) Dc ~D TRE
QUATTRO
~D 
*/