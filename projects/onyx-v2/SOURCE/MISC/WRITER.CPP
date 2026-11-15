#include "gphfiles.h"
#include "writer.h"

/* Funkcja wypisuje litere na ekran */
void graphPutC(datImage *letter, int x, int y,char *buffer)
{
  int sizeX, sizeY;                     /* Rozmiar litery w pikselach */
  int i,j;                              /* Liczniki petli             */
  char *dst;
  char *src;
  char color;

  src = letter->image;
  sizeX = letter->x; sizeY = letter->y;
  dst = buffer + x + 320*y;
  for (i=0; i<sizeY; i++){
      for (j=0; j<sizeX; j++){
          color = *src++;               /* Czy w tym miejscu znak nie jest */
          if(color) *dst = color;       /* przezroczysty                   */
          dst++;
      }
      dst+=(320-sizeX);                 /* Nastepna linia */
  }
}

/* Funkcja wypisuje tekst na ekranie */
void drawText(gphHandle *font, char *text, int align,char *out)
{
 int charCount;
 int i;
 int x, y;
 datImage dat;

 /* Policz dlugosc tekstu */
 charCount=0;
 while(*(text + charCount)) charCount++;

 /* Sprawdz, czy tekst zmiesci sie w jednej linijce */
 /* Jesli nie, to wyjscie                           */
 if (font->x*charCount>320) return;

 switch(align){
        case TOP_LEFT:
                  x = 0;
                  y = 0;
                  break;
        case TOP_RIGHT:
                  x = 320 - font->x*charCount;
                  y = 0;
                  break;
        case BOTTOM_LEFT:
                  x = 0;
                  y = 200 - font->y;
                  break;
        case BOTTOM_RIGHT:
                  x = 320 - font->x*charCount;
                  y = 200 - font->y;
                  break;
        default:
                  return;
 }

 /* Wypisz tekst literka po literce */
 for (i=0; i<charCount; i++){
     getDatImageInfo(font, &dat, *(text+i));
     graphPutC(&dat,x,y,out);
     x+=font->x;
 }
}


