//	------------------------------------------------------------------------------------
//	(c)	2002	Michal Pomaranski
//		mpomaranski@poczta.onet.pl
//	------------------------------------------------------------------------------------

#ifndef __GEOMETRY_SIMPLE_H
#define __GEOMETRY_SIMPLE_H

#include <list>

using namespace std;

#include	"engine.common.h"
#include	"geo.basic.h"
#include	"geo.mng.simple.h"
#include	"math.k3d.h"


//	------------------------------------------------------------------------------------
//	Podstawowa klasa definiujaca geometrie
//
//	Opis metod:
//
//		giveGeometry (state, faces)
//			Zgodnie ze stanem swiata zapisanym w states dodaje do listy face'ow faces
//			trojkaty (lub cokolwiek innego) we wspolrzednych kamery
//
//		giveData ()
//			Zwraca wskaznik do danych specyficznych dla danej geometrii. 
//
//	Opis skladowych
//		localTransform	- macierz transformujaca wspolrzedne objektu do wspolrzednych 
//						swiata
//
//		data			- lista manadzerow danych geometrii, z ktorych moze korzystac
//						dana geometria
//	------------------------------------------------------------------------------------

typedef	list <GeometryDataManager *> GeoDataList;

class	GeometryBasic
{
		Matrix4		localTransform;
		GeoDataList	data;


		// Konstruktor, destruktor
		GeometryBasic () { localTransform.identity ();};
		~GeometryBasic () { };

		// Z tego korzysta shader
		int	giveGeometry (CameraState &state, FaceList &faces) = 0;
		void *giveData () = 0;
};

#endif