/*
**      VERTEX3D.H              Definicja punktu w przestrzeni 3d
**
**      Sarin/!ArisE!
*/

#ifndef __VERTEX3D_H
#define __VERTEX3D_H

#include <iostream.h>

#include "vector3d.h"
#include "transform.h"

class vertex3d : public vector3d {
      public:
              unsigned char u,v;        // wspolrzedne bitmapy
              unsigned char color;      // intensywnosc koloru

              vector3d norm;            // wektor normalny do wierzcholka

              vertex3d(float const coordinates[3]);
              vertex3d(float const &x, float const &y, float const &z);
              vertex3d(float const k);
              vertex3d(void);
              vertex3d(vector3d &vect);

              vertex3d& transform(transformation &t);
              vector3d& transformNorm(transformation &t);

              inline vertex3d& operator =(vertex3d &vert)
              {
                this->xyz.x = vert[0]; this->xyz.y = vert[1]; this->xyz.z = vert[2];
                this->u = vert.u; this->v = vert.v;
                this->color = vert.color;
                this->norm = vert.norm;
                return *this;
              }
              inline vertex3d& operator =(vector3d &vect)
              {
                this->xyz.x = vect[0]; this->xyz.y = vect[1]; this->xyz.z = vect[2];
                return *this;
              }

              // we/wy
              friend ostream& operator << (ostream &s, vertex3d &vert);
              friend istream& operator >> (istream &s, vertex3d &vert);

              ostream& save (ostream &s);
              istream& load (istream &s);
              void get (char const *buff);
};

#endif