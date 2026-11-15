/*
 *      CUBE.H          Tworzenie szescianu
 *      Sarin/!ArisE!
 */

#ifndef __CUBE_H
#define __CUBE_H

#include <sar3d.h>

/* Funkcja tworzaca szescian
 * cube - wskaznik na tablice, gdzie zostana umieszczone wierzcholki
 * object - wskaznik na tablice przechowywujaca objekty
 * bitmap - wskaznik do bitmapki narzuconej na szescian
 * srodek - wskaznik na punkt znajdujacy sie w srodku ciezkosci szescianu
 * skala  - ile jednostek bedzie miala krawedz
 * phong - czy objekt bedzie cieniowany
 */
void makeCube (vertex3d *cube, object3d *object, char *bitmap, vertex3d *srodek, double skala, int phong);

#endif