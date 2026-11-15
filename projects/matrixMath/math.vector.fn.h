//	------------------------------------------------------------------------------------
//
//	Integralna czesc modulu math.vector i nie powinna byc oddzielnie dalaczana !!!
//
//	(c)	2002	Michal Pomaranski
//		mpomaranski@poczta.onet.pl
//	------------------------------------------------------------------------------------

#ifndef __MATH_VECTOR3_FN_H
#define __MATH_VECTOR3_FN_H

#include	<math.h>

//	------------------------------------------------------------------------------------
//	Kopiowane dwoch macierzy
//	------------------------------------------------------------------------------------

inline void Vector3::copy(Vector3 &dst, const Vector3 &src)
{
	if (dst.data != src.data)
		memcpy (dst.data, src.data, sizeof (float) * 3);
}





//	------------------------------------------------------------------------------------
//	Iloczyn skalarny
//	------------------------------------------------------------------------------------

inline	void	Vector3::dot (float& dst, const Vector3 &a, const Vector3 &b)
{
	dst = a.data[0] * b.data[0] + 
		a.data[1] * b.data[1] + 
		a.data[2] * b.data[2];
}





//	------------------------------------------------------------------------------------
//	Iloczyn wektorowy
//	------------------------------------------------------------------------------------

inline	void	Vector3::cross (Vector3& dst, const Vector3 &a, const Vector3 &b)
{
	assert (a.data != dst.data); assert (b.data != dst.data);
	dst.v.x = a.v.y * b.v.z - b.v.y * a.v.z;
	dst.v.y = b.v.x * a.v.z - a.v.x * b.v.z;
	dst.v.z = a.v.x * b.v.y - b.v.x * a.v.y;
}





//	------------------------------------------------------------------------------------
//	Sprowadza dlugosc wektora do 1
//	------------------------------------------------------------------------------------

inline	void	Vector3::normalize (Vector3& dst, Vector3& src)
{
	float f = src.len ();
	dst.data[0] /= f;
	dst.data[1] /= f;
	dst.data[2] /= f;
}







//	------------------------------------------------------------------------------------
//	Liczy dlugosc wektora
//	------------------------------------------------------------------------------------

inline	float	Vector3::len ( void )
{
	return	(float)sqrt ( (double)(data[0]*data[0] + data[1]*data[1] + data[2]*data[2]) );
}

inline	float	Vector3::len2 ( void )
{
	return	data[0]*data[0] + data[1]*data[1] + data[2]*data[2];
}



//	------------------------------------------------------------------------------------
//	Dodaje wektory
//	------------------------------------------------------------------------------------

inline	void	Vector3::add (Vector3& dst, const Vector3 &a, const Vector3 &b)
{
	dst.v.x = a.v.x + b.v.x;
	dst.v.y = a.v.y + b.v.y;
	dst.v.z = a.v.z + b.v.z;
}





//	------------------------------------------------------------------------------------
//	Odejmuje wektory
//	------------------------------------------------------------------------------------

inline	void	Vector3::sub (Vector3& dst, const Vector3 &a, const Vector3 &b)
{
	dst.v.x = a.v.x - b.v.x;
	dst.v.y = a.v.y - b.v.y;
	dst.v.z = a.v.z - b.v.z;
}





//	------------------------------------------------------------------------------------
//	Mnozy wektor przez skalar
//	------------------------------------------------------------------------------------

inline	void	Vector3::mul (Vector3& dst, const Vector3 &a, const float &b)
{
	dst.v.x = a.v.x * b;
	dst.v.y = a.v.y * b;
	dst.v.z = a.v.z * b;
}





//	------------------------------------------------------------------------------------
//	Dodaje wektor do skalara
//	------------------------------------------------------------------------------------

inline	void	Vector3::add (Vector3& dst, const Vector3 &a, const float &b)
{
	dst.v.x = a.v.x + b;
	dst.v.y = a.v.y + b;
	dst.v.z = a.v.z + b;
}





//	------------------------------------------------------------------------------------
//	Odejmuje wektor od skalara
//	------------------------------------------------------------------------------------

inline	void	Vector3::sub (Vector3& dst, const Vector3 &a, const float &b)
{
	dst.v.x = a.v.x - b;
	dst.v.y = a.v.y - b;
	dst.v.z = a.v.z - b;
}


#endif