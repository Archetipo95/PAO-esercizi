#include <iostream>
#include <vector>
using namespace std;

class Account {
	private:
	string username;
	public:
	string getUser() const {return username;}
	
	bool operator==(const Account& a) const {return username == a.username;}
};

class Image {
	private:
	int key;
	public:
	int getKey() const {return key;}
};

class Exc {
	private:
	int code;
	public:
	Exc(int i=0) : code(i) {cout << "Errore: " << i << endl;}
};


class Tweet {
	private:
	string messaggio;
	public:
	Tweet(const string& s){
		if(s.size() > 140){
			messaggio = "";
			throw Exc(s.size());
		}
		else {
			messaggio = s;
		}
	}
	
	string getMex() const {return messaggio;}
	
	Tweet* clone() const { return new Tweet(*this);}
	
	virtual ~Tweet() ;
	
};

class ReTweet : public Tweet {
	private:
	Account utente;
	public:
	Account getUtente() const {return utente;} 
};

class ImageTweet : public Tweet {
	private:
	Image img;
	public:
	Image getImg() const {return img;}
};


class UtenteTwitter {

	private:
	class SmartTweet{
		public:
		Tweet* pt;
		SmartTweet(const Tweet& t){ pt= t.clone(); }
		SmartTweet(const SmartTweet& st) : pt(st.pt->clone()){}
		SmartTweet& operator=(const SmartTweet& st) {
			if (this != &st) {
				delete pt;
				pt = st.pt->clone();
			}
			return *this;
		}
		~SmartTweet() { if(pt) delete pt; }
	};

	vector<SmartTweet> sma;

	public:
	void insert(const ImageTweet& imt){
		bool flag = false;
		for(vector<SmartTweet>::const_iterator cit = sma.begin() ; cit < sma.end() ; ++cit){
			ImageTweet* pit = dynamic_cast<ImageTweet*> (cit->pt);
			if(pit && pit->getImg().getKey() == imt.getImg().getKey()){
				flag = true;
			}
		}
		if(!flag) sma.push_back(imt);
	}
	
	void removeReTweet(const Account& a){
		bool flag = false;
		for(vector<SmartTweet>::iterator it = sma.begin() ; it < sma.end() ; ++it){
			ReTweet* prt = dynamic_cast<ReTweet*> (it->pt);
			if (prt && prt->getUtente() == a) {
				flag = true;
				delete it->pt;
				sma.erase(it);
				}
		}
		if(!flag) throw Exc(0);
	}
	
	void modify(int k) {
		for(vector<SmartTweet>::iterator it = sma.begin() ; it < sma.end() ; ++it){
			ImageTweet* pit = dynamic_cast<ImageTweet*> (it->pt);
			if (pit && pit->getImg().getKey() == k) {
				Tweet t(pit->getMex());
				it->pt = &t;
			}
		}
	}
	
};
