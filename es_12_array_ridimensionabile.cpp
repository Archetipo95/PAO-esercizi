/*
Definire un template di classe Array<T> i cui oggetti rappresentano una struttura dati “array ridimensionabile” di elementi di uno stesso tipo T. Si ricorda che in un array ridimensionabile la sua dimensione (cio`e il numero di elementi correntemente contenuti) `e sempre ≤ alla sua capacit`a (cio`e il numero di elementi che pu`o contenere senza dover ridimensionarsi), e quando si inserisce un nuovo elemento in un array con dimensione uguale alla capacit`a, l’array viene ridimensionato raddoppiandone la capacit`a. Il template Array<T> deve soddisfare i seguenti vincoli:
1. Ovviamente, Array<T> non pu`o usare i contenitori STL o Qt come campi dati (inclusi puntatori e riferimenti a contenitori STL o Qt).
2. Deve essere disponibile un costruttore Array(int k = 0 , const T& t = T()) che costruisce un array contenente k copie di t quando k > 0, mentre se k ≤ 0 costruisce un array vuoto.
3. Gestione della memoria senza condivisione.
4. Deve essere disponibile un metodo void pushBack(const T&) con il seguente comportamento: a.pushBack(t) inserisce l’elemento t alla fine dell’array a dopo il suo ultimo elemento corrente; ci`o provoca quindi il ridimensionamento di a se e solo se la dimensione di a `e uguale alla sua capacit`a.
5. Deve essere disponibile un metodo T popBack() con il seguente comportamento: se l’array a non `e vuoto, a.popBack() rimuove l’ultimo elemento corrente di a e quindi lo ritorna; se invece a `e vuoto allora solleva una eccezione di tipo Empty (una opportuna classe di eccezioni di cui `e richiesta la definizione).
6. Opportuno overloading dell’operatore di uguaglianza. 7. Opportuno overloading dell’operatore di output.
*/

#include <iostream>

using namespace std;

// if dimensione == capacita -> capacitax2

class Empty{
public:
  Empty(){cout << "Vuoto";}
};
template <class T> class Array;
template <class T> ostream& operator<<(ostream&, const Array<T>&);
template <class T>
class Array {
  friend ostream& operator<< <>(ostream&, const Array<T>&);
private:
  T* x;
  int size, capacity;

  static T* copia(T* t, int sz, int cap){
    T* a = new T[cap];
    for(int i=0; i<sz; ++i)
      a[i]=t[i];
    return a;
  }

public:
  Array(int k=0, const T& t = T()): x(0), size(k), capacity(k*2){
    if (k) {
        x=new T[k*2];
        for(int i=0; i<size; i++)
          x[i]=t;
      }
  }
  //richiamo copia sull'oggetto di invocazione e gli passo i parametri di t
  Array(const Array& t):x(copia(t.x,t.size,t.capacity)),size(t.size),capacity(t.capacity){}
  ~Array(){delete[] x;}
  Array& operator=(const Array& t){
    if(this != t){
        delete[] x;
        x=copia(t,t.size,t.capacity);
        size=t.size;
        capacity=t.capacity;
      }
    return *this;
  }

  void pushBack(const T& t){
    if (size==capacity) {
        x=copia(x, size, capacity*2);
        capacity=capacity*2;
        x[size]=t;
        size++;
      }
    else {
        x[size]=t;
        size++;
      }
  }

  T popBack(){
    if(x){
        T aux = x[size-1];  //T SENZA *
        delete x[size-1];
        size--;   //RICORDATI
        return aux;
      }else throw Empty();
  }

  bool operator==(const Array& a){
    if(size != a.size) return false;
    for(int i=0; i<size; i++) if(x[i]!=a[i]) return false;
    return true;
  }
};

template<class T>
ostream& operator<<(ostream& os, const Array<T>& a){
  for (int i=0; i<a.size; i++) {
      os << (a.x)[i] << " ";
    }
  return os;
}

int main()
{
  cout << "Hello World!" << endl;
  return 0;
}
