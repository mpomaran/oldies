/*
**      VESA.CPP                Funkcje umozliwiajace korzystanie z VESA
**
**      Sarin/!ArisE!
*/

// Piszac te funkcje korzystalem z ksiazki "Karty graficzne VGA i SVGA"
// autorstwa Tomasza Kopacza

#include <stdio.h>

#include <string.h>
#include <i86.h>
#include <iostream.h>

#include <math.h>

#include "rmi.h"
#include "vesa.h"

char *copyright = ">>>> COPYRIGHT: ONYX 3D LIB version 2 - copyright (c) 2000 by Michal Pomaranski. If you want to use this code, please phone me: +48604637913, or use email: mpomaranski@poczta.onet.pl <<<<<<";

static int activeMode;

extern unsigned char colorTable[256][256];      /* tablica definiujaca cienie */

// Struktura opisujaca tryb
__modeInfo modes[MODE_NO] = {
      {0x13,  320, 200, 256,1},           // tryby 256-kolorowe
      {0x101, 640, 480, 256,1},
      {0x103, 800, 600, 256,1},
      {0x10e, 320, 200, 0x10000,2},       // tryby 64k kolorowe
      {0x111, 640, 480, 0x10000,2},
      {0x114, 800, 600, 0x10000,2},
      {0x10f, 320, 200, 0x1000000,3},     // tryby TRUE COLOR
      {0x112, 640, 480, 0x1000000,3},
      {0x115, 800, 600, 0x1000000,3} };

///////////////////////////////////////////////////////////////////////////
struct {
       int tryb_jest            : 1;
       int jest_inf_dodatkowa   : 1;
       int bios_piksel          : 1;
       int kolor                : 1;
       int grafika              : 1;
       int rez_tryb             : 11;

       /* Atrybuty okien A i B */
       int istnieje_A           : 1;
       int odczyt_A             : 1;
       int zapis_A              : 1;
       int rez_A                : 5;

       int istnieje_B           : 1;
       int odczyt_B             : 1;
       int zapis_B              : 1;
       int rez_B                : 5;

       unsigned short granularity;    // minimalny odstep miedzy bankami w kB
       unsigned short okno;     // rozmiar okna w kB
       unsigned short segA;     // segment adresu okna A
       unsigned short segB;     // segment adresu okna B
       void * winFunc;          // wskaznik do funkcji przelaczajacej banki
                                // w trybie rzeczywistym i V86 procesora.
                                // Ta funkcja nie jest przeznaczona dla trybu
                                // wirtualnego
       unsigned short bytes;    // liczba bajtow linii logicznej

       // Informacje dodatkowe. W zaleznosci od VESA-BIOS moga byc niewy
       // korzystane. Standard mowi tylko, ze wymagane jest, by te informacje
       // byly wypelnione dla trybow specyficznych dla danej karty
       char reszta [238];
} modesInfo[MODE_NO];

///////////////////////////////////////////////////////////////////////////
// Inicjacja trybu
int setVideoMode(int modeNo)
{
  REGS regs;
  SREGS sregs;

  if (modesInfo[modeNo].tryb_jest){
     memset((void *)&regs, 0, sizeof(REGS));
     memset((void *)&sregs, 0, sizeof(SREGS));

     regs.w.ax = 0x4f02;
     regs.w.bx = modes[modeNo].modeNo;

     if (0x4f == rmInt(0x10,&regs,&regs,&sregs)){
        activeMode = modeNo;
        return 1;
     }

  }
  return 0;
}

///////////////////////////////////////////////////////////////////////////
// Funkcja sprawdza, czy tryby graficzne sa dostepne
int vesaInit (void)
{
 int i,j;
 SREGS sregs;
 REGS  regs;
 rmAddr addr;
 int avail = 0;


#ifdef SHAREWARE
        setTextMode();
        cout << "                ------========>SHAREWARE COUNTDOWN<========------\n";
        cout << "\nTo contact with author use email :\n";
        cout << "\tsarin@czart.pulawy.pl (until July of 1999)\n\n\t\tor\n\n";
        cout << "Snail-mail:\n\tMichal Pomaranski\n\tul. Kollataja 25/17\n\t";
        cout << "24-100 Pulawy\n\tPOLAND\n\n";
        for (i=0; i<80; i++){
          delay(25);
            cout << ".";
        };
#endif

        // tablica kolorow wykorzystywana przez funkcje teksturujace
        for (i=0; i<256; i++)
            for (j=0; j<256; j++)
                colorTable[i][j] = (double)i * (log (1+(exp(1)-1)*((double)j/256.)));

        addr=rmAlloc(256/16);        // alokacja pamieci ponizej 1 mb

        for (i=0; i<MODE_NO; i++){
            memset((void *)&sregs, 0, sizeof(SREGS));
            memset((void *)&regs,  0, sizeof(REGS));

            regs.w.ax = 0x4f01;
            regs.w.cx = modes[i].modeNo;
            sregs.es = addr.segment;
            regs.w.di = 0;
            // wywolanie VESA-BIOS
            if (0x4f==rmInt(VIDEO_INT, &regs, &regs, &sregs)){
               // kopiowane z bufora do tablicy
               _fmemcpy((void far *)(modesInfo+i),
                              MK_FP(addr.selector,0),256);

               // sprawdz, czy naprawde da sie tryb uruchomic
               if (!setVideoMode(i))
                  memset((void *)(modesInfo+i),0,256);
               else
                    avail = 1;
            } else            // tryb niedostepny
               memset((void *)(modesInfo+i),0,256);
        }

        if (avail) return 1;
        else return 0;
}

