// Assumere che abs sia una classe astratta. Definire un template di funzione bool Fun(Tq*, T2&), dove T1 e T2 sono
// parametri di tipo, con il seguente comportamento. Si considera un istanza implicita Fun(ptr, ref) dove si suppone che i parametri
// di tipo T1 e T2 siano istanziati a tipi polimorfi. Allora Fun(ptr, ref) ritorna true se e solo se valgono le seguenti due condizioni:

// 1. I parametri di tipo T1 e T2 sono istanziati allo stesso tipo
// 2. Siano D1* il tipo dinamico di ptr e D2& il tipo dinamico di ref, allora:
//    (i) D1 e D2 sono lo stesso tipo
//   (ii) Questo tipo è un sottotipo proprio della classe Abs

// Soluzione

template <class T1, class T2>
bool Fun(T1* ptr, T2& ref) const {
     return ( typeid(T1) == typeid(T2) ) && 
            ( typeid(*ptr) == typeid(ref) ) &&
            ( dynamic_cast<Abs*>(ptr) );
}