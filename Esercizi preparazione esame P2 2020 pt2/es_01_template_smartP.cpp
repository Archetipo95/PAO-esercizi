#include <iostream>

using namespace std;

template <class T>
class SmartP {
private:
    T* p;
public:
    SmartP() : p(nullptr) {}
    SmartP(const SmartP& s) : p(new T(*(s.p))) {}
    SmartP& operator=(const SmartP& s) {
        if(this != &s) {
            delete p;
            p = new T(*(s.p));
        }
        return *this;
    }
    SmartP(const T* t) : p(new T(*t)) {}
    ~SmartP() {
        delete p;
    }
    T& operator*() const {
        return *p;
    }
    T* operator->() const {
        return p;
    }
    bool operator==(const SmartP& s) const {
        return *p == *s.p;
    }
    bool operator!=(const SmartP& s) const {
        return *p != *s.p;
    }
};

class C {
public:
    int *p;
    C() : p(new int(5)) {}
};

int main() {
    const int a = 1; const int* p = &a;
    SmartP<int> r; SmartP<int> s(&a); SmartP<int> t(s);
    cout << *s << " " << *t << " " << *p << endl;
    *s = 2; *t = 3;   
    cout << *s << " " << *t << " " << *p << endl;
    r = t; *r = 4;
    cout << *r << " " << *s << " " << *t << " " << *p << endl;
    cout << (s == t) << " " << (s != p) << endl;
    C c; SmartP<C> x(&c);
    cout << *(c.p) << " " << *(x->p) << endl;
    *(c.p) = 6;
    cout << *(c.p) << " " << *(x->p) << endl;
    SmartP<C>* q = new SmartP<C> (&c);
    delete q;
    cout << *(x->p) << endl;
}

/*
1 1 1
2 3 1
4 2 3 1
0 1
5 5
6 6
6
*/