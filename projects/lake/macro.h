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
//	lake.common.h		Frequently used header 
//
//	Features:
//
//		-	shortcuts for common types
//
//
////////////////////////////////////////////////////////////////////////

#ifndef __LK_VER_0005_MACRO
#define __LK_VER_0005_MACRO

// Zwraca unsigned z 4 znakow
inline	unsigned	fourCC (char a, char b, char c, char d)
{
	return ((unsigned)a) + ((unsigned)b<<8) + ((unsigned)c<<16) + ((unsigned)d<<24);
}

#endif