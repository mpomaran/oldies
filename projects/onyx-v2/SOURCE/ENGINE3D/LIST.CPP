//      LIST.CPP                Lista dwukierunkowa. Implementacja
//      coded by Sarin/!ArisE!  (sarin@czart.pulawy.pl)
//
//      13.12.1997 Pulawy/Poland

#include <assert.h>
#include "list.h"

listElem::listElem(void *elem)
{
        data = elem;
        prev = next = NULL;
}

listElem::listElem(void)
{
        data = NULL;
        prev = next = NULL;
}

listElem::~listElem()
{
        if (prev != NULL) prev->next = next;
        if (next != NULL) next->prev = prev;
}

list::list(void *elem)
{
  last = first = new listElem(elem);
  current = NULL;
}

list::list(void)
{
  last = first = NULL;
  current = NULL;
}

void list::init(void)
{
  current = first;
}

void list::addElemFirst(void *elem)
{
  listElem *lElem = new listElem(elem);

  lElem->prev = NULL;
  lElem->next = first;
  if (first==last==NULL)
    current=first=last=lElem;
  else
  {
    if ((lElem->next) != NULL)
                   (lElem->next)->prev = lElem;
    if (last == NULL) last = lElem;
    first = lElem;
  }
}

void list::addElemLast(void *elem)
{
  listElem *lElem = new listElem(elem);

  lElem->next = NULL;
  lElem->prev = last;
  if (last==first==NULL)
     current=last=first=lElem;
  else
  {
    if ((lElem->prev) != NULL)
                   (lElem->prev)->next = lElem;
    if (last == NULL) first = lElem;
    last = lElem;
  }
}

void* list::getFirst()
{
  return first->data;
}

void* list::getLast()
{
  return last->data;
}

void* list::getNext()
{
  void *elem;
  if (current == NULL) return NULL;
  else elem=current->data;
  current = current->next;
  return elem;
}

void *list::getPrev()
{
  void *elem;
  if (current == NULL) return NULL;
  else elem=current->data;
  current = current->prev;
  return elem;
}

void *list::getCurr()
{
  if (current == NULL) return NULL;
  return current->data;
}

void *list::delFirst()
{
 void *elem;
 listElem *newFirst;

  assert(first != NULL);

  elem = first->data;
  newFirst = first->next;

  delete first;

  first = newFirst;

  return elem;
}

void *list::delLast()
{
 void *elem;
 listElem *newLast;

  assert(last != NULL);

  elem = last->data;
  newLast = last->prev;

  delete last;

  last = newLast;

  return elem;
}

void* list::delNext()
{
 void *elem;

  assert(current != NULL);
  current = current->next;
  if (current == NULL) return NULL;

  elem = current->data;
  delete current;
  return elem;
}

void* list::delPrev()
{
 void *elem;

  assert(current != NULL);
  current = current->prev;
  if (current == NULL) return NULL;

  elem = current->data;
  delete current;
  return elem;
}

void* list::delCurr()
{
 void *elem;

  assert(current != NULL);

  elem = current->data;
  delete current;
  return elem;
}

bool list::empty()
{
 return (first==NULL || last==NULL);
}

// lista jest przejrzana takze wtedy, gdy jest pusta
bool list::viewed()
{
 return (current==NULL || first==NULL || last==NULL);
}



