/*
**        Efekt wody
**
**        Sarin/!ArisE!
*/

#ifndef __WATER_H
#define __WATER_H

void      initWater(void);                        // inicjuje buforki
void      waterPlot(int x, int y, char dep);      // rysowanie punktu (zrodla fali)

void      computeWater(char *bitmap,char *screen);// liczy wode, rysuje w screen

void      unInitWater(void);
#endif