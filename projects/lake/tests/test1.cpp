////////////////////////////////////////////////////////////////////////
//	Open LK Project
//
//	MOTTO:
//		Read me as an open book.
//
//	(c) 2002 by Michal Pomaranski
//	mpomaranski@poczta.onet.pl
//
//	!!!COMMECIAL SOFTWARE!!!
//	You aren't allowed to use this software without a written permission.
//
//
//	test1.cpp	:	Test file
//
//	IMPLEMENTATION
//		Test dla identyfikacji objektow
//
//
////////////////////////////////////////////////////////////////////////

#include "stdio.h"				// I/O
#include "../base.object.h"		// testowany modul


////////////////////////////////////////////////////////////////////////


class class1 : public lkBaseObject
{
public:
	class1 ()
	{
		setClassID (fourCC ('c','l','s','1'));
	}
};



int main ()
{
	class1	c1,c2;

	// recna zmiania id obiektu
	c1.setObjectID(c2.getObjectID());
//	c2.setClassID (fourCC ('a','b','c','d'));

	if (c1 == c2)
	{
		printf ("Ten sam obiekt\n");
	}
	else
	{
		printf ("Obiekty sa rozne\n");
	}

	getchar();

	return 0;
}