//	------------------------------------------------------------------------------------
//
//	engine.common.h		-	definicje wspolne dla calego engine'u
//
//
//	(c)	2002	Michal Pomaranski
//		mpomaranski@poczta.onet.pl
//	------------------------------------------------------------------------------------

#ifndef __ENGINE_COMMOM_H
#define __ENGINE_COMMOM_H


#include	"math.k3d.h"






//	------------------------------------------------------------------------------------
//	Struktura opisujaca polozenie kamery
//	------------------------------------------------------------------------------------

struct	Camera
{
	Point3	camera;			// gdzie jest kamera
	Vector3	lookAt;			// w ktora strone sie patrzy
	Vector3	up;				// gdzie jest "gora" dla kamery
};





//	------------------------------------------------------------------------------------
//	Struktura, ktora mowi geometrii gdzie znajduje sie kamera i w ktora strone patrzy.
//	Na jej podstawie geometria wie, co ma wyrzucic
//	------------------------------------------------------------------------------------

struct	CameraState
{
	Camera	camera;

	//	inne informacje, np. poziom detali
	unsigned	levelOfDetail;			// 0 - najwyzszy
};



#endif