#include "monopal.h"

void    setMonoPalette(double kr, double kg, double kb, int firstLut, int lastLut, int noOfColors)
{
 int ikr, ikg, ikb;     // te same wspolczynnini co pozyzej ale jako fixed point
 int i;
 char r;
 char g;
 char b;
 double ratio;
 double color;

 color = 0;
 ratio = (double)noOfColors/(double)(lastLut - firstLut + 1);
 for (i=firstLut; i<=lastLut; i++){
     r = color*kr;
     g = color*kg;
     b = color*kb;
     setLUTRegister(i, r, g, b);
     color += ratio;
 }
}