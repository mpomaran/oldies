// ---------------------------------------------------------------------
//	bigMatrix.h
//		duperele do fraktali
//
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
//	Macierz jest skladowana jako tablica o postaci
//		+-		-+
//		|0 1 ...n|
//		|........|
//		|...n*n-1|
//		+-		-+
//
// ---------------------------------------------------------------------

#include	<math.h>

#include	<windows.h>

#include	"bigMatrix.h"


// ---------------------------------------------------------------------
//	Cholesky decomposition
// ---------------------------------------------------------------------

void	BigMatrix::choldc ()
{
	int			i,j,k;
	double		sum;
	double		*p = new double[n];
	BigMatrix	result (n);

	result.clear ();

	try{
	for (i=0; i<n; i++)
	{
		for (j=i; j<n; j++)
		{
			for (sum=get(i,j), k=i; k>=0; k--) sum -= get(i,k)*get(j,k);
			if (i==j)
			{
				if (sum <= 0.0)
					throw "choldc failed";

				p[i] = sqrt (sum);
			}
			else set(j,i, sum/p[i]);
		}
	}
	} catch (char *txt)
	{
		MessageBox (NULL, txt, "", MB_OK);
	}



	// kopiowanie danych do macierzy wyjciowej
	for (i=0; i<n; i++)
		result.set (i, i, p[i]);
	BigMatrix::copy (*this, result);
	
	delete	p;
}





// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

void	BigMatrix::inverse ()
{
	BigMatrix	L(n), Lt(n);

	BigMatrix::copy (L, *this);
	L.choldc ();

	BigMatrix::transpose (Lt, L);

	BigMatrix::multiply (*this, Lt, L);
}





// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

void	BigMatrix::clear		()
{
	for (int i=0; i<n*n; i++)
		data[i] = 0.0;
}





// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

void	BigMatrix::multiply	(BigMatrix &result, BigMatrix &a, BigMatrix &b)
{
	int i,j,k;
	double sum;

	if (a.n != b.n || result.n != a.n)
		throw "Mult: zle arg";

	for (i=0; i<a.n; i++)				// rzedy
		for (j=0; j<a.n; j++)			// kolumny
		{
			sum = 0.0;
			for (k=0; k<a.n; k++)		// ilosc dodawan
				sum += a.get(k,i) * b.get(j, k);

			result.set (i, j, sum);
		}
}




// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

void	BigMatrix::add			(BigMatrix &result, BigMatrix &a, BigMatrix &b)
{
	for (int i=a.n*a.n; i>=0; i--)
		result.data[i] = a.data[i] + b.data[i];
}




// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

void	BigMatrix::transpose	(BigMatrix &result, const BigMatrix &src)
{
	for (int i=0; i<src.n; i++)
		for (int j=0; j<src.n; j++)
			result.set (i, j, src.get (j, i));
}




// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

void	computeCxx	(BigMatrix& result, double *x, double d)
{
	double H = 3.0-d;

	for (int i=0; i<result.n; i++)
		for (int j=0; j<result.n; j++)
			;
}




// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

void	computeCyx	(BigMatrix& result, double *x, double *y double d)
{
	double H = 3.0-d;
}




// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

void	computeCyy	(BigMatrix& result, double *y, double d)
{
	double H = 3.0-d;
}


