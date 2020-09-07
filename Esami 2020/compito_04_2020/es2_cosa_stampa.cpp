// Esercizio "cosa stampa"
// Per ogni istruzione dire se compila o meno, se produce errore a run time e cosa stampa.

#include <iostream>
using namespace std;

class A {
  bool x;
  public:
    virtual ~A(){};
};

class B {
  bool y;
  public:
    virtual void f() const { cout << "B::f "; }
};

class C: public A {};

class D: public B {
  public:
    void f() const { cout << "D::f "; }
};

class E: public D {
  public:
    void f() const { cout << "E::f "; }
};

template <class T>
void Fun(const T& ref) {
  const B* pB = dynamic_cast<const B*>(&ref);
  const E* pE = dynamic_cast<const E*>(&ref);

  if (dynamic_cast<const C*>(&ref)) {
    cout << "C ";
    ref.f();
    return;
  }

  if (pE) {
    cout << "E ";
    pE->f();
    return;
  }

  if (pB) {
    cout << "B ";
    pB->f();
    return;
  }

  if (dynamic_cast<const A*>(&ref)) {
    cout << "A ";
    return;
  }

  if (dynamic_cast<const D*>(&ref)) {
    cout << "D ";
    return;
  }
}

int main() {
  C c;
  D d;
  E e;
  A& a1 = c;
  B& b1 = d;
  B& b2 = e;
  B* b3 = new B();
  D& d1 = e;
  D* pD1 = dynamic_cast<E*>(&b2);
  D* pD2 = dynamic_cast<D*>(&b2);

  // Fun<A>(c);
  // Fun(a1);
  // Fun(b1);
  // Fun(d1);
  // Fun(*pD2);
  // Fun<E>(d1);
  // Fun<E>(e);
  // Fun(*b3);
  // Fun<D>(e);
  // Fun(b2);

  return 0;
}
