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
//	message_client.cpp	Implementacja klienta zdarzen
//
//	IMPLEMENTATION
//		Read message.client.h for more details.
//
//
////////////////////////////////////////////////////////////////////////

#include	<windows.h>
#include	<stdlib.h>

#include	"base.object.h"

#include	"message.client.h"
#include	"message.defs.h"
#include	"message.server.h"


////////////////////////////////////////////////////////////////////////
// automatyczne nazywanie mutexow
static	unsigned mutexNo = 0;


////////////////////////////////////////////////////////////////////////


lkMsgClient::lkMsgClient	()
{
	int i;

	// ustawienie ID klasy
	setClassID ('M','s','g','C');		// Stands for MessageClient

	// czyszczenie tablic
	for (i=0; i<LK_SERVER_ENTRY_LEN; i++)
	{
		m_servers[i] = NULL;
		m_serversID[i] = LK_ENTRY_FREE;
	}

	// Tworzenie mutex'a
	itoa (mutexNo++, m_mutexName, 16);							// nowa nazwa
	SECURITY_ATTRIBUTES attr;									// atrybuty bezpieczenstwa
	attr.lpSecurityDescriptor = NULL;
	m_msgListMutex = CreateMutex (attr, false, m_mutexName);		// tworzenie mutex'a

	if (m_msgListMutex == NULL)									// czy zostal utworzony?
		throw "lkMsgClient::lkMsgClient(): CreateMutex failed";

	assert (GetLastError() != ERROR_ALREADY_EXISTS));			// to sie zdarza tylko
																// gdy jest bug
}


////////////////////////////////////////////////////////////////////////


lkMsgClient::~lkMsgClient	()
{
	int i;

	for (int i=0; i<LK_SERVER_ENTRY_LEN; i++)
		if (m_serversID[i] == LK_ENTRY_USED)
		{
			// TODO:
			//	- wyrejestrowanie sie z serwerow
		}
}


////////////////////////////////////////////////////////////////////////
