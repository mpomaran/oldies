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
//		|...n*m-1|
//		+-		-+
//
// ---------------------------------------------------------------------

#ifndef __BIGMATRIX_H
#define __BIGMATRIX_H

#define		INIT_ERROR		"BigMatrix: Macierz nie zostala zainicjowana!"
#define		RANGE_ERROR		"BigMatrix: Zapis poza granicami"
#define		VALUE_ERROR		"BigMatrix: Zly argument"

class	BigMatrix
{
	private:
		double	*data;
		bool	init;			//

	public:

				int		n;				// wymiary macierzy
		
				BigMatrix	() { init = false; }
				
				BigMatrix	(int col) { init = true; n = col; data = new double [n*n]; }


// ---------------------------------------------------------------------
				~BigMatrix  ()
				{
					free ();
				}

// ---------------------------------------------------------------------
	void		assign		(double *mData, int col) 
				{
					#ifndef NDEBUG
						if (!mData)
							throw (VALUE_ERROR);

						if (col < 0)
							throw (RANGE_ERROR);
					#endif

						if (init)
						free();

					data=mData; n=col;
					init=true;
					data = new double [n*n];
				}


				
// ---------------------------------------------------------------------
inline	double	get			(int col, int row) const
				{
					#ifndef NDEBUG
						if (!init)
							throw (INIT_ERROR);

						if (col >= n || row >= n || col < 0 || row < 0)
							throw (RANGE_ERROR);
					#endif

					return data[col+row*n];
				}


// ---------------------------------------------------------------------
inline	void	set			(int col, int row, double value)
				{
					#ifndef NDEBUG
						if (!init)
							throw (INIT_ERROR);

						if (col >= n || row >= n || col < 0 || row < 0)
							throw (RANGE_ERROR);
					#endif

					data[col+row*n] = value;
				}

// ---------------------------------------------------------------------
		void	free		()
				{
					if (init)
						delete data;
					init = false;
				}
			

		void	choldc ();
		void	inverse ();
		void	clear		();

static	void	copy		(BigMatrix &dst, const BigMatrix &src)
				{
						for (int i=0; i<dst.n*dst.n; i++)
						dst.data[i] = src.data[i];
				}

static	void	multiply	(BigMatrix &result, BigMatrix &a, BigMatrix &b);
static	void	transpose	(BigMatrix &result, const BigMatrix &src);
static	void	add			(BigMatrix &result, BigMatrix &a, BigMatrix &b);
};



// ---------------------------------------------------------------------
//	Liczenie macierzy kowariancji
//		result - wynik 
//		data   - macierz o takich samych wymiarach, co result
//		d	   - wymiar fraktalny	
// ---------------------------------------------------------------------

void	computeCxx	(BigMatrix& result, double *t, double d);
void	computeCyx	(BigMatrix& result, double *t, double *s, double d);
void	computeCyy	(BigMatrix& result, double *s, double d);


#endif
