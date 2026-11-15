
#include	<windows.h>
#include	<stdlib.h>
#include	<math.h>
#include	"makeTerrain.h"
#include	"globals.h"

// basis matrix for spline interpolation
#define CR00	-0.5
#define CR01	1.5
#define CR02	-1.5
#define CR03	0.5
#define CR10	1.0
#define CR11	-2.5
#define CR12	2.0
#define CR13	-0.5
#define CR20	-0.5
#define CR21	0.0
#define CR22	0.5
#define CR23	0.0
#define CR30	0.0
#define CR31	1.0
#define CR32	0.0
#define CR33	0.0



#define	DAT(data,x,y) data[x+(y)*dataSizeX]
#define	COND_SET(data,x,y) if (data[x+(y)*dataSizeX]==0.0) data[x+(y)*dataSizeX]

static int	mask[dataSizeX*dataSizeY];

static	int level;

void prepareMaskRec (int x1, int y1, int x2, int y2, int level)
{
	if (level <= 0)
		return;

	if (x1 < 0 || x2 <0 || y1 <0 || y2 <0) return;

	if (x2 - x1 <= 1) return;
	if (y2 - y1 <= 1) return;

	// policzenie dla 4 rogow
	DAT (mask, x1, y1) = 1;
	DAT (mask, x2, y1) = 1;
	DAT (mask, x1, y2) = 1;
	DAT (mask, x2, y2) = 1;

	int midx = (x2-x1) / 2.0;
	int midy = (y2-y1) / 2.0;


	double sum;
	bool quit = false;

	if (midx <= 1 || midy <= 1)
		// tez musimy postawic punkty w srodku, ale tylko raz
		quit = true;

	midx += x1; midy += y1;



	// teraz kolejnych 5 wartosci

	DAT (mask, midx, y1) = 1;
	DAT (mask, midx, y2) = 1;
	DAT (mask, x1, midy) = 1;
	DAT (mask, x2, midy) = 1;
	DAT (mask, midx, midy) = 1;

	if (quit)
		return;

	level--;

	prepareMaskRec (x1, y1, midx, midy, level);
	prepareMaskRec (midx, y1, x2, midy, level);
	prepareMaskRec (x1, midy, midx, y2, level);
	prepareMaskRec (midx, midy, x2, y2, level);
}

void prepareMask ()
{
	int i;

	for (i=0; i<dataSizeX*dataSizeY; i++)
		mask[i] = 0;

	prepareMaskRec (0, 0, dataSizeX-1, dataSizeY-1, 7);
}

#define N 15.0

inline double random (double value)
{
	static int i;
	double sum = 0.0;

	for (i=0; i<N; i++)
		sum += rand();

	return ( (1.0/RAND_MAX)*sqrt (12.0/N)*sum - sqrt(3.0*N) ) * value;
}

///////////////////////////////////////////////////////////////////
//	Standardowy algorytm przesuwania œrodka
///////////////////////////////////////////////////////////////////

void	makeFractal (double data[], int x1, int y1, int x2, int y2, double H, double level)
{
	if (level == 0.0)
		level = sqrt (1.0 - pow (2, 2.0*H - 2.0));
	
	if (x1 < 0 || x2 <0 || y1 <0 || y2 <0) return;

	// policzenie dla 4 rogow
	COND_SET (data, x1, y1) = random (level);
	COND_SET (data, x2, y1) = random (level);
	COND_SET (data, x1, y2) = random (level);
	COND_SET (data, x2, y2) = random (level);

	int midx = (x2-x1) / 2.0;
	int midy = (y2-y1) / 2.0;


	double sum;
	bool quit = false;

	if (midx <= 1 || midy <= 1)
		// tez musimy postawic punkty w srodku, ale tylko raz
		quit = true;

	midx += x1; midy += y1;


	// teraz kolejnych 5 wartosci
	sum = DAT (data, x1, y1) + DAT (data, x1, y2) + DAT (data, x2, y2) + DAT (data, x1, y2);
	sum /= 4.0;
	sum += random (level);
	COND_SET (data, midx, midy) = sum;
	
	sum = DAT (data, x1, y1) + DAT (data, x2, y1) + DAT (data, midx, midy);
	sum /= 3;
	sum += random (level);
	COND_SET (data, midx, y1) = sum;

	sum = DAT (data, x1, y2) + DAT (data, x2, y2) + DAT (data, midx, midy);
	sum /= 3;
	sum += random (level);
	COND_SET (data, midx, y2) = sum;

	sum = DAT (data, x1, y1) + DAT (data, x1, y2) + DAT (data, midx, midy);
	sum /= 3;
	sum += random (level);
	COND_SET (data, x1, midy) = sum;

	sum = DAT (data, x2, y1) + DAT (data, x2, y2) + DAT (data, midx, midy);
	sum /= 3;
	sum += random (level);
	COND_SET (data, x2, midy) = sum;

	if (quit)
		return;

	level /= pow (2, H);

	makeFractal (data, x1, y1, midx, midy, H, level);
	makeFractal (data, midx, y1, x2, midy, H, level);
	makeFractal (data, x1, midy, midx, y2, H, level);
	makeFractal (data, midx, midy, x2, y2, H, level);


}
///////////////////////////////////////////////////////////////////


void	zoom (double data[], int xPos, int yPos)
{
	static	double temp[dataSizeX*dataSizeY];
	int		i, j, x, y, tx, ty;

//	xPos = yPos = 0;

	prepareMask ();

	// czyszczenie bitmapy
	for (i=0; i<dataSizeX*dataSizeY; i++)
		temp[i] = 0.0;

	// rozmieszczanie nowych punktow siatki
	for (x=xPos, tx=0; x<xPos+128; x++, tx+=4)
		for (y=yPos, ty=0; y<yPos+128; y++, ty+=4)
			for (i=0; i<4; i++)
				for (j=0; j<4; j++)
					temp[tx+i+(ty+j)*dataSizeX] = data[x+y*dataSizeX];

	for (i=0; i<dataSizeX*dataSizeY; i++)
		data[i] = 0.0;

	// kopiowanie bitmap
	for (i=0; i<dataSizeX*dataSizeY; i++)
		if (mask[i]) data[i] = temp[i];

}

