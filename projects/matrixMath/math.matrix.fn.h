//	------------------------------------------------------------------------------------
//
//	Integralna czesc modulu math.matrix i nie powinna byc oddzielnie dalaczana !!!
//
//	(c)	2002	Michal Pomaranski
//		mpomaranski@poczta.onet.pl
//	------------------------------------------------------------------------------------


#ifndef __MATH_MATRIX_FN_H
#define __MATH_MATRIX_FN_H

#include	<iostream.h>

#include	<assert.h>

//	------------------------------------------------------------------------------------
//	Kopiowane dwoch macierzy
//	------------------------------------------------------------------------------------

inline void Matrix4::copy(Matrix4 &dst, const Matrix4 &src)
{
	if (dst.data != src.data)
		memcpy (dst.data, src.data, sizeof (float) * 16);
}




//	------------------------------------------------------------------------------------
//	Mnozy dwie macierze a1 i a2 i wynik umieszcza w dst
//	------------------------------------------------------------------------------------

inline void Matrix4::mul (Matrix4 &dst, const Matrix4 &a1, const Matrix4 &a2)
{
	static int i;

	// petla jest czesciowo rozwinieta, aby bylo szybciej
	// mozna jeszcze zastapic for na while i bedzie jeden skok mniej
	for (i = 0; i<=12; i+=4)
	{

		dst.data[i] = a1.data[i] * a2.data[0] 
					+ a1.data[i+1] * a2.data[4]
					+ a1.data[i+2] * a2.data[8] 
					+ a1.data[i+3] * a2.data[12];

		dst.data[i+1] = a1.data[i] * a2.data[1]
					+ a1.data[i+1] * a2.data[5]
					+ a1.data[i+2] * a2.data[9]
					+ a1.data[i+3] * a2.data[13];

		dst.data[i+2] = a1.data[i] * a2.data[2]
					+ a1.data[i+1] * a2.data[6]
					+ a1.data[i+2] * a2.data[10]
					+ a1.data[i+3] * a2.data[14];

		dst.data[i+3] = a1.data[i] * a2.data[3]
					+ a1.data[i+1] * a2.data[7]
					+ a1.data[i+2] * a2.data[11] 
					+ a1.data[i+3] * a2.data[15];
	}
}




//	------------------------------------------------------------------------------------
//	Mnozy macierz przez skalar
//	!	Jako paramatry mozna podac te same macierze
//	------------------------------------------------------------------------------------

inline void Matrix4::mul (Matrix4 &dst, const Matrix4 &src, const float &a)
{
	dst.data[0] = src.data[0] * a;
	dst.data[1] = src.data[1] * a;
	dst.data[2] = src.data[2] * a;
	dst.data[3] = src.data[3] * a;
	dst.data[4] = src.data[4] * a;
	dst.data[5] = src.data[5] * a;
	dst.data[6] = src.data[6] * a;
	dst.data[7] = src.data[7] * a;
	dst.data[8] = src.data[8] * a;
	dst.data[9] = src.data[9] * a;
	dst.data[10] = src.data[10] * a;
	dst.data[11] = src.data[11] * a;
	dst.data[12] = src.data[12] * a;
	dst.data[13] = src.data[13] * a;
	dst.data[14] = src.data[14] * a;
	dst.data[15] = src.data[15] * a;
}




//	------------------------------------------------------------------------------------
//		Dodaje dwie macierze
//	!	Jako paramatry mozna podac te same macierze
//	------------------------------------------------------------------------------------

inline void Matrix4::add (Matrix4 &dst, const Matrix4 &a1, const Matrix4 &a2)
{
	dst.data[0] = a1.data[0] + a2.data[0];
	dst.data[1] = a1.data[1] + a2.data[1];
	dst.data[2] = a1.data[2] + a2.data[2];
	dst.data[3] = a1.data[3] + a2.data[3];
	dst.data[4] = a1.data[4] + a2.data[4];
	dst.data[5] = a1.data[5] + a2.data[5];
	dst.data[6] = a1.data[6] + a2.data[6];
	dst.data[7] = a1.data[7] + a2.data[7];
	dst.data[8] = a1.data[8] + a2.data[8];
	dst.data[9] = a1.data[9] + a2.data[9];
	dst.data[10] = a1.data[10] + a2.data[10];
	dst.data[11] = a1.data[11] + a2.data[11];
	dst.data[12] = a1.data[12] + a2.data[12];
	dst.data[13] = a1.data[13] + a2.data[13];
	dst.data[14] = a1.data[14] + a2.data[14];
	dst.data[15] = a1.data[15] + a2.data[15];
}




