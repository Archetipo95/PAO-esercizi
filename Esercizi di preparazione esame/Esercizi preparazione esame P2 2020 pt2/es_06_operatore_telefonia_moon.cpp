#include <iostream>
#include <vector>

using namespace std;

class Cliente {
private:
    unsigned int minuti, chiamate, sms, mb;
public:
    static const float costoMB;

    virtual float costoMeseCorrente() const = 0;
    virtual Cliente* clone() const = 0;
    virtual ~Cliente() = default;

    unsigned int getMinuti() const { return minuti;}
    unsigned int getChiamate() const { return chiamate;}
    unsigned int getSms() const { return sms;}
    unsigned int getMb() const { return mb;}
};
const float Cliente::costoMB(0.01);

class AlMinuto : public Cliente {
private:
    static const float scattoAllaRisposta, costoTelefonataAlMinuto, costoSMS;
public:
    virtual float costoMeseCorrente() const{
        return static_cast<float>(Cliente::getMinuti()) * costoTelefonataAlMinuto + 
        static_cast<float>(Cliente::getChiamate()) * scattoAllaRisposta + 
        static_cast<float>(Cliente::getSms()) * costoSMS + 
        static_cast<float>(Cliente::getMb()) * costoMB;
    }
    virtual AlMinuto* clone() const {
        return new AlMinuto(*this);
    }
};
const float AlMinuto::scattoAllaRisposta(0.15);
const float AlMinuto::costoTelefonataAlMinuto(0.2);
const float AlMinuto::costoSMS(0.1);

class Abbonamento : public Cliente {
private:
    float costoFissoMensile;
    unsigned int sogliaMinuti;
public:
    static const float costoMinutoOltreSoglia;
    virtual float costoMeseCorrente() const {
        return costoFissoMensile + (sogliaMinuti < Cliente::getMinuti() ?
        static_cast<float>(Cliente::getMinuti() - sogliaMinuti) * costoMinutoOltreSoglia : 0) +
        static_cast<float>(Cliente::getMb()) * costoMB;
    }
    virtual Abbonamento* clone() const {
        return new Abbonamento(*this);
    }
    unsigned int getSogliaMinuti() const { return sogliaMinuti;}
};
const float Abbonamento::costoMinutoOltreSoglia(0.3);

class SedeMoon {
private:
    vector<Cliente*> vClienti;
public:
    void aggiungiCliente(const Cliente& c) {
        vClienti.push_back(c.clone());
    }
    double incassoMensileCorrente() const {
        double tot = 0;
        for(auto it = vClienti.begin(); it != vClienti.end(); ++it){
            tot += (*it)->costoMeseCorrente();
        }
        return tot;
    }
    int numClientiAbbonatiOltreSoglia() const {
        int somma = 0;
        for(auto it = vClienti.begin(); it != vClienti.end(); ++it){
            Abbonamento* b = dynamic_cast<Abbonamento*>(*it);
            if(b && b->getMinuti() > b->getSogliaMinuti()) ++somma;
        }
        return somma;
    }
    vector<AlMinuto> alMinutoSMS(int x) const {
        vector<AlMinuto> v;
        for(auto it = vClienti.begin(); it != vClienti.end(); ++it){
            auto* p = dynamic_cast<AlMinuto*>(*it);
            if(p && p->getSms() > x) v.push_back(*(p->clone()));
        }
        return v;
    }
};

int main() {
    cout << "Hello World!";

    return 0;
}