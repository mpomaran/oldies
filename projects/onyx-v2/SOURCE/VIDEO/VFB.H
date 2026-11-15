//
//      FrameBuffer
//                  klasa podstawowa dla frameBufferkow
//
//      Onyx 3d ver. 2  (c) 2000 by Michal Pomaranski
//           If you want to use any of this code, please contact me:
//           mpomaranski@poczta.onet.pl or phone me: +4860463719

#ifndef __VFB_H
#define __VFB_H

#include "mappers.h"

class virtualFrameBuffer{
        protected:
                 int x,y;               // rozmiary bufora
                 char *buff;            // pamiëç przeznaczona na ten bufor
                 int  *zbuffer;         // pamiëc przeznaczona na z-bufor
        public:
                 // jesli zwroci false - nic z tego, tryb nieobslugiwany,
                 //       przynajmniej nie przez ten framebuffer
                 virtual bool init(int mode) = 0;
                 virtual bool initZBuff() = 0;

                 virtual void deleteBuff() = 0;
                 virtual void deleteZBuff() = 0;

                 // ustawia parametry obcinania
                 virtual void setClip(unsigned left, unsigned right,
                                        unsigned top, unsigned bottom) = 0;

                 virtual void fill(int color) = 0;
                 virtual void copy(char *buff) = 0;
                 virtual void show(void) = 0;
                 virtual void fillZBuff(int value) = 0;

                 virtual void initVideoMode(void) = 0;

                 virtual void getSize (int &sizeX, int &sizeY);

                 // rysowanie trojkatow
                 // przyjalem nastepujaca konwencje nazywania funkcji
                 //  g,t - Gouraud i/lub teksturowanie
                 //  Z - Z-bufor
                 virtual inline void gtTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text)=0;
                 virtual inline void gtZTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text)=0;
                 virtual inline void tTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text)=0;
                 virtual inline void tZTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text)=0;
};

#endif