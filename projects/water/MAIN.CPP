//
//        Przyklad wykorzystujacy efekt wody
//

#include "water.h"

#include <conio.h>  /* kbhit()                    */
#include <stdlib.h> /* rand()                     */
#include <eos.h>    /* Modulesy                   */
#include <math.h>   /* sin(), cos()               */

// Te wstawki sa jedynymi fragmentami, ktore nalezy zmienic, jesli
// nie masz watcoma
#pragma aux setLUTRegister =     \
        "mov    al,    0ffh"     \
        "mov    dx,    03c6h"    \
        "out    dx,    al"       \
        "mov    dx,    03c8h"    \
        "mov    al,    ah"       \
        "out    dx,    al"       \
        "mov    dx,    03c9h"    \
        "mov    al,    cl"       \
        "out    dx,    al"       \
        "mov    al,    bh"       \
        "out    dx,    al"       \
        "mov    al,    bl"       \
        "out    dx,    al"       \
        parm [ah] [bl] [bh] [cl] \
        modify [eax ebx ecx edx];

#pragma aux setVideoMode =      \
        "int    10h"            \
        parm [eax]              \
        modify [eax];

void setPalette(char *palette)
{
 int    lutElem=0;

 for (; lutElem<256; lutElem++)
     setLUTRegister(lutElem, *(palette++), *(palette++), *(palette++));
}

void main()
{
  char *buff;
  int i;
  int  card=0,port=1,irq=2,dma=3,infos=4;
  int x,y;


  // inicjacja eos'a i procki robiacej wode
  init_eos(_psp);
  initWater();

  // ladujemy modka
  card=detect_sound_card  (1,&port,&irq,&dma,&infos);
  load_module ("beingthe.mod",1,44100,0);

  // wyswietlenie durnego bannerka
  setVideoMode(0x03);
  direct_send("\n\0\x13                                 Sarin/!ArisE!                                 \0\0");
  direct_send("\n\0\x8                         To jest tylko program testowy\0\0");
  direct_send("\n          Nie rozpowszechniaj tego, gdyz nic oprocz kodu nie jest moje\0\0");
  getch();
  setVideoMode(0x03);


  // ladjemy obrazek
  buff = load_internal_gif_handle("suplogo.gif");

  // tryb graficzny
  setVideoMode(0x13);

  // ustawiamy palete
  setPalette(gif_palette);

  // odpalamy modka
  play_module();

  // ok. teraz woda

  i=0;
  while(!kbhit()){

          if (!(i%10))                // czy narysowac punkt ?
             waterPlot(rand()%310 , rand()%190, rand()%40);

         i++;

          x = sin(i/20.)*150 + 160;
          y = cos(i/25.)*90 + 100;
          waterPlot(x,y,20);
          waterPlot(160+sin(i/30.)*(x/2),100+cos(i/30.)*(y/2), 20);

          x = cos(i/43.)*150 + 160;
          y = sin(i/30.)*80 + 100;
          waterPlot(x,y,20);
          waterPlot(x*cos(i/40.), 199-y, 20);

          computeWater(buff, (char *)0xa0000);
  }
  getch();

  unInitWater();

//  stop_module();
  clear_module();

  delete buff;
  setVideoMode(0x03);

  direct_send("\n\0\x13                                 Sarin/!ArisE!                                 \0\0");
  direct_send("\n   Jesli chcesz sie ze mna skontaktowac, to pisz: sarin@grzes.czart.pulawy.pl     \0\0\n");
}