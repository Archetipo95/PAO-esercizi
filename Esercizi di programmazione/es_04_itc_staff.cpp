/*
Si consideri il seguente modello concernente gli specialisti ICT (Information and Communication Technology) che lavorano per la internet company Amazonia c. (A) Definire la seguente gerarchia di classi.
1. Definire una classe base polimorfa astratta ICTstaff i cui oggetti rappresentano uno specialista ICT che lavora in Amazonia. Ogni ICTStaff `e caratterizzato da uno stipendio fisso mensile contrattato individualmente, dal titolo di laurea posseduto e dal possedere una laurea triennale o magistrale, dove il titolo di laurea `e un valore del seguente tipo enumerativo: enum Laurea {Informatica, Ingegneria, Altro}; La classe `e astratta in quanto prevede i seguenti metodi virtuali puri:
• un metodo di “clonazione” con l’usuale contratto di “costruzione di copia polimorfa”. • un metodo double salary() con il seguente contratto: p->salary() ritorna lo stipendio mensile per il mese corrente di *p.
2. Definire una classe concreta SwEngineer derivata da ICTStaff i cui oggetti rappresentano un ingegnere software che lavora in Amazonia. Ogni SwEngineer `e caratterizzato dall’occuparsi di sicurezza oppure no. La classe SwEngineer implementa i metodi virtuali puri di ICTStaff come segue:
• implementazione del metodo di clonazione specifica del tipo SwEngineer;
• per ogni puntatore p a SwEngineer, l’invocazione p->salary() ritorna lo stipendio fisso mensile di *p, aumentato di 500 e se *p si occupa di sicurezza software.
3. Definire una classe concreta HwEngineer derivata da ICTStaff i cui oggetti rappresentano un ingegnere hardware che lavora in Amazonia. Ogni HwEngineer `e caratterizzato dal numero di trasferte di lavoro effettuate nel mese corrente. La classe HwEngineer implementa i metodi virtuali puri di ICTStaff come segue:
• implementazione del metodo di clonazione specifica del tipo HwEngineer; • per ogni puntatore p a HwEngineer, l’invocazione p->salary() ritorna lo stipendio fisso mensile di *p, aumentato di 300 e per ogni trasferta di lavoro effettuata da *p nel mese corrente.
(B) Definire una classe Amazonia i cui oggetti rappresentano gli specialisti ICT che correntemente lavorano in Amazonia. La classe Amazonia deve soddisfare le seguenti specifiche:
4. E` definita una classe annidata SmartP i cui oggetti rappresentano un puntatore polimorfo smart a ICTStaff.
• La classe annidata SmartP deve essere dotata di un costruttore SmartP(ICTstaff*) con il seguente comportamento: SmartP(q) costruisce un oggetto SmartP il cui puntatore polimorfo punta ad una copia dell’oggetto *q.
• La classe SmartP ridefinisce costruttore di copia profonda, assegnazione profonda e distruttore profondo. • La classe SmartP ridefinisce gli operatori di dereferenziazione * e di accesso mediante freccia -> nell’usuale modo che permetta di usare i puntatori smart di SmartP come puntatori ordinari.
5. Un oggetto di Amazonia `e caratterizzato da un contenitore di oggetti di tipo SmartP che memorizza i puntatori smart a tutti e soli gli specialisti ICT che lavorano in Amazonia.
6. La classe Amazonia rende disponibili i seguenti metodi:
6.1 Un metodo bool insert(SwEngineer*, unsigned int) con il seguente comportamento: una invocazione am.insert(p,k) inserisce un puntatore smart ad una copia di *p nel contenitore di am se il numero di ingegneri software di Amazonia che si occupano di sicurezza `e minore di k, altrimenti non viene effettuato l’inserimento; se l’inserimento viene effettuato allora si ritorna true, altrimenti false.
6.2 Un metodo vector<HwEngineer> fire(double) con il seguente comportamento: una invocazione am.fire(s) elimina dal contenitore di am tutti gli specialisti ICT di Amazonia che hanno uno stipendio mensile maggiore di s; inoltre ritorna un vector di HwEngineer che contiene tutti e soli gli ingegneri hardware eliminati.
6.3 Un metodo vector<SwEngineer*> masterInf() con il seguente comportamento: una invocazione am.masterInf() ritorna un vector di puntatori ordinari a SwEngineer contenente tutti e soli gli ingegneri software di Amazonia in possesso di una Laurea Magistrale in Informatica.

*/

