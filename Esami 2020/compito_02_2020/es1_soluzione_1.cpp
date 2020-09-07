// Definire un template di classe Vettore<T, sz> in modo da produrre le stampe date

#include<iostream>
using namespace std;

// Soluzione 1
template <class T = int, unsigned int _size = 0>
class Vettore {
private:
  T* a;
public:
  Vettore(const T& x=T()):
    a(_size==0 ? nullptr :  new T[_size]) {
    for(int i=0; i<_size; ++i) a[i]=x;
  }   
  Vettore(const Vettore& v): a(_size == 0 ? nullptr : new T[_size]) {
    for(int i=0; i<_size; ++i) a[i]=v.a[i];
  }
  Vettore& operator=(const Vettore& v) {
    if(this != &v) {
      delete[] a;
      a = _size == 0 ? nullptr : new T[_size];
      for(int i=0; i<_size; ++i) a[i]=v.a[i];
    }
    return *this;
  }
  ~Vettore() { delete[] a;}
  
  const T& operator[](unsigned int i) const {
    return a[i];
  }
  T& operator[](unsigned int i) {
    return a[i];
  }
    
  const T& operator*() const {
    return a[0];
  }
  T& operator*() {
    return a[0];
  }
};

// Parte di codice fornita

template <class T, unsigned int sz>
std::ostream& operator<<(std::ostream& os, const Vettore<T,sz>& v) {
  for(int i=0; i<sz; ++i) os << v[i] << ' '; 
  return os;
}

int main() {
  Vettore<int,4> v1(2); Vettore< Vettore<int,3> ,3> v2(3);
  Vettore<int,4> v3(v1); Vettore<int,4> v4; v3[2]=6;
  *v1=9;
  v4=v1;
  v4[3]=5;
  std::cout << v1 << std::endl; // 9 2 2 2
  std::cout<<v2<<std::endl;     // 3 3 3  3 3 3  3 3 3
  std::cout << v3 << std::endl; // 2 2 6 2
  std::cout << v4 << std::endl; // 9 2 2 5
}

