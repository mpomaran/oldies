// ---------------------------------------------------------------------
//	ShowHighField.cpp
//		Wyswietlanie zadanego highfielda na srodku regionu
//
// ---------------------------------------------------------------------


#include	<windows.h>
#include	<assert.h>
#include	"showhighfield.h"
#include	"globals.h"

inline unsigned	computeColor (double color)
{
	unsigned x = 255.0 * color;
	if (x>255) x = 255;
	return RGB (x, x, 30+0.3*x);

}

void showHighfield (HDC hdc, RECT &rt, double *d)
{
	int left, top;
	int diff;
	int i;
	double		*data = new double [dataSizeX*dataSizeY];
	double		min=10000000000, max=-10000000000;


	// normalizacja: mierzenie wartosci
	for (i=0; i<dataSizeX*dataSizeY; i++)
	{
		if (d[i] < min)
			min = d[i];
		if (d[i] > max)
			max = d[i];
	}

	// normalizacja: kopiowanie
	for (i=0; i<dataSizeX*dataSizeY; i++)
		data[i] = (d[i]-min)*((double)0.8/(double)(max-min));


	// obliczanie wspolrzednych lewego gornego rogu prostokata do wyswietlenia
	// highfield'a
	diff = rt.right - rt.left;
	assert (diff >= dataSizeX);
	left = (diff - dataSizeX)/2;

	diff = rt.bottom - rt.top;
	assert (diff >= dataSizeY);
	top = (diff - dataSizeY)/2;

	// wyswietlanie highfield'a w petli
	for (int x=0; x<dataSizeX; x++)
		for (int y=0; y<dataSizeY; y++)
			SetPixelV (hdc, x+left, y+top, computeColor (data[x+y*dataSizeX]));
}
