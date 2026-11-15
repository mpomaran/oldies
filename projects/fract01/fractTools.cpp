// ---------------------------------------------------------------------
//	fractTools.h
//		duperele do fraktali
//
// ---------------------------------------------------------------------


#include "fractTools.h"
#include <math.h>

// Liczenie wymiaru fraktala zadanego highfield'em o boku size
// za pomoca algorytmu Box Counting. Steps powinno byc potega 2
double	computeBCDim (double *d, unsigned size, unsigned steps)
{
	double	*dimTabLnN, *dimTabLnE;		// tablice, w ktorych zapisujemy wyniki
										// obliczen

	unsigned	e;				// dlugosc boku pudelka
	unsigned	N;				// ilosc zliczonych pudelek
	unsigned	i;				// numer kroku
	unsigned	x,y,z;			// wspolrzedne lewego, dolnego, blizszego rogu pudelka
	unsigned	xx,zz;
	double		*data = new double [size*size];
	double		min=10000000000, max=-10000000000;


	// normalizacja: mierzenie wartosci
	for (i=0; i<size*size; i++)
	{
		if (d[i] < min)
			min = d[i];
		if (d[i] > max)
			max = d[i];
	}

	// normalizacja: kopiowanie
	for (i=0; i<size*size; i++)
		data[i] = (d[i]-min)*((double)(size)/(double)(max-min));


	// wl. algorytm	
	i=0;
	e=size/4;
	dimTabLnN = new double[size];
	dimTabLnE = new double[size];
		
	do
	{
		N=0;
		for (x=0; x<size; x+=e)			// przeszukiwanie wszystkich pudelek
	     for (y=0; y<size; y+=e)
		  for (z=0; z<size; z+=e)
		  {
				for (zz=z; zz < z+e; zz++)		// mamy pudelko, przeszukiwanie w srodku
				{
					unsigned offset = zz*size+x;
					for (xx=x; xx < x+e; xx++)
						if (data[offset++] > y)
						{
							N++;
							goto outerLoop;
						}
				}
outerLoop: ;
		  }

		if (N==0)
			N=1;

		dimTabLnE[i] = log ( 1./(double)e );
		dimTabLnN[i] = log ( (double)N );


		i++;
		e/=2;
	} while (e > 1 && i<steps);

	double retValue=0;
	for (i=1; i<steps-1; i++)
		retValue += (dimTabLnN[i]-dimTabLnN[i-1])/(dimTabLnE[i] - dimTabLnE[i-1]);

	retValue /= ((int)steps-2);

	delete dimTabLnE;
	delete dimTabLnN;
	delete data;

	return retValue;
}

