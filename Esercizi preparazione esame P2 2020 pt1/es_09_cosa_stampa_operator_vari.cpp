class A { 
    friend class C; 
    private: 
        int k; 
    public: 
        A(int x=2): k(x) {} 
        void m(int x=3) {k=x;}
};
class C { 
    private: 
        A* p; 
        int n; 
    public: 
        C(int k=3) {if (k>0) {p = new A[k]; n=k;}} 
        A* operator->() const {return p;} 
        A& operator*() const {return *p;} 
        A* operator+(int i) const {return p+i;} 
        void F(int k, int x) {if (k<n) p[k].m(x);} 
        void stampa() const { for(int i=0; i<n; i++) cout << p[i].k << " ";} 
};

int main() { 
    C c1; c1.F(2,9); 
    C c2(4); c2.F(0,8); 
    *c1=*c2;

    (c2+3)->m(7); c1.stampa(); cout << "UNO\n"; 
    c2.stampa(); cout << "DUE\n"; 
    c1=c2; 
    *(c2+1)=A(3);
    c1->m(1); 
    *(c2+2)=*c1; 
    c1.stampa(); cout << "TRE\n"; 
    c2.stampa(); cout << "QUATTRO";
}

/*
8 2 9 UNO                                                                                                                                      
8 2 2 7 DUE                                                                                                                                    
1 3 1 7 TRE                                                                                                                                    
1 3 1 7 QUATTRO
*/