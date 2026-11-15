/*
**      VESA.H          Obsluga VESA 1.2
**
**      Sarin/!ArisE!
*/

#ifndef __VESA_H
#define __VESA_H

/* Wlaczyc czy wylaczyc przeszkadzanie */
//#define SHAREWARE

#define VIDEO_INT 0x10

// Ilosc trybow graficznych
#define MODE_NO 9

// Struktura opisujaca tryb
struct __modeInfo{
       int modeNo;
       int resX, resY;
       unsigned colors;
       char bytesPerPixel;
};

extern __modeInfo modes[MODE_NO];

// Nazwy trybow graficznych
#define VMODE320x200x256    0
#define VMODE640x480x256    1
#define VMODE800x600x256    2
#define VMODE320x200x64k    3
#define VMODE640x480x64k    4
#define VMODE800x600x64k    5
#define VMODE320x200x16m    6
#define VMODE640x480x16m    7
#define VMODE800x600x16m    8

// Funkcje
int        vesaInit();                  // sprawdza dostepnosc trybow. Zwraca -1 jesli nie ma VESA 1.2
int        setVideoMode(int modeNo);    // ustawia tryb (korzystaj ze zdefiniowanych nazw)
void       setTextMode(void);

int        getModeAuto();               // zwraca numer najlepszego mozliwego trybu
int        getModeUser();               // jw. ale uzytkownik wybiera z MENU

int        checkMode(int modeNo);       // zwraca 1 jesli tryb jest,
                                        // 0 jesli go nie ma

void       copyToScreen(int *src);

#pragma aux setTextMode = \
        "mov ax, 03h"     \
        "int 10h"         \
        modify [eax];

#endif