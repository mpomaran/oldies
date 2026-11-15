/*
**	MISC.C		inne delkaracje
**
**	Autor:	Michal Pomaranski
**	Kontakt:	mpomanran@elektron.elka.pw.edu.pl
**	Historia:
**			9.11.2000	pierwsza wersja
**			28.11.2000	dodano funkcje PRINT (do debuggingu)
**
**	Kategoria:	PUBLIC DOMAIN
**
*/

#include "misc.h"

const unsigned powersOf2 [32] = {1, 2, 4, 8, 16, 32, 64, 128,
	256, 512, 1024, 2048, 4096, 8192, 16384,
	32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304,
	 8388608, 16777216, 33554432, 67108864, 134217728,  268435456, 536870912, 1073741824};

void PRINT (char *c)
{
	#ifdef DEBUG
		printf (c);
	#endif
}