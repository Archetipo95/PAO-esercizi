class B {
  private:
    vector<bool>* ptr;
    virtual void m() =0;
};

class D: public B {
  private:
    int x;
};

class E: public D {
  private:
    list<int*> l;
    int& ref;
    double* p;
  public:
    void m() {}

    // Ridefinire il costruttore di copia in modo che il suo comportamento
    // sia identico a quello standard

    // Soluzione
    E(const E& e) : D(e), l(e.l), ref(e.ref), p(e.p) {}
};