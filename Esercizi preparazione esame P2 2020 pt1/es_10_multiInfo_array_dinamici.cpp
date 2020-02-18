#include "iostream"

using namespace std;

template<class T, unsigned int size> class Array;
template<class T, unsigned int size> ostream& operator<<(ostream&, const Array<T, size>&);
template<class T, unsigned int size>
class Array {
    friend ostream& operator<< <T, size>(std::ostream&, const Array<T, size>&);
private:
    class MultiInfo {
    public:
        T info;
        unsigned int times;
        MultiInfo(const T& t = T(), int mult = 0) : info(t), times(mult) {};
        bool operator!=(const MultiInfo& m) const {
            return info != m.info || times != m.times;
        }
    };
    MultiInfo* elements;
public:
    Array(const T& element, int times) : elements(new MultiInfo[size]) {
        for(unsigned int i=0; i<size; i++) {
            elements[i] = MultiInfo(element, times < 0 ? 0 : times);
        }
    }
    Array(const Array& ar) {
        elements = new MultiInfo[size];
        for(unsigned int i=0; i<size; i++) {
            elements[i] = MultiInfo(ar.elements[i].info, ar.elements[i].times);
        }
    }
    ~Array() { delete[] elements;}
    Array& operator=(const Array& ar) {
        delete[] elements;
        elements = new MultiInfo[size];
        for(unsigned int i=0; i<size; i++) {
            elements[i] = MultiInfo(ar.elements[i].info, ar.elements[i].times);
        }
        return *this;
    }
    T* operator[](int pos) {
        return pos < size && pos>-1 ? &(elements[pos].info) : nullptr;
    }
    const T* operator[](int pos) const {
        return pos < size && pos>-1 ? &(elements[pos].info) : nullptr;
    }
    int occorrenze(const T& toFind) const {
        int tot = 0;
        for(unsigned int i = 0; i<size; i++) if(elements[i].info == toFind) tot+= elements[i].times;
        return tot;
    }
    bool operator==(const Array&a) const {
        for(unsigned int i =0 ; i<size;++i) if(elements[i] != a.elements[i]) return false;
        return true;
    }
};

template <class T, unsigned int size>
ostream& operator<<(ostream& os, const Array<T, size>& a) {
    for(unsigned int i = 0; i<size; i++) os<<a.elements[i].info<<" occorre "<<a.elements[i].times<<" volte"<<std::endl;
    return os;
}

int main() {

    cout << "Hello world!";

    return 0;
}
