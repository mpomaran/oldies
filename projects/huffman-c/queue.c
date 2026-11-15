/*
**	QUEUE.C		kolejka priorytetowa. implementacja
**
**	Autor:	Michal Pomaranski
**	Kontakt:	mpomanran@elektron.elka.pw.edu.pl
**
**	Kategoria:	PUBLIC DOMAIN
**
**	Zajrzyj do pliku queue.h w celu zasiegniecia dodatkowych
**	informacji.
*/

#include <stdlib.h>		/* NULL			*/
#include <malloc.h>		/* alloc, free 		*/

#include "queue.h"
#include "misc.h"


int onlist (queue *q)
{
	int r=1;

		while (q->next)
		{
			r++; q = q->next;
		}
	return r;
}

/*******************************************************************/
queue*	initQueue 		(void)
{
  queue *q;

	q = malloc (sizeof (queue));	/* alokacja pamieci 	*/
	if (!q)
		return NULL;		/* blad			*/

	q->data = NULL;			/* zainicjowanie		*/
	q->next = q->prev = NULL;	/* pierwszego elementu	*/
	q->priority = MAXINT;		/* kolejki			*/

	return q;
}

/*******************************************************************/
queue*	insertElemQueue 	(queueData d, int priority, queue *q)
{
  queue *p;		/* prev & current - poprzedni i aktualnie	*/
  register queue *c;     	/* przegladany element kolejki		*/
  static queue *temp;

	c=q; p=NULL;

	while (c->priority < priority)
	{
		p = c;
		c = c->next;
	}

	temp = malloc (sizeof (queue));	/* wstawianie nowego	*/
	if (!temp)					/*   elementu		*/
		return NULL;			/* brak pamieci		*/

	temp->data = d; temp->priority = priority;
	temp->prev = p; temp->next = c;

	if (p)				/* uaktualnienie 		*/
		p->next = temp;		/* powiazan na liscie	*/
	else
		q = temp;			/* pierwszy element?	*/

	c->prev = temp;

	return q;
}

/*******************************************************************/
/* zawsze usuwamy pierwszy element listy					 */
/*******************************************************************/
queue*	removeElemQueue 	(queue **q)
{
  static queue *result;

	if ((*q)->priority == MAXINT)		/* czy jest cos na liscie*/
		return NULL;

	result = *q;
	*q = (*q)->next;

	return result;
}