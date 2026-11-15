/*
 *      NOISE.H         Procedury do generowania 'szumu' na ekranie
 *      copyright (c) 1997 by Sarin/!ArisE!
 */

#ifndef __NOISE_H
#define __NOISE_H

#define BARS_NO 80              /* ilosc pionowych paskow */

/* Najpierw musisz zainicjowac generator liczb losowych */
void    generateNoise(char *buff);
void    generateBars(char *buff);

#endif