//
//      OBJECT.H        -       definicja objektu
//
//      ONYX 3D (c) 2000 by Michal Pomaranski
//

#ifndef __OBJECT_H
#define __OBJECT_H

#include "..\math\vector3d.h"           // aparat matematyczny
#include "..\math\vertex3d.h"
#include "..\math\matrix.h"
#include "..\math\transform.h"

#include "..\video\vfb.h"               // wyswietlanie

#include "list.h"                       // do listy obiektow

#include <stdio.h>
#include <iostream.h>                   // i/o

// t - tekstura, z - zbufor, g - Gouraud, p - Phong
enum {t, gt, tz, gtz, ptz};

// plaszczyzna obcinajaca widziana przez obserwatora
// (druga plaszczyzna ma rownanie z=BehindClip i jest niewidzialna (automatyczne
// obcinanie przez z-bufor)
extern float AftClip;
extern int BehindClip;

class triangle {
     public:
       unsigned v1, v2, v3;             // offsety (numery) wierzcholkow
       unsigned type;                   // rodzaj trojkata
       char     *texture;               // tekstura nalozona na trojkat
       char     *phongMask;
       int      textureNo;              // numer tekstury

       vector3d norm;                   // normalna do trojkata

       friend ostream& operator << (ostream &s, triangle &tr);
       friend istream& operator >> (istream &s, triangle &tr);

       ostream& save (ostream &s);
       istream& load (istream &s);
       void get (char const *buff);
};

class object3d{
      private:
               list     objectList;
               list     triangleList;  // lista trojkotow
               unsigned vertexesNo;     // ilosc wierzcholkow
               vertex3d *vertexes;      // lista wierzcholkow
               vertex3d *tempVert;      // tutaj beda przeksztalcone vertexy
               vertex3d boundary[6];    // ograniczenie

               int loadA0 (const char *fname, char *text, int textureNo);
      public:
               vector3d position;
               float    scaleX, scaleY, scaleZ;

               object3d  ();
               ~object3d ();

               // mode = 0 - nowa transformacja, 1 = na bazie starej tr.
               object3d& transform(transformation &tr, int mode=0);
               object3d& rotateNormals(transformation &tr);

               // przeksztalcenie perspektywiczne k-wsp. persp., sizeX, sizeY - wielkosc obrazu
               object3d& perspective(int k, int sizeX, int sizeY);
               void     show(virtualFrameBuffer &frBuffer);

               void     findBoundary();
               void     computeNormals();       // liczy normalne w objekcie
               void     computeLight();         // liczy swiatlo

               // dostep do listy objektow, vertexow, trojkatow
               inline list& getObjectList(void) { return objectList; };
               inline vertex3d*& getVertexes(void) { return vertexes; };
               inline unsigned& getVertexesNo(void) { return vertexesNo; };
               inline list& getTriangleList(void) { return triangleList; };

               // we/wy
               // ladowanie pliku ASC
               int loadA0 (FILE *in, char *text, int textureNo);

               // zapis i odczyt w formacie onx (ASCII)
               friend ostream& operator<<(ostream &s, object3d &obj);
               friend istream& operator>>(istream &s, object3d &obj);

               // zapis i odczyt w postaci binarnej
               istream& load (istream &s);
               ostream& save (ostream &s);

               // kopiuje dane objektu z pamieci do struktury wewnetrznej
               void get (char *buff, int len);

               // ladowanie tekstury (zwraca adres tekstur)
               char* loadTexture (istream &s);
               void getTexture (char *buff);
};

#endif