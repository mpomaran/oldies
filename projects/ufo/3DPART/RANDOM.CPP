/*
 *      RANDOM.C                Generator liczb losowych
 *      copyright (c) 1997 by Sarin/!ArisE!
 */

#include <stdlib.h>               /* rand() */
#include "random.h"

static int ktoraLosowa = 0;    /* Ktora jest to liczba z kolei */
static int randomTab[RANDOMS_NUMBER];

void    initRandom(int randomMax)
{
 int i;

 for (i=0; i<RANDOMS_NUMBER; i++)
     randomTab[i] = rand() % randomMax;
 }

int     getRandom()
{
 if (++ktoraLosowa>=RANDOMS_NUMBER) ktoraLosowa=0;
 return randomTab[ktoraLosowa];
}
