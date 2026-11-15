/*
**	BITIO.H		bit input/output header file
**				biblioteka pozwalajaca na zapis/odczyt plikow
**				bit po bicie
**	Autor:	Michal Pomaranski
**	Kontakt:	mpomanran@elektron.elka.pw.edu.pl
**	Historia:
**			8.11.2000	pierwsza wersja. zdefiniowane 5
**					podstawowych funkcji
**
**	Kategoria:	PUBLIC DOMAIN
**
**	Opis funkcji:
**		bitFILE * bitFopen (char *fPath, char *mode)
**			otwiera plik do zapisu binarnego analogicznie
**			do funkcji fopen();
**
**		int bitFclose (bitFILE *f);
**			zamyka plik alalogicznie z funkcja fclose();
**
**		int bitGet (bitFILE *f);
**			odczytuje wartosc pojedynczego bitu z pliku
**			zwraca -1 jesli sie nie powiodlo
**
**		int bitPut (int bitValue, bitFILE *f);
**			zapisuje bit o wartosci bitValue do pliku f
**			zwraca -1 jesli sie nie powiodlo
**
**		int bitGetN (int n, bitFILE *f);
**			odczytuje n bitow z pliku f. n nie moze byc wieksze
**			niz 16. zwraca -1 jesli sie nie powiodlo.
**
**		int bitPutN (int n, int bitsValue, bitFILE *f);
**			zapisuje n bitow o wartosci bitsValue do pliku f
**
**	Format zapisu:
**		jesli oznaczymy kolejno naplywajace bity przez 1, 2, ..., z
**		to kolejnosc zapisu wyglada nastepujaco:
**
**			12345678 9abcdefg hijklmno
**			\bajt 1/ \bajt 2/ \bajt 3/
**
*/

#ifndef __BITIO_H
#define __BITIO_H

#include	<stdio.h>

/* struktura uzywana przez funkcje dokonujace operacji na plikach */
typedef struct
{
	FILE *pF;			/* wskaznik na deskryptor pliku 	*/
	unsigned char buff;	/* bufor, w ktorym przechowywany	*/
					/* jest bajt				*/
	int bitsUsed;		/* ile bitow w buforze jest zajetych*/
} bitFILE;

bitFILE*	bitFopen	(char *fPath, char *mode);
int 		bitFclose 	(bitFILE *f);
int		bitGet	(bitFILE *f);
int		bitPut	(int bitValue, bitFILE *f);
int		bitGetN	(int n, bitFILE *f);
int 		bitPutN	(int n, int bitsValue, bitFILE *f);

#endif

