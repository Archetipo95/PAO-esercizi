#include<String>

class Widget{

private:
    int larghezza;
    int altezza;
    bool visible=false;

public:
    virtual void setStandardSize() = 0;

    void setLarghezza(int l){
            larghezza = l;
    }
    void setAltezza(int a){
           altezza=a;
    }

    void setVisible(bool b){
        visible=b;
    }

    Widget(int l, int a,bool b):larghezza(l), altezza(a), visible(b) {}
};

class AbstractButton :  public Widget{
private:
    std::string nome;
public:
    AbstractButton(std::string s,int l, int a, bool b) : Widget(l,a,b), nome(s) {}
    std::string getNome(){
        return nome;
    }
};

class PushButton  : public AbstractButton{
private:
public:
    void setStandardSize(){
        this->setLarghezza(80);
        this->setAltezza(20);
    }
    PushButton(std::string s,int l,int a,bool b) : AbstractButton(s,l,a,b){}
};

class CheckBox : public  AbstractButton{
private:
    bool state=false; // false = unchecked
public:
    void setStandardSize(){
        this->setLarghezza(5);
        this->setAltezza(5);
    }
    CheckBox(std::string s,int l,int a,bool b) : AbstractButton(s,l,a,b) {}
    bool getState(){
        return state;
    }
};










class Gui{
private:
    std::vector<const Widget*> NoButtons;
    std::list<const AbstractButton*> Buttons;
public:
    void insert(Widget* w) throw(std::string){
        if(!w){
            throw "NoInsert";
        }
        else{
            AbstractButton* ab = dynamic_cast<AbstractButton*>(w);
            if(ab){
                Buttons.push_back(ab);
            }
            else{
                AbstractButton* pb = dynamic_cast<PushButton*>(w);
                if(pb){
                    NoButtons.push_back(pb);
                }
                else{
                    CheckBox* cb = dynamic_cast<CheckBox*>(w);
                    NoButtons.push_back(cb);
                }
            }
        }
    }
    void insert(unsigned int pos, PushButton& pb) throw(std::string){
        std::list<const AbstractButton*>::iterator it= Buttons.begin();
        bool inserito=false;
        for( ; it != Buttons.end() && !inserito ; ++it){
            if(!pos){
                AbstractButton* ab = new PushButton(pb);
                Buttons.insert(it,/*&*/ab);
                inserito=true;
            }
            pos--;
        }
        if(!inserito){
            throw "NoInsert";
        }
    }
    std::vector<AbstractButton*> removeUnchecked(){
        std::vector<AbstractButton*> aux;
        std::list<const AbstractButton*>::iterator it= Buttons.begin();
        for(; it!=Buttons.end() ; ++it){
            AbstractButton* ab = const_cast<AbstractButton*>(*it);
            CheckBox* cb = dynamic_cast<CheckBox*>(ab);
            if(cb && !cb->getState()){
                aux.push_back(ab);
                Buttons.erase(it);
            }
        }
        return aux;
    }
    void setStandardPushButton(){
        std::list<const AbstractButton*>::iterator it= Buttons.begin();
        for(; it!=  Buttons.end() ; ++it){
            AbstractButton* ab = const_cast<AbstractButton*>(*it);
            PushButton* pb= dynamic_cast<PushButton*>(ab);
            if(pb && pb->getNome() != ""){
                pb->setStandardSize();
            }
        }
    }
};


