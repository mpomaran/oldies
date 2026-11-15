//
//      3DIO.CPP       -       implementacja I/O objektu
//
//      ONYX 3D (c) 2000 by Michal Pomaranski
//

#include "..\math\vector3d.h"           // aparat matematyczny
#include "..\math\vertex3d.h"
#include "..\math\matrix.h"
#include "..\math\transform.h"
#include "..\video\vfb.h"               // wyswietlanie
#include "list.h"                       // do listy obiektow
#include "object.h"                     // definicja klasy
#include "text.h"                       // ciagi uzywane podczas I/O
#include <iostream.h>                   // i/o
#include <strstream.h>                  // i/o wewnetrzne
#include <stdio.h>                      // i/o dla C
#include <float.h>
#include <iomanip.h>                    // setw()
#include <string.h>
#include <stdlib.h>
#include <assert.h>

// ladowanie pliku A0 (zmodyfikowany ASC)
// zwraca 0 jesli sie nie powiodlo
int object3d::loadA0 (const char *fname, char *text, int textNo)
{
  FILE *in;
  float numb;
  int faceNo;
  int i;
  int objectsNo;

        in = fopen (fname, "rt");
        if (!in)
           return 0;

        fscanf (in, "%d", &objectsNo);
        fscanf (in, "%d", &vertexesNo);
        fscanf (in, "%d", &faceNo);
        // ladowanie vertexow
        if (vertexes) delete vertexes;
        vertexes = new vertex3d[vertexesNo];
        for (i=0; i<vertexesNo; i++)
        {
          fscanf (in, "%f", &numb);
          vertexes[i].x() = numb;

          fscanf (in, "%f", &numb);
          vertexes[i].y() = numb;

          fscanf (in, "%f", &numb);
          vertexes[i].z() = numb;
          vertexes[i].u =  (char)rand();
          vertexes[i].v = (char)rand();
        }

        // ladowanie trojkatow
        while (!getTriangleList().empty())
              getTriangleList().delFirst();

        getTriangleList().init();
        for (i=0; i<faceNo; i++)
        {
          triangle *tr = new triangle;

          fscanf (in, "%f", &numb); tr->v1 = (int)numb;
          fscanf (in, "%f", &numb); tr->v2 = (int)numb;
          fscanf (in, "%f", &numb); tr->v3 = (int)numb;
          tr->type = gtz;               // rodzaj trojkata - gouraud + tekstura
          tr->texture = text;
          tr->textureNo = textNo;
          getTriangleList().addElemFirst ((void *)tr);
        }

        // ladowanie nastepnych objektow
        // kasowanie i alokacja pamieci
        objectList.init();
        while (!objectList.viewed())
              delete (object3d *)objectList.getNext();
        objectList.init();
        while (!objectList.empty()) objectList.delFirst();

        objectList.init();
        object3d *o;
        for (i=1; i<objectsNo; i++)
        {
              o = new object3d;
              o->loadA0(in, text, textNo);
              objectList.addElemFirst((void *)o);
        }

        fclose (in);

        return 1;
}

int object3d::loadA0 (FILE *in, char *text, int textNo)
{
  float numb;
  int faceNo;
  int i;

        fscanf (in, "%d", &vertexesNo);
        fscanf (in, "%d", &faceNo);

        assert (vertexesNo >= 0);
        assert (faceNo >= 0);

        // ladowanie vertexow
        if (vertexes) delete vertexes;
        vertexes = new vertex3d[vertexesNo];
        for (i=0; i<vertexesNo; i++)
        {
          fscanf (in, "%f", &numb);
          vertexes[i].x() = numb;

          fscanf (in, "%f", &numb);
          vertexes[i].y() = numb;

          fscanf (in, "%f", &numb);
          vertexes[i].z() = numb;
          vertexes[i].u =  (char)rand();
          vertexes[i].v = (char)rand();
        }

        // ladowanie trojkatow
        while (!getTriangleList().empty())
              getTriangleList().delFirst();

        for (i=0; i<faceNo; i++)
        {
          triangle *tr = new triangle;

          fscanf (in, "%f", &numb); tr->v1 = (int)numb;
          fscanf (in, "%f", &numb); tr->v2 = (int)numb;
          fscanf (in, "%f", &numb); tr->v3 = (int)numb;
          tr->type = gtz;               // rodzaj trojkata - gouraud + tekstura
          tr->texture = text;
          tr->textureNo = textNo;
          triangleList.addElemFirst ((void *)tr);
        }

        return 1;
}

