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
//	message.defs.h	Podstawowe definicje dla klasy lkMsgHandler
//
////////////////////////////////////////////////////////////////////////


#ifndef __LK_VER_0005_MESSAGE_DEFS
#define __LK_VER_0005_MESSAGE_DEFS

#include <windows.h>

#include "lake.common.h"
#include "lake.message.client.h"

//	Microsoft Specific
typedef	__int16	lkInt16;

////////////////////////////////////////////////////////////////////////
// Defines types of messages
//	Determines type of message, for ex. LK_MSG_SYSTEM or LK_MSG_DIRECTX
enum lkMessageType 
{
	USER_TYPE0	=	0,
	USER_TYPE1	=	1,
	USER_TYPE2	=	2,
	USER_TYPE3	=	3,
	USER_TYPE4	=	4,
	USER_TYPE5	=	5,
	USER_TYPE6	=	6,
	USER_TYPE7	=	7,
	USER_TYPE8	=	8,
	USER_TYPE9	=	9,
	USER_TYPE10	=	10,
	USER_TYPE11	=	11,
	USER_TYPE12	=	12,
	USER_TYPE13	=	13,
	USER_TYPE14	=	14,
	USER_TYPE15	=	15,
	USER_TYPE16	=	16,
	USER_TYPE17	=	17,
	USER_TYPE18	=	18,
	USER_TYPE19	=	19,
	USER_TYPE20	=	20,
	USER_TYPE21	=	21,
	USER_TYPE22	=	22,
	USER_TYPE23	=	23,
	USER_TYPE24	=	24,
	USER_TYPE25	=	25,
	USER_TYPE26	=	26,
	USER_TYPE27	=	27,
	USER_TYPE28	=	28,
	USER_TYPE29	=	29,
	USER_TYPE30	=	30,
	USER_TYPE31	=	31
};


////////////////////////////////////////////////////////////////////////
//	Source of message
#define	LK_MSG_SYSTEM	(USER_TYPE0)


////////////////////////////////////////////////////////////////////////
//	Destination of message
#define LK_MSG_ALL	(0xFFFFFFFF)


////////////////////////////////////////////////////////////////////////
//	Message Client List Entry 
struct lkMsgClientDescripion
{
	lkMsgClient*	m_pClient;		// wskaznik na klienta
	lkInt64			m_clientID;		// ID obiektu klienta
	unsigned		m_accepts;		// co klient chce dostawac
	int				m_newThread;	// czy wywolywac za kazdym razem
									// nowy watek
};

////////////////////////////////////////////////////////////////////////
//	Message Data
typedef	unsigned	lkMsgData;


////////////////////////////////////////////////////////////////////////
//	Message Dsciption
struct	lkMsgDescription
{
	int				m_priority;				// priotytet - 0 normalny;
											// 20 najwiekszy; -20 najmniejszy
	lkMessageType	m_msgType;				// klasa wiadomosci
	lkInt64			m_objectID;				// ID obiektu, ktory to wyslal
	lkMsgData		m_data;					// nadana wiadomosc
};


////////////////////////////////////////////////////////////////////////
//	Is server entry used or not in class lkMsgClient?
#define	LK_ENTRY_FREE	0
#define LK_ENTRY_USED	1


////////////////////////////////////////////////////////////////////////
//	Do ilu serwerow moze jednoczesnie nalezec klient komunikatow
#define LK_SERVER_ENTRY_LEN 32


////////////////////////////////////////////////////////////////////////
//	Typedefs
typedef	HANDLE	lkMutex;
#endif