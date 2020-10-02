#include <iostream>
#include <vector>
using namespace std;

class QString {
private:
	string q;
public:
	QString(const char* str) { q = str;}	
};

class QPaintDevice {
private:
	int h, w;
public:
	virtual ~QPaintDevice(){}
	
	int height() const {return h;}
	int width() const {return w;}
	
	QPaintDevice(int a=40, int l=40): h(a), w(l){}
};

class QWidget : public QPaintDevice {
private:
	bool focus;
public:
	bool hasFocus() const {return focus;}
	void clearFocus() {focus = false;}
	
	QWidget(int a=40, int l=40, bool f=true): QPaintDevice(a,l), focus(f){}
};

class QAbstractButton : public QWidget {
private:
	QString ettichetta;
public:
	void setText(const QString& s) {
		ettichetta = s;
	}
	
	QAbstractButton(int a=40, int l=40, bool f=true, QString e=" "): QWidget(a, l, f), ettichetta(e){}
};

vector<QAbstractButton*> fun(const vector<QPaintDevice*>& v){
	vector<QAbstractButton*> rit;
	for (int it=0; it != v.size(); ++it) {
		QWidget* pqw = dynamic_cast<QWidget*> (v[it]);
		if (pqw){
			if( pqw->height() > 50 || pqw->width() > 50)	throw QString("TooBig");
			if( pqw->hasFocus() )	pqw->clearFocus();
		}
		QAbstractButton* pqab = dynamic_cast<QAbstractButton*> (v[it]);
		if (pqab) {
			pqab->setText("Pulsante");
			rit.push_back(pqab);
		}	
	}
	return rit;
}

main(){
	
	QPaintDevice* pqpd1 = new QWidget;
	//QPaintDevice* pqpd2 = new QWidget(60, 60);
	QPaintDevice* pqpd3 = new QWidget(20, 20, true);
	QPaintDevice* pqpd4 = new QAbstractButton;
	QPaintDevice* pqpd5 = new QAbstractButton;	
	
	
	vector<QPaintDevice*> v;
	v.push_back(pqpd1); 
	//v.push_back(pqpd2); 
	v.push_back(pqpd3); v.push_back(pqpd4); v.push_back(pqpd5);
	
	fun(v);
}