/**
 *	Koder adaptacyjnego kodu Huffmana
 *
 *	@author: Micha³ Pomarañski, mpomaran@elka.pw.edu.pl
 *
 *	----------------------------------
 *	(c) 2001 by Micha³ Pomaranski
 *	do wykorzystania w bibliotece Cage
 *	----------------------------------
 *
 *	Algorytm:
 *		Patrz "Struktury danych w jêzyku C", A. Drozdek, D.L.Simon, WNT 1996
 *
 *	Uwagi:
 *		Ze wzgldu na uzyty algorytm, aby uzyskac wyzszy stopien kompresji, 
 *		zaleca sie oddzielna kompresje roznych rodzajow danych, tzn. 
 *		jesli chcemy zakodowac dwa bloki danych, tekst oraz obraz, 
 *		to za pomoca jednej pary metod init/code kompresujemy tekst, 
 *		a za pomoca drugiej pary obraz.
 *		
**/




#ifndef _HUFFMAN_CODER_H
#define _HUFFMAN_CODER_H




#include <stdio.h>
#include "huffman.tree.h"




/**
 *	huffmanCoder: klasa zajmujaca sie kompresja
 *
 *	@remarks
 *		void init ( FILE *in, FILE *out, unsigned buffSize, unsigned symbolSize)
 *			inicjacja dzialania kompresora
 *			in, out - plik wejsciowy/wyjsciowy
 *			symbolSize - dlugosc symbolu w bitach
 *			buffSize - rozmiar bufora danych poddawanych kompresji
 *
 *		void code ( void )
 *			kompresja bloku danych, musi zostac zainicjowana przedtem za pomoca
 *			metody init ()
**/


class huffmanCoder
{
	public:
		void		init	(FILE *in, FILE *out, unsigned buffSize, 
							unsigned symbolSize = 8);
		void		code	(void)

					huffmanCoder() : i(NULL), o(NULL) {};

	private:
		huffmanTree	tree;			// drzewo kompresji
		FILE		*i, *o;			// pliki we/wy
};





#endif