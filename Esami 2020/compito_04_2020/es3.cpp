#include <iostream>
using namespace std;

class C {
 public:
  C() { cout << "C0 "; }
  C(const C&) { cout << "Cc "; }
  C& operator=(const C& e) {
    cout << "C= ";
    return *this;
  }
};

class D {
 public:
  C c;
  D() { cout << "D0 "; }
  D(const D&) { cout << "Dc "; }
};

class E : public C {
 public:
  C c;
  E() { cout << "E0 "; }
  E& operator=(const E& e) {
    *this = e;
    cout << "E= ";
    return *this;
  }
};

class F : public C {
 public:
  C* pc;
  F() { cout << "F0 "; }
  F(const F&) { cout << "Fc "; }
  F& operator=(const F& f) {
    C::operator=(f);
    pc = f.pc;
    cout << "E= ";
    return *this;
  }
};
int main(int argc, char const* argv[]) {
  C x1, x2;
  E y1, y2;
  F z1, z2;

  cout << endl;

  // D d1;
  // D d2(d1);
  // E e1;
  // E e2 = y1;
  // y1 = y2;
  // F* pf = new F();
  // F f = z1;
  // z1 = z2;
  // x1 = y1;
  // z1 = x1;

  return 0;
}
