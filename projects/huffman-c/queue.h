/*
**	QUEUE.H		kolejka priorytetowa
**
**	Autor:	Michal Pomaranski
**	Kontakt:	mpomanran@elektron.elka.pw.edu.pl
**	Historia:
**			9.11.2000	pierwsza wersja
**
**	Kategoria:	PUBLIC DOMAIN
**
**	Opis funkcji:
**		queue*	initQueue 		(void)
**			inicjuje kolejke i zwraca do niej adres
**			jesli zwroci NULL, to wystapil blad
**
**		queue*	insertElemQueue 	(queueData d, int priority, 
**							 queue *q);
**			dolacza do kolejki q nastepny element, o wartosci d
**			i priorytecie priority. 
**
**		queue*	removeElemQueue 	(queue *q);
**			usuwa z kolejki element o najmniejszym priorytecie.
**			zwraca wskaznik do struktury queue, ktora uzykownik
**			musi zdealokowac we wlasnym zakresie
**
**	Algorytm:
**		Kolejka zostala zaimplementowana jako lista dwukierunkowa.
**		Elementy o najnizszych priorytetach sa przechowywane
**		na poczatku. Funkcje zaznaczaja element pusty (przydatne
**		podczas inicjacji i przegladania) jako element o priorytecie
**		MAXINT. MAXINT jest straznikiem zatrzymania petli
**		podczas wyszukiwania miejsca do wstawienia
**		
**
**	Do zrobienia:
**		- stworzyc tablice, w ktorej beda przechowywane elementy
**		  o najmniejszym, najwiekszym i kilku posrednich 
**		  priorytetach (optymalizacja wstawiania)
**
*/

#ifndef __QUEUE_H
#define __QUEUE_H

typedef void * queueData;

struct queueStruct
{
	queueData	data;
	int		priority;

	struct queueStruct *next;
	struct queueStruct *prev;
};

typedef struct queueStruct queue;

queue*	initQueue 		(void);
queue*	insertElemQueue 	(queueData d, int priority, queue *q);
queue*	removeElemQueue 	(queue **q);

#endif