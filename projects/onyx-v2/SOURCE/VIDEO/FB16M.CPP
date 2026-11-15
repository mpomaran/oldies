//
//      frameBuffer16m
//                  frameBuffer dla trybow truecolor. implementacja.
//
//      Onyx 3d ver. 2  (c) 2000 by Michal Pomaranski
//           If you want to use any of this code, please contact me:
//           mpomaranski@poczta.onet.pl or phone me: +4860463719

#include "mappers.h"                    // po prostu mappery
#include "vfb.h"                        // virtual frame buffer - klasa
                                        // podstawowa
#include "fb16m.h"
#include "..\low-lev\vesa.h"
#include "..\misc\defs.h"

static int mode;

bool frameBuffer16m::init(int m)
{
        // sprawdzamy, czy tryb jest dostepny
        switch(m)
        {
          case VMODE800x600x16m:             // tryb 800x600
               if (!checkMode(mode=VMODE800x600x16m))
                  return false;
               x = 800; y = 600;
               break;
          case VMODE640x480x16m:
               if (!checkMode(mode=VMODE640x480x16m))
                  return false;
               x = 640; y = 480;
               break;
          case VMODE320x200x16m:
               if (!checkMode(mode=VMODE320x200x16m))
                  return false;
               x = 320; y = 200;
               break;
          default:
               return false;
        }

        // inicjujemy buforki
        buff = new char [x*y*3];
        if (!buff) return false;
        LeftClip = TopClip = 0;
        RightClip=x;
        BotClip=y;
        scanlineLen = x;
        return true;
}

bool frameBuffer16m::initZBuff()
{
        // najpierw nalezy wywolac init()
        if (!x || !y)
           return false;

        zbuffer = new int [x*y];
        if (!zbuffer)
           return false;

        return true;
}

void frameBuffer16m::deleteBuff()
{
        if (buff)
           delete buff;
}

void frameBuffer16m::deleteZBuff()
{
        if (zbuffer)
           delete zbuffer;
}

// ustawia parametry obcinania
void frameBuffer16m::setClip(unsigned left, unsigned right,
                             unsigned top, unsigned bottom)
{
  LeftClip = left;
  RightClip = right;
  BotClip = bottom;
  TopClip = top;
}

void frameBuffer16m::fill(int color)
{
  int i;

       for (i=0; i<x*y*3; i+=3) *(int *)(buff+i) = color;
}


void frameBuffer16m::show(void)
{
  copyToScreen((int *)buff);
}

void frameBuffer16m::fillZBuff(int value)
{
  int i;

        for (i=0; i<x*y; i++)
            zbuffer[i] = value * 0x10000;
}

void frameBuffer16m::initVideoMode(void)
{
        setVideoMode(mode);
}

void frameBuffer16m::copy(char *b)
{}