//PROBABILE CHE SIA SBAGLIATO 

#include "iostream"
#include "vector"
#include "list"

using namespace std;

enum Laurea {Informatica, Ingegneria, Altro};

class ICTstaff {
private:
    double stipendioMensile;
    Laurea l;
    bool magistrale;
protected:
    double getFisso() const {          // perche protected ?
        return stipendioMensile;
    }
public:
    virtual ICTstaff* clone() const =0;
    virtual double salary() const =0;
    virtual ~ICTstaff() =default;
    Laurea getLaurea() const{
        return l;
    }
    bool isMagistrale() const{
        return magistrale;
    }
};

class SwEngineer: public ICTstaff {
private:
    bool workInSecurity;
    static double extra;
public:
    virtual SwEngineer* clone() const { 
        return new SwEngineer(*this);
    }
    virtual double salary() const {
        return workInSecurity ? getFisso()+extra : getFisso(); // better ? return getFisso() + (workInSecurity ? extra : 0); 
    }
    bool isSecurity() const{
        return workInSecurity;
    }
};
double SwEngineer::extra = 500.0;

class HwEngineer: public ICTstaff {
private:
unsigned int trasferte;
static double extra;
public:
    virtual HwEngineer* clone() const {
        return new HwEngineer(*this);
    }
    virtual double salary() const {
        return getFisso()+extra*trasferte;
    }
};
double HwEngineer::extra = 300.0;

