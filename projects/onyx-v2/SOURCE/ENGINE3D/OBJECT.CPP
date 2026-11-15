//
//      OBJECT.CPP       -       implementacja objektu
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
#include <stdio.h>                      // i/o dla C - dla mnie wygodniejsze
#include <float.h>
#include <iomanip.h>                    // setw()
#include <string.h>
#include <stdlib.h>

// zrodlo swiatla
vector3d sceneLight(0.5,0.5,1);

// konstruktor i destruktor
object3d::object3d()
{
  scaleX=scaleY=scaleZ=1;
  vertexesNo=0;
  vertexes=tempVert=0;
}

object3d::~object3d()
{
  object3d *obj;
  triangle *tr;

  if (!vertexesNo && objectList.empty())
     return;

  if (vertexes)
    delete vertexes;
  if (tempVert)
    delete tempVert;

  // kasowanie listy obiektow
  objectList.init();
  while (!objectList.viewed())
        delete (object3d *)objectList.getNext();
  objectList.init();
  while (!objectList.empty()) objectList.delFirst();

  // kasowanie listy trojkatow
  // kasowanie listy obiektow
  triangleList.init();
  while (!triangleList.viewed())
        delete (triangle *)triangleList.getNext();
  triangleList.init();
  while (!triangleList.empty()) triangleList.delFirst();
}

///////////////////////////////////////////////
// transformacje
object3d& object3d::transform(transformation &tr, int mode)
{
  object3d *obj;
  transformation t;

  t.matrix = tr.matrix;
  t.vector = tr.vector;
  t.vector += position;
  t.addScale(scaleX, scaleY, scaleZ);

  // alokacja pamieci pod tempVert (jesli trzeba)
  if (mode==0 || !tempVert)
  {
    if (tempVert)
       delete tempVert;

       tempVert = new vertex3d [vertexesNo];
       for (int i=0; i<vertexesNo; i++)
         tempVert[i] = vertexes[i];
  }

  // transformacja punktow
  for (int i=0; i<vertexesNo; i++)
    tempVert[i].transform(t);

  // transformacja "podleglych" objektow
  if (objectList.empty())
     return *this;

  objectList.init();
  while(!objectList.viewed())
  {
    obj = (object3d *)objectList.getNext();
    obj->transform(t, mode);
  }

  return *this;
}

object3d& object3d::perspective(int k, int sizeX, int sizeY)
{
 float z;
 vertex3d *v;
 int i;
 object3d *obj;

  // perspektywa
  if (tempVert)
     for (i=0; i<vertexesNo; i++)
     {
       v = tempVert+i;
       z =(*v)[2];
       if (z>=0)
       {
          z /= k;
          if (z==0) z=1;
          (*v)[0] -= sizeX>>1;
          (*v)[1] -= sizeY>>1;
          (*v)[0] /= z;
          (*v)[1] /= z;
          (*v)[0] += sizeX>>1;
          (*v)[1] += sizeY>>1;
       }
     }

  // perspektywa dla objektow potomnych
  if (objectList.empty())
     return *this;

  objectList.init();
  while(!objectList.viewed())
  {
    obj = (object3d *)objectList.getNext();
    obj->perspective(k, sizeX, sizeY);
  }

  return *this;

}


// obrot normalnych
object3d& object3d::rotateNormals(transformation &t)
{
  object3d *obj;

  // jesli nie obrocono punktow, po co obracac normalne?
  if (!tempVert)
     return *this;

  // transformacja punktow
  for (int i=0; i<vertexesNo; i++)
  {
    tempVert[i].norm = vertexes[i].norm;
    tempVert[i].norm *= t.matrix;
  }

  // transformacja "podleglych" objektow
  objectList.init();

  while(!objectList.viewed())
  {
    obj = (object3d *)objectList.getNext();
    obj->rotateNormals(t);
  }

  return *this;
}

float min (float a, float b)
{
  if (a<b) return a;
  return b;
}

float abs (float a)
{
  if (a<0) return -a;
  return a;
}

