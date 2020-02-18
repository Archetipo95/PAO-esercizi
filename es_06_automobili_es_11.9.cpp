/*
Esercizio 11.9. 

Definire una superclasse Auto i cui oggetti rappresentano generiche
automobili e due sue sottoclassi Benzina e Diesel, i cui oggetti
rappresentano automobili alimentate, rispettivamente, a benzina e a
diesel (ovviamente non esistono automobili non alimentate e si assume
che ogni auto è o benzina o diesel). Ci interesserà l’aspetto fiscale
delle automobili, cioè il calcolo del bollo auto. Queste classi devono
soddisfare le seguenti specifiche:

– Ogni automobile è caratterizzata dal numero di cavalli fiscali. La
  tassa per cavallo fiscale è unica per tutte le automobili (sia
  benzina che diesel) ed è fissata in 5 euro. La classe Auto fornisce
  un metodo tassa() che ritorna la tassa di bollo fiscale per
  l’automobile di invocazione.

– La classe Diesel è dotata (almeno) di un costruttore ad un parametro
  intero x che permette di creare un’auto diesel di x cavalli
  fiscali. Il calcolo del bollo fiscale per un’auto diesel viene fatto
  nel seguente modo: si moltiplica il numero di cavalli fiscali per la
  tassa per cavallo fiscale e si somma una addizionale fiscale unica
  per ogni automobile diesel fissata in 100 euro.

– Un’auto benzina può soddisfare o meno la normativa europea Euro6. La
  classe Benzina è dotata di (almeno) un costruttore ad un parametro
  intero x e ad un parametro booleano b che permette di creare un’auto
  benzina di x cavalli fiscali che soddisfa Euro6 se b vale true
  altrimenti che non soddisfa Euro6. Il calcolo del bollo fiscale per
  un’auto benzina viene fatto nel seguente modo: si moltiplica il
  numero di cavalli fiscali per la tassa per cavallo fiscale; se
  l’auto soddisfa Euro6 allora si detrae un bonus fiscale unico per
  ogni automobile benzina fissato in 50 euro, altrimenti non vi è
  alcuna detrazione.


Si definisca inoltre una classe ACI i cui oggetti rappresentano delle
filiali ACI addette all’incasso dei bolli auto. Ogni oggetto ACI è
caratterizzato da un array di puntatori ad auto che rappresenta le
automobili gestite dalla filiale ACI. La classe ACI fornisce un metodo
incassaBolli() che ritorna la somma totale dei bolli che devono pagare
tutte le auto gestite dalla filiale di invocazione.
*/

class Auto {
private:
  unsigned int cvf;
  static double tassaPerCF;
public:
  Auto(unsigned int x): cvf(x) {}
  virtual double tassa() const =0;
  unsigned int getCVF() const {return cvf;}
  virtual ~Auto() {} 
  static double getTassaPerCF() {return tassaPerCF;}
};
double Auto::tassaPerCF = 5.0;

class Diesel: public Auto {
private:
  static double addizionaleDiesel;
public:
  Diesel(unsigned int cf=0): Auto(cf) {}
  double tassa() const {
    return getCVF()*getTassaPerCF() + addizionaleDiesel;
  }
};
double Diesel::addizionaleDiesel = 100.0;

class Benzina: public Auto {
private:
  bool euro6;
  static double bonusEuro6;
public:
  Benzina(unsigned int cf=0, bool e6=true): Auto(cf), euro6(e6) {}
  double tassa() const {
    return euro6 ? 
      getCVF()*getTassaPerCF() - bonusEuro6 :
      getCVF()*getTassaPerCF();
  } 
};
double Benzina::bonusEuro6 = 50.0;

class ACI {
private:
  Auto** veicoli;
  unsigned int size;
public:
  double incassaBolli() const {
    double i=0.0;
    for(int x=0; x<size; ++x) 
      i += veicoli[x]->tassa();
    return i;
  }
};