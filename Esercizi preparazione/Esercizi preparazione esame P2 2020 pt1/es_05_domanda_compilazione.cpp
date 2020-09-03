#include <iostream>

using namespace std;

namespace ns { 
    class C { 
        private: 
            friend int f(); 
            int x; 
        public: 
            C(int n=0) : x(n) {}
    };
}

int f() { ns::C c; return c.x; }

int main() { 
    f();
}

// 1. non compila perchè f non può accedere alla parte privata di C
// C ha f() come amica ma nel suo namespace ns