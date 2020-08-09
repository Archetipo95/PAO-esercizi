#include <iostream>

using namespace std;

class Vettore {
private:
	int* a;
	unsigned int _size;

	int* copy() const {
		if(_size == 0) return nullptr;
		int* x = new int[_size];
		for(unsigned int i=0; i<_size; ++i) x[i]=a[i];
		return x;
	}
public:
	unsigned int size() const { return _size;}
	Vettore() : a(0), _size(0) {}
	Vettore(unsigned int k) : a(k>0 ? new int[k] : 0), _size(k) {
		for(unsigned int i=0; i<_size; ++i) a[i]=k;
	}
	Vettore(const Vettore& v) : a(v.copy()), _size(v._size) {}
	Vettore& operator=(const Vettore& v) {
		if(this != &v){
			delete[] a;
			a = v.copy();
			_size = v._size;
		}
		return *this;
	}
	~Vettore() { delete[] a;}

	Vettore operator+(const Vettore& v) const {
		Vettore x;
		x.a = new int[_size + v._size];
		x._size = _size + v._size;
		unsigned int i = 0;
		for(; i<_size; i++) x.a[i] = a[i];
		for(; i<x._size; ++i) x.a[i] = v.a[i-_size];
		return x;
	}
	void append(const Vettore& v) {
		*this = *this + v; 
	}
	bool operator==(const Vettore& v) const {
		if(_size != v._size) return false;
		for(unsigned int i=0; i<_size; ++i) 
			if(a[i] != v.a[i]) return false;
		return true;
	}
	int& operator[](unsigned int i) const {
		return a[i];
	}
};

ostream& operator<<(ostream& os, const Vettore& v) {
	for(unsigned int i=0; i<v.size(); ++i) os << v[i] << " ";
	return os;
}

int main() {
	Vettore v1(3), v2(2);
	cout << v1 + v2 << endl;
	v1.append(v2+v2);
	cout << v1 << endl;
	v2 = v1;
	v2.append(v1);
	cout << v2 << endl;
}