// wyjscie
// format:
//         wszystkie liczby sa zapisywane jako ciag ascii w formacie
//         dziesietnym.
//         w nawiasach trojkatnych zapisywane jest, to co powinno sie
//         znalezc w rzeczywistym pliku
//
//         plik wyglada nastepujaco:
//         Object 3D ONYX LIB file
//         SystemVersion: <wersja systemu *100 (aktualnie 200)
//         VertexesNo: <ilosc wierzcholkow w objekcie>
//         ObjectsNo: <ilosc objektow 'potomnych'>
//         FacesNo: <ilosc trojkatow w objekcie>
//
//         VertexesList:
//         <tutaj leci VertexesNo vertexow>
//
//         FacesList:
//         <tutaj leca opisy trojkatow>
//
//         ObiectList:
//         <tutaj sa opisy kolejnych ObjectsNo objektow>
ostream& operator<<(ostream &s, object3d &obj)
{
  s << BANNER_FILE_STR << endl;     // naglowek
  s << SYS_VER_STR << " " << ONYX3D_SYSTEM_VERSION << "\n"; // wersja systemu
  s << VERTEXES_NO_STR << " " << obj.vertexesNo << "\n";

  // liczymy ilosc objektow
  unsigned objectsNo=0;
  obj.objectList.init();
  while (!obj.objectList.viewed())
  {
    objectsNo++;
    obj.objectList.getNext();
  }

  s << OBJECTS_NO_STR << " " << objectsNo << "\n";

  // liczymy ilosc trojkatow
  unsigned facesNo=0;
  obj.triangleList.init();
  while (!obj.triangleList.viewed())
  {
    facesNo++;
    obj.triangleList.getNext();
  }

  s << FACES_NO_STR << " " << facesNo << "\n\n";

  // teraz opisy kolejnych vertexow
  s << VERTEXES_LIST_STR << "\n";
  for (int i=0; i<obj.vertexesNo; i++)
      s << obj.vertexes[i];

  // teraz opisy kolejnych trojkatow
  s << FACES_LIST_STR << "\n";
  triangle *tr;
  obj.triangleList.init();
  tr = (triangle *)obj.triangleList.getFirst();
  while (!obj.triangleList.viewed())
  {
    s << *tr;
    tr = (triangle *)obj.triangleList.getNext();
  }

  // teraz kolejne objekty
  object3d *o;
  s << OBJECTS_LIST_STR << "\n";
  obj.objectList.init();
  while (!obj.objectList.viewed())
  {
    o = (object3d *)obj.objectList.getNext();
    s << *o;
  }

  return s;
}

// laduje ciag znakow az do napotkania znaku konca wiersza
// in: s - strumien we
//     buff - bufor, do ktorego ladujemy znaki
//     len - dlugosc bufora
// out: brak
void readLine (istream &s, char *buff, int len)
{
  char c;
  int i=0;

        s.get(c);
        // za znak konca wiersza uznajemy 0x0a (zapewni to tez nam zgodnosc
        // z U**Xem). Znak 0x0d, wystepujacy pod dosem, ignorujemy.
        while ((i<(len-1)) && (c != 0x0a))
        {
          if (c != 0x0d){
             buff[i] = c;
             i++;
          }
          s.get(c);
        }
        buff[i]=0;
}

istream& operator>>(istream &s, object3d &obj)
{
  char buff[80];
  int systemVersion, vertexesNo, objectsNo, facesNo;
  int i;

  // ladujemy identyfikator
  readLine (s, buff, 80);
  if (strcmp(buff, BANNER_FILE_STR))     // czy sie zgadza?
     return s;

  // ladujemy wersje systemu
  s >> setw(sizeof(buff)) >> buff;
  if (strcmp(buff, SYS_VER_STR))         // czy poprawna komenda?
     return s;
  s >> systemVersion;
  if (systemVersion > ONYX3D_SYSTEM_VERSION)
     return s;

  // ilosc wierzcholkow
  s >> setw(sizeof(buff)) >> buff;
  if (strcmp(buff, VERTEXES_NO_STR))
     return s;
  s >> vertexesNo;

  // ilosc objektow
  s >> setw(sizeof(buff)) >> buff;
  if (strcmp(buff, OBJECTS_NO_STR))
     return s;
  s >> objectsNo;

  // ilosc face'ow
  s >> setw(sizeof(buff)) >> buff;
  if (strcmp(buff, FACES_NO_STR))
     return s;
  s >> facesNo;

  // teraz mozemy ladowac objekt

  // ladowanie vertexow
  s >> setw(sizeof(buff)) >> buff;
  if (strcmp(buff, VERTEXES_LIST_STR))
     return s;

  if (obj.vertexes) delete obj.vertexes;
  obj.vertexes = new vertex3d[vertexesNo];
  obj.vertexesNo = vertexesNo;
  for (i=0; i<vertexesNo; i++)
      s >> obj.vertexes[i];

  // ladowanie trojkatow
  s >> setw(sizeof(buff)) >> buff;
  if (strcmp(buff, FACES_LIST_STR))
     return s;

  // kasowanie i alokacja pamieci
  obj.triangleList.init();
  while (!obj.triangleList.viewed()) delete (triangle *)obj.triangleList.getNext();
  obj.triangleList.init();
  while (!obj.triangleList.empty()) obj.triangleList.delFirst();

  triangle *tr;
  tr = new triangle;
  for (i=0; i<facesNo; i++)
  {
        tr = new triangle;
        s >> *tr;
        obj.getTriangleList().addElemFirst((void *)tr);
  }

  // ladowanie objektow
  s >> setw(sizeof(buff)) >> buff;
  if (strcmp(buff, OBJECTS_LIST_STR))
     return s;

  // kasowanie i alokacja pamieci
  obj.objectList.init();
  while (!obj.objectList.viewed())
        delete (object3d *)obj.objectList.getNext();
  obj.objectList.init();
  while (!obj.objectList.empty()) obj.objectList.delFirst();

  object3d *o;
  for (i=0; i<objectsNo; i++)
  {
        o = new object3d;
        s >> *o;
        obj.getObjectList().addElemFirst((void *)o);
  }

  return s;
}

