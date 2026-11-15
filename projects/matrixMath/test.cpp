#include <windows.h>

#include	<math.h>
#include	<iostream.h>
#include	<stdio.h>
#include	<mmsystem.h>

#include	"math.k3d.h"

void	main ()
{

	Vector3 a(1,1,1),b;
	Matrix4 m;
	Matrix4 rot;


	m.perspective (640, 320, -5, 5);
	m.identity ();
	rot.rotationZ (0.01f);
	rot.rotation (0.01, 0.01, 0.01);
	m *= rot;
	

	b = a * m;

	m.inverse();
	a = b * m;
	a = a+b;
	a = a-b;

	cout << a << " -> " << b;

	cout << "\nOK\n";
	cout << "\nKoniec. Napisz cos i enter..." << endl;
	getchar();
}
