#include <sar3d.h>
#include <stdlib.h>
#include <conio.h>
#include <eos.h>

#include "blur.h"
#include "noise.h"
#include "random.h"
#include "flash.h"
#include "monopal.h"

#include "cubepart.h"

char scr[320][200];

void main()
{

   init_eos(_psp);

   initRandom(320000);

   // 1. Inicjacja
   initCubes();

   setVideoMode(0x13);
   flash((int *)0xa0000,255);

  /* Paleta kolorow */
  setMonoPalette(0.75,0.75,0.50, 0, 63, 64);
  setLUTRegister(255,63,63,63);
 // petla glowna

   while (1){
         showCubesFrame((char *)scr);
         generateBars((char *)scr);
         blur((char *)scr, (char *)scr);
         blur((char *)scr,(char *)0xa0000);
         copyBackground((int *)scr);
   }
   uninitCubes();

   setVideoMode(0x03);
}