//	------------------------------------------------------------------------------------
//		Odejmuje dwie macierze
//	!	Jako paramatry mozna podac te same macierze
//	------------------------------------------------------------------------------------

inline void Matrix4::sub (Matrix4 &dst, const Matrix4 &a1, const Matrix4 &a2)
{
	dst.data[0] = a1.data[0] - a2.data[0];
	dst.data[1] = a1.data[1] - a2.data[1];
	dst.data[2] = a1.data[2] - a2.data[2];
	dst.data[3] = a1.data[3] - a2.data[3];
	dst.data[4] = a1.data[4] - a2.data[4];
	dst.data[5] = a1.data[5] - a2.data[5];
	dst.data[6] = a1.data[6] - a2.data[6];
	dst.data[7] = a1.data[7] - a2.data[7];
	dst.data[8] = a1.data[8] - a2.data[8];
	dst.data[9] = a1.data[9] - a2.data[9];
	dst.data[10] = a1.data[10] - a2.data[10];
	dst.data[11] = a1.data[11] - a2.data[11];
	dst.data[12] = a1.data[12] - a2.data[12];
	dst.data[13] = a1.data[13] - a2.data[13];
	dst.data[14] = a1.data[14] - a2.data[14];
	dst.data[15] = a1.data[15] - a2.data[15];
}





//	------------------------------------------------------------------------------------
//		Dodaje skalar do macierzy
//	!	Jako paramatry mozna podac te same macierze
//	------------------------------------------------------------------------------------

inline void Matrix4::add (Matrix4 &dst, const Matrix4 &src, const float &a)
{
	dst.data[0] = src.data[0] + a;
	dst.data[1] = src.data[1] + a;
	dst.data[2] = src.data[2] + a;
	dst.data[3] = src.data[3] + a;
	dst.data[4] = src.data[4] + a;
	dst.data[5] = src.data[5] + a;
	dst.data[6] = src.data[6] + a;
	dst.data[7] = src.data[7] + a;
	dst.data[8] = src.data[8] + a;
	dst.data[9] = src.data[9] + a;
	dst.data[10] = src.data[10] + a;
	dst.data[11] = src.data[11] + a;
	dst.data[12] = src.data[12] + a;
	dst.data[13] = src.data[13] + a;
	dst.data[14] = src.data[14] + a;
	dst.data[15] = src.data[15] + a;
}




//	------------------------------------------------------------------------------------
//		Odejmuje skalar od macierzy
//	!	Jako paramatry mozna podac te same macierze
//	------------------------------------------------------------------------------------

inline void Matrix4::sub (Matrix4 &dst, const Matrix4 &src, const float &a)
{
	dst.data[0] = src.data[0] - a;
	dst.data[1] = src.data[1] - a;
	dst.data[2] = src.data[2] - a;
	dst.data[3] = src.data[3] - a;
	dst.data[4] = src.data[4] - a;
	dst.data[5] = src.data[5] - a;
	dst.data[6] = src.data[6] - a;
	dst.data[7] = src.data[7] - a;
	dst.data[8] = src.data[8] - a;
	dst.data[9] = src.data[9] - a;
	dst.data[10] = src.data[10] - a;
	dst.data[11] = src.data[11] - a;
	dst.data[12] = src.data[12] - a;
	dst.data[13] = src.data[13] - a;
	dst.data[14] = src.data[14] - a;
	dst.data[15] = src.data[15] - a;
}




//	------------------------------------------------------------------------------------
//		Tworzy macierz jednostkawa
//	------------------------------------------------------------------------------------

inline void Matrix4::identity (Matrix4 &dst)
{
	// Bez petli, zeby bylo szybciej
	dst.data[1] = dst.data[2]  = dst.data[3] = 0.0;
	dst.data[4] = dst.data[6]  = dst.data[7] = 0.0;
	dst.data[8] = dst.data[9]  = dst.data[11] = 0.0;
	dst.data[12] = dst.data[13]  = dst.data[14] = 0.0;
	dst.data[0] = dst.data[5] = dst.data[10] = dst.data[15] = 1.0;
}



//	------------------------------------------------------------------------------------
//		Transponuje macierz
//	------------------------------------------------------------------------------------

