/*
**	MAIN.C	funkcja glowna
**
**	Autor:	Michal Pomaranski
**	Kontakt:	mpomanran@elektron.elka.pw.edu.pl
**	
**
**	Historia:
**		28.11.2000 - pierwsza wersja, sluzaca to testu 
**				compressHuffman()
**
**	Do zrobienia:
**		- prawidlowa obsluga bledow zwracanych przez put i get
**
*/

#include "bitio.h"
#include "cmprss.h"

static bitFILE *in;
static bitFILE *out;

/* Funkcje pomocnicze */
int bGetN (int);
int bPutN (int, int);
int compress(char *, char *);

/* Fukcja glowna */
int main (int argc, char *argv[])
{
	return compress ("test.in", "test.out");
}

int bGetN (int n)
{
	return bitGetN (n, in);
}

int bPutN (int n, int value)
{
	return bitPutN (n, value, out);
}

int compress (char *i, char *o)
{
  compressStruct cS;

	in = bitFopen (i, "rb");
	out = bitFopen (o, "wb");

	if (!in || !out)
	{
		printf ("blad i/o przy fopen");
		return -1;
	}

	cS.dataLen = 200000;
	cS.symbolLen = 8;

	cS.bGetN = bGetN; cS.bPutN = bPutN;

	return compressHuffman (&cS);
}

	
