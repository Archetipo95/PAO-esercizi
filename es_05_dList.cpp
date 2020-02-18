/*
ESERCIZIO. 

Definire un template di classe dList<T> i cui oggetti rappresentano una struttura dati lista doppiamente concatenata (doubly linked list) per elementi di uno stesso tipo T. Il template dList<T> deve soddisfare i seguenti vincoli:

1. Gestione della memoria senza condivisione.

2. dList<T> rende disponibile un costruttore dList(unsigned int k, const T& t) che costruisce una 
lista contenente k nodi ed ognuno di questi nodi memorizza una copia di t.

3. dList<T> permette l’inserimento in testa ed in coda ad una lista in tempo O(1) (cioe` costante):
-- Deve essere disponibile un metodo void insertFront(const T&) con il seguente comportamento: dl.insertFront(t) inserisce l’elemento t in testa a dl in tempo O(1).
-- Deve essere disponibile un metodo void insertBack(const T&) con il seguente comportamento: dl.insertBack(t) inserisce l’elemento t in coda a dl in tempo O(1).

4. dList<T> rende disponibile un opportuno overloading di operator< che implementa l’ordinamento lessicografico (ad esempio, si ricorda che per l'ordinamento lessicografico tra stringhe abbiamo che "campana" < "cavolo" e che
"eccellente" < "ottimo").

5. dList<T> rende disponibile un tipo iteratore costante dList<T>::const_iterator i cui oggetti permettono di iterare sugli elementi di una lista.
*/

#include <iostream>

using namespace std;

template<class T>
class dList {
private:
	class nodo {
	public:
		T info;
		nodo *prev, *next;
		nodo(const T& t = T(), nodo* p=nullptr, nodo* n=nullptr) : info(t), prev(p), next(n) {}
		~nodo() {delete next;}
	};
	nodo *last, *first; // lista vuota iff first==last==nullptr
		
	static nodo* copy(nodo* p, nodo*& l){
		if(!p) return l=nullptr;
		nodo* prec=new nodo(p->info);
		nodo* succ=prec;
		nodo* start=prec;
		while(p->next) {
			succ = new nodo(p->next->info,prec,nullptr);
			prec->next=succ;
			p=p->next;
			prec=prec->next;
		}
		l=succ;
		return start;
	}
	/* possibile versione ricorsiva
	static nodo* copy(nodo* p, nodo* pre, nodo*& l) {
		if(!p) return p = nullptr;
		nodo* temp = new nodo(p->info,pre,nullptr);
		temp->next = copy(p->next,temp,l);
		if(!p->next) l=temp;
		return temp;
	}*/

	static bool isLess(nodo* d1, nodo* d2) {
		if(!d2) return false;
		if(!d1) return true;
		return d1->info < d2->info || (d1->info==d2->info && isLess(d1->next,d2->next));
	}

public:
	~dList() {delete first;}
	dList(const dList& d): first(copy(d.first,last)) {}

	dList& operator=(const dList& d) {
		if(this != &d) {
			delete first;
			first=copy(d.first,last);
		}
		return *this;
	}

	void insertFront(const T& t) {
		first = new nodo(t,nullptr,first);
		if(!first->next) last=first;
		else (first->next)->prev=first;
	}

	void insertBack(const T& t) {
		last = new nodo(t,last,nullptr);
		if(!last->prev) first=last;
		else (last->prev)->next=last;
	}

	dList(unsigned int k, const T& t) : last(nullptr), first(nullptr) {
		for(unsigned int i=0; i<k; ++i) 
			insertFront(t);
	}

	bool operator<(const dList& d) const {
		return isLess(first,d.first);
	}
  
  	class const_iterator {
	friend class dList<T>;
	private:
		nodo* ptr;
		bool pastTheEnd; // true iff const_iterator è "past-the-end"
		// conversione nodo* => const_iterator
		const_iterator(nodo* p, bool pte=false) : ptr(p), pastTheEnd(pte) {}
  	public:
		const_iterator() : ptr(nullptr), pastTheEnd(false) {}

		const T& operator*() const {
	  		return ptr->info;
		}
	
		const T* operator->() const {
	  		return &(ptr->info);
		}
	
		const_iterator& operator++() {
			if(ptr && !pastTheEnd) {
				if(!ptr->next) { 
					++ptr; 
					pastTheEnd=true;
				}
				else ptr=ptr->next;
			}
			return *this;
		}
	
		const_iterator& operator--() {
	  		if(ptr) {
				if(pastTheEnd) {--ptr; pastTheEnd=false;}
				else ptr=ptr->prev;
	  		}
	  		return *this;
		}
	
		bool operator==(const const_iterator& x) const {
	  		return ptr==x.ptr;
		}

		bool operator!=(const const_iterator& x) const {
			return ptr!=x.ptr;
		}
	};

  	const_iterator begin() const {
		return first;
  	}
  