inline void Matrix4::transpose (Matrix4 &dst, const Matrix4 &src)
{
	static float tmp;


	if (dst.data == src.data)
	{
		tmp = src.data[1];
		dst.data[1] = src.data[4]; dst.data[4] = tmp;

		tmp = src.data[8];
		dst.data[8] = src.data[2]; dst.data[2] = tmp;

		tmp = src.data[9];
		dst.data[9] = src.data[6]; dst.data[6] = tmp;

		tmp = src.data[12];
		dst.data[12] = src.data[3]; dst.data[3] = tmp;

		tmp = src.data[13];
		dst.data[13] = src.data[7]; dst.data[7] = tmp;

		tmp = src.data[11];
		dst.data[11] = src.data[14]; dst.data[14] = tmp;
		return;
	}

	dst.data[0] = src.data[0];	dst.data[5] = src.data[5];
	dst.data[10] = src.data[10];dst.data[15] = src.data[15];
	dst.data[1] = src.data[4]; dst.data[4] = src.data[1];
	dst.data[8] = src.data[2]; dst.data[2] = src.data[8];
	dst.data[9] = src.data[6]; dst.data[6] = src.data[9];
	dst.data[12] = src.data[3]; dst.data[3] = src.data[12];
	dst.data[13] = src.data[7]; dst.data[7] = src.data[13];
	dst.data[11] = src.data[14]; dst.data[14] = src.data[11];

}




//	------------------------------------------------------------------------------------
//		Liczy wyznacznik macierzy
//	------------------------------------------------------------------------------------

inline float Matrix4::det (const Matrix4 &src)
{
	return src.data[3] * src.data[6] * src.data[9] *src.data[12] - 
          src.data[2] * src.data[7] * src.data[9] * src.data[12] - 
          src.data[3] * src.data[5] * src.data[10] * src.data[12] + 
          src.data[1] * src.data[7] * src.data[10] * src.data[12] + 
          src.data[2] * src.data[5] * src.data[11] * src.data[12] - 
          src.data[1] * src.data[6] * src.data[11] * src.data[12] - 
          src.data[3] * src.data[6] * src.data[8] * src.data[13] + 
          src.data[2] * src.data[7] * src.data[8] * src.data[13] + 
          src.data[3] * src.data[4] * src.data[10] * src.data[13] - 
          src.data[0] * src.data[7] * src.data[10] * src.data[13] - 
          src.data[2] * src.data[4] * src.data[11] * src.data[13] + 
          src.data[0] * src.data[6] * src.data[11] * src.data[13] + 
          src.data[3] * src.data[5] * src.data[8] * src.data[14] - 
          src.data[1] * src.data[7] * src.data[8] * src.data[14] - 
          src.data[3] * src.data[4] * src.data[9] * src.data[14] + 
          src.data[0] * src.data[7] * src.data[9] * src.data[14] + 
          src.data[1] * src.data[4] * src.data[11] * src.data[14] - 
          src.data[0] * src.data[5] * src.data[11] * src.data[14] - 
          src.data[2] * src.data[5] * src.data[8] * src.data[15] + 
          src.data[1] * src.data[6] * src.data[8] * src.data[15] + 
          src.data[2] * src.data[4] * src.data[9] * src.data[15] - 
          src.data[0] * src.data[6] * src.data[9] * src.data[15] - 
          src.data[1] * src.data[4] * src.data[10] * src.data[15] + 
          src.data[0] * src.data[5] * src.data[10] * src.data[15];
}




//	------------------------------------------------------------------------------------
//		Odwraca macierz
//	------------------------------------------------------------------------------------

