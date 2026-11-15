//	------------------------------------------------------------------------------------
//
//	Integralna czesc modulu math.vector i nie powinna byc oddzielnie dalaczana !!!
//
//	(c)	2002	Michal Pomaranski
//		mpomaranski@poczta.onet.pl
//	------------------------------------------------------------------------------------


#ifndef __MATH_MATRIX_TOOLS_H
#define __MATH_MATRIX_TOOLS_H

#include	<assert.h>
#include	"math.vector.h"



//	------------------------------------------------------------------------------------
//		Metody uzytkowe
//	------------------------------------------------------------------------------------

inline void Matrix4::lookAt (Matrix4 &dst, 
			const Vector3 &eye, const Vector3 &at, const Vector3 &up)
{
	Vector3	x,y,z;
	
	// tworzenie pomocniczych wektorow
	z = at-eye; z.normalize();
	Vector3::cross (x, up, z); x.normalize();
	Vector3::cross (y, z, x);
	dst.data[0] = x.v.x;	dst.data[1] = y.v.x;	dst.data[2] = z.v.x;	dst.data[3] = 0;
	dst.data[4] = x.v.y;	dst.data[5] = y.v.y;	dst.data[6] = z.v.y;	dst.data[7] = 0;
	dst.data[8] = x.v.z;	dst.data[9] = y.v.z;	dst.data[10] = z.v.z;	dst.data[11] = 0;
	Vector3::dot(dst.data[12], x, eye);	Vector3::dot(dst.data[13],y, eye);	
	Vector3::dot(dst.data[14],z, eye); dst.data[15] = 1;
	dst.data[12] *= -1;
	dst.data[13] *= -1;
	dst.data[14] *= -1;
}





inline void Matrix4::ortho (Matrix4 &dst, float w, float h, float zn, float zf)
{
	dst.data[0] = 2.0f/w;	dst.data[1] = 0.0f;		dst.data[2] = 0.0f;			dst.data[3] = 0.0f;
	dst.data[4] = 0.0f;		dst.data[5] = 2.0f/h;	dst.data[6] = 0.0f;			dst.data[7] = 0.0f;
	dst.data[8] = 0.0f;		dst.data[9] = 0.0f;		dst.data[10] = 1.0f/(zf-zf);dst.data[11] = 0.0f;
	dst.data[12] = 0.0f;	dst.data[13] = 0.0f;	dst.data[13] = zn/(zn-zf);	dst.data[13] = 1.0f;
}




inline void Matrix4::perspective (Matrix4 &dst, float w, float h, float zn, float zf)
{
	dst.identity ();

	dst.data[0] = (2.0f * zn) / w;
	dst.data[5] = (2.0f * zn) / h;
	dst.data[10] = zf / (zf - zn);
	dst.data[11] = 1.0f;
	dst.data[14] = (zn * zf) / (zn - zf);
}





inline void Matrix4::rotationX (Matrix4 &dst, float a)
{
	float s = (float)sin(a), c = (float)cos(a);
	dst.identity ();

	dst.data[5] = c;		dst.data[6] = s;
	dst.data[9] = -s;		dst.data[10] = c;
}





inline void Matrix4::rotationY (Matrix4 &dst, float a)
{
	float s = (float)sin(a), c = (float)cos(a);
	dst.identity ();

	dst.data[0] = c;		dst.data[2] = -s;
	dst.data[8] = s;		dst.data[10] = c;
}





inline void Matrix4::rotationZ (Matrix4 &dst, float a)
{
	float s = (float)sin(a), c = (float)cos(a);
	dst.identity ();

	dst.data[0] = c;		dst.data[1] = s;
	dst.data[4] = -s;		dst.data[5] = c;
}




inline void Matrix4::rotation (Matrix4 &dst, float x, float y, float z)
{
	Matrix4 tmp, tmp2, tmp3;

	Matrix4::rotationX (tmp, x);
	Matrix4::rotationY (tmp2, y);
	Matrix4::rotationZ (tmp3, z);

	dst = tmp * tmp2 * tmp3;
}




#endif

