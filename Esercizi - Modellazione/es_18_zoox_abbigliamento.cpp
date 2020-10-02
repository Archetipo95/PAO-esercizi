// ESERCIZIO SVOLTO IN AULA NELLE LEZIONI DEL 20-22/01/2015
//soluzione dell'esercizio "Zoox" (primo appello dell'a.a. 13/14) come discussa in aula nelle lezioni del 20-22/01/2015.
//Soluzione by Ranzato
//URL: http://pastebin.com/A8j355kf

#include<list>
#include<vector>
#include<string>
using namespace std;

class Capo {
private:
  string brand;
  int taglia;
public:
  Capo(string b = "noBrand", int t = 40): brand(b), taglia(t) {}

  // distruttore virtuale puro
  virtual ~Capo() =0;
  // in alternativa: virtual Capo* clone() const =0; con ridefinizioni nelle sottoclassi

  // uguaglianza polimorfa
  virtual bool operator==(const Capo& c) const {
    return brand==c.brand && taglia==c.taglia;
  }
  string getBrand() const {return brand;}
};
Capo::~Capo() {} // distruttore virtuale "puro" in versione standard

class Tshirt: public Capo {
private:
  bool corta; // true per manica corta
public:
  Tshirt(string b = "noBrand", int t=40, bool c = true): Capo(b,t), corta(c) {}
  
  virtual bool operator==(const Capo& c) const {
    return typeid(const Tshirt&)==typeid(c) && Capo::operator==(c) 
      && corta == (static_cast<const Tshirt&>(c)).corta;
  }
  bool getManicaL() const {return !corta;}
};

class Jeans: public Capo {
private:
  int fondo; // in cm
public:
  Jeans(string b = "noBrand", int t=40, int f = 20): Capo(b,t), fondo(f) {}
  
  virtual bool operator==(const Capo& c) const {
    return typeid(const Jeans&)==typeid(c) && Capo::operator==(c) 
      && fondo == (static_cast<const Jeans&>(c)).fondo;
  }
  int getFondo() const {return fondo;}
};

class Articolo {
  friend class Zoox;
private:
  Capo* c; // puntatore polimorfo
  int q;   // num articoli presenti in magazzino
public: 
  int getQuantita() const {return q;}
  
  void scarica() {
    if(q>1) {--q; return;}
    delete c; 
  }
  
  Articolo(Capo* p, int x=1): c(p), q(x) {}  
  
  bool uguale(const Capo& c) const {
    return *(this->c) == c;
  }
};

class Exception {
public:
  Exception(string s="") {} 
};

class Zoox {
private:
  list<Articolo> mag;
public:
  int giacenza(const Capo& c) const {
    list<Articolo>::const_iterator it = mag.begin();
    for( ; it != mag.end(); ++it) 
      if(it->uguale(c)) return it->getQuantita();
    return 0;
  } 
  
  vector<Jeans> getJeans(string m, int s, int f) const {
    vector<Jeans> v;
    list<Articolo>::const_iterator it = mag.begin();
    for( ; it != mag.end(); ++it) {
      Jeans* p = dynamic_cast<Jeans*>(it->c); 
      if(p && Jeans(m,s).Capo::operator==(*(it->c)) && p->getFondo() >= f) 
	v.push_back(*p);
    }
    return v;
  }
  
  void scarica(const Tshirt* pt) {
    list<Articolo>::iterator it = mag.begin();
    for( ; it != mag.end(); ++it) 
      if(it->uguale(*pt)) {it->scarica(); mag.erase(it); return;}
    throw Exception("assente");
  }
  
  void insert(const Tshirt& t, int x) {
    list<Articolo>::const_iterator it = mag.begin();
    for( ; it!= mag.end(); ++it) 
      if(typeid(*(it->c))==typeid(Tshirt)) {
	Tshirt* p  = static_cast<Tshirt*>(it->c);
	if(p->getManicaL() && t.getBrand()==p->getBrand())
	  throw Exception("presente"); 
      }
    mag.push_front(Articolo(const_cast<Tshirt*>(&t),x));
  }
  
};

int main() {}
