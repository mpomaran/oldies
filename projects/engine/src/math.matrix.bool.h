//	------------------------------------------------------------------------------------
//
//	Integralna czesc modulu math.matrix i nie powinna byc oddzielnie dalaczana !!!
//
//	(c)	2002	Michal Pomaranski
//		mpomaranski@poczta.onet.pl
//	------------------------------------------------------------------------------------

#ifndef __MATH_MATRIX_BOOL_H
#define __MATH_MATRIX_BOOL_H

#include	<math.h>

#include	"math.k3d.h"



//	------------------------------------------------------------------------------------
//	Operatory porownania
//	------------------------------------------------------------------------------------

inline	bool	Matrix4::operator == (const Matrix4	&a)
{
	for (int i=0; i<16; i++)
	{
		if (fabs(a.data[i] - data[i]) > FLOAT_EQUAL_RESOLUTION)
			return false;
	}

	return true;
}


//	------------------------------------------------------------------------------------

inline	bool	Matrix4::operator != (const Matrix4	&a)
{
	if (*this == a)
		return false;
	
	return true;
}

#endif