/*
Si assumano le seguenti specifiche riguardanti la libreria Qt (attenzione: non si tratta di codice da definire!). • QWidget `e la classe base di tutte le classi Gui della libreria Qt.
– La classe QWidget ha il distruttore virtuale. – La classe QWidget rende disponibile un metodo virtuale QSize sizeHint() const con il seguente comportamento: w.sizeHint() ritorna un oggetto di tipo QSize che rappresenta la dimensione raccomandata per il widget w.
E` disponibile
l’operatore esterno di uguaglianza bool operator==(const QSize&, const QSize&) che testa l’uguaglianza tra oggetti di QSize.
– La classe QWidget rende disponibile un metodo virtuale di clonazione QWidget* clone() con l’usuale contratto di “costruttore di copia polimorfo”: pw->clone() ritorna un puntatore polimorfo ad nuovo oggetto QWidget che `e una copia polimorfa di *pw. Ogni sottoclasse di QWidget definisce quindi il proprio overriding di clone().
• La classe QAbstractButton deriva direttamente e pubblicamente da QWidget ed `e la classe base astratta di tutti i button widgets.
– Le classi QCheckBox, QPushButton e QRadioButton derivano direttamente e pubblicamente da QAbstractButton. Le classi QCheckBox e QPushButton definiscono il proprio overriding di QWidget::sizeHint().
• La classe QAbstractSlider deriva direttamente e pubblicamente da QWidget ed `e la classe base astratta di tutti gli slider widgets.
– Le classi QScrollBar e QSlider derivano direttamente e pubblicamente da QAbstractSlider. Entrambe le classi definiscono il proprio overriding di QWidget::sizeHint().
Definire una funzione vector<QAbstractButton*> fun(list<QWidget*>&, const QSize&) con il seguente comportamento: in ogni invocazione fun(lst,sz)
1. per ogni puntatore p elemento (di tipo QWidget*) della lista lst al momento del passaggio del parametro: (a) se *p ha una dimensione raccomandata uguale a sz allora inserisce nella lista lst un puntatore ad una copia di *p;
(b) se p non `e nullo, *p non `e uno slider widget e ha una dimensione raccomandata uguale a sz allora rimuove dalla lista lst il puntatore p e dealloca l’oggetto *p;
2. inoltre, si devono rimuovere dalla lista lst al momento del passaggio del parametro ed inserirli nel vector di QAbstractButton* da ritornare tutti i rimanenti puntatori p della lista lst tali che *p `e un QCheckBox oppure un QPushButton.
*/

#include <vector>
#include <list>
#include <iostream>

using namespace std;

vector<QAbstractButton*> fun(list<QWidget*>& lis, const QSize& sz){
    QAbstractButton* v;
    //se non posso usare auto, uso iterator
    list<QWidget*>::iterator it;
    for(it=lis.begin(); it != lis.end(); ++it){
        if(*it && *it->sizeHint()==sz){ //CONTROLLO CHE *it esista (accetto con *it)
            lis.push_fron(*it->clone());
            QAbstractSlider* abs = dynamic_cast<QAbstractSlider*>(*it);
            if(!abs){
                //la soluzione dice di fare prima
                //delete *it;
                //e poi un passaggio strano
                //it=lis.erase(it);
                lis.erase(it);
                delete *it;
            }
        }else if(*it){
            if(dynamic_cast<QCheckBox*>(*it) || dynamic_cast<QPushButton*>(*it)){
                //ATTENZIONE SERVE UNO STATIC CAST
                v.push_back(static_cast<QAbstractButton*>(*it));
                //si cancella con il metodo di prima (che non ho capito)
                it=lis.erase(it);
            }
        }
    }
    return v;
}


/*
#include <iostream>
#include <list>
#include <vector>

using namespace std;

// ESERCIZIO 1 DEL COMPITO D'ESAME DEL 18/2/2016

vector<QAbstractButton*> fun(list<QWidget*>& l, const QSize& s) {
	list<QWidget*>::iterator it = l.begin();
	vector<QAbstractButton*> v;
	while(it != l.end()) {
		if(*it && (*it)->sizeHint() == s) l.push_front((*it)->clone());
		QAbstractSlider* p = dynamic_cast<QAbstractSlider*>(*it);
		if(*it && !p && (*it)->sizeHint() == s) {delete *it; it=l.erase(it);}
		else
			if(dynamic_cast<QCheckBox*>(*it) || dynamic_cast<QPushButton*>(*it)) {
				v.push_back(static_cast<QAbstractButton*>(*it));
				it=l.erase(it);
			}
			else ++it;
	}
	return v;
}

main(){

}


*/