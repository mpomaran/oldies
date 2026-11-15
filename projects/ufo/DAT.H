/*
 *      DAT.H           format zapisu obrazkow mono
 *      copyright (c) by Sarin/!ArisE!
 */

#ifndef __DAT_H
#define __DAT_H

typedef struct {
       int colors;              /* ilosc kolorow                         */
       int x,y;                 /* rozmiar X i Y                         */
} datFile;

typedef struct {
       int colors;              /* ilosc kolorow                         */
       int x,y;                 /* rozmiar X i Y                         */
       char *image;
} datImage;

#endif