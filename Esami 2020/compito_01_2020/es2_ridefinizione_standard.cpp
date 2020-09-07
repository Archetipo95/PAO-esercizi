// Scrivere ridefinizioni standard

class B { 
private:
    vector<bool>* ptr;
    virtual void m() const=0;
};

class D: public B { 
    private: int x;
};

class F: public D { 
private: 
    list<int*> l; 
    int& ref; 
    double* p; 
public: 
    void m() const {}
    
    F(F f): D(f), l(f.l), ref(f.ref), p(f.p) {} // ridefinizione del costruttore di F 
    
    F(const F& f): D(f), l(f.l), ref(f.ref), p(f.p) {} // ridefinizione del costruttore di copia di F
    
    F& operator=(const F& f) {  // ridefinizione del costruttore di assegnazione di F (NB non si fanno controlli in quello standard)
        D::operator=(f);
        l = f.l;
        ref = f.ref;
        p = f.p;

        return *this;
    }
};