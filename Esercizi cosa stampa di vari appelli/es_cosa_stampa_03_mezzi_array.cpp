#include <iostream>

using namespace std;

class B {
public:
    int x;
    B(int z=1) : x(z) {}
};

class D: public B {
public:
    int y;
    D(int z=5) : B(z-2), y(z) {}
};

void fun(B* a, int size) {
    for(int i=0; i<size; ++i) cout << (*(a+i)).x << " ";
}

int main() {
    fun(new D[4], 4); cout << "**1\n";
    B* b = new D[4]; fun(b,4); cout << "**2\n";
    b[0] = D(6); b[1] = D(9); fun(b,4); cout << "**3\n";
    b = new B[4]; b[0] = D(6); b[1] = D(9); fun(b,4); cout << "**4\n";
}

/*
3 5 3 5 **1
3 5 3 5 **2
4 7 3 5 **3
4 7 1 1 **4
*/