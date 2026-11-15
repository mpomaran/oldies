/*
**      RMI.H                   Real Mode Int
**                              Funkcje sluzace do wywolywania
**                              przerwan w REAL MODE
**      Sarin/!ArisE!
*/

#ifndef __RMI_H
#define __RMI_H

#include <i86.h>

// Struktura zwracana przez rmAlloc
struct rmAddr {
       short selector;
       short segment;
};

// Struktura przekazujaca informacje do REAL MODE
struct rmInfo {
       long edi;
       long esi;
       long ebp;
       long reserved;
       long ebx;
       long edx;
       long ecx;
       long eax;
       short flags;
       short es, ds, fs, gs, ip, cs, sp, ss;
};

// Alokacja pamieci ponizej 1 mb. Rozmiar podajemy w paragrafach.
// Jeden paragraf ma 16 bajtow
rmAddr rmAlloc(int parAmount);

// Wywolanie przerwania REAL MODE
// zwracana zawartosc rejestru EAX
int rmInt(int intNo, union REGS *inRegs, union REGS *outRegs, struct SREGS *segRegs);

#endif