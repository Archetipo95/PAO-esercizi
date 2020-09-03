#include "iostream"

using namespace std;

//classe per errori
class Vuoto {
public:
    Vuoto() {}
};

//dichiarazione incompleta classe
template <class T, int num>
class stack;

//dichiarazione incompleta operator<<
template <class T, int num> 
ostream& operator<<(ostream&, const stack<T,num>&);

//stack completa
template <class T = char, int num = 100>
class stack {
friend ostream& operator<< <T,num> (ostream&, const stack<T,num>&);
private:
    class nodo {
    public:
        T info;
        nodo* next;

        nodo(T t = T(), nodo* n = nullptr) : info(t), next(n) {}
        ~nodo() { delete next;}

        ostream& print(ostream& os) {
            os << "(" << info << ",";
            if(next) {next->print(os); os << ",";}
            else os << "NULL)";
            return os;
        }
    };

    nodo* topPtr;  //stack empty iff topPtr==nullptr
    unsigned int elements;
    static nodo* copia(nodo* p) {
        if(!p) return nullptr;
        nodo* ret = new nodo(p->info, nullptr);
        nodo* aux = ret;
        while(p->next) {
            aux->next = new nodo(p->next->info, nullptr);
            aux = aux->next;
            p = p->next;
        }
        return ret;
    }
    static bool uguale(nodo* n1, nodo* n2) {
        if(!n1 && !n2) return true;
        if(!n1 || !n2) return false;
        return n1->info == n2->info && uguale(n1->next, n2->next);
    }

public:
    stack() : topPtr(nullptr) {}

    stack(T t = T(), int k = 0) {
        if(k <= 0) topPtr(nullptr);
        else {
            if(k > num) k = num;
            topPtr = new nodo(t);
            k--;
            elements++;
            while(k) {
                nodo* aux = new nodo(t,topPtr);
                topPtr = aux;
                k--;
                elements++;
            }
        }
    }

    stack(const stack& s) : topPtr(copia(s.topPtr)), elements(s.elements) {}
    stack& operator=(const stack& s){
        if(this != &s){
            delete topPtr;
            topPtr = copia(s.topPtr);
            elements = s.elements;
        }
        return *this;
    }

    ~stack() { delete topPtr;}
    
    bool isEmpty() const { return elements==0;}

    bool isFull() const { return elements==num;}

    unsigned int size() const { return elements;}

    // 8. Operatore esplicito di conversione ad int che ritorna la dimensione dello stack.
    operator int() const {
        return elements;
    }

    /*9. Metodo bool push(const T&): in una chiamata s.push(t), inserisce al top dello 
    stack s un nuovo elemento che memorizza il valore t se ci`o non provoca il superamento
    del limite num, altrimenti lascia lo stack s invariato. Ritorna true se l’inserimento
    `e avvenuto, false altrimenti.*/
    bool push(const T& t) {
        if(isFull()) {
            return false;
        } else {
            topPtr = new nodo(t,topPtr);
            elements++;
            return true;
        }
    }

    // 10. Metodo void pop(): in una chiamata s.pop() rimuove l’elemento al top dello stack
    // s non vuoto; se s `e vuoto lo lascia inalterato.
    void pop() {
        if(!isEmpty()) {
            nodo* temp = topPtr;
            temp->next = nullptr;
            topPtr = topPtr->next;
            delete temp;
        }
    }

    // 11. Metodo T top(): s.top() ritorna una copia dell’elemento al top dello stack s non vuoto;
    // se s `e vuoto, allora s.top() provoca undefined behaviour (da definirsi opportunamente).
    T top() {
        if(!isEmpty()) {
            nodo* temp = topPtr;
            topPtr = topPtr->next;
            temp->next = nullptr;
            return temp;
        }else {
            throw Vuoto();
        }
    }

    // 12. Metodo T bottom(): s.bottom() ritorna una copia dell’elemento al bottom dello stack s non vuoto;
    // se s `e vuoto, allora s.bottom() provoca undefined behaviour (da definirsi opportunamente).
    T bottom() {
        if(!isEmpty()) {
            nodo* temp = topPtr;
            while(temp->next) temp = temp->next;
            return temp->info;
        }else {
            throw Vuoto();
        }
    }

    // 13. Metodo bool search(const T&): in una chiamata s.search(t) ritorna true se il valore t 
    // occorre nello stack s, altrimenti ritorna false.
    bool search(const T& t) const {
        bool found = false;
        nodo* temp = topPtr;
        while(temp && !found){
            if(t == temp->info) found = true;
            temp = temp->next;
        }
        return found;
    }

    // 14. Metodo void flush() che svuota lo stack di invocazione.
    void flush() {
        delete topPtr;
    }

    // 15. Overloading dell’operatore di somma tra stack: s1 + s2 deve ritornare un nuovo stack ottenuto
    // impilando s2 sopra s1 (il bottom di s2 `e quindi sopra il top s1), sino all’eventuale raggiungimento
    // del massimo num di elementi.
    //NB1 sarebbe da mettere fuori dalla classe dichiarandola friend
    //NB2 "sino all’eventuale raggiungimento del massimo num di elementi" non so bene a cosa si riferisce
    //stack operator+(const stack& s1, const stack& s2){
    //    stack s3 = new stack(s2);
    //    while (s3.push(/*s1 END*/)){
    //        //NO PUSH mette in cima
    //    }
    //    return s3;
    //}

    // 16. Overloading dell’operatore di uguaglianza.
    //NB non so se controllare num elementi max
    bool operator==(const stack& d){
        if(elements != d.elements) return false;
        return uguale(topPtr, d.topPtr);
    }   

    
    class iterator {
    friend class stack<T, num>;
    private:
        nodo* punt;
    public:
        bool operator==(iterator i) const {
            return (punt == i.punt);
        }

        bool operator!=(iterator i) const {
            return !(punt == i.punt);
        }

        iterator operator++() { //prefisso
            if (punt) punt = punt->next;
            return *this;
        }

        T& operator*() const {
            return punt->info;
        }
    };

    iterator begin() const {
        iterator aux;
        aux.punt = topPtr;
        return aux;
    }

    iterator end() const {
        iterator aux;
        aux.punt = 0;
        return aux;
    }

    T operator[](iterator i) {
        return (i.punt)->info;

    }
};
unsigned int elements = 0;

// 17. Overloading dell’operatore di output.
template <class T, int num>
ostream& operator<<(ostream& os, const stack<T,num>& s){
    os << s.print();
    return os;
}

int main() {
    cout << "Hello world!";
    
    return 0;
}