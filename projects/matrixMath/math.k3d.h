//	------------------------------------------------------------------------------------
//	math.k3d.h		-	Klasy ulwiajace manipulacje matematyczne w przestrzeni 3d
//
//	(c)	2002	Michal Pomaranski
//		mpomaranski@poczta.onet.pl
//	------------------------------------------------------------------------------------

#ifndef __MATH_K3D_H
#define __MATH_K3D_H


// co robic z 4 'wirtualna' wspolrzedna wektora[3]
#define SAFE_MATRIX_MUL

// z jaka dokladnoscia powinny byc porownywane floaty
#define FLOAT_EQUAL_RESOLUTION	(0.01)



#include	<assert.h>
#include	"math.vector.h"
#include	"math.matrix.h"





//	------------------------------------------------------------------------------------
//	Mnozenie macierzy przez wektor
//	------------------------------------------------------------------------------------

inline Vector3 operator	* (Matrix4 &b, Vector3 &a)
{
	Vector3 result;
	float	temp;

	result.v.x = a.data[0] * b.data[0] + a.data[1] * b.data[1] + a.data[2] * b.data[2] + b.data[3];
	result.v.y = a.data[0] * b.data[4] + a.data[1] * b.data[5] + a.data[2] * b.data[6] + b.data[7];
	result.v.z = a.data[2] * b.data[10] + b.data[11] + a.data[0] * b.data[8] + a.data[1] * b.data[9];

#ifdef SAFE_MATRIX_MUL
	temp = a.data[0] * b.data[12] + a.data[1] * b.data[13] + a.data[2] * b.data[14] + b.data[15];

	// przez 0 dzielic nie mozna !!!
	if (temp == 0) temp = (float)0.0000000000000000000000000000000000000000000000000001;
	assert (temp != 0);
	result /= temp;
#endif

	return result;
}





//	------------------------------------------------------------------------------------
//	Mnozenie wektora przez macierz
//	------------------------------------------------------------------------------------

inline Vector3 operator	* (Vector3 &a, Matrix4 &b)
{
	Vector3 result;
	float temp;

	result.v.x = a.data[0] * b.data[0] + b.data[12] + a.data[1] * b.data[4] + a.data[2] * b.data[8];
	result.v.y = a.data[0] * b.data[1] + b.data[13] + a.data[1] * b.data[5] + a.data[2] * b.data[9];
	result.v.z = a.data[2] * b.data[10] + b.data[14] + a.data[0] * b.data[2] + a.data[1] * b.data[6];

#ifdef SAFE_MATRIX_MUL
	temp = a.data[2] * b.data[11] + b.data[15] + a.data[0] * b.data[3] + a.data[1] * b.data[7];

	// przez 0 dzielic nie mozna !!!
	if (temp == 0) temp = (float)0.000000000000001;

	result /= temp;
#endif

	return result;
}




//	------------------------------------------------------------------------------------
//	Operatory WY
//	------------------------------------------------------------------------------------

ostream&	operator << (ostream &o, const Vector3 &a)
{
	o << "[" << a.v.x << " ";
	o << a.v.y << " ";
	o << a.v.z << "]";
	return o;
}



inline	ostream& operator << (ostream &o, const Matrix4 &a)
{
	o << endl << "Matrix dump:" << endl;
	for (int i=0; i<16; i+=4)
	{
		for (int j=0; j<4; j++)
			o << a.data[i+j] << " ";
		o << endl;
	}

	return o;
}





//	------------------------------------------------------------------------------------
//	dolaczenie funkcji inline
//	------------------------------------------------------------------------------------

#include	"math.matrix.fn.h"
#include	"math.matrix.arithmetic.h"
#include	"math.matrix.bool.h"
#include	"math.matrix.tools.h"

#include	"math.vector.fn.h"
#include	"math.vector.arithmetic.h"

#endif
