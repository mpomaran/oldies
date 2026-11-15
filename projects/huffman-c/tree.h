/*
**	TREE.H	drzewo binarne
**
**	Autor:	Michal Pomaranski
**	Kontakt:	mpomanran@elektron.elka.pw.edu.pl
**	Historia:
**			9.11.2000	pierwsza wersja
**
**	Kategoria:	PUBLIC DOMAIN
**
**	Opis funkcji:
**		tree*	buildTree (int *freqTable, int sylbolLen)
**			tworzy drzewo o odpowiedniej strukturze z kolejki
**			priorytetowej. Zwraca wskaznik do tego drzewa.
**			musi byc zdefiniowana tablica freqTable o dlugosci
**			2^symbolLen, gdzie bylyby zapisane priorytety
**
**		int	saveTree (tree* t, int symbolLen, 
**				f, int (bPut *)(int, bitFILE *));
**			zapisuje utworzone drzewo t za pomaca funkcji bPut.
**			Zwraca to samo, co bPut;
**			Jest to fuknkcja rekurencyjna.
**
**
**		tree* loadTree (bitFILE *f, int (bGet *)(bitFILE *),
**					int *symbolLen);
**			laduje drzewo z pliku o deksryptorze f, za pomaca
**			funkcji bGet. Zrwaca wskaznik do tego drzewa,
**			jesli odczyt sie nie powiodl, to zwraca NULL
**			symbolLen - tam bedzie zapisana dlugosc symbolu w 
**			bitavh
**
**		void		delTree (tree *t);
**			kasuje pamiec zajeta przez drzewo
**
**	Format zapisu:
**			Pierwsze 24 bity, to dlugosc symbolu
**			Nastepnie zostaje zapisana rekurencyjnie struktura
**			drzewa.
**			Po bicie NODE zawsze wyjstepuje zapis 2 poddrzew,
**			po bicie LEAF wystepuje dlugosc_symbolu bitow
**			zawierajacych symbol
*/

#ifndef __TREE_H
#define __TREE_H

#include "queue.h"
#include "bitio.h"
#include "misc.h"

/* stale definiuja, czy element jest wezlem drzewa czy lisciem */
#define NODE (0)
#define LEAF (1)

typedef symbol* treeData;
struct treeStruct 
{
	struct treeStruct *left;
	struct treeStruct *right;

	int	 type;
	treeData data;
};
typedef struct treeStruct tree;

tree*		buildTree (int *freqTable, int sylbolLen);
int		saveTree (tree *t, int symbolLen, int (*bPutN)(int, int));
tree *	loadTree (int (*bGetN)(int), int *symbolLen);
void		delTree (tree *t);

#endif