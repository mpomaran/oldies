//	------------------------------------------------------------------------------------
//
//	Integralna czesc modulu math.vector i nie powinna byc oddzielnie dalaczana !!!
//
//	(c)	2002	Michal Pomaranski
//		mpomaranski@poczta.onet.pl
//	------------------------------------------------------------------------------------

#ifndef __MATH_VECTOR3_ARITHMETIC_H
#define __MATH_VECTOR3_ARITHMETIC_H





//	------------------------------------------------------------------------------------
//	Operatory dodawania, odejmowania, dzielenia, mnozenia przez skalar wektora
//	------------------------------------------------------------------------------------
inline	Vector3& Vector3::operator /= (const float   &a)
{
	assert (a != 0);

#ifdef NDEBUG
	if (a == 0)
		throw "Blad dzielenia przez 0!";
#endif

	mul (*this, *this, (float)1./a);
	return *this;
}





inline	Vector3 Vector3::operator * (const float   &a)
{
	Vector3	result;
	mul (result, *this, a);
	return result;
}





inline	Vector3 Vector3::operator / (const float   &a)
{
	Vector3	result;

	assert (a != 0);

#ifdef NDEBUG
	if (a == 0)
		throw "Blad dzielenia przez 0!";
#endif

	mul (result, *this, a);
	return result;
}





inline	Vector3 Vector3::operator + (const float   &a)
{
	Vector3 result;
	Vector3::add(result, *this, a);

	return result;
}





inline	Vector3 Vector3::operator - (const float   &a)
{
	Vector3 result;
	Vector3::sub(result, *this, a);

	return result;
}




//	------------------------------------------------------------------------------------
//	Operatory dodawania, odejmowania wektorow
//	------------------------------------------------------------------------------------

inline	Vector3 operator - (const Vector3 &a, const Vector3 &b)
{
	Vector3 result;
	Vector3::sub(result, a, b);

	return result;
}





inline	Vector3 Vector3::operator + (const Vector3 &a)
{
	Vector3 result;
	Vector3::add(result, *this, a);

	return result;
}





//	------------------------------------------------------------------------------------
//	Mnozenie wektora przez macierz
//	------------------------------------------------------------------------------------

inline	Vector3& Vector3::operator *= (const Matrix4 &b)
{
	static Vector3 temp, result;
	float tmp;

	copy (temp, *this);


	v.x = temp.data[0] * b.data[0] + b.data[12] + temp.data[1] * b.data[4] + temp.data[2] * b.data[8];
	v.y = temp.data[0] * b.data[1] + b.data[13] + temp.data[1] * b.data[5] + temp.data[2] * b.data[9];
	v.z = temp.data[2] * b.data[10] + b.data[14] + temp.data[0] * b.data[2] + temp.data[1] * b.data[6];

#ifdef SAFE_MATRIX_MUL
	tmp = temp.data[2] * b.data[11] + b.data[15] + temp.data[0] * b.data[3] + temp.data[1] * b.data[7];

	// przez 0 dzielic nie mozna !!!
	if (tmp == 0) tmp = (float)0.0000000000000000000000000000000000000000000000000001;
	*this /= tmp;
#endif

	return *this;

}


#endif