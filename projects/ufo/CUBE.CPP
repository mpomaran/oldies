/*
 *      CUBE.H          Tworzenie szescianu
 *      Sarin/!ArisE!
 */

#include "cube.h"
#include <sar3d.h>

/* Wierzcholki typowego szescianu */
static vertex3d wierzcholki[8] = {
       {-0.5,-0.5,-0.5,0,0}, {0.5,-0.5,-0.5,255,0},
       {0.5,0.5,-0.5,255,255}, {-0.5,0.5,-0.5,0,255},
       {-0.5,-0.5,0.5,0,0}, {0.5,-0.5,0.5,255,0},
       {0.5,0.5,0.5,255,255}, {-0.5,0.5,0.5,0,255} };

/* Kolejnosc krawedzi */
static int krawedzie[12*3] = {
       0,2,1,
       0,3,2,
       5,6,7,
       5,7,4,
       4,1,5,
       4,0,1,
       6,2,3,
       6,3,7,
       1,6,5,
       1,2,6,
       4,3,0,
       4,7,3};

/* Funkcja tworzaca szescian
 * cube - wskaznik na tablice, gdzie zostana umieszczone wierzcholki
 * object - wskaznik na tablice przechowywujaca wskazniki do objektow
 * bitmap - wskaznik do bitmapki narzuconej na szescian
 * srodek - wskaznik na punkt znajdujacy sie w srodku ciezkosci szescianu
 * skala  - ile jednostek bedzie miala krawedz
 */
void makeCube (vertex3d *cube, object3d *object, char *bitmap, vertex3d *srodek, double skala, int phong)
{
  int i;

  // 1. Wypelnij wierzcholki
  for (i=0; i<8; i++){
      cube[i].x = wierzcholki[i].x * skala + srodek->x;
      cube[i].y = wierzcholki[i].y * skala + srodek->y;
      cube[i].z = wierzcholki[i].z * skala + srodek->z;

      cube[i].u = wierzcholki[i].u;
      cube[i].v = wierzcholki[i].v;

      cube[i].bitmap = bitmap;
      cube[i].phongFlag = phong;
  }
  // 2. Stworz objekt
  object->vertexesTab = (vertex3d **)memAlloc(sizeof(vertex3d*)*12*3);

  // 3. Wypelnij objekt
  for (i=0; i<12*3; i++)
      object->vertexesTab[i] = cube + krawedzie[i];

  object->bitmap = bitmap;
  object->vrtCnt = 12*3;

  // 4. Czy liczyc phonga ?
  if (phong)
     computeNormals(object);
}

