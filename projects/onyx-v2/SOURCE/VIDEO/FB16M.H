//
//      frameBuffer16m
//                  frameBuffer dla trybow truecolor
//
//      Onyx 3d ver. 2  (c) 2000 by Michal Pomaranski
//           If you want to use any of this code, please contact me:
//           mpomaranski@poczta.onet.pl or phone me: +4860463719

#ifndef __FB16M_H
#define __FB16M_H

#include "mappers.h"                    // po prostu mappery
#include "vfb.h"                        // virtual frame buffer - klasa
                                        // podstawowa

#include <iostream.h>

class frameBuffer16m : virtual public virtualFrameBuffer{
        public:
                 bool init(int mode);
                 bool initZBuff();

                 void deleteBuff();
                 void deleteZBuff();

                 // ustawia parametry obcinania
                 void setClip(unsigned left, unsigned right,
                                        unsigned top, unsigned bottom);

                 void fill(int color);
                 void copy(char *buff);
                 void show(void);
                 void fillZBuff(int value);

                 void initVideoMode(void);

                 void getSize (int &sizeX, int &sizeY)
                 {
                   sizeX = x; sizeY = y;
                 }

                 // rysowanie trojkatow
                 // przyjalem nastepujaca konwencje nazywania funkcji
                 //  g,t - Gouraud i/lub teksturowanie
                 //  p - Phong
                 //  Z - Z-bufor
                 inline void ptZTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text, char *phongMask);
                 inline void gtZTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text);
                 inline void gtTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text);
                 inline void tZTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text);
                 inline void tTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text);

};

inline void frameBuffer16m::ptZTriangle(vertex2d &a, vertex2d &b, vertex2d &c,
                                                 char *text, char *phongMask)
{
  ptClipZ16mTriangle(&a, &b, &c, this->buff, text, phongMask, this->zbuffer);
}

inline void frameBuffer16m::gtZTriangle(vertex2d &a, vertex2d &b, vertex2d &c, char *text)
{
  gtClipZ16mTriangle(&a, &b, &c, this->buff, text, this->zbuffer);
}

inline void frameBuffer16m::gtTriangle(vertex2d &a, vertex2d &b, vertex2d &c, char *text)
{
  gtClip16mTriangle(&a, &b, &c, this->buff, text);
}

inline void frameBuffer16m::tZTriangle(vertex2d &a, vertex2d &b, vertex2d &c, char *text)
{
  tClipZ16mTriangle(&a, &b, &c, this->buff, text, this->zbuffer);
}

inline void frameBuffer16m::tTriangle(vertex2d &a, vertex2d &b, vertex2d &c, char *text)
{
  tClip16mTriangle(&a, &b, &c, this->buff, text);
}


#endif