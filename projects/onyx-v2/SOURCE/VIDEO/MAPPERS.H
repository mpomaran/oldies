/*
**      Wspolne definicje dla wszystkich moich mapperow
**
**      (c) 2000 by Michal Pomaranski
*/

#ifndef _MAPPER_H
#define _MAPPER_H

#include "..\math\vertex3d.h"
#include "..\math\vector3d.h"

class vertex2d{
        public:
                int x,y;
                int z;          /* z-bufor       */
                unsigned char color;
                unsigned char u,v;        /* wsp. tekstury */
                int visible;    /* do obcinania  */
                unsigned char phU, phV;   /* wsp. tekstury do Phong'a */

                inline vertex2d& operator=(vertex3d &vert)
                {
                  x = (int)vert[0]; y = (int)vert[1]; z = (int)vert[2];
                  u = vert.u; v = vert.v;
                  phU = 127+127*vert.norm[0]; phV = 127+127*vert.norm[1];
                  color = vert.color;
                  return *this;
                }

                inline vertex2d& operator=(vertex2d const &vert)
                {
                  x = vert.x; y = vert.y; z = vert.z;
                  u = vert.u; v = vert.v;
                  phU = vert.phU; phV = vert.phV;
                  color = vert.color;
                  return *this;
                }
};

extern unsigned char colorTable[256][256];      /* tablica definiujaca cienie */
extern int BehindClip;                        /* obcinanie przed obs. */

/* nazewnictwo jest nastepujace:
**  pierwsze litery: g - gorouatd, t - teksturowanie
**  kolejny wyraz - Clip albo Noclip - czy obcinane czy tez nie
**  jesli wystepuje literka Z - to znaczy ze jest zbufor
**  kolejny czlon - 256c lub 16m - w ilu kolorach mapper dziala */
void gtClipZ16mTriangle (vertex2d *a, vertex2d *b, vertex2d *c, char *buff,
                         char *text, int *zbuff);
void gtClip16mTriangle  (vertex2d *a, vertex2d *b, vertex2d *c, char *buff,
                         char *text);
void tClipZ16mTriangle  (vertex2d *a, vertex2d *b, vertex2d *c, char *buff,
                         char *text, int *zbuff);
void tClip16mTriangle   (vertex2d *a, vertex2d *b, vertex2d *c, char *buff,
                         char *text);

#endif