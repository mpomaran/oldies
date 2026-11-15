#include "random.h"
#include "noise.h"

void generateNoise(char *buff)
{
  char *end = buff + 320*200;
  char color;

  for (; buff<end; buff++){
      color = *buff;
      if (!(color&48))
            *buff = color + (getRandom()&0xf);
      else
            *buff = color - (getRandom()&0xf);
  }
}

void drawBar(int x, int y, int dlugosc,char *buff)
{
 char *dst = buff + x + y*320;
 char color;

 color = getRandom()&0x1f + 32;
 for (; dlugosc--;){
     *dst = color;
     dst+=320;
 }
}

void generateBars(char *buff)
{
 int i;
 int x, startY, dlugosc;

 for (i=0; i<BARS_NO*0.15; i++){
     x = getRandom() %319;
     startY = 0;
     dlugosc = 199;
     drawBar(x,startY, dlugosc,buff);
 }

 for (i=0; i<BARS_NO*0.75; i++){
     x = getRandom() %319;
     startY = getRandom()%180;
     dlugosc = getRandom() % 20;
     drawBar(x,startY, dlugosc,buff);
 }
}
