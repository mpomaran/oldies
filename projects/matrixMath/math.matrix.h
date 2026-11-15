//	------------------------------------------------------------------------------------
//	math.matrix.h		-	klasa Matrix4x4 i podstawowe operacje
//							na niej
//
//	Wykorzystanie za pomoca funkcji lub operatorów (nie zalecane)
//
//	Tak wyglada macierz:
//		+-           -+
//		| 0  1  2  3  |
//		| 4  5  6  7  |
//		| 8  9  10 11 |
//		| 12 13 14 15 |
//		+-           -+
//
//	Zaimplementowano:
//		operatory:
//			 + * += *= == != - / -= /=
//	
//		metody statyczne:
//			mul, add, identity, copy, transpose, inverse, sub, det
//
//	Wywo³ywanie:
//		Wszystkie metody statyczne wywolujemy zgodnie z konwencja
//			metoda (element_docelowy, [operand1], [operand 2]),
//		oprocz metody det, ktora liczy wyznacznik macierzy i jest
//		postaci 
//			float det (const macierz)
//
//	Uwaga:
//		Poniewaz wewnetrznie wszystko jest wywokonywane na float'ach
//		to nalezy liczyc sie z utrata dokladnosci.
//
//		Definicja FLOAT_EQUAL_RESOLUTION jest uzywana podczas porownywania
//		macierzy (z taka dokladnoscia sa wykonywane obliczenia na floatach,
//		i to te nie bardzo skomplikowane
//
//	(c) 2002 Michal Pomaranski
//	------------------------------------------------------------------------------------



#ifndef __MATH_MATRIX_4X4_H
#define __MATH_MATRIX_4X4_H

#include	<memory.h>			// memcpy.h

//#include	"math.vector.h"

//	------------------------------------------------------------------------------------
//	Klasa macierzy 4x4
//	------------------------------------------------------------------------------------
class	Vector3;

class Matrix4
{
public:
	float	data[4*4];		// tutaj sa wpisywane kolejne dane

	static 	void copy(Matrix4 &dst, const Matrix4 &src);
	static	void mul (Matrix4 &dst, const Matrix4 &a1,  const Matrix4 &a2);
	static	void mul (Matrix4 &dst, const Matrix4 &src, const float &a);
	static	void add (Matrix4 &dst, const Matrix4 &a1,  const Matrix4 &a2);
	static	void add (Matrix4 &dst, const Matrix4 &src, const float &a);
	static	void sub (Matrix4 &dst, const Matrix4 &a1,  const Matrix4 &a2);
	static	void sub (Matrix4 &dst, const Matrix4 &src, const float &a);
	static	void identity (Matrix4 &dst);
	static	void transpose (Matrix4 &dst, const Matrix4 &src);
	static	void inverse (Matrix4 &dst, const Matrix4 &src);

	static	float det (const Matrix4 &src);

	// Metody uzytkowe (patrz dokumentacja DirectX)
	static	void lookAt (Matrix4 &dst, const Vector3 &eye, const Vector3 &at, const Vector3 &up);
	static	void ortho (Matrix4 &dst,  float w,  float h,  float zn, float zf);
	static	void perspective (Matrix4 &dst, float w, float h, float zn, float zf);
	static	void rotationX (Matrix4 &dst, float a=0.0f);
	static	void rotationY (Matrix4 &dst, float a=0.0f);
	static	void rotationZ (Matrix4 &dst, float a=0.0f);
	static	void rotation (Matrix4 &dst, float angleX=0.0f, float angleY=0.0f, float angleZ=0.0f);


	//	Konstruktor
	inline Matrix4 (const Matrix4 &m) {	copy (*this, m); }
	inline Matrix4 (const float* f) { memcpy (data, f, sizeof (float) * 16); }
	inline Matrix4 () {};

	//	Trywialne operacje 
	inline void identity (void)	 { identity (*this);		}
	inline void	transpose (void) { transpose (*this, *this); };
	inline void	inverse (void)	 { inverse (*this, *this);  };
	inline float det (void) { return det (*this); };

	// Metody uzytkowe
	inline void lookAt (const Vector3 &eye, const Vector3 &at, const Vector3 &up)
	{	Matrix4::lookAt (*this, eye, at, up); }

	inline void ortho (float w, float h, float zn, float zf)
	{	Matrix4::ortho (*this, w, h, zn, zf); }

	inline void perspective (float w, float h, float zn, float zf)
	{	Matrix4::perspective (*this, w, h, zn, zf); }

	inline void rotationX (float angle=0.0f)
	{	Matrix4::rotationX (*this, angle); }

	inline void rotationY (float angle=0.0f)
	{	Matrix4::rotationY (*this, angle); }

	inline void rotationZ (float angle=0.0f)
	{	Matrix4::rotationZ (*this, angle); }

	inline void rotation (float aX=0.0f, float aY=0.0f, float aZ=0.0f)
	{	Matrix4::rotation (*this, aX, aY, aZ); }

				

	//	Operatory arytmetyczne i przypisania
	inline	Matrix4 operator * (const Matrix4 &a);
	inline	Matrix4 operator * (const float   &a);
	inline	Matrix4 operator / (const float   &a);
	inline	Matrix4 operator + (const Matrix4 &a);
	inline	Matrix4 operator + (const float   &a);
	inline	Matrix4 operator - (const Matrix4 &a);
	inline	Matrix4 operator - (const float   &a);
	inline	Matrix4& operator = (const Matrix4 &a);

	inline	Matrix4& operator *= (const Matrix4 &a);
	inline	Matrix4& operator *= (const float   &a);
	inline	Matrix4& operator /= (const float   &a);
	inline	Matrix4& operator += (const Matrix4 &a);
	inline	Matrix4& operator += (const float   &a);
	inline	Matrix4& operator -= (const Matrix4 &a);
	inline	Matrix4& operator -= (const float   &a);

	// Operatory porownania
	inline	bool	operator == (const Matrix4	&a);
	inline	bool	operator != (const Matrix4	&a);

	//	WE/WY
	inline	friend ostream&	operator << (ostream &o, const	Matrix4 &a);
};




#endif
	