#include <iostream>

using namespace std;

template <class T> class Trialbero;
template <class T> ostream& operator<<(ostream&, const Trialbero<T>&);
template <class T>
class Trialbero {
    friend ostream& operator<< <T>(ostream&, const Trialbero<T>&);
private:
    class Nodo {
    public:
        T info;
        Nodo *sx, *cx, *dx;

        Nodo(const T& t=T(), Nodo* s=nullptr, Nodo* c=nullptr, Nodo* d=nullptr) : info(t), sx(s), cx(c), dx(d) {}
        ostream& rec_print(ostream& os) const {
            os << "(" << info << ")";
            if(sx) { sx->rec_print(os); os << ",";}
            if(cx) { cx->rec_print(os); os << ",";}
            if(dx) { dx->rec_print(os); os << ",";}
            return os;
        }
    };

    Nodo* root;
    static Nodo* copy(Nodo* p) {
        if(!p) return nullptr;
        return new Nodo(p->info, copy(p->sx), copy(p->cx), copy(p->dx));
    }
    static void destroy(Nodo* p) {
        if(p) {
            destroy(p->sx);
            destroy(p->cx);
            destroy(p->dx);
        }
        delete p;
    }
    static bool rec_search(Nodo* p, const T& t) {
        if(!p) return false;
        return p->info == t || rec_search(p->sx, t) || rec_search(p->cx, t) || rec_search(p->dx, t);
    }
    static bool rec_equal(Nodo* p1, Nodo* p2) {
        if(!p1 && !p2) return true;
        if(!p1 || !p2) return false;
        return p1->info == p2->info && rec_equal(p1->sx, p2->sx) && rec_equal(p1->cx, p2->cx) && rec_equal(p1->dx, p2->dx);
    }
public:
    Trialbero() : root(nullptr) {}
    Trialbero(const Trialbero& t) : root(copy(t.root)) {}
    Trialbero& operator=(const Trialbero& t) {
        if(this != &t) {
            destroy(root);
            root = copy(t.root);
        }
        return *this;
    }
    ~Trialbero() { destroy(root);}

    //inserisce una nuova radice e copia quella attuale a sx, cx e dx
    void insert(const T& t) {
        root = new Nodo(t, root, copy(root), copy(root));
    }
    bool search(const T& t) const {
        return rec_search(root, t);
    }
    bool operator==(const Trialbero& t) const {
        return rec_equal(root, t.root);
    }
};

template <class T>
ostream& operator<<(ostream& os, const Trialbero<T>& t) {
    if(t.root != nullptr) return t.root->rec_print(os);
    return os;
}

int main() {
    
    Trialbero<int> a;
    Trialbero<int> b;
    
    a.insert(1);
    a.insert(2);
    a.insert(3);
    
    cout << "Trialbero a: "<< a << endl;
    
    cout << "Trialbero b: "<< b << endl;


    return 0;
}