#include "iostream"

using namespace std;

class errore {
public:
    errore() {}    
};

template <class T = double>
class Coda {
private:
    class nodo {
    public:
        T info;
        nodo* next;

        nodo(T t=T(), nodo* n=nullptr):next(n), info(t) {}
        ~nodo() {delete next;}

    };

    nodo *last, *first; //empty iff first==nullptr
    static nodo* copia(const nodo* p) {
        if(!p) return nullptr;
        nodo* ret = new nodo(p->info,nullptr);
        nodo* aux = ret;
        while(p->next){
            aux->next = new nodo(p->next->info, nullptr);
            aux = aux->next;
            p = p->next;
        }
        return ret;
    }
    static bool minore(const nodo& n1, const nodo& n2) {
        if(!n1 && !n2) return true;
        if(!n1 || !n2) return false;
        return n1->info < n2->info && minore(n1->next, n2->next);
    }

public:
    // 4. Deve essere disponibile un costruttore di default che costruisce la coda vuota.
    Coda() : first(nullptr), last(nullptr) {}

    // 5. Deve essere disponibile un costruttore Coda(int k, const T& t) che costruisce 
    // una coda contenente k copie dell’elemento t.
    Coda(int k, const T& t) {
        if(k<=0) first=last=nullptr;
        else {
            first = last = new nodo(t);
            k--;
            while(k) {
                nodo* aux = new nodo(t,first);
                first = aux;
                k--;
            }
        }
    }

    // 6. Deve essere disponibile un metodo void insert(const T&) con il seguente comportamento:
    // c.insert(t) inserisce l’elemento t in coda a c in tempo costante.
    void insert(const T& t) {
        nodo* aux = new nodo(t);
        last->next = aux;
        last = aux;
    }

    // 7. Deve essere disponibile un metodo T removeNext() con il seguente comportamento:
    // se la coda c non `e vuota, c.removeNext() rimuove l’elemento in testa alla coda c in
    // tempo costante e lo ritorna; se invece c `e vuota allora provoca undefined behaviour
    // (da definirsi opportunamente).
    T removeNext() {
        if(!first) throw errore();
        else {
            T ret = first->info;
            nodo* aux = first;
            first = first->next;
            aux->next = nullptr;
            delete aux;
            return ret;
        }
    }

    // 8. Deve essere disponibile un metodo T* getNext() con il seguente comportamento:
    // se la coda c non `e vuota, c.getNext() ritorna un puntatore all’elemento in testa
    // a c in tempo costante; se invece c `e vuota ritorna il puntatore nullo.
    T* getNext() {
        if(!first) return nullptr;
        else return first->info;
    }

    // 9. Overloading di operator< che implementa il confronto lessicografico tra code.
    bool operator<(const Coda& c) const {
        return minore(first,c.first);
    }

    // 10. Overloading dell’operatore di somma che agisca come concatenazione: c + d
    // ritorna la coda che si ottiene aggiungendo d in coda a c.
    Coda operator+(const Coda& c) const {
        if(first) {
            Coda c1 = copia(first);
            Coda c2 = copia(c.first);
            c1.last->next = c2.first;
            return c1;
        }
        Coda c2 = copia(c.first);
        return c2;
    }

    // 11. Coda<T> rende disponibile un tipo iteratore costante Coda<T>::const iterator i cui oggetti
    // permettono di iterare sugli elementi di una coda c senza permettere modifiche al contenuto di c.
    class const_iterator {
    friend class Coda<T>;
    private:
        const nodo* ptr;
    public:
        const_iterator operator++() {
            if(ptr) ptr = ptr->next;
            return *this;
        }
        const T& operator*() const {
            return ptr->info;
        }
        const T operator[](const_iterator i) const {
            return (i.ptr)->info;
        }
    };
};

int main() {

    cout << "Hello world";

    return 0;
}