/*
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Widget {
private:
	int height;
	int width;
	bool visible;
public:
	Widget( int h, int w, bool v ) : height( h ), width( w ), visible( v ) {}
	virtual ~Widget() = 0;
	virtual void setStandardSize() = 0;
	void setHeight( int h ) { height = h; }
	void setWidth( int w ) { width = w; }
	void setVisible( bool v ) { visible = v; }
	int getHeight() const { return height; }
	int getWidth() const { return width; }
	bool isVisible() const { return visible; }
};

class AbstractButton : public Widget {
private:
	string label;
public:
	AbstractButton( int h, int w, bool v, string l = "" ) : 
		Widget( h, w, v ), label( l ) {}
	void setLabel( string l ) { label = l; }
	string getLabel() const { return label; }
};

class PushButton : public AbstractButton {
public:
	PushButton( int h, int w, bool v, string l ) : AbstractButton( h, w, v, l ) {}
	virtual void setStandardSize() {
		setHeight( 80 );
		setWidth( 20 );
	}
};

class CheckBox : public AbstractButton {
private:
	bool checked;
public:
	CheckBox( int h, int w, bool v, string l, bool s ) : 
		AbstractButton( h, w, true, l ), checked( s ) {}
	void setCheckState( bool s ) { checked = s; }
	bool isChecked() const { return checked; }
	void setStandardSize() {
		setHeight( 5 );
		setWidth( 5 );
	}
};

class Gui {
private:
	vector<const Widget*> NoButtons;
	list<const AbstractButton*> Buttons;
public:
	void insert( Widget* w ) throw( string ) {
		if( !w )
			throw "";
		AbstractButton* ab = dynamic_cast<AbstractButton*>( w );
		if( ab )
			Buttons.push_back( ab );
		else NoButtons.push_back( ab );

	}	
	void insert( unsigned int pos, PushButton& pb ) throw( string ) {
		if( pos < 0 || pos > Buttons.size() )
			throw "";
		if( pos == 0 )
			Buttons.push_front( &pb );
		else if( pos == Buttons.size() )
			Buttons.push_back( &pb );
		else {
			list<const AbstractButton*>::iterator it;
			int i = 1;
			for( it = ++Buttons.begin(); it != Buttons.end(); ++it, ++i ) {
				if( pos == i )
					Buttons.insert( it, &pb );
			}
		}
	}
	vector<AbstractButton*> removeUnchecked() {
		vector<AbstractButton*> uncheckedButtons;
		list<const AbstractButton*>::iterator it;
		for( it = Buttons.begin(); it != Buttons.end(); ++it ) {
			AbstractButton* aux = const_cast<AbstractButton*>( *it );
			CheckBox* cb = dynamic_cast<CheckBox*>( aux );
			if( cb && !cb->isChecked() ) {
				uncheckedButtons.push_back( cb );
				Buttons.erase( it );
			}
		}
		return uncheckedButtons;
	}
	void setStandardPushButton() const {
		list<const AbstractButton*>::const_iterator it;
		for( it = Buttons.begin(); it != Buttons.end(); ++it ) {
			AbstractButton* aux = const_cast<AbstractButton*>( *it );
			CheckBox* cb = dynamic_cast<CheckBox*>( aux );
			if( cb && cb->getLabel() != "" )
				cb->setStandardSize();
		}
	}
};


int main() {

}

*/


/*
#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Widget{
	private:
	
	unsigned int larg, lung;
	bool hide;
	
	public:
	unsigned int getLarg() const {return larg;}
	unsigned int getLung() const {return lung;}
	bool isHide() const {return hide;}
	
	void setLarg(int la) { larg=la; }
	void setLung(int lu) { lung=lu; }
	
	virtual ~Widget();
	virtual void setStandardSize() =0;
	
	Widget(unsigned int la=1, unsigned int lu=1, bool h=false) : larg(la), lung(lu) , hide(h){} 
	
};

class AbstractButton : public Widget {
	private:
	
	string etichetta;
	
	public:
	
	string getEtichetta() const {return etichetta;}
	
	AbstractButton( string e="", unsigned int la=1, unsigned int lu=1, bool h=false ) : etichetta(e), Widget(la,lu,h) {}
	
};

class PushButton : public AbstractButton {
	public:
	
	virtual void setStandardSize() { setLarg(80); setLung(20); }
	
	PushButton( string e="", unsigned int la=80, unsigned int lu=20, bool h=false ) : AbstractButton(e, la, lu, h) {}

};

class CheckBox : public AbstractButton {
	private:
	
	bool check;
	
	public:
	
	bool isCheck() const {return check;}
	
	virtual void setStandardSize() { setLarg(5); setLung(5); }
	
	CheckBox( bool c = true, string e="", unsigned int la=80, unsigned int lu=20, bool h=false ) : check(c) , AbstractButton(e, la, lu, true) {}
 
};

class Gui {
	private:
	
	vector<const Widget*> NoButtons;
	
	list<const AbstractButton*> Buttons;
		
	public:
	
	void insert(Widget* p) {
		if (!p) {
			throw string("NoInsert");
		}
		else {
			AbstractButton* pab = dynamic_cast<AbstractButton*> (p);
			if (p) {
				Buttons.push_back(pab);
			}
			else {
				NoButtons.push_back(p);
			}

		}
	}
	
	void insert(unsigned int pos, PushButton& pb) {
		if (0 > pos || pos > Buttons.size() ) {
			throw string("NoInsert");
		}
		
		auto it = Buttons.begin();
		for( ; pos < 0 || it < Buttons.end() ; ++it , --pos){
		}
		Buttons.insert(it, &pb);
		
	}
	
	vector<AbstractButton*> removeUnchecked() {
		vector<AbstractButton*> rit;
		
		for (list<const AbstractButton*>::iterator it = Buttons.begin(); it < Buttons.end(); ++it) {
			const CheckBox* pccb = dynamic_cast<const CheckBox*> (*it);
			if (pccb && !pccb->isCheck()) {
				rit.push_back(*it);
				Buttons.erase(it);
			}
		}
		
		return rit;
	}
	
	void setStandardPushButton() {
		for (auto it = Buttons.begin() ; it < Buttons.end(); ++it) {
			PushButton* ppb = dynamic_cast<PushButton*> (const_cast<AbstractButton*>(*it));
			if (ppb && ppb->getEtichetta()) {
				ppb->setStandardSize();
			}
		}
	}


};

*/


