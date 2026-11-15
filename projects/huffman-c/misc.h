/*
**	MISC.H		inne delkaracje
**
**	Autor:	Michal Pomaranski
**	Kontakt:	mpomanran@elektron.elka.pw.edu.pl
**	Historia:
**			9.11.2000	pierwsza wersja
**
**	Kategoria:	PUBLIC DOMAIN
**
*/

#ifndef __MISC_H
#define __MISC_H

#define DEBUG

#define	SUCCESS	0
#define	FAIL		-1

void PRINT (char *);

#define MAXINT (1 << 24)

extern const unsigned powersOf2 [32];

typedef struct 
{
	int	len;
	int	value;
} symbol;

#endif
