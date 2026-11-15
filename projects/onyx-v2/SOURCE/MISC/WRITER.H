/*
 *      WRITER.H                Procedury do wypisywania tekstu na ekranie
 *      copyright (c) 1997 by Sarin/!ArisE!
 */

#ifndef __WRITER_H
#define __WRITER_H

#include "gphfiles.h"

/* Mozliwe ustawienia tekstu */
#define TOP_LEFT      0
#define TOP_RIGHT     1
#define BOTTOM_LEFT   2
#define BOTTOM_RIGHT  3

/* Rysuje tekst fontem FONT (fonty w formacie .gph). Wskaznik do tekstu - text
 * align - ustawienie tesktu (patrz makra wyzej). out = bufor wyjsciowy
 */
void    drawText(gphHandle *font, char *text, int align,char *out);

#endif