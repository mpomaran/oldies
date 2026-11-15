////////////////////////////////////////////////////////////////////////
//	Open LK Project
//
//	MOTTO:
//		Read me as an open book.
//
//	(c) 2002 by Michal Pomaranski
//	mpomaranski@poczta.onet.pl
//
//	!!!COMMECIAL SOFTWARE!!!
//	You aren't allowed to use this software without a written permission.
//
//	!!!OPROGRAMOWANIE KOMERCYJNE!!!
//	Zabronione jest korzystanie z tego kodu w jakikolwiek sposob
//	bez pisemnego zezwolenia autora.
//
//
//	base.object.h	Object identification engine. Base class for all 
//					lake classes.
//
//	Features:
//
//		-	automatyczne nadawanie identyfikatorow objektom
//		-	obsluguje 2^64 objektow
//
//
////////////////////////////////////////////////////////////////////////


#ifndef __LK_VER_0005_LAKE_BASE_OBJECT
#define __LK_VER_0005_LAKE_BASE_OBJECT

#include <assert.h>
#include "macro.h"

// Microsoft specific
typedef	__int64 lkInt64;



extern	lkInt64	lkAutoObjectID;



////////////////////////////////////////////////////////////////////////
//	Nazwa klasy:
//		lkBaseOBject
//
//
//	Przeznaczenie:
//		Klasa bazowa dla wszystkich obiektow w systemie lake. Umozliwia
//		automatyczna identyfikacje obiektow
//
//
//	Skladowe:
//		m_objectID		-	64-bitowa wartosc odpowiadajaca numerowi
//							kolejnego obiektu tworzonego przez program.
//							Po utworzeniu obiektu zwiekszana jest wartosc
//							licznika lkAutoObjectID o 1
//
//		m_classID		-	Czterobajtowy identyfikator opisujacy klase
//							do jakiej nalezy obiekt. Ta wartosc jest
//							ustawiana w klasie potomnej.
//
//	Uwagi:
//		Wartosc m_objectID nie powinna byc modyfikowana przez klasy
//		potomne bez wyraznej przyczyny. Dla odmiany m_classID POWINNA
//		byc ustwiona w klasie potomnej.
//
//
//	TODO:
//		-	dokumentacja
//
class	lkBaseObject
{
	private:
		lkInt64		m_objectID;		// kolejny numer obiektu w programie
		unsigned	m_classID;		// FourCC dla klasy

	public:
		lkBaseObject ();


		////////////////////////////////////////////////////////////////////////

		void		setObjectID (lkInt64 newID);		// ustawianie ID obiektu
		lkInt64		getObjectID ();						// zwraca ID obiektu


		////////////////////////////////////////////////////////////////////////

		void		setClassID	(unsigned newID);		// ustwaianie ID klasy
		unsigned	getClassID ();						// zwraca ID klasy


		////////////////////////////////////////////////////////////////////////
		bool		operator == (const lkBaseObject &l);
};




////////////////////////////////////////////////////////////////////////
//	Implementacja metod klasy
////////////////////////////////////////////////////////////////////////
inline			lkBaseObject::lkBaseObject ()
{
	// nadanie numeru objektu i klasa jako UnKnoWN
	m_objectID = lkAutoObjectID++;
	m_classID = fourCC ('U','K','w','n');
}


////////////////////////////////////////////////////////////////////////


inline	void	lkBaseObject::setObjectID (lkInt64 newID)
{
	m_objectID = newID;
}


////////////////////////////////////////////////////////////////////////


inline	lkInt64	lkBaseObject::getObjectID ()
{
	return m_objectID;
}


////////////////////////////////////////////////////////////////////////


inline	void	lkBaseObject::setClassID	(unsigned newID)
{
	m_classID = newID;
}


////////////////////////////////////////////////////////////////////////


inline	unsigned lkBaseObject::getClassID ()
{
	return m_classID;
}


////////////////////////////////////////////////////////////////////////


inline	bool	lkBaseObject::operator == (const lkBaseObject &l)
{
	if (m_objectID != l.m_objectID)
		return false;

	// jesli ta asercja nie jest spelniona, to znaczy, ze istnieja
	// dwa objekty o takich samych objectID i roznych klasach, co
	// nie powinno byc miejsca
	// jest to blad wynikajacy prawdopodobnie z blednego 'recznego'
	// przypisania wartosci m_objectID za pomoca metody setObjectID()
	assert (m_classID == l.m_classID);
	return true;
}

#endif