///////////////////////////////////////////////////////////////////////////
// Wybor dostepnego trybu
int getModeUser(void)
{
 int i;
 int modeAvail[MODE_NO];

  memset((void *)modeAvail,0,sizeof(modeAvail));

  do {
        setTextMode();
        cout << "VESA 1.2 LIB\t(";
        cout << __DATE__ << " " << __TIME__ << ")\n";
        cout << "\tCopyright (c) 1998 by Sarin/!Arise! (sarin@czart.pulawy.pl)\n";
        cout << "\n** It is forbidden to use this system for commercial purposes\n";
        cout << "** 64k modes aren't supported yet...\n\n";

        for (i=0; i<MODE_NO; i++)
            if (modesInfo[i].tryb_jest){
               modeAvail[i] = 1;
               cout << i << ". Resolution " << modes[i].resX << "x" << modes[i].resY;
               cout << " with " << modes[i].colors << " colors.\n";
            }

        cout << "\nChoose video mode:";
        cin >> i;
        i %= MODE_NO;
  } while (!modeAvail[i]);

  return i;
}

int        checkMode(int modeNo)
{
  if (modesInfo[modeNo].tryb_jest)
     return 1;
  else
       return 0;
}

///////////////////////////////////////////////////////////////////////////
int getModeAuto ()
{
  int i;

        for (i=MODE_NO-1; i>=0; i--)
            if (modesInfo[i].tryb_jest)
               break;

        return i;
};

///////////////////////////////////////////////////////////////////////////
// ustawia aktywny bank w oknie A
void setBankA(short unsigned bankNo)
{
  REGS regs;
  SREGS sregs;

  memset((void *)&sregs, 0, sizeof(SREGS));
  memset((void *)&regs, 0, sizeof(REGS));

  regs.w.ax = 0x4f05;
  regs.w.bx = 0;
  regs.w.dx = bankNo;

  rmInt(VIDEO_INT,&regs,&regs,&sregs);
}

// wersja w C, moze bedzie dzialac :) ale i tak nie jest szybka

static int bpp_przez_8;

void    copyInner(char *dst, char *src, char *end, int bpp);
#pragma aux copyInner =           \
          "petla:          "     \
          " mov eax, [esi] "     \
          " mov [edi], eax "     \
          " add edi, ebx   "     \
          " add esi, 3     "     \
          " cmp edi, ecx   "     \
          " jle petla      "     \
          parm [edi] [esi] [ecx] [ebx]  \
          modify [eax];

void    copyScanLine(char *dst, char *src, int len)
{
  int i,j;
  char *end;

        len *= bpp_przez_8;
        end = dst + len;
        copyInner (dst, src, end, bpp_przez_8);
//        for (; dst<end; dst+=bpp_przez_8, src+=3)
//          *(int *)dst = *(int *)src;
//
}

void copyToScreen(int *src)
{
  int *dst;
  int *end;
  int bytesPerScanline;         // na karcie
  int granularity;
  int i;
  int bankNo=0;
  int bytesPerLine;             // w pamieci
  int dodajDoBanku;

  int poprawka;                 // nie chce mi sie myslec, skad sie bierze
  int bpp;                      // ile jest bitow na piksel

  bytesPerScanline = modesInfo[activeMode].bytes>>2;
  bytesPerLine = (modes[activeMode].resX * modes[activeMode].bytesPerPixel)>>2;
  granularity = modesInfo[activeMode].granularity*1024; // granularity jest w KB

  dst = (int *)(modesInfo[activeMode].segA<<4);
  end = dst + (modesInfo[activeMode].okno * 1024)/4;

  dodajDoBanku = modesInfo[activeMode].okno / modesInfo[activeMode].granularity;
  setBankA(0);

  bpp = (bytesPerScanline*8*4)/modes[activeMode].resX;
  bpp_przez_8 = bpp >> 3;

  for (i=0; i<modes[activeMode].resY; i++){
      copyScanLine((char *)dst,(char *)src, bytesPerScanline);

      dst += bytesPerScanline;
      if (dst >= end){
         poprawka = (24*(int)(dst-end))/bpp;
         // malo kompatybilne.... doprowadz do stanu uzywalnosci
         src -= poprawka;
         setBankA(bankNo += dodajDoBanku);
         dst = (int *)(modesInfo[activeMode].segA<<4);
      } else
         src += bytesPerLine;
  }
}

///////////////////////////////////////////////////////////////////////////