class Amazonia {
private:
    class SmartP {
    public:
        ICTstaff* p;
        SmartP(ICTstaff* q):p(q->clone()) {}
        SmartP(const SmartP& s):p(s.p->clone()) {}
        SmartP& operator=(SmartP& s){
            if(this != &s) {
                if(p) delete p;
                p= s.p != nullptr ? s.p->clone() : nullptr;
            }/*
Si consideri il seguente modello concernente gli specialisti ICT (Information and Communication Technology) che lavorano per la internet company Amazonia c. (A) Definire la seguente gerarchia di classi.
1. Definire una classe base polimorfa astratta ICTstaff i cui oggetti rappresentano uno specialista ICT che lavora in Amazonia. Ogni ICTStaff `e caratterizzato da uno stipendio fisso mensile contrattato individualmente, dal titolo di laurea posseduto e dal possedere una laurea triennale o magistrale, dove il titolo di laurea `e un valore del seguente tipo enumerativo: enum Laurea {Informatica, Ingegneria, Altro}; La classe `e astratta in quanto prevede i seguenti metodi virtuali puri:
• un metodo di “clonazione” con l’usuale contratto di “costruzione di copia polimorfa”. • un metodo double salary() con il seguente contratto: p->salary() ritorna lo stipendio mensile per il mese corrente di *p.
2. Definire una classe concreta SwEngineer derivata da ICTStaff i cui oggetti rappresentano un ingegnere software che lavora in Amazonia. Ogni SwEngineer `e caratterizzato dall’occuparsi di sicurezza oppure no. La classe SwEngineer implementa i metodi virtuali puri di ICTStaff come segue:
• implementazione del metodo di clonazione specifica del tipo SwEngineer;
• per ogni puntatore p a SwEngineer, l’invocazione p->salary() ritorna lo stipendio fisso mensile di *p, aumentato di 500 e se *p si occupa di sicurezza software.
3. Definire una classe concreta HwEngineer derivata da ICTStaff i cui oggetti rappresentano un ingegnere hardware che lavora in Amazonia. Ogni HwEngineer `e caratterizzato dal numero di trasferte di lavoro effettuate nel mese corrente. La classe HwEngineer implementa i metodi virtuali puri di ICTStaff come segue:
• implementazione del metodo di clonazione specifica del tipo HwEngineer; • per ogni puntatore p a HwEngineer, l’invocazione p->salary() ritorna lo stipendio fisso mensile di *p, aumentato di 300 e per ogni trasferta di lavoro effettuata da *p nel mese corrente.
(B) Definire una classe Amazonia i cui oggetti rappresentano gli specialisti ICT che correntemente lavorano in Amazonia. La classe Amazonia deve soddisfare le seguenti specifiche:
4. E` definita una classe annidata SmartP i cui oggetti rappresentano un puntatore polimorfo smart a ICTStaff.
• La classe annidata SmartP deve essere dotata di un costruttore SmartP(ICTstaff*) con il seguente comportamento: SmartP(q) costruisce un oggetto SmartP il cui puntatore polimorfo punta ad una copia dell’oggetto *q.
• La classe SmartP ridefinisce costruttore di copia profonda, assegnazione profonda e distruttore profondo. • La classe SmartP ridefinisce gli operatori di dereferenziazione * e di accesso mediante freccia -> nell’usuale modo che permetta di usare i puntatori smart di SmartP come puntatori ordinari.
5. Un oggetto di Amazonia `e caratterizzato da un contenitore di oggetti di tipo SmartP che memorizza i puntatori smart a tutti e soli gli specialisti ICT che lavorano in Amazonia.
6. La classe Amazonia rende disponibili i seguenti metodi:
6.1 Un metodo bool insert(SwEngineer*, unsigned int) con il seguente comportamento: una invocazione am.insert(p,k) inserisce un puntatore smart ad una copia di *p nel contenitore di am se il numero di ingegneri software di Amazonia che si occupano di sicurezza `e minore di k, altrimenti non viene effettuato l’inserimento; se l’inserimento viene effettuato allora si ritorna true, altrimenti false.
6.2 Un metodo vector<HwEngineer> fire(double) con il seguente comportamento: una invocazione am.fire(s) elimina dal contenitore di am tutti gli specialisti ICT di Amazonia che hanno uno stipendio mensile maggiore di s; inoltre ritorna un vector di HwEngineer che contiene tutti e soli gli ingegneri hardware eliminati.
6.3 Un metodo vector<SwEngineer*> masterInf() con il seguente comportamento: una invocazione am.masterInf() ritorna un vector di puntatori ordinari a SwEngineer contenente tutti e soli gli ingegneri software di Amazonia in possesso di una Laurea Magistrale in Informatica.

*/

//PROBABILE CHE SIA SBAGLIATO 

#include "iostream"
#include "vector"
#include "list"

using namespace std;

enum Laurea {Informatica, Ingegneria, Altro};

class ICTstaff {
private:
    double stipendioMensile;
    Laurea l;
    bool magistrale;
protected:
    double getFisso() const {          // perche protected ?
        return stipendioMensile;
    }
public:
    virtual ICTstaff* clone() const =0;
    virtual double salary() const =0;
    virtual ~ICTstaff() =default;
    Laurea getLaurea() const{
        return l;
    }
    bool isMagistrale() const{
        return magistrale;
    }
};

class SwEngineer: public ICTstaff {
private:
    bool workInSecurity;
    static double extra;
public:
    virtual SwEngineer* clone() const { 
        return new SwEngineer(*this);
    }
    virtual double salary() const {
        return workInSecurity ? getFisso()+extra : getFisso(); // better ? return getFisso() + (workInSecurity ? extra : 0); 
    }
    bool isSecurity() const{
        return workInSecurity;
    }
};
double SwEngineer::extra = 500.0;

class HwEngineer: public ICTstaff {
private:
unsigned int trasferte;
static double extra;
public:
    virtual HwEngineer* clone() const {
        return new HwEngineer(*this);
    }
    virtual double salary() const {
        return getFisso()+extra*trasferte;
    }
};
double HwEngineer::extra = 300.0;

class Amazonia {
private:
    class SmartP {
    public:
        ICTstaff* p;
        SmartP(ICTstaff* q):p(q->clone()) {}
        SmartP(const SmartP& s):p(s.p->clone()) {}
        SmartP& operator=(SmartP& s){
            if(this != &s) {
                if(p) delete p;
                p= s.p != nullptr ? s.p->clone() : nullptr;
            }
            return *this;
        }
        ~SmartP(){
            if(p) delete p; //serve if ?
        }
        ICTstaff& operator*(){return *p;}
        ICTstaff* operator->(){return p;}
    };
    std::list<SmartP> sp;
    
public:
    bool insert(SwEngineer* p, unsigned int k){
        int num=0;
        SwEngineer* q= nullptr; //NB
        for(auto it = sp.begin(); it != sp.end() && num<k; ++it){ //uso di auto?
            q=dynamic_cast<SwEngineer*>(it->p); // NB SENZA *
            if(q && q->isSecurity()) num++;
        }
        if(num<k){sp.push_back(p); return true;}
        return false;
    }

    vector<HwEngineer> fire(double s) {
        std::vector<HwEngineer> v;
        HwEngineer* q = nullptr;
        for(auto it = sp.begin(); it != sp.end(); ++it){
            if((*it)->salary() > s) {   //NB come accedere a salary
                q=dynamic_cast<HwEngineer*>(it->p); //NB come accedere ad ITCStaff
                if(q) v.push_back(*q); //NB *q
                // delete it->p;  NB: non serve perche' ~SmartP() e' profondo
                it=sp.erase(it); --it; //IN CHE SENSO??? NON CAPISCO
            }
        }
        return v;
    }

    vector<SwEngineer*> masterInf(){
        vector<SwEngineer*> v;
        SwEngineer* q= nullptr; //NB
        for(auto it = sp.begin(); it != sp.end(); ++it){
            q = dynamic_cast<SwEngineer*>((it)->p); // it senza *
            if(q && q->getLaurea()==1 && q->isMagistrale()){
                v.push_back(q->clone());
            }
        }
        return v;
    }
};

int main() {
    cout << "Hello world!";
    return 0;
}
            return *this;
        }
        ~SmartP(){
            if(p) delete p; //serve if ?
        }
        ICTstaff* operator*(){return p;} // NB * e return p coz p is *
        ICTstaff& operator->(){return *p;} // NB & e return *p
    };
    std::list<SmartP> sp;
    
public:
    bool insert(SwEngineer* p, unsigned int k){
        int num=0;
        SwEngineer* q= nullptr; //NB
        for(auto it = sp.begin(); it != sp.end() && num<k; ++it){ //uso di auto?
            q=dynamic_cast<SwEngineer*>(it->p); // NB SENZA *
            if(q && q->isSecurity) num++;
        }
        if(num<k){sp.push_back(p); return true;}
        return false;
    }

    vector<HwEngineer> fire(double s) {
        std::vector<HwEngineer> v;
        HwEngineer* q = nullptr;
        for(auto it = sp.begin(); it != sp.end(); ++it){
            if((*it)->salary() > s) {   //NB come accedere a salary
                q=dynamic_cast<HwEngineer*>(it->p) //NB come accedere ad ITCStaff
                if(q) v.push_back(*q); //NB *q
                // delete it->p;  NB: non serve perche' ~SmartP() e' profondo
                it=sp.erase(it); --it; //IN CHE SENSO??? NON CAPISCO
            }
        }
        return v;
    }

   /* std::vector<SwEngineer*> masterInf(){
        std::vector<SwEngineer*> v;
        SwEngineer* q= nullptr; //NB
        for(auto it = sp.begin(); it != sp.end() && num<k; ++it){
            q = dynamic_cast<SwEngineer*>((it)->p)  // it senza *
            if(q && q.getLaurea()==1 && q.isMagistrale()){
                v.push_back(*q);
            }
            //oppure ere meglio? if(q && (*it)->getLaurea()==Informatica && (*it)->isMaster()) v.push_back(q);
        }
        return v;
    }*/
};

int main() {
    cout << "Hello world!";
    return 0;
}