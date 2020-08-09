// Programma 2
#include <iostream>

using namespace std;

class C {
    public:
    string s;
    C(string x="1"):s(x) {}
    ~C() { cout << s << "Cd "; }
};

//funzione esterna passaggio del parametro per riferimento
C F(C& p) { return p;}

//variabile globale
C w("3");

class D {
    public:
    static C c; //campo dati statico
};

C D::c("4");

int main()
{
    cout << "Programma 2\n";
    C x("5"), y("6");
    D d;

    y=F(x);
    cout << "uno\n";

    C z=F(x);
    cout << "due\n";

    return 0;
}

/*
Programma 2
5Cd uno
due
5Cd 5Cd 5Cd 4Cd 3Cd 
*/