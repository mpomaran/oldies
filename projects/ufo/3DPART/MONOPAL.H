/*
 *      MONOPAL.H               ustawia palete moochromatyczna
 *      copyright (c) 1997 by Sarin/!ArisE!
 */

#ifndef __MONOPAL_H
#define __MONOPAL_H

void    setMonoPalette(double kr, double kg, double kb, int firstLut, int lastLut, int noOfColors);

void    setLUTRegister(char regNo, char r, char g, char b);
#pragma aux setLUTRegister =     \
        "mov    al,    0ffh"     \
        "mov    dx,    03c6h"    \
        "out    dx,    al"       \
        "mov    dx,    03c8h"    \
        "mov    al,    ah"       \
        "out    dx,    al"       \
        "mov    dx,    03c9h"    \
        "mov    al,    bl"       \
        "out    dx,    al"       \
        "mov    al,    bh"       \
        "out    dx,    al"       \
        "mov    al,    cl"       \
        "out    dx,    al"       \
        parm [ah] [bl] [bh] [cl] \
        modify [eax ebx ecx edx];

#endif
