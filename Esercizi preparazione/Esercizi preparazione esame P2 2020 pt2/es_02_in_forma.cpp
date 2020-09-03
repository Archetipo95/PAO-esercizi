#include <iostream>
#include <vector>

using namespace std;

// PUNTO A

class Workout {
private:
    double durata;      //in minuti
public:
    virtual Workout* clone() const =0;
    virtual int calorie() const =0;
    virtual ~Workout() {}
    double getDurata() const {return durata;}
};

class Corsa: public Workout {
private:
    double distanza;    //in km
    static unsigned int calorieBase;
public:
    Corsa* clone() const {return new Corsa(*this);}
    int calorie() const {return (calorieBase*distanza*distanza)/getDurata();}
    double getDistanza() const {return distanza;}
};
unsigned int Corsa::calorieBase(500);

class Nuoto: public Workout {
private:
    int vasche;    //numero vasche
public:
    Nuoto* clone() const =0;
    int calorie() const =0;
    int getVasche() const {return vasche;}
};

class StileLibero: public Nuoto {
private:
    static unsigned int sogliaVasche, lowCalorie, highCalorie;
public:
    StileLibero* clone() const { return new StileLibero(*this);}
    int calorie() const { return getDurata()>=sogliaVasche ? lowCalorie*getVasche() : highCalorie*getVasche();}
};
unsigned int StileLibero::sogliaVasche(10);
unsigned int StileLibero::lowCalorie(35);
unsigned int StileLibero::highCalorie(40);

class Dorso: public Nuoto {
private:
    static unsigned int sogliaVasche, lowCalorie, highCalorie;
public:
    Dorso* clone() const { return new Dorso(*this);}
    int calorie() const { return getDurata()>=sogliaVasche ? lowCalorie*getVasche() : highCalorie*getVasche();}
};
unsigned int Dorso::sogliaVasche(15);
unsigned int Dorso::lowCalorie(30);
unsigned int Dorso::highCalorie(15);

class Rana: public Nuoto {
private:
    static unsigned int baseCalorie;
public:
    Rana* clone() const { return new Rana(*this);}
    int calorie() const { return baseCalorie*getVasche();}
};
unsigned int Rana::baseCalorie(25);

// PUNTO B

class InForma {
private:
    vector<const Workout*> allenamenti;
public:
    //vector<const Workout*>::const_iterator al posto di auto
    vector<Nuoto*> vasche(int v) const {
        const Nuoto* p = nullptr;
        vector<Nuoto*> ret;
        for(auto cit = allenamenti.begin(); cit != allenamenti.end(); ++cit){
            p = dynamic_cast<const Nuoto*>(*cit);
            if(p && p->getVasche()>v) ret.push_back(p->clone());
        }
        return ret;
    }

    vector<Workout*> calorie(int x) const {
        const Rana* ra = nullptr;
        vector<Workout*> ret;
        for(auto cit = allenamenti.begin(); cit != allenamenti.end(); ++cit){
            ra = dynamic_cast<const Rana*>(*cit);
            if(!ra && (*cit)->calorie()>x) ret.push_back((*cit)->clone());
        }
        return ret;
    }

    void removeNuoto() {
        const Nuoto* p = nullptr;
        int maxCal = 0;
        for(auto cit = allenamenti.begin(); cit != allenamenti.end(); ++cit){
            p = dynamic_cast<const Nuoto*>(*cit);
            if(p && p->calorie()>maxCal) maxCal = p->calorie();
        }
        for(auto cit = allenamenti.begin(); cit != allenamenti.end(); ++cit){
            p = dynamic_cast<const Nuoto*>(*cit);
            if(p && p->calorie()==maxCal) allenamenti.erase(cit);
        }
    }
};

int main()
{
    cout<<"Hello World";

    return 0;
}
