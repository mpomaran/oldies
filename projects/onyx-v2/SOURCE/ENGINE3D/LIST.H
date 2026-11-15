//      LIST.H                  Lista dwukierunkowa
//      coded by Sarin/!ArisE!  (sarin@czart.pulawy.pl)
//
//      13.12.1997 Pulawy/Poland

//      I didn't want to use list from standard c++ lib, 'coz
//      i don't know c++ very much and I wanted to optimize it

#ifndef __LIST_H
#define __LIST_H

#ifndef NULL
 #define NULL 0
#endif

class   listElem {              // klasa reprezentujaca element listy
        public:
                 listElem(void *elem);
                 listElem();
                 ~listElem();
//        protected:
                 listElem *prev;// previous element
                 listElem *next;// next element
                 void *data;    // this value is stored in the list

};

class   list : private listElem {
        private:
                 listElem *first;// pierwszy element listy
                 listElem *last; // ostatni element listy
                 listElem *current;
        public:
                 list(void *elem);
                 list(void);

                 void addElemFirst(void *elem); // dodaje element na poczatek
                 void addElemLast(void *elem); // dodaje element na koniec
                 void init();                  // inicjuje przegladanie
                 void *getFirst();    // zwraca pierwszy element listy
                 void *getLast();     // zwraca ostatni element listy
                 void *getNext();
                 void *getPrev();
                 void *getCurr();


                 void *delFirst();    // jw. ale kasuje z listy
                 void *delLast();     // jw. ale kasuje z listy
                 void *delNext();
                 void *delPrev();
                 void *delCurr();

                 bool empty();        // czy lista pusta?
                 bool viewed();       // czy juz przejrzana?
};

#endif


