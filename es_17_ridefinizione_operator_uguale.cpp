#include <iostream>

using namespace std;

class Z { private: int x; };

class B { private: Z x; };

class D: public B { 
	private:
	Z y; 
	public:
	// ridefinizione di operator=
	D& operator=(const D&);
};

D& D::operator= (const D& x){
	this->B::operator=(x);
	//mi devo occupare del campo dati
	y= x.y;
	return *this;
}

int main(){
	
}

