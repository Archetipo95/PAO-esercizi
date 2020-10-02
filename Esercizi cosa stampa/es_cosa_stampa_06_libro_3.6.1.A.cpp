// Programma 1
#include <iostream>

using namespace std;

class C {
public:
    string s;
    C(string x="1"):s(x) {}
    ~C() { cout << s << "Cd "; }
};

//funzione esterna passaggio del parametro per valore
C F(C p) { return p;}

//variabile globale
C w("3");

class D {
public:
    static C c; //campo dati statico
};

C D::c("4");

int main()
{
    cout << "Programma 1\n";
    C x("5"), y("6");
    D d;

    y=F(x); cout << "uno\n";

    C z=F(x); cout << "due\n";

    return 0;
}

// 2 distruttori invocati. uno per il parametro passato e uno per il parametro di ritorno
/*
Programma 1
5Cd 5Cd uno
5Cd 5Cd due
5Cd 5Cd 5Cd 4Cd 3Cd
*/
