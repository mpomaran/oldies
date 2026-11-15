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
//	message.handler.h		Message Handler
//
//	Features:
//
//		-	supports multithread
//		-	32 message types of messages
//
//
////////////////////////////////////////////////////////////////////////


#ifndef __LK_VER_0005_MESSAGE_HANDLER
#define __LK_VER_0005_MESSAGE_HANDLER

#include <list>

#include "base.object.h"

#include "message.defs.h"
#include "message.client.h"
#include "return.values.h"

using	namespace std;
typedef list<lkMsgClientDescripion>	lkMsgClientList;

////////////////////////////////////////////////////////////////////////
//	Nazwa klasy:
//		lkMsgHandler
//
//
//	Przeznaczenie:
//		Serwer zdarzen. Rozsyla komunikaty do swoich klientow wg.
//		roznych krytertiow
//
//	Skladowe:
//		m_clients		-	lista klientow 
//
//	Metody:
//		registerClient	-
//			...
//
//		unregisterClient-
//			...
//
//		modifyClientAccept -
//			Modyfikacja wlasciwosci "accept" podawanej podczas rejestracji klienta.
//			Pobiera wskaznik do klienta chcacego zmodyfikowac ta wlasciwosc
//			oraz jej nowa wartosc.
//
//		modifyClientNewThread - 
//			Modyfikacja wlasciwosci "newThread" podawanej podczas rejestracji klienta.
//			Pobiera wskaznik do klienta chcacego zmodyfikowac ta wlasciwosc
//			oraz jej nowa wartosc.
//
//	Uwagi:
//		Serwer moze dzialac zarowno jedno jak i wielowatkowo. Trzeba jednak zauwazyc,
//		iz tworzenie wielu watkow zwalnia system, nalezy wiec tego unikac. Poza tym
//		PC nie jest stworzone do pracy wielowatkowej i moze sie cos pokrzaczyc ;)
//
//
//	TODO:
//		-	dokumentacja
//		-	klasa definiujaca klienta
//		-	klasa definiujaca komunikat
//		-	uzycie mutexow
//
class	lkMsgHandler : protected lkBaseObject 
{
private:
	lkMsgClientList	m_clients;			// lista zarejestrowanych klientow

public:
	lkMsgHandler	();
	~lkMsgHandler	();

	LK_RESULT		registerClient (const lkMsgClient*	client, 
									cosnt lkInt64&		objectID, 
									unsigned			accepts = LK_MSG_ALL,
									int					newThread = false );

	LK_RESULT		unregisterClient	(const lkMsgClient* client);

	LK_RESULT		modifyClientAccept	 (const lkMsgClient* client, unsigned accepts = LK_MSG_ALL);
	LK_RESULT		modifyClientNewThread(const lkMsgClient* client, int	newThread = false );

};

#endif
