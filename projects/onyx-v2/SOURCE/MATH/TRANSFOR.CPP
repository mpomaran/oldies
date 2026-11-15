/*
**      Transform.cpp           Transformacje
**      Sarin/!Arise!
*/

#include <math.h>

#include "matrix.h"
#include "vertex3d.h"

void transformation::addRotation(vector3d &x, vector3d &y, vector3d &z)
{
  matrix3x3 result;
  int i;

  for (i=0; i<3; i++)
      result.get(0,i) = x[i];

  for (i=0; i<3; i++)
      result.get(1,i) = y[i];

  for (i=0; i<3; i++)
      result.get(2,i) = z[i];

  matrix=result;
}

void transformation::addRotation(float angleX, float angleY, float angleZ)
{
  static matrix3x3 result;

  // zajmujemy sie obrotem wokol x
  result.clear();
  result.get(1,1) = cos(angleX);
  result.get(2,1) = -sin(angleX);
  result.get(1,2) = sin(angleX);
  result.get(2,2) = cos(angleX);
  matrix = result;

  // obrot wokol osi y
  result.clear();
  result.get(0,0) = cos(angleY);
  result.get(2,0) = sin(angleY);
  result.get(0,2) = -sin(angleY);
  result.get(2,2) = cos(angleY);
  matrix *= result;

  // obrot wokol osi z;
  result.clear();
  result.get(0,0) = cos(angleZ);
  result.get(1,0) = -sin(angleZ);
  result.get(0,1) = sin(angleZ);
  result.get(1,1) = cos(angleZ);
  matrix *= result;
}

void transformation::clearMatrix(void)
{
  matrix3x3 clear;

  matrix=clear;
}

void transformation::addScale(float const scaleX, float const scaleY,
                                  float const scaleZ)
{
  static matrix3x3 scale;

  scale.get(0,0) = scaleX;
  scale.get(1,1) = scaleY;
  scale.get(2,2) = scaleZ;

  matrix *= scale;
}
