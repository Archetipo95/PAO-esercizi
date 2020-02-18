#include <iostream>
#include <vector>

using namespace std;

class Prodotto {
private:
    double prezzo;
public:
    Prodotto(double p=0):prezzo(p){}
    double getPrezzo()const {return prezzo;}
};

class Cliente{
    friend class ClienteFedele;
private:
    vector<Prodotto*> carello;
public:
    virtual ~Cliente(){}
    virtual double spesaTotale() const{
        double tot = 0;
        for(vector<Prodotto*>::const_iterator it = carello.begin(); it != carello.end(); ++it){
            tot += (*it)->getPrezzo();
        }
        return tot;
    }
};

class RitiroPremio{
public:
    RitiroPremio(){cout<<"Premio da ritirare";}
};

class ClienteFedele: public Cliente {
private:
    int saldoPunti;
    static int sogliaPunti;
    static double percSconto;
public:
    ClienteFedele(int p=0):saldoPunti(p){}
    virtual double spesaTotale() const {
        double tot = 0;
        for(vector<Prodotto*>::const_iterator it = carello.begin(); it != carello.end(); ++it){
            tot += (*it)->getPrezzo()-(*it)->getPrezzo()*percSconto;
        }
        return tot;
    }
    void accreditaPunti(int n){
        saldoPunti+=n;
        if(saldoPunti>=sogliaPunti){
            saldoPunti -=sogliaPunti;
            throw RitiroPremio();
        }
    }
    int getPunti() const {return saldoPunti;}
};
int ClienteFedele::sogliaPunti(100);
double ClienteFedele::percSconto(0.05);

class GestioneGiornaliera{
private:
    vector<Cliente*> listaClienti;
public:
    double chiudiCassa() {
        double tot = 0;
        for(vector<Cliente*>::iterator it = listaClienti.begin(); it != listaClienti.end(); ++it){
            ClienteFedele* cf = dynamic_cast<ClienteFedele*>(*it);
            if(cf){
                tot += cf->spesaTotale();
                int punti = cf->spesaTotale()/10;
                cf->accreditaPunti(punti);
            }else{
                tot+= (*it)->spesaTotale();
            }
        }
        return tot;
    }


};

int main() {
    cout << "hello world";

    return 0;
}