/*
 *      GPHFILES.H               Ladowanie pliku GPH i inne rzeczy niezbedne do obslugi
 *      copyright (c) 1997 by Sarin/!ArisE!
 */

#ifndef __GPHFILES_H
#define __GPHFILES_H

#include "dat.h"
#include <eos.h>

#define  INTERNAL       0
#define  EXTERNAL       1

typedef struct {
        int colors;
        int x,y;        /* rozmiar wszystkich plikow w tym pack'u       */
        int no;
        char *image;    /* wskaznik na pierwszy rozmiar                 */
        long *handleFile;
        char *memHandle;
} gphHandle;

gphHandle* loadGphFile(char *name, int mode);  /* mode - 0 - internal, 1 - external */
void    gphFree(gphHandle *handle);
/* Pobiera DatImage zadanego obrazka */
void       getDatImageInfo(gphHandle const  *packHandle, datImage *dat, int no);

#endif