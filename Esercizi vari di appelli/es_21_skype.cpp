//
// Created by Alberto Sinigaglia on 04/02/2020.
//

#ifndef LIBRERIELEZIONI_ALL_H
#define LIBRERIELEZIONI_ALL_H

#include <vector>
#include <list>
#include <string>

class Nome{
private:
    std::string nome;
public:
    const std::string& getNome() const{
        return nome;
    }
    bool operator==(const Nome& n) const{ return nome == n.nome;}
};
class Numero{
private:
    std::string numero;
public:
    const std::string& getNumero() const{
        return numero;
    }
    bool operator==(const Numero& n)const{
        return numero == n.numero;
    }
};



class Contatto{
private:
    Nome nome;
public:
    virtual ~Contatto() = default;
    virtual Contatto* clone() const = 0;
    virtual bool operator== (const Contatto&) const = 0;
    const Nome& getNome() const{
        return nome;
    }
};
class Telefonico : public Contatto{
private:
    Numero numero;
    unsigned int num_sms;
    bool whatsapp;
public:
    virtual Telefonico* clone() const{ return new Telefonico(*this); }
    virtual bool operator==(const Contatto& t) const{
        auto p = dynamic_cast<const Telefonico*>(&t);
        return p && numero == p->numero;
    }
    const std::string& getNumero() const{
        return numero.getNumero();
    };
    unsigned int getSms() const{
        return num_sms;
    };
    bool getWhatsapp() const{ return whatsapp; };
};

class Skype : public Contatto{
private:
    std::string username;
    bool videochiamate;
public:
    virtual Skype* clone() const{ return new Skype(*this); }
    virtual bool operator==(const Contatto& t) const{
        auto p = dynamic_cast<const Skype*>(&t);
        return p && username == p->username;
    }
    bool getVideochiamate() const{
        return videochiamate;
    }
};

class Rubrica{
private:
    class Entry{
        friend class Rubrica;
    public:
        Contatto* c;
        unsigned int n;
        Entry(Contatto * p, unsigned int x): c(p->clone()), n(x){}
        Entry(const Entry& e) : c(e.c->clone()), n(e.n){}
        Entry& operator= (const Entry& e){
            if(this != &e){
                delete c;
                c = e.c->clone();
                n = e.n;
            }
            return *this;
        }
        ~Entry(){ delete c; };
    };
    std::vector<Entry> contatti;
public:
    void insert(Contatto* c, int n){
        Entry entry(c, n);
        for(Entry& e  : contatti)
            if(*(e.c) == *(entry.c)){
                e.n++;
                return;
            }
        contatti.push_back(entry);
    }
    std::list<Telefonico> tel(const Nome& n, int s){
        std::list<Telefonico> l;
        for(Entry& e : contatti){
            auto p = dynamic_cast<Telefonico*>(e.c);
            if(p && p->getNome() == n && p->getSms() >= s){
                l.push_back(*p);
            }
        }
    }
    int whatsCall(){
        unsigned int n = 0;
        for(Entry& e : contatti){
            auto p1 = dynamic_cast<Telefonico*>(e.c);
            auto p2 = dynamic_cast<Skype*>(e.c);
            if((p1 && p1->getWhatsapp())||(p2 && p2->getVideochiamate())) ++n;
        }
        return n;
    }

};
#endif //LIBRERIELEZIONI_ALL_H