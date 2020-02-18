#include <iostream>
#include <vector>

using namespace std;

class GalloFile {
private:
    double mb;
public:
    virtual GalloFile* clone() const = 0;
    virtual bool HighQuality() const = 0;
    virtual ~GalloFile() = default;
    double getMb() const { return mb;}
};

class Foto : public GalloFile {
private:
    unsigned int iso;
    bool hasFlash;
public:
    virtual Foto* clone() const { return new Foto(*this);}
    virtual bool HighQuality() const { return iso >= 500;}
    unsigned int getIso() const { return iso;}
    bool hasFlashOn() const { return hasFlash;}
};

class Video : public GalloFile {
private:
    unsigned int durata;
    bool isFullHD;
public:
    virtual Video* clone() const { return new Video(*this);}
    virtual bool HighQuality() const { return isFullHD;}
    unsigned int getDurata() const { return durata;}
};

class Gallo {
private:
    vector<GalloFile*> galleria;
public:
    vector<GalloFile*> selectHQ() const {
        vector<GalloFile*> v;
        for(auto it = galleria.begin(); it != galleria.end(); ++it){
            Foto* p = dynamic_cast<Foto*>(*it);
            if((p && p->hasFlashOn() && p->HighQuality()) || !p && (*it)->HighQuality()) v.push_back(*it);
        }
        return v;
    }
    void removeNonFoto(double x) {
        bool erased = false;
        for(auto it = galleria.begin(); it != galleria.end(); ++it){
            Foto* p = dynamic_cast<Foto*>(*it);
            if(!p && (*it)->getMb() > x) { 
                galleria.erase(it);
                erased = true;
            }
        }
        if(!erased) throw(logic_error("NoRemove"));
    }
    const GalloFile* insert(const GalloFile* pf) {
        const Video* p = dynamic_cast<const Video*>(pf);
        if(!p || (p && p->getDurata() < 1)) {
            galleria.push_back(pf->clone());
            return galleria.end();
        }
        else return nullptr;
    }
};

int main() {
 cout << "Hello World";
 return 0;   
}
}