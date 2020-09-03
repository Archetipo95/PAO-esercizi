#include <iostream>

using namespace std;

class A { public: virtual ~A() {} };
class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};
class E : public D {};
class F : public E {};

template<class T>
void Fun( T& ref ) {
	bool b = 0;
	B *p = &ref;
	try { throw ref; }
	catch( E ) { cout << "E "; b = 1; }
	catch( D ) { cout << "D "; b = 1; }
	catch( B ) { cout << "B "; b = 1; }
	catch( A ) { cout << "A "; b = 1; }
	catch( C ) { cout << "C "; b = 1; }
	if( b == 0 ) cout << "ZERO ";
}

/*
	T(S) = Tipo Statico
	T(D) = Tipo Dinamico
	
	T(S) p  = B*		T(D) p  = T* 
	T(S) pa = A*		T(D) pa = B* 
	T(S) pb = B*		T(D) pb = B*
	T(S) pc = C*		T(D) pc = E*
	T(S) pd = D*		T(D) pd = F*
	T(S) pe = E*		T(D) pe = E*

*/

int main() {
	A a; B b; C c; D d; E e; F f;
	A *pa = &b; D *pd = &f;
	B *pb = dynamic_cast<B*>( pa );
	C *pc = dynamic_cast<E*>( pd );
	E *pe = static_cast<E*>( pd );

	// Fun( a ); 
	// NON COMPILA 
	// Spiegazione: non è possibile effettuare la conversione A* => B*

	// Fun( b );
	// Stampa: B

	// Fun( c );
	// NON COMPILA
	// Spiegazione: non è possibile effettuare la conversione C* => B*

	// Fun( d );
	// Stampa: D

	// Fun( e );
	// Stampa: E

	// Fun( f );
	// Stampa: E
	// Spiegazione: essendo una derivazione pubblica, avviene la conversione F => E
	// NB: in questo caso non essendo una conversione tra puntatori o riferimenti viene 
	// estratto fisicamente il sottoggetto E di F

	// Fun( *pa );
	// NON COMPILA
	// Spiegazione: poichè il template è instanziato a tempo di compilazione, il tipo di 
	// ref è TS( *pa ) = A; non è possibile effettuare la conversione A* => B*

	// Fun( *pb );
	// Stampa: B

	// Fun( *pc );
	// NON COMPILA
	// Spiegazione: poichè il template è instanziato a tempo di compilazione, il tipo di
	// ref è TS( *pc ) = C; non è possibile effettuare la conversione C* => B*

	// Fun( *pd );
	// Stampa: D

	// Fun( *pe );
	// Stampa: E

	// Fun<B>( *pd );
	// Stampa: B

	// Fun<D>( *pd );
	// Stampa: D (?)

	// Fun<E>( *pd );
	// NON COMPILA
	// Spiegazione: non è possibile effettuare la conversione D => E&
}




//Fun(a); 		 //NON COMPILA invalid conversion from A* to B*
	//Fun(b); 		 B
	//Fun(c);  		 NON COMPILA cannot convert C* to B* in initialization B*p = &ref
	//Fun(d); 		 D
	//Fun(e);   	 E
	//Fun(f); 	     E (quando fa la throw di ref, ref ha tipo statico F. 
	//				 Lui guarda la prima catch, che prevede un E. Essendo F 
	//				 sottotipo di E, estrae il sottooggetto di F, che è E, ed entra dentro la catch.)
	//Fun(*pa); 	 NON COMPILA invalid conversion from A* to B*
	//Fun(*pb);  	 B
	//Fun(*pc);  	 NON COMPILA cannot convert C* to B* in initialization B*p = &ref
	//Fun(*pd);  	 D
	//Fun(*pe);		 E
	//Fun<B>(*pd);   B
	//Fun<D>(*pd);   D
	//Fun<E>(*pd);   NON COMPILA cannot convert *pd (type D) to type E&