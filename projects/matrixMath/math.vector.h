//	------------------------------------------------------------------------------------
//	math.vector.h		-	klasa Vector3 i podstawowe operacje
//							na niej
//
//	Wykorzystanie za pomoca funkcji lub operatorów (nie zalecane)
//
//
//	Zaimplementowano:
//		mnozenie skalarne - dot ()
//		  - " -  wektorowe - cross ()
//
//	Wywo³ywanie:
//		Wszystkie metody statyczne wywolujemy zgodnie z konwencja
//			metoda (element_docelowy, [operand1], [operand 2]),
//
//	Uwaga:
//
//	(c)	2002	Michal Pomaranski
//		mpomaranski@poczta.onet.pl
//	------------------------------------------------------------------------------------



#ifndef __MATH_VECTOR3_H
#define __MATH_VECTOR3_H

#include	<memory.h>
#include	"math.matrix.h"


//	------------------------------------------------------------------------------------
//	Klasa definiujaca wektor 3d
//	------------------------------------------------------------------------------------

class	Vector3
{
public:
//	float	data[3];		// tutaj sa wpisywane kolejne dane

	union
	{
		float	data[3];
		struct
		{
			float x;
			float y;
			float z;
		} v;
	};


	//  Metody statyczne
	static	void	copy (Vector3& dst, const Vector3& src);
	static	void	dot (float& dst, const Vector3 &a, const Vector3 &b);
	static	void	cross (Vector3& dst, const Vector3 &a, const Vector3 &b);
	static	void	normalize (Vector3& dst, Vector3& src);
	static	void	add (Vector3& dst, const Vector3 &a, const Vector3& b);
	static	void	add (Vector3& dst, const Vector3 &a, const float& b);
	static	void	sub (Vector3& dst, const Vector3 &a, const Vector3& b);
	static	void	sub (Vector3& dst, const Vector3 &a, const float& b);
	static	void	mul (Vector3& dst, const Vector3 &a, const float& b);


	//	Konstruktor
	inline Vector3 (const Vector3 &m) {	Vector3::copy (*this, m); }
	inline Vector3 (const float& x, const float& y, const float& z)
		{ v.x = x; v.y = y; v.z = z; }
	inline Vector3 (const float *f) { memcpy (data, f, sizeof (float) * 3); }

	inline Vector3 () {};


	//  Inne metody
	inline	float	len		( void );
	inline	float	len2	( void );		// dlugosc w kwadracie
	inline	void	normalize	( void ) { Vector3::normalize (*this, *this); };

	//	Operatory arytmetyczne i przypisania
	inline	Vector3 operator * (const float   &a);
	inline	Vector3 operator / (const float   &a);
	inline	Vector3 operator + (const Vector3 &a);
	inline	Vector3 operator + (const float   &a);
	inline	Vector3 operator - (const float   &a);
	inline	Vector3& operator = (const Vector3 &a) { copy (*this, a); return *this; };

	inline	Vector3& operator *= (const float   &a) { mul (*this, *this, a); return *this; };
	inline	Vector3& operator *= (const Matrix4 &a);
	inline	Vector3& operator /= (const float   &a);
	inline	Vector3& operator += (const Vector3 &a) { add (*this, *this, a); return *this; };
	inline	Vector3& operator += (const float   &a) { add (*this, *this, a); return *this; };
	inline	Vector3& operator -= (const Vector3 &a) { sub (*this, *this, a); return *this; };
	inline	Vector3& operator -= (const float   &a) { sub (*this, *this, a); return *this; };

	friend	Vector3 operator - (const Vector3 &a, const Vector3 &b);



	//	WE/WY
	inline	friend ostream&	operator << (ostream &o, const	Vector3 &a);

};




#endif