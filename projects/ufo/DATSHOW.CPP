#include "dat.h"
#include "datshow.h"
#include "blur.h"
#include "noise.h"

char buffer[64000];

/* Kopiuje obrazek w formacie .dat do bufora o wymiarach 320x200 */
void    copyDatImage(datImage *dat, char *dest, int filter)
{
  int toSkipX,toSkipY;          /* ile pixelkow przeskakujemy w pionie i poziomie */
  int x,y;
  int sizeX, sizeY;
  int i;
  int flag;
  char *tmp;
  char *src,*dst;

  if (filter&BLUR_FILTER)
     dst = buffer;
  else
     dst = dest;

  sizeX = 320;
  sizeY = 200;
  src = dat->image;
  tmp = dst;
  toSkipX = 320/dat->x;
  flag = toSkipY = 200/dat->y;

  for (y=0; y<sizeY; y++){
      for (x=0; x<sizeX; x+=toSkipX){
          *dst++ = *src;
          for (i=1; i<toSkipX; i++){
              *dst++ = *src;
          }
          src++;
      }
      /* Czy nie trzeba cofnac w pionie */
      if (!(--flag)){
         flag = toSkipY;
      }
      else{
         src-=dat->x;
      }
  }
  dst = tmp;

  if (filter&NOISE_FILTER)
         generateNoise(dst);

  if (filter&BARS_FILTER)
         generateBars(dst);

  if (filter&BLUR_FILTER)
         blur(dst,dest);
}
