/*
**      RMI.CPP
**
**      Sarin/!ArisE!
*/

#include <i86.h>
#include <string.h>

#include "rmi.h"

#define DPMI_INT 0x31

rmAddr rmAlloc(int parAmount)
{
  REGS regs;
  SREGS sregs;
  rmAddr result;

  memset(&sregs, 0, sizeof(sregs));
  regs.w.ax = 0x100;
  regs.w.bx = parAmount;
  int386x(DPMI_INT, &regs, &regs, &sregs);

  result.segment = regs.w.ax;
  result.selector = regs.w.dx;
  return result;
}

int rmInt(int intNo, union REGS *inRegs, union REGS *outRegs, struct SREGS *segRegs)
{
  REGS regs;
  SREGS sregs;
  rmInfo rmi;

  memset(&rmi, 0, sizeof(rmi));

  // Setup RMI structure
  rmi.eax = inRegs->x.eax;  rmi.ebx = inRegs->x.ebx;
  rmi.ecx = inRegs->x.ecx;  rmi.edx = inRegs->x.edx;
  rmi.edi = inRegs->x.edi;  rmi.esi = inRegs->x.esi;
  rmi.es = segRegs->es; rmi.ds = segRegs->ds;
  rmi.fs = segRegs->fs; rmi.gs = segRegs->gs;

  memset(inRegs, 0, sizeof(REGS));
  memset(segRegs, 0, sizeof(SREGS));

  // Setup DPMI 0x300 call
  inRegs->w.ax = 0x300;
  inRegs->h.bl = intNo;

  segRegs->es = FP_SEG(&rmi);
  inRegs->x.edi = FP_OFF(&rmi);

  int386x(DPMI_INT, inRegs, outRegs, segRegs);

  outRegs->x.eax = rmi.eax; outRegs->x.ebx = rmi.ebx;
  outRegs->x.ecx = rmi.ecx; outRegs->x.edx = rmi.edx;
  outRegs->x.edi = rmi.edi; outRegs->x.esi = rmi.esi;

  return rmi.eax;
}
