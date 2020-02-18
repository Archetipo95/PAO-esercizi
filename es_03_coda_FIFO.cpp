#include <iostream>

using namespace std;

class Error {};

template <class T = int>
class Coda {
friend class const_iteratore;
private:
    class Nodo {
    public:
        T info;
        Nodo* next;

        Nodo(const T& t=T(), Nodo* n=nullptr) : info(t), next(n) {}
        ~Nodo() { delete next;}
    };
    Nodo *last, *first;

    static Nodo* copy(Nodo* p) {
        if(!p) return nullptr;
        return new Nodo(p->info, copy(p->next));
    }
    static bool rec_equal(Nodo* p1, Nodo* p2) {
        if(!p1 && !p2) return true;
        if(!p1 || !p2) return false;
        return p1->info == p2->info && rec_equal(p1->next, p2->next);
    }
public:
    Coda() : first(nullptr), last(nullptr) {}
    Coda(const Coda& t) : first(copy(t.first)), last(t.last) {}
    Coda& operator=(const Coda& c) {
        if(this != &c) {
            delete first;
            first = copy(c.first);
            last = c.last;
        }
        return *this;
    }
    ~Coda() { delete first;}
    Coda(int k, const T& t) {
        if(k <= 0) first=last=nullptr;
        else {
            first = last = new Nodo(t);
            k--;
            while(k) {
                Nodo* aux = new Nodo(t, first);
                first = aux;
                k--;
            }
        }
    }
    void insert(const T& t) {
        Nodo* aux = new Nodo(t);
        last->next = aux;
        last = aux;
    }
    T removeNext() {
        if(!first) throw Error();
        else {
            T ret = first->info;
            Nodo* aux = first;
            first = first->next;
            aux->next = nullptr;
            delete aux;
            return ret;   
        }
    }
    T* getNext() const {
        if(!first) return nullptr;
        return first->info;
    }

    bool operator==(const Coda& c) const {
        return rec_equal(first, c.first);
    }

    Coda& operator+(const Coda& c) const {
        Coda ret = new Coda();
        ret.first = first;
        ret.last = last;
        ret.last->next = c.first;
        last = c.last;

        return ret;
    }

    class const_iteratore{
	private:
		const Nodo* it;
	public:
		const_iteratore operator++() {
			if(it) it = it->next;
			return *this;
		}
		const T& operator*() const {
			return (*it)->info;
		}
        const T* operator->() const {
            return it;
        }
		const T operator[](const_iteratore i) {
			return (i.it)->info;
		}
	};
};

int main() {
    cout << "Hello world";
    return 0;
}