inline void Matrix4::inverse (Matrix4 &dst, const Matrix4 &src)
{
	Matrix4 s = src;

	float d = s.det();

	assert (d != 0);

	// 1. macierz dopelnien algebraicznych
	//		(nikt tego nie klepal na zywca - Mathematica)
	dst.data[0] = -s.data[7] * s.data[10] * s.data[13] + 
		  s.data[6] * s.data[11] * s.data[13] + s.data[7] * s.data[9] * s.data[14] - 
		  s.data[5] * s.data[11] * s.data[14] - s.data[6] * s.data[9] * s.data[15] + 
          s.data[5] * s.data[10] * s.data[15];

	dst.data[1] = s.data[3] * s.data[10] * s.data[13] - 
          s.data[2] * s.data[11] * s.data[13] - s.data[3] * s.data[9] * s.data[14] + 
          s.data[1] * s.data[11] * s.data[14] + s.data[2] * s.data[9] * s.data[15] - 
          s.data[1] * s.data[10] * s.data[15];

	dst.data[2] = -s.data[3] * s.data[6] * s.data[13] + 
          s.data[2] * s.data[7] * s.data[13] + s.data[3] * s.data[5] * s.data[14] - 
          s.data[1] * s.data[7] * s.data[14] - s.data[2] * s.data[5] * s.data[15] + 
          s.data[1] * s.data[6] * s.data[15];

	dst.data[3] = s.data[3] * s.data[6] * s.data[9] - 
          s.data[2] * s.data[7] * s.data[9] - s.data[3] * s.data[5] * s.data[10] + 
          s.data[1] * s.data[7] * s.data[10] + s.data[2] * s.data[5] * s.data[11] - 
          s.data[1] * s.data[6] * s.data[11];

	dst.data[4] = s.data[7] * s.data[10] * s.data[12] - 
          s.data[6] * s.data[11] * s.data[12] - s.data[7] * s.data[8] * s.data[14] + 
          s.data[4] * s.data[11] * s.data[14] + s.data[6] * s.data[8] * s.data[15] - 
          s.data[4] * s.data[10] * s.data[15];

	dst.data[5] = -s.data[3] * s.data[10] * s.data[12] + 
          s.data[2] * s.data[11] * s.data[12] + s.data[3] * s.data[8] * s.data[14] - 
          s.data[0] * s.data[11] * s.data[14] - s.data[2] * s.data[8] * s.data[15] + 
          s.data[0] * s.data[10] * s.data[15];

	dst.data[6] = s.data[3] * s.data[6] * s.data[12] - 
          s.data[2] * s.data[7] * s.data[12] - s.data[3] * s.data[4] * s.data[14] + 
          s.data[0] * s.data[7] * s.data[14] + s.data[2] * s.data[4] * s.data[15] - 
          s.data[0] * s.data[6] * s.data[15];

	dst.data[7] = -s.data[3] * s.data[6] * s.data[8] + 
          s.data[2] * s.data[7] * s.data[8] + s.data[3] * s.data[4] * s.data[10] - 
          s.data[0] * s.data[7] * s.data[10] - s.data[2] * s.data[4] * s.data[11] + 
          s.data[0] * s.data[6] * s.data[11];

	dst.data[8] = -s.data[7] * s.data[9] * s.data[12] + 
          s.data[5] * s.data[11] * s.data[12] + s.data[7] * s.data[8] * s.data[13] - 
          s.data[4] * s.data[11] * s.data[13] - s.data[5] * s.data[8] * s.data[15] + 
          s.data[4] * s.data[9] * s.data[15];

	dst.data[9] = s.data[3] * s.data[9] * s.data[12] - 
          s.data[1] * s.data[11] * s.data[12] - s.data[3] * s.data[8] * s.data[13] + 
          s.data[0] * s.data[11] * s.data[13] + s.data[1] * s.data[8] * s.data[15] - 
          s.data[0] * s.data[9] * s.data[15];

	dst.data[10] = -s.data[3] * s.data[5] * s.data[12] + 
          s.data[1] * s.data[7] * s.data[12] + s.data[3] * s.data[4] * s.data[13] - 
          s.data[0] * s.data[7] * s.data[13] - s.data[1] * s.data[4] * s.data[15] + 
          s.data[0] * s.data[5] * s.data[15];

	dst.data[11] = s.data[3] * s.data[5] * s.data[8] - 
          s.data[1] * s.data[7] * s.data[8] - s.data[3] * s.data[4] * s.data[9] + 
          s.data[0] * s.data[7] * s.data[9] + s.data[1] * s.data[4] * s.data[11] - 
          s.data[0] * s.data[5] * s.data[11];

	dst.data[12] = s.data[6] * s.data[9] * s.data[12] - 
          s.data[5] * s.data[10] * s.data[12] - s.data[6] * s.data[8] * s.data[13] + 
          s.data[4] * s.data[10] * s.data[13] + s.data[5] * s.data[8] * s.data[14] - 
          s.data[4] * s.data[9] * s.data[14];

	dst.data[13] = -s.data[2] * s.data[9] * s.data[12] + 
          s.data[1] * s.data[10] * s.data[12] + s.data[2] * s.data[8] * s.data[13] - 
          s.data[0] * s.data[10] * s.data[13] - s.data[1] * s.data[8] * s.data[14] + 
          s.data[0] * s.data[9] * s.data[14];

	dst.data[14] = s.data[2] * s.data[5] * s.data[12] - 
          s.data[1] * s.data[6] * s.data[12] - s.data[2] * s.data[4] * s.data[13] + 
          s.data[0] * s.data[6] * s.data[13] + s.data[1] * s.data[4] * s.data[14] - 
          s.data[0] * s.data[5] * s.data[14];

	dst.data[15] = -s.data[2] * s.data[5] * s.data[8] + 
          s.data[1] * s.data[6] * s.data[8] + s.data[2] * s.data[4] * s.data[9] - 
          s.data[0] * s.data[6] * s.data[9] - s.data[1] * s.data[4] * s.data[10] + 
          s.data[0] * s.data[5] * s.data[10];

	// 2. Dzielimy macierz przez wyznacznik
	dst /= d;
}




#endif