void object3d::computeLight()
{
  object3d *obj;
  vector3d vector;
  float r;
  int i;

  // swiatlo moze byc liczone tylko na obroconych normalnych
  if (!tempVert)
     return;

  sceneLight /= sceneLight.lenght();
  // transformacja punktow
  for (i=0; i<vertexesNo; i++)
  {
   static float cos_a;
   static vector3d *v;
   static float len;

    v=&(tempVert[i].norm);
    cos_a = sceneLight[0]*(*v)[0]+sceneLight[1]*(*v)[1]+sceneLight[2]*(*v)[2];
    cos_a /= v->lenght();
    if (cos_a<0) cos_a=0;

    // liczymy swiatlo z uwzglednieniem kierunku i odleglosci od obserwatora
    r = tempVert[i].lenght();
    if (r>=AftClip) r = 1;
    else {
         r /= AftClip;
         r *= r;
    }

//    tempVert[i].color = (225*cos_a+30)* (1-r);
    tempVert[i].color = 255*(1-r);
    tempVert[i].norm /= tempVert[i].norm.lenght();
    tempVert[i].norm *= 127;
    tempVert[i].u = tempVert[i].norm[0]+127;
    tempVert[i].v = tempVert[i].norm[1]+127;
  }
  // transformacja "podleglych" objektow
  if (objectList.empty())
     return;

  objectList.init();
  while(!objectList.viewed())
  {
    obj = (object3d *)objectList.getNext();
    obj->computeLight();
  }

  return;
}

// obliczanie normalnych
//Procedura oblicza normalna do plaszczyzny zadanej punktami p1, p2, p3
vector3d computeNormal (vector3d &p1, vector3d &p2, vector3d &p3)
{
  vector3d w2;
  vector3d norm;
  float l;              // dlugosc wektora

   norm = p2-p1; w2 = p2-p3;
   norm *= w2;
   return norm;
}

void object3d::computeNormals (void)
{
 vector3d v1, v2, v3;
 triangle *tr;
 object3d *o;
 vector3d normal;               // wektor normalny do wierzcholka
 int      trNo;                 // ile normalnych dodalismy

  // przegladanie objektow potomnych

  objectList.init();                    // inicjacja przegladania
  if (!objectList.empty())
  {
    while (!objectList.viewed())
    {
      o = (object3d *)objectList.getNext();
      o->computeNormals();
    }
  }

  // przegladanie trojkatow
  triangleList.init();
  while (!triangleList.viewed())
  {
    tr = (triangle *)triangleList.getNext();
    v1 = vertexes[tr->v1];
    v2 = vertexes[tr->v2];
    v3 = vertexes[tr->v3];
    tr->norm = computeNormal (v1, v2, v3);
  }

  // zabieramy sie do vertexow
  for (int i=0; i<vertexesNo; i++)
  {
    // dla kazdego wierzcholka znajdz wszystkie trojkaty, ktore sie stykaja
    triangleList.init();
    normal[0] = normal[1] = normal[2] = 0;
    while (!triangleList.viewed())
    {
      tr = (triangle *)triangleList.getNext();
      if ((tr->v1==i) || (tr->v2==i) || (tr->v3==i))
         normal += tr->norm;
     }

     // dzielimy normalna przez odpowiednia liczbe

    if (normal.lenght())
       vertexes[i].norm = normal/normal.lenght();
    else
       vertexes[i].norm = normal;

    vertexes[i].color = 0;
  }
}

// wyswietla objekt
void     object3d::show(virtualFrameBuffer &frBuffer)
{
  triangle *tr;
  vertex2d v1, v2, v3;
  object3d *o;

  // wyswietlenie objektow potomnych
  objectList.init();                    // inicjacja przegladania
  while (!objectList.viewed())
  {
    o = (object3d *)objectList.getNext();
    o->show(frBuffer);
  }

  // wyswietlenie trojkatow
  triangleList.init();
  while (!triangleList.viewed())
  {
      tr = (triangle *)triangleList.getNext();
      v1 = tempVert[tr->v1];
      v2 = tempVert[tr->v2];
      v3 = tempVert[tr->v3];

      switch (tr->type)                 // rozpoznanie rodzaju trojkata
      {
        case t:
                 frBuffer.tTriangle (v1, v2, v3, tr->texture);
                 break;
        case gt:
                 frBuffer.gtTriangle (v1, v2, v3, tr->texture);
                 break;
        case tz:
                 frBuffer.tZTriangle (v1, v2, v3, tr->texture);
                 break;
        case gtz:
                 frBuffer.gtZTriangle (v1, v2, v3, tr->texture);
                 break;
    }
  }
  // to by bylo na tyle
}

// NIESKONCZONE!!!NIESKONCZONE!!!
// Znajdowanie szescianu ograniczajacego objekt
//      Wierzcholki sa numerowane nastepujaco:
//                     5
//                     ^  2
//                     |/
//               3 <---+---> 4
//                    /|
//                  1  v
//                     6
// NIESKONCZONE!!!
void     object3d::findBoundary()
{
 object3d *o;
 float b_min, b_max;    // najmniejsza/najwieksza znaleziona dotychczas
                        // wspolrzedna

 // 1. znajdz ograniczenie wszystkich objektow potomnych
 objectList.init();                    // inicjacja przegladania
 if (!objectList.viewed())
 {
   o = (object3d *)objectList.getNext();
   o->findBoundary();
 }
}

