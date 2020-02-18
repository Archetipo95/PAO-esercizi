//ES 11.18

#include "iostream"
#include "string"
#include "vector"
#include "typeinfo"

using namespace std;

class FileAudio {   //base astratta e polimorfa
private:
    string titolo;
    double size;
public: // costruttori solo se richiesti
    double getSize() const {return size;}
    virtual bool qualita() const =0;
    virtual FileAudio* clone() const =0;    //costruzione di copia polimorfa
    virtual ~FileAudio() {}     //METTERLO SEMPRE IMPORTANTISSIMO!!!
    virtual bool operator==(const FileAudio& f) const {
        return titolo == f.titolo && size==f.size;
    }
};

class Mp3: public FileAudio {   //NON METTERE DISTRUTTORI!!!
private:
    unsigned int bitrate;
    static unsigned int sogliaQualita;
public:
    unsigned int getBitrate() const {return bitrate;}
    /*virtual*/ bool qualita() const {return bitrate>=sogliaQualita;}
    /*virtual*/ Mp3* clone() const {return new Mp3(*this);} //Uso la covarianza e ritorno un Mp3 non un FileAudio!
    /*virtual*/ bool operator==(const FileAudio& f) const {
        if(typeid(const Mp3&)!=typeid(f)) return false;
        const Mp3* p = static_cast<const Mp3*>(&f);
        return FileAudio::operator==(f) && bitrate == p->bitrate;
    }
};
unsigned int Mp3::sogliaQualita = 256;

class WAV: public FileAudio {   //NON METTERE DISTRUTTORI!!!
private:
    unsigned int frequenza;
    bool lossLess;
    static unsigned int sogliaQualita;
public:
    bool getLossLess() const {return lossLess;}
    /*virtual*/ bool qualita() const {return frequenza>=sogliaQualita;}
    /*virtual*/ WAV* clone() const {return new WAV(*this);} //Uso la covarianza e ritorno un Mp3 non un FileAudio!
    /*virtual*/ bool operator==(const FileAudio& f) const {
        if(typeid(const WAV&)!=typeid(f)) return false;
        const WAV* p = static_cast<const WAV*>(&f);
        return FileAudio::operator==(f) && frequenza == p->frequenza && lossLess == p->lossLess;
    }
};
unsigned int WAV::sogliaQualita = 96;

class iZod { 
private:
    class Brano {
    public:
        FileAudio* ptr; //puntatore (super) polimorfo
        Brano(FileAudio* p):ptr(p->clone()) {}
        Brano(const Brano& b):ptr(b.ptr->clone()) {}
        Brano& operator=(const Brano& b) {
            if(this!=&b){
                delete ptr;     //IMPORTANTE!!!
                ptr = b.ptr->clone();
            }
            return *this;
        }
        ~Brano() {delete ptr;}
        // se chiedeva un'opportuna interfaccia pubblica servivano anche operator* e operator->
        
    };
    vector<Brano> brani;
public:
    vector<Mp3> mp3(double dim, int br) const {
        Mp3* p = nullptr;
        vector<Mp3> v;
        vector<Brano>::const_iterator /*auto*/ cit = brani.begin();  //METODO COSTANTE QUINDI CONST ITERATOR!!!
        for(cit; cit != brani.end(); ++cit) {
            p = dynamic_cast<Mp3*>(cit->ptr);    //cit->ptr ha tipo FileAudio* const "il puntatore è costante"
            if(p != nullptr && p->getSize()>dim && p->getBitrate()>br)
                v.push_back(*p);
        }
    }

    vector<FileAudio*> braniQulita() const{
        WAV* p = nullptr;
        vector<FileAudio*> v;
        auto cit = brani.begin();
        for(cit; cit != brani.end(); ++cit) {
            p = dynamic_cast<WAV*>(cit->ptr);    //cit->ptr ha tipo FileAudio* const "il puntatore è costante"
            if((cit->ptr)->qualita() && (!p || p->getLossLess()))
                v.push_back(cit->ptr);
        }
    }

    void insert(Mp3* m) {
        for(auto cit = brani.begin(); cit != brani.end(); ++cit)
            if(*m == *((*cit).ptr)) return;
            brani.push_back(m);
    }
};

int main() {
    
    cout << "Hello world";
    
    return 0;
}