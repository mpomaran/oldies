/*
**      TRANSFORM.H             Przeksztalcenie w 3d ukladze wspolrzednych
**      Sarin/!ArisE!
*/

#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include "matrix.h"
#include "vector3d.h"

class transformation {
      public:
              matrix3x3 matrix;
              vector3d vector;

              void addRotation(float angleX, float angleY, float angleZ);
              void addRotation(vector3d &x, vector3d &y, vector3d &z);
              void addScale(float const scaleX, float const scaleY,
                                  float const scaleZ);
              void clearMatrix(void);
};

#endif
