/*
**	TREE.C	drzewo binarne
**
**	Autor:	Michal Pomaranski
**	Kontakt:	mpomanran@elektron.elka.pw.edu.pl
**	Historia:
**			21.11.2000	pierwsza wersja buildTree()
**			28.11.2000  usunieto bledy z buildTree()
**
**	Kategoria:	PUBLIC DOMAIN
**
**	Zajrzyj do pliku tree.h w celu zasiegniecia dodatkowych
**	informacji.
*/

#include <malloc.h>
#include <assert.h>

#include "queue.h"
#include "bitio.h"
#include "misc.h"
#include "tree.h"

/*******************************************************************/
tree*		buildTree (int *freqTable, int symbolLen)
{
	int i;
	int symbNo = 1 << symbolLen;
	symbol *s;
	queue *q, *tLeft, *tRight;
	
	/* stworzenie kolejki z symbNo poddrzewami */
	q = initQueue();
	for (i=0; i<symbNo; i++)
	{
		static tree *t;

		/* jesli symbol nie wystepuje w pliku, to po co sie	*/
		/* nim przejmowac ?						*/
		if (freqTable[i] != 0)
		{
			t = (tree *) malloc (sizeof (tree));
			s = (symbol *) malloc (sizeof (symbol));

			s->len = symbolLen; s->value = i;

			t->left = t->right = 0;
			t->type = LEAF; t->data = s;

			q = insertElemQueue ((queueData *)t, freqTable[i], q);
		}
	}

	/* kolejka zostala stworzona, teraz nalezy stworzyc z niej 	*/
	/* drzewo 									*/
	do
	{
		tLeft = removeElemQueue (&q);
		tRight = removeElemQueue (&q);

		if (tRight != NULL)		/* czy jest co laczyc ?	*/
		{
			static int prior;
			static tree *t;

			assert (tLeft && tRight);

			t = (tree *) malloc (sizeof (tree));
			t->left = (tree *)tLeft->data;
			t->right = (tree *)tRight->data;
			t->type = NODE;

			prior = tLeft->priority + tRight->priority;
			q = insertElemQueue ((queueData *)t, prior, q);
		}
	} while (tRight != NULL);
	
	PRINT ("\n----------------\ntree ok\n-------------------\n");

	/* drzewo zostalo zbudowane */
	return (tree *)tLeft->data;
}	

/*******************************************************************/
int		sT (tree *t, int (* bPutN)(int, int))
{
	if (t->type == NODE)
	{
		bPutN (1, NODE);
		sT (t->left, bPutN);
		sT (t->right, bPutN);
	}
	else
	{
		bPutN (1, LEAF);
		bPutN (t->data->len, t->data->value);
		return 1;
	}
}

int		saveTree (tree *t, int symbolLen, int (* bPutN)(int, int))
{
	bPutN (24, symbolLen); 
	sT (t, bPutN);

	return 1;
}

/*******************************************************************/
tree *	lT (int (* bGetN)(int), int symbolLen)
{
	static int bit;
	tree *t;

	/* alokacja pamieci pod drzewo					*/
	t = (tree *)malloc (sizeof (tree));
	if (!t)
		return NULL;

	/* odczytywanie i interpretacja struktury drzewa		*/

	bit = bGetN(1);
	if (bit == LEAF)		/* to jest lisc drzewa			*/
	{
		symbol *s;

		s = (symbol *)malloc (sizeof (symbol));
		if (!s)
			return NULL;

		s->len = symbolLen;
		s->value = bGetN (symbolLen);

		t->type = LEAF;
		t->data = s;
	}
	else				/* to jest wierzcholek drzewa		*/
	{
		tree *left, *right;

		left = (tree *)malloc (sizeof (tree));
		right = (tree *)malloc (sizeof (tree));

		if (!left || !right)
			return NULL;

		left = lT (bGetN, symbolLen);
		right = lT (bGetN, symbolLen);

		assert (left != NULL);
		assert (right != NULL);

		t->type = NODE;
		t->left = left; t->right = right;
	}

	return t;
}			

tree *	loadTree (int (* bGetN)(int), int *symbolLen)
{
	tree *t;

	*symbolLen = bGetN (24);
	t = lT (bGetN, *symbolLen);

	return t;
}

/*******************************************************************/
void		delTree (tree *t)
{
	assert (t != NULL);

	if (t->type == LEAF)
	{
		free (t->data);
		free (t);
	}
	else
	{
		assert (t->left != NULL);
		assert (t->right != NULL);

		delTree (t->left);
		delTree (t->right);

		free (t);
	}
}
