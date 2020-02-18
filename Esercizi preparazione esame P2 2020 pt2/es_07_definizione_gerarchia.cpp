class A{
public:
    virtual ~A() = default;
};

class B: public A{
public:
    ~B() = 0;
};
B::~B() = default;

class C: public B{};

class D{
protected:
    D() = default;
};

class E: public D{
    E& operator=(const E& e){
        D::operator=(e);
        return *this;
    }
};