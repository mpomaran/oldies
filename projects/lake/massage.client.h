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
//
//	message.client.h		Message Client
//
//	Features:
//
//		-	supports multithread
//		-	up to 32 message servers
//
//
//
//
//
////////////////////////////////////////////////////////////////////////

#ifndef __LK_VER_0005_MESSAGE_CLIENT
#define __LK_VER_0005_MESSAGE_CLIENT


#include <list>
#include "return.values.h"
#include "message.defs.h"
#include "message.handler.h"

using	namespace std;
typedef list<lkMsgDescripion>	lkMsgList;

////////////////////////////////////////////////////////////////////////
//	Nazwa klasy:
//		lkMsgClient
//
//
//	Przeznaczenie:
//
//	Skladowe:
//
//	Metody:
//
//	Uwagi:
//
//
//	TODO:
//		- dokumentacja
//		- uzycie mutexow
//		- konstrktor czysci tablice, towrzy mutexy
//		- destruktor wypieprza z serwerow, kasuje mutexy
//		- rejestracja w serwerze
//		- zwraca no. serwera
//		- odbior komunikatow
//		- wysylanie komunikatow do jednego/wielu/wsztystkich
//			z 32 serwerow, do ktorych moze bys w danej chwili
//			dolaczony jest dany klient
//		- domyslne przewtwarzane komunikatow
//		- wysylanie 32 roznych typow komunikatow
//
class	lkMsgClient
{
	friend	class	lkMsgHandler;		// zeby mogla wpisywac do kolejki komunikatow
private:
	char			m_serversAutoID;

	lkMsgHander*	m_servers   [LK_SERVER_ENTRY_LEN];	// lista serwerow
	lkInt16			m_serversID [LK_SERVER_ENTRY_LEN];	// liczba identyfikujaca dany serwer

protected:

	char			m_mutexName[32];

	lkMutex			m_msgListMutex;		// mutex blokujacy nazwe 
	lkMsgList		m_msgList;			// lista wiadomosci

public:
	lkMsgClient		();
	~lkMsgClient	();

};

#endif