/*
**	CMPRSS.C		kompresja algorytmem Huffmana
**
**	Autor:	Michal Pomaranski
**	Kontakt:	mpomanran@elektron.elka.pw.edu.pl
**	
**	Zajrzyj do pliku cmprss.h w celu zasiegniecia dodatkowych
**	informacji.
**
**	Historia:
**		21.11.2000 - compressHuffman()
**		22.11.2000 - makeLookupTable()
**		28.11.2000 - poprawino blad w compressHuffman()
**
**	Do zrobienia:
**		- prawidlowa obsluga bledow zwracanych przez put i get
**
*/

#include <malloc.h>
#include <assert.h>

#include "misc.h"
#include "tree.h"
#include "cmprss.h"

/*******************************************************************
**
**	makeLookupTable()
**		rekurencyjne tworzenie tablicy przyspieszajacej
**		kompresje
**
** 	lT 	- wskaznik do lookup table
**	t	- wskaznik do drzewa z ktorego nalezy stworzyc tablice
**	level - na jakim poziomie drzewa znajduje sie funkcja
**	path	- sciezka do danego elementu
*/
void	makeLookupTable (symbol *lT, tree *t, int level, unsigned path)
{
	assert (t->type == NODE || t->type == LEAF);
	if (t->type == NODE)
	{
		makeLookupTable(lT, t->right, level+1, path | (1<<level));
		makeLookupTable(lT, t->left, level+1, path);
	}
	else
	{
		lT[t->data->value].value = path;
		lT[t->data->value].len = level;
	}
}

/*******************************************************************/
int	compressHuffman (compressStruct *cS)
{
	int	*freqTable;
	int 	symbolsNo;
	int 	i;
	int	currSymbol;
	tree  *compressTree;
	symbol *lookupTable;
	int	*dataToCompress;

	/* tworzymy tablice czestosci wystepowania symboli	*/
	symbolsNo = 1 << cS->symbolLen;
	freqTable = (int *) malloc (sizeof (int)*symbolsNo);
	lookupTable = (symbol *) malloc (sizeof (symbol)*symbolsNo);
	dataToCompress = (int *) malloc (sizeof (int)*cS->dataLen);
	if (!freqTable || !lookupTable || !dataToCompress)
		return FAIL;

	PRINT ("c1\n");

	for (i=0; i<symbolsNo; i++)		/* czyszczenie	*/
		freqTable[i] = 0;			/* tablicy		*/

	for (i=0; i<cS->dataLen; i++)
	{
		dataToCompress[i]= currSymbol = cS->bGetN (cS->symbolLen);
		freqTable[currSymbol]++;
	}

	printf ("c2\n");
		
	/* tworzymy drzewo kompresji i zwalnianie zbednej mem	*/
	compressTree = buildTree (freqTable, cS->symbolLen);
	free (freqTable);

	PRINT ("c3\n");

	saveTree (compressTree, cS->symbolLen, cS->bPutN);

	/* tworzymy lookup-table					*/
	makeLookupTable (lookupTable, compressTree, 0, 0);


	/* zapisywanie przetworzonych danych			*/
	for (i=0; i<cS->dataLen; i++)
	{
		currSymbol = dataToCompress[i];
		
		cS->bPutN (lookupTable[currSymbol].len, 
				lookupTable[currSymbol].value);
	}

	PRINT ("c5\n");

	/* zwalnianie pamieci						*/
	free (lookupTable);
	free (dataToCompress);
	delTree (compressTree);

	return SUCCESS;
}
