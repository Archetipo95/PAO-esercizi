/*
Ridefinire il costruttore di copia di E in modo tale che il suo comportamento coincida con quello del costruttore di copia standard di E.
*/

#include <iostream>
#include <vector>
#include <list>
using namespace std;

class B { 
private:
	list<double>* ptr;
	virtual void m() =0; 
};

class C: virtual public B {};

class D: virtual public B { 
private: 
	int x;
};

class E: public C, public D {
private:
	vector<int*> v; 
public:
	void m() {}
	
	// ridefinizione del costruttore di copia di E
	E(const E& e){ 
		B::operator=(e);
		D::operator=(e);
		for (int i; i < e.v.size(); ++i) {
			v[i] = e.v[i];
		}
	}
};

main(){

}