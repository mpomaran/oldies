//	------------------------------------------------------------------------------------
//	geo.mng.basic.h		-	klasa GeometryMng, menedzer danych geometrii
//
//
//	(c)	2002	Michal Pomaranski
//		mpomaranski@poczta.onet.pl
//	------------------------------------------------------------------------------------

#ifndef __GEOMETRY_MNG_SIMPLE_H
#define __GEOMETRY_MNG_SIMPLE_H


// TODO !!!
#include	"geo.mng.basic.h"



//	------------------------------------------------------------------------------------
//	Struktura uzywana do wymiany informacji
//	------------------------------------------------------------------------------------
struct	GeoDataS
{
	int	data1;
};



//	------------------------------------------------------------------------------------
//	Najprostrza mozliwa klasa zarzadzajaca danymi
//	dziedziczyc.
//
//	Opis metod:
//		giveData ()
//			daje dane dla geometrii
//
//		giveDataLen ()
//			zwraca dlugosc danych
//
//	------------------------------------------------------------------------------------

class	GeoDataMngSimple : public GeometryDataMng
{
	private:

	public:

		// Konstruktor/destruktor
		GeoDataMng () {};
		~GeoDataMng () {};

		// Dostarczanie kolejnych danych dla geometrii
		void*	giveData () { return (void *)0; };
		int		giveDataLen () {return 0;}
};


#endif