/*
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Widget {
private:
	int height;
	int width;
	bool visible;
public:
	Widget( int h, int w, bool v ) : height( h ), width( w ), visible( v ) {}
	virtual ~Widget() = 0;
	virtual void setStandardSize() = 0;
	
	void setHeight( int h ) { height = h; }
	void setWidth( int w ) { width = w; }
	void setVisible( bool v ) { visible = v; }
	
	int getHeight() const { return height; }
	int getWidth() const { return width; }
	bool isVisible() const { return visible; }
};

class AbstractButton : public Widget {
private:
	string label;
public:
	AbstractButton( int h, int w, bool v, string l = "" ) : 
		Widget( h, w, v ), label( l ) {}
	void setLabel( string l ) { label = l; }
	string getLabel() const { return label; }
};

class PushButton : public AbstractButton {
public:
	PushButton( int h, int w, bool v, string l ) : AbstractButton( h, w, v, l ) {}
	virtual void setStandardSize() {
		setHeight( 80 );
		setWidth( 20 );
	}
};

class CheckBox : public AbstractButton {
private:
	bool checked;
public:
	CheckBox( int h, int w, bool v, string l, bool s ) : 
		AbstractButton( h, w, true, l ), checked( s ) {}
	void setCheckState( bool s ) { checked = s; }
	bool isChecked() const { return checked; }
	void setStandardSize() {
		setHeight( 5 );
		setWidth( 5 );
	}
};

class Gui {
private:
	vector<const Widget*> NoButtons;
	list<const AbstractButton*> Buttons;
public:
	void insert( Widget* w ) throw( string ) {
		if( !w )
			throw "";
		AbstractButton* ab = dynamic_cast<AbstractButton*>( w );
		if( ab )
			Buttons.push_back( ab );
		else NoButtons.push_back( w );
	}	
	
	void insert( unsigned int pos, PushButton& pb ) throw( string ) {
		if( pos < 0 || pos > Buttons.size() )
			throw "";
		if( pos == 0 )
			Buttons.push_front( &pb );
		else if( pos == Buttons.size() )
			Buttons.push_back( &pb );
		else {
			list<const AbstractButton*>::iterator it;
			int i = 1;
			for( it = ++Buttons.begin(); it != Buttons.end(); ++it, ++i ) {
				if( pos == i )
					Buttons.insert( it, &pb );
			}
		}
	}
	vector<AbstractButton*> removeUnchecked() {
		vector<AbstractButton*> uncheckedButtons;
		list<const AbstractButton*>::iterator it;
		for( it = Buttons.begin(); it != Buttons.end(); ++it ) {
			AbstractButton* aux = const_cast<AbstractButton*>( *it );
			CheckBox* cb = dynamic_cast<CheckBox*>( aux );
			if( cb && !cb->isChecked() ) {
				uncheckedButtons.push_back( cb );
				Buttons.erase( it );
			}
		}
		return uncheckedButtons;
	}
	void setStandardPushButton() const {
		list<const AbstractButton*>::const_iterator it;
		for( it = Buttons.begin(); it != Buttons.end(); ++it ) {
			AbstractButton* aux = const_cast<AbstractButton*>( *it );
			CheckBox* cb = dynamic_cast<CheckBox*>( aux );
			if( cb && cb->getLabel() != "" )
				cb->setStandardSize();
		}
	}
};


int main() {

}

*/