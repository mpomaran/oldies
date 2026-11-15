/*
**        GIF 2 GPH Converter
**
**        By Sarin/!ArisE!    PUBLIC DOMAIN
*/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <eos.h>

char *obr;
char *pal;

char buff[200][320][3];
char blurBuff[200][320][3];
int pix = 1;

void loadGif(char *name)
{
 int x,y,i,j;
 int colNo;
 char r;
 int c;
 float ratio;
 char *b;
 int col;

 obr = load_external_gif_handle(name);
 pal = gif_palette;

 r=0;
 ratio = 4;
 c=0;
 for (x=0; x<320; x++)
     for (y=0; y<200; y++) {
      colNo = *(obr+x+y*320);
      colNo *=3;
      col = ((*(pal + colNo)*ratio) + (*(pal + colNo + 1)*ratio) + (*(pal + colNo + 2)*ratio))/3;
      buff[y][x][2] = col;
      buff[y][x][1] = col;
      buff[y][x][0] = col;

 }
 for (x=0; x<320; x+=pix)
     for (y=0; y<200; y+=pix){
         colNo=0;

         for (i=0; i<pix; i++)
             for (j=0; j<pix; j++)
                 colNo+=buff[y+i][x+j][0];

        colNo /= 1<<pix;

        colNo &= 252;

        for (i=0; i<pix; i++)
             for (j=0; j<pix; j++){
                 buff[y+i][x+j][0] = colNo;
                 buff[y+i][x+j][1] = colNo*0.8;
                 buff[y+i][x+j][2] = colNo;
             }
     }
}

void saveGph(char *name)
{
  FILE *out;
  int x,y;
  char color;
  char *dst = (char *)0xa0000;

  if (NULL == (out = fopen(name, "wb")))
  {
     printf("FAILED !!!\n");
     exit(-1);
  }

  // zapisz naglowek

  // ilosc kolorow
  fputc(0x40,out); fputc(0,out); fputc(0,out); fputc(0,out);
  // rozdzielczosc X
  fputc( (320/pix)&0xff, out); fputc( ((320/pix)&0xff00)>>8,out); fputc(0,out); fputc(0,out);
  // rozdzielczosc Y
  fputc( (200/pix)&0xff, out); fputc(((200/pix)&0xff00)>>8,out); fputc(0,out); fputc(0,out);


  for(y=0; y<200; y+=pix)
           for (x=0; x<320; x+=pix){
               color = buff[y][x][0];
               color>>=2;
               fputc(color, out);
           }

  fclose(out);
}


void main(int argc, char *argv[])
{
  int x,y;
  char name[13];

  if (argc!=4){
     printf("    þ Usage: \n\tgif2gph <gifname> <gphname> <aspect ratio>\n");
     return;
  }

  printf("    þ Gif to Gph converter by Sarin/!ArisE!. PUBLIC DOMAIN\n");

  pix = atoi(argv[3]);
  if (pix < 1 || pix > 200){
     printf("    þ Invalid aspect ratio value (should be 1-200)\n");
     return;
  } else
     printf("    þ Aspect ratio valid. Output resolution will be %dx%d.\n",320/pix, 200/pix);


  printf("    þ Loading %s...",argv[1]);
  loadGif(argv[1]);
  printf("OK\n");
  printf("    þ Saving %s...",argv[2]);
  saveGph(argv[2]);
  printf("OK\n");

  printf("    þ Everything went OK.\n");
}