ostream& object3d::save (ostream &s)
{
  int ID = 44;

  // zapis identyfikacji
  s.write ((char *)&ID, sizeof (ID));

  // liczymy ilosc objektow
  unsigned objectsNo=0;
  objectList.init();
  while (!objectList.viewed())
  {
    objectsNo++;
    objectList.getNext();
  }

  s.write ( (char *)&objectsNo, sizeof (objectsNo));

  // liczymy ilosc trojkatow
  unsigned facesNo=0;
  triangleList.init();
  while (!triangleList.viewed())
  {
    facesNo++;
    triangleList.getNext();
  }

  s.write ( (char *)&facesNo, sizeof (facesNo));

  // teraz ilosc vertexow i ich opisy
  s.write ( (char *)&vertexesNo, sizeof (vertexesNo));
  for (int i=0; i<vertexesNo; i++)
  {
      vertexes[i].save(s);
      assert (!s.fail());
  }

  // teraz opisy kolejnych trojkatow
  triangle *tr;
  triangleList.init();
  while (!triangleList.viewed())
  {
    tr = (triangle *)triangleList.getNext();
    tr->save(s);
    assert (!s.fail());
  }

  // teraz kolejne objekty
  object3d *o;
  objectList.init();
  while (!objectList.viewed())
  {
    o = (object3d *)objectList.getNext();
    o->save(s);
  }

  return s;
}

istream& object3d::load (istream &s)
{
  int ID;

  // sprawdzam poprawnosc
  s.read ( (char *)&ID, sizeof (ID) );
  if (ID != 44) return s;

  // ladowanie ilosci objektow
  unsigned objectsNo;
  s.read ( (char *)&objectsNo, sizeof (objectsNo));
  // ladowanie ilosci trojkatow
  unsigned facesNo;
  s.read ( (char *)&facesNo, sizeof (facesNo));
  // ladowanie ilosci vertexow
  s.read ( (char *)&vertexesNo, sizeof (vertexesNo));

  // ladowanie vertexow
  if (vertexes) delete vertexes;
  vertexes = new vertex3d[vertexesNo];
  vertex3d vrt;
  for (int i=0; i<vertexesNo; i++)
  {
      vertexes[i].load(s);
      assert (!s.fail());
  }

  // ladowanie trojkatow
  // kasowanie i alokacja pamieci
  triangleList.init();
  while (!triangleList.viewed()) delete (triangle *)triangleList.getNext();
  triangleList.init();
  while (!triangleList.empty()) triangleList.delFirst();

  triangle *tr;
  for (i=0; i<facesNo; i++)
  {
        tr = new triangle;
        tr->load(s);
        getTriangleList().addElemFirst((void *)tr);
        assert (!s.eof());
        assert (!s.fail());
  }

  // ladowanie objektow
  // kasowanie i alokacja pamieci
  objectList.init();
  while (!objectList.viewed())
        delete (object3d *)objectList.getNext();
  objectList.init();
  while (!objectList.empty()) objectList.delFirst();

  object3d *o;
  objectList.init();
  for (i=0; i<objectsNo; i++)
  {
        o = new object3d;
        o->load(s);
        getObjectList().addElemFirst((void *)o);
  }

  return s;
}

void object3d::get (char *buff, int buffLen)
{
  istrstream str(buff, buffLen);

  load(str);
}

// zwraca adres do tekstur
char *object3d::loadTexture (istream &s)
{
  char ID;
  int texNo;
  char *textures;

  // znacznik poprawnosci pliku
  s.read ( &ID, sizeof (ID));
  if (ID != 'T')
     return NULL;

  // ilosc tekstur
  s.read ( (char *)&texNo, sizeof (texNo));
  assert (texNo>0);

  // tu powinna byc obsluga pamieci
  textures = new char [256*256*texNo];
  assert (textures != NULL);

  // ladowanie tekstur
  s.read (textures, texNo*256*256);
  getTexture (textures);

  return textures;
}

void object3d::getTexture (char *buff)
{
  triangle *tr;

  triangleList.init();
  while (!triangleList.viewed())
  {
    tr = (triangle *)triangleList.getNext();
    tr->texture = tr->textureNo*256*256+buff;
  }

  objectList.init();
  while (!objectList.viewed())
  {
    object3d *o = (object3d *)objectList.getNext();
    list *l = &o->triangleList;
    l->init();
    while (!l->viewed())
    {
      tr = (triangle *)l->getNext();
      tr->texture = tr->textureNo*256*256+buff;
    }
  }
}

