/*
**	CMPRSS.H		kompresja algorytmem Huffmana
**
**	Autor:	Michal Pomaranski
**	Kontakt:	mpomanran@elektron.elka.pw.edu.pl
**	Historia:
**			21.11.2000	pierwsza wersja
**
**	Kategoria:	PUBLIC DOMAIN
**
**	Opis funkcji:
**		compressHuffman (compressStruct *cS);
**			funkcja dokonuje kompresji Huffmana
**			Komunikacja z funkcja odbywa sie za pomoca 
**			struktury compressStruct, opisanej ponizej.
**
**	Opis struktur:
**		compressStruct
**		{
**			int dataLen;
**			int symbolLen;
**			int (*bGetN)(int, int);
**			int (*bPutN)(int, int);
**		}
**			dataLen - ilosc symboli do kompresji
**			symbolLen - dlugosc pojedynczego symbolu
**				w bitach
**			bGetN, bPutN - funkcje odczytujace i zapisujace n bitow
**			o postaci:
**				int bGetN (int iloscBitow, int wartoscBitow);
*/

#ifndef __CMPRSS_H
#define __CMPRSS_H

typedef struct  
{
	int	dataLen;		/* ilosc tych danych			*/

	int	symbolLen;		/* rozmiar symbolu (np. 8 bitow dla */
					/* tekstu					*/

	int (*bGetN)(int);	/* wskaznik do funkcji odczytujacej	*/
					/* bity					*/
	int (*bPutN)(int, int);	/* wskaznik do funkcji zapisujacej	*/
					/* bity					*/
} compressStruct;

int	compressHuffman (compressStruct *cS);

#endif