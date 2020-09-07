// Esercizio vero o falso

class A {
public:
    virtual ~A() {}
};

class B: public A {
public:
    virtual bool m() const =0;
};

class C: public B {
public:
    bool m() const {return true;}
};

class D: virtual public A {
protected:
    D() {}
};

class E: public D {
public:
    E& operator=(const E& x) {
        D::operator=(x);
        return *this;
    }
};

/*
1. A è una classe base polimorfa A. Vero
2. Il costruttore di copia di A non è pubblicamente disponibile. Falso
3. A è una classe base astratta. Falso  // non ha metodi virtuali puri
4. Il costruttore senza parametri di A è polimorfo. Falso  // non ha senso
5. B è una classe derivata astratta. Vero
6. B è una classe polimorfa. Vero
7. L’assegnazione di B è virtuale pura. Falso
8. B è una classe virtuale pura. Falso  // non ha senso
9. C è una sottoclasse concreta di B. Vero
10. C è una classe polimorfa. Vero
11. C è una classe che non permetta la costruzione pubblica dei suoi oggetti. Falso
12. Nella classe C il metodo m() è overloaded. Falso
13. D è una classe che non permette di costruire pubblicamente i suoi oggetti. Vero
14. D è una classe che permette la costruzione di oggetti di D che siano sottooggetti di altri oggetti. Vero
15. Se d è un oggetto di tipo D allora in un main() la chiamata d->m() non compila. Falso   // errore -> 
16. D ha il costruttore di copia protetto. Falso
17. E è una classe derivata indirettamente da D. Falso
18. L’assegnazione ridefinita di E ha comportamento identico a quello dell’assegnazione standard di E. Vero
19. Se c è un oggetto di tipo C allora in un main lo statement E e(c); compila correttamente. Falso
20. E è una classe derivata indirettamente da D. Falso
21. Se d è un oggetto di tipo D e c è un oggetto di tipo C allora in un main lo statement c=e compila correttamente. Vero  // vera se e = d
*/