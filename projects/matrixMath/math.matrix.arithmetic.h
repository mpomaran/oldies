//	------------------------------------------------------------------------------------
//
//	Integralna czesc modulu math.matrix i nie powinna byc oddzielnie dalaczana !!!
//
//	(c)	2002	Michal Pomaranski
//		mpomaranski@poczta.onet.pl
//	------------------------------------------------------------------------------------


#ifndef __MATH_MATRIX_ARITHMETIC_H
#define __MATH_MATRIX_ARITHMETIC_H


#include	<assert.h>






//	------------------------------------------------------------------------------------
//	Operatory mnozewnia przez macierz i  mnozenia, dzielenia przez skalar
//	------------------------------------------------------------------------------------

inline	Matrix4 Matrix4::operator * (const Matrix4 &a)
{

	Matrix4 tmp;
	mul (tmp, *this, a);
	return tmp;
}




inline	Matrix4 Matrix4::operator * (const float   &a)
{
	Matrix4 tmp;
	mul (tmp, *this, a);
	return tmp;
}




inline	Matrix4& Matrix4::operator *= (const Matrix4 &a)
{
	static Matrix4 tmp;
	mul (tmp, *this, a);
	copy (*this, tmp);
	return *this;
}




inline	Matrix4& Matrix4::operator *= (const float   &a)
{
	mul (*this, *this, a);
	return *this;
}




inline	Matrix4& Matrix4::operator /= (const float   &a)
{
	assert (a != 0);
	mul (*this, *this, (float)1./a);
	return *this;
}




inline	Matrix4 Matrix4::operator / (const float   &a)
{
	Matrix4 tmp;

	assert (a != 0);

	mul (tmp, *this, (float)1./a);
	return tmp;
}




//	------------------------------------------------------------------------------------
//	Operatory dodawania i odejmowania skalara i macierzy
//	------------------------------------------------------------------------------------

inline	Matrix4 Matrix4::operator + (const Matrix4 &a)
{
	Matrix4 tmp;
	add (tmp, *this, a);
	return tmp;
}




inline	Matrix4 Matrix4::operator + (const float   &a)
{
	Matrix4 tmp;
	add (tmp, *this, a);
	return tmp;
}




inline	Matrix4 Matrix4::operator - (const Matrix4 &a)
{
	Matrix4 tmp;
	sub (tmp, *this, a);
	return tmp;
}




inline	Matrix4 Matrix4::operator - (const float   &a)
{
	Matrix4 tmp;
	add (tmp, *this, -a);
	return tmp;
}





inline	Matrix4& Matrix4::operator += (const Matrix4 &a)
{
	add (*this, *this, a);
	return *this;
}




inline	Matrix4& Matrix4::operator += (const float   &a)
{
	add (*this, *this, a);
	return *this;
}





//	------------------------------------------------------------------------------------
//	Operator przypisania
//	------------------------------------------------------------------------------------

inline	Matrix4& Matrix4::operator = (const Matrix4 &a)
{
	copy (*this, a);
	return *this;
}

#endif



