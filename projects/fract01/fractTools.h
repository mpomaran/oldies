// ---------------------------------------------------------------------
//	fractTools.h
//		duperele do fraktali
//
// ---------------------------------------------------------------------

#ifndef __FRACTTOOLS_H
#define __FRACTTOOLS_H

// Liczenie wymiaru fraktala zadanego highfield'em o boku size
// za pomoca algorytmu Box Counting
double	computeBCDim (double *data, unsigned size, unsigned steps=5);

#endif
