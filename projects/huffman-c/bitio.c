/*
**	BITIO.C		bit input/output
**				biblioteka pozwalajaca na zapis/odczyt plikow
**				bit po bicie
**	Autor:	Michal Pomaranski
**	Kontakt:	mpomanran@elektron.elka.pw.edu.pl
**	
**	Zajrzyj do pliku bitio.h w celu zasiegniecia dodatkowych
**	informacji.
**
**
**	Do zrobienia (optymalizacja) - ta czesc komentarza do kasacji:
**		- zamienic bitFILE.bitsUsed na bitFILE.bitsFree,
**		  co umozliwi usuniecie odejmowania w get i put (uwazaj
**		  na bitsUsed w innych funkcjach
**		- get i put niepoprawnie sprawdza wystapienie bledu
**		- get powinna zwracac 0 i nie-0, a nie 0 i 1
*/

#include	"misc.h"
#include	"bitio.h"
#include	<stdio.h>		/* operacje i/o 	*/
#include	<malloc.h>		/* alloc, free	*/
#include	<assert.h>		/* assert		*/

/*******************************************************************/
bitFILE*	bitFopen	(char *fPath, char *mode)
{
  bitFILE *bF;
  FILE *f;

	f = fopen (fPath, mode);	/* otwieranie pliku i alokacja */
	if (!f) return NULL;
	bF = (bitFILE *)malloc (sizeof (bitFILE));
	if (!bF) return NULL;

	bF->pF = f;				/* inicjacja pol struktury	*/
	bF->buff = 0; bF->bitsUsed = 0;

	return bF;
}

/*******************************************************************/
int 		bitFclose 	(bitFILE *f)
{
  int error;

	if (f->bitsUsed != 0)		/* zapis bufora 			*/
		fputc (f->buff, f->pF);

	error = fclose (f->pF);
	if (error)
		return error;

	free (f);
}
	
/*******************************************************************/
int		bitGet	(bitFILE *f)
{
  int result;

	if (f->bitsUsed == 0)		/* nie zaladowano zadnego 	*/
	{					/* bajtu				*/
		result = fgetc (f->pF);
		if (result == -1) 	/* blad !!!				*/
			return -1;
		else
			f->buff = result;

		f->bitsUsed = 8;
	}

	result = (powersOf2[8 - f->bitsUsed] & f->buff) != 0 ? 1 : 0; 
/*	result = powersOf2[f->bitsUsed] & f->buff != 0 ? 1 : 0; */
	f->bitsUsed--;

	return result;

}  

/*******************************************************************/
int		bitPut	(int bitValue, bitFILE *f)
{
  int result;

	if (f->bitsUsed == 8)		/* trzeba zapisac bufor		*/
	{
		result = fputc (f->buff, f->pF);
		if (result == EOF)	/* blad podczas zapisu		*/
			return EOF;

		f->bitsUsed = 0;
		f->buff = 0;
	}

	f->buff |= bitValue == 0 ? 0 : powersOf2[f->bitsUsed];
	f->bitsUsed++;

	return 1;
}

/*******************************************************************/
int		bitGetN	(int n, bitFILE *f)
{
  int result;
  int bit;
  int i;

	assert (n<=24);
	result=0;

	for (i=0; i<n; i++)
	{

		bit = bitGet (f);
		if (bit == -1)
			return -1;

		if (bit != 0)
			result |= powersOf2[i];
	}

	return result;
}

/*******************************************************************/
int 		bitPutN	(int n, int bitsValue, bitFILE *f)
{
	int result;
	int i;

	for (i=0; i<n; i++)
	{
		result = bitPut (bitsValue & powersOf2[i], f);
		if (result == -1)
			return -1;
	}

	return 0;
}