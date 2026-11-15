/*
**        Efekt wody
**
**        Sarin/!ArisE!
*/

#define  WATER_SIZE_X      320
#define  WATER_SIZE_Y      200
#define  WATER_BUFF_SIZE   (WATER_SIZE_X*WATER_SIZE_Y*sizeof(short))

#define  WATER_PLOT_PIXEL_SIZE 2

/* Wspolczynnik, od ktorego zalezy stopien 'lepkosci' wody */
#define DELTA 32

#include "water.h"

////////////////////////////////////////////////////////////////////////
// buforki
////////////////////////////////////////////////////////////////////////
static    short *waterBuff;
static    char ktoryBufor; // z ktorego bufora korzystamy w tym przebiegu

////////////////////////////////////////////////////////////////////////
// Funkcje
////////////////////////////////////////////////////////////////////////
void      initWater(void)
{
  int i;
  int *help;        // uzywany do czyszczenia

  waterBuff = new short[WATER_BUFF_SIZE*2];
  help = (int *)waterBuff;

  // czyszczenie buforow
  for (i=0; i<WATER_BUFF_SIZE*2/2; i++)
      *help++ = 0;

  ktoryBufor = 0;
}

// stawianie punktu, ktory jest zrodlem fali
void      waterPlot(int x, int y, char dep)
{
  int i,j;
  short *buff;
  short *buff2;

  buff = waterBuff + ktoryBufor*WATER_BUFF_SIZE + y*WATER_SIZE_X + x;
  buff2 = waterBuff + !(ktoryBufor)*WATER_BUFF_SIZE + y*WATER_SIZE_X + x;

  // rysowanie pikselka
  for (i=0; i<WATER_PLOT_PIXEL_SIZE; i++)
  {
      for (j=0; j<WATER_PLOT_PIXEL_SIZE; j++){
          *buff++ = dep*256;
          *buff2++ = -dep*256;
      }
      buff += WATER_SIZE_X-WATER_PLOT_PIXEL_SIZE;
      buff2 += WATER_SIZE_X-WATER_PLOT_PIXEL_SIZE;
  }
}

void computeWater(char *bitmap, char *buff)
{
  int offset,i;
  short k;
  short *water,*water2;
  int  *help;

  water = (waterBuff + ktoryBufor*WATER_BUFF_SIZE);
  water2 = waterBuff + (!ktoryBufor)*WATER_BUFF_SIZE;
  help = (int *)buff;

  // 1. wyswietlamy wszystko w buforze (bufor 320x200x256 kolorow)
  //    a. zerujemy na dole i gorze bufora
  for (i=0; i<80; i++)
      *help++ = 0;

  help = (int *)(buff + 64000 - 320);

  for (i=0; i<80; i++)
      *help++ = 0;

  //    b. wysietlamy wszystko
  offset = 320;
  for (; offset < 64000-320; offset++)
  {
     // nie mozna stosowac przesunies, bo sa to liczby ze znakiem
     *buff++ = bitmap[offset + water[offset]/256];

     // teraz liczymy wode
     k = (water[offset+1] + water[offset-1] + water[offset+320] + water[offset - 320])/2;
     k -= water2[offset];

     water2[offset] = (k-k/DELTA);
  }

  ktoryBufor = !ktoryBufor;
}

void unInitWater(void)
{
  delete waterBuff;
}