  	const_iterator end() const {
		if(!last) return nullptr;
		return const_iterator(last+1,true);
  	}
};


// esempio d'uso
int main() {
	dList<int> x(4,2), y(0,0), z(6,8);
	y=x;
	x.insertFront(-2); z.insertFront(3); y.insertFront(0);
	if(x<y) std::cout << "x < y" << std::endl;
	if(z<x) std::cout << "z < x" << std::endl;
	if(y<z) std::cout << "y < z" << std::endl;
	if(z<y) std::cout << "z < y" << std::endl;

	std::cout << "x= ";
	dList<int>::const_iterator j = --(x.end());
	for(; j != x.begin(); --j) std::cout << *j << ' '; 
	std::cout << *j << std::endl << "y= ";
	for(dList<int>::const_iterator k = y.begin(); k != y.end(); ++k) std::cout << *k << ' ';  
	std::cout << std::endl << "z= ";
	dList<int>::const_iterator i = z.begin(); 
	for( ; i != z.end(); ++i) std::cout << *i << ' ';  
	std::cout << std::endl;
}


/*
// ESERCIZIO SVOLTO IN AULA NELLA LEZIONE DEL 23/1/2015
//soluzione dell'esercizio dList (lista doppiamente linkata, primo appello dell'a.a. 13/14) come discussa in aula nell'ultima lezione del 23/1/2015.
//Soluzione by Ranzato
//URL: http://pastebin.com/JxRX6AAk

template<class T>
class dList {
  friend class const_iterator;
private:
  class nodo {
  public:
    T info;
    nodo *prev, *next; 
    nodo(nodo* p =0, const T& t = T(), nodo* n=0): prev(p), info(t), next(n) {}
    ~nodo() {if(next) delete next;} 
  };
  nodo *first, *last; // empty list  IFF  first==0==last

  static nodo* copia(nodo* p) {
    if(p==0) return 0;
    nodo* f = new nodo(0,p->info,0);
    nodo* currN = f;
    while(p->next !=0) {
      currN->next = new nodo(currN, p->next->info,0);
      currN = currN->next;
      p = p->next;
    }
    return f;
  }
  static nodo* getLast(nodo* f) {
    while(f && f->next) f=f->next;
    return f;
  }
  
  static bool compareLex(nodo* p1, nodo* p2) {
    if(!p1) return true;
    if(!p2) return false;
    // p1 && p2
    if(p1->info < p2->info) return true;
    if(p1->info > p2->info) return false;
    // p1 && p2 && p1->info == p2->info
    return compareLex(p1->next,p2->next);
  }
  
public:
  ~dList() {if(first) delete first;} 

  dList(const dList& l): first(copia(l.first)), last(getLast(first)) {}

  dList& operator=(const dList& l) {
    if(this != &l) {
      if(first) delete first;
      first = copia(l.first); 
      last = getLast(first);
    }
    return *this;
  } 
  dList(): first(0), last(0) {}
  dList(int k, const T& t) {
    if(k<=0) {first=last=0;}
    else {
      first = new nodo(0,t,0);
      nodo* temp = first;
      --k;
      while(k>0) {
	temp->next = new nodo(temp,t,0);
	temp = temp->next;
	--k;
      }
      last = temp;
    }
  } 
  void insertFront(const T& t) {
    first = new nodo(0,t,first);
    if(first->next==0) last = first;
    if(first->next) (first->next)->prev=first;
  }
  void insertBack(const T& t) {
    last = new nodo(last,t,0);
    if(last->prev != 0) (last->prev)->next = last;
    else first = last;
  }
  bool operator<(const dList& l) const {
    return compareLex(first,l.first);
  }
  class const_iterator {
    friend class dList<T>;
  private:
    const nodo* punt;
    // costruttore privato
    const_iterator(const nodo* p=0): punt(p) {}
  public:
    const T& operator*() const {
      return punt->info;
    }
    const T* operator->() const { 
      return &(punt->info); 
    }
    const_iterator& operator++() {
      if(punt) punt = punt->next;
      return *this;
    }
    const_iterator& operator--() {
      if(punt) punt=punt->prev;
      return *this;
    }
    bool operator==(const const_iterator& i) const {
      return punt == i.punt;
    }
  };
  const_iterator begin() const {
    return const_iterator(first); 
  }
  const_iterator end() const {
    return const_iterator(0);
  }
};

int main() {
  // codice che istanzia il template dList
  dList<int> x1,x2;
  dList<int> x3(5,2);
  x1=x2;
  x1<x3;
  dList<int>::const_iterator it1 = x1.begin();
  dList<int>::const_iterator it2 = x3.end();
  ++it1;
  --it2;
  x1.insertBack(5);
  x3.insertFront(4);
  dList<int> x4(x3);
  x4<x1;
  bool b = it1 == it2;
}


*/
