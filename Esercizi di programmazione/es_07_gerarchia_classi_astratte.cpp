/*
classe base polimorfa A alla radice della gerarchia
classe derivata astratta B
sottoclasse C di B che sia concreta
una classe D definita tramite derivazione multipla con base virtuale
*/

#include <iostream>
using namespace std;

class A {
public:
    virtual ~A() {}
};

class B : public A { 
public:
    virtual ~B() = 0;
};
B::~B() {}

class C : public B {};

class D : virtual public B, public C {};

int main() {
    cout << "Hello world";
}