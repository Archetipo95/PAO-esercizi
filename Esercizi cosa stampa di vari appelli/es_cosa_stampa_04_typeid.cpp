#include <iostream>
#include <typeinfo>

using namespace std;

class B {
public:
    virtual ~B() = 0;
    int x;
};
B::~B() {}

class D : public B {
public:
    int y;
};

class E : public D {
public:
    int z;
};

int main()
{
    D d; E e;
    B* b1 = &e;
    cout << typeid(b1).name() << endl;  //P1B*
    cout << typeid(*b1).name() << endl; //1E
    b1 = static_cast<D*>(b1);   //ATTENZIONE b1 rimane di tipo B* perchè sto cercando di salvare castD* su B*
    cout << typeid(b1).name() << endl;  //P1B
    cout << typeid(*b1).name() << endl; //1E

    return 0;
}
