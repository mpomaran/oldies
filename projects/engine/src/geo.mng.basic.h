//	------------------------------------------------------------------------------------
//	geo.mng.basic.h		-	klasa GeometryMng, menedzer danych geometrii
//
//
//	(c)	2002	Michal Pomaranski
//		mpomaranski@poczta.onet.pl
//	------------------------------------------------------------------------------------

#ifndef __GEOMETRY_MNG_BASIC_H
#define __GEOMETRY_MNG_BASIC_H






//	------------------------------------------------------------------------------------
//	Klasa definiuje podstawowego zarzadce geomentrii. Inne geometrie powinny z tego
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

class	GeometryDataMng
{
	private:

	public:

		// Konstruktor/destruktor
		GeoDataMng () = 0;
		~GeoDataMng () = 0;

		// Dostarczanie kolejnych danych dla geometrii
		void*	giveData () = 0;
		int		giveDataLen () = 0;
};


#endif