/*
**      MATRIX.CPP              Definicja macierzy
**      Sarin/!ArisE
*/

#include <assert.h>
#include <iostream.h>
#include <math.h>

#include "matrix.h"

///////////////////////////////////////////////////////////
matrix3x3::clear()
{
 int i,j;

 for (i=0; i<3; i++)
     for (j=0; j<3; j++)
         matrix[i][j] = (i==j)?1:0;       // tworzenie macierzy jednostkowej
}

///////////////////////////////////////////////////////////
matrix3x3::matrix3x3()
{
 int i,j;

 for (i=0; i<3; i++)
     for (j=0; j<3; j++)
         matrix[i][j] = (i==j)?1:0;       // tworzenie macierzy jednostkowej
}

///////////////////////////////////////////////////////////
matrix3x3::matrix3x3(float matr[3][3])
{
 int i,j;

 for (i=0; i<3; i++)
     for (j=0; j<3; j++)
         this->matrix[i][j] = matr[i][j];
}

///////////////////////////////////////////////////////////
matrix3x3::matrix3x3(float k)
{
 int i,j;

 for (i=0; i<3; i++)
     for (j=0; j<3; j++)
         this->matrix[i][j] = k;
}

///////////////////////////////////////////////////////////
matrix3x3::matrix3x3(matrix3x3 const &matr)
{
 int i,j;

 for (i=0; i<3; i++)
     for (j=0; j<3; j++)
         this->matrix[i][j] = matr.matrix[i][j];
}

///////////////////////////////////////////////////////////
// operator przypisania
matrix3x3& matrix3x3::operator=(matrix3x3 const &matr)
{
 int i,j;

 for (i=0; i<3; i++)
     for (j=0; j<3; j++)
         this->matrix[i][j] = matr.matrix[i][j];

 return *this;
}

///////////////////////////////////////////////////////////
// operacje na macierzach
matrix3x3& matrix3x3::operator+=(matrix3x3 const &matr)
{
 int i,j;

 for (i=0; i<3; i++)
     for (j=0; j<3; j++)
         this->matrix[i][j] += matr.matrix[i][j];

 return *this;
}

///////////////////////////////////////////////////////////
matrix3x3& matrix3x3::operator-=(matrix3x3 const &matr)
{
 int i,j;

 for (i=0; i<3; i++)
     for (j=0; j<3; j++)
         this->matrix[i][j] -= matr.matrix[i][j];

 return *this;
}

///////////////////////////////////////////////////////////
matrix3x3& matrix3x3::operator*=(matrix3x3 const &matr)
{
 matrix3x3 result;
 int i,j,k;

  for (i=0; i<3; i++)
      for (j=0; j<3; j++)
      {
        result.matrix[i][j] = 0;
        for (k=0; k<3; k++)
            result.matrix[i][j] += this->matrix[i][k] * matr.matrix[k][j];
      }

  *this = result;

  return *this;
}

///////////////////////////////////////////////////////////
matrix3x3& matrix3x3::operator+=(float &k)
{
 int i,j;

 for (i=0; i<3; i++)
     for (j=0; j<3; j++)
         this->matrix[i][j] += k;

 return *this;
}

///////////////////////////////////////////////////////////
matrix3x3& matrix3x3::operator-=(float &k)
{
 int i,j;

 for (i=0; i<3; i++)
     for (j=0; j<3; j++)
         this->matrix[i][j] -= k;

 return *this;
}

///////////////////////////////////////////////////////////
matrix3x3& matrix3x3::operator*=(float &k)
{
 int i,j;

 for (i=0; i<3; i++)
     for (j=0; j<3; j++)
         this->matrix[i][j] *= k;

 return *this;
}

///////////////////////////////////////////////////////////
matrix3x3& matrix3x3::operator/=(float &k)
{
 int i,j;

 for (i=0; i<3; i++)
     for (j=0; j<3; j++)
         this->matrix[i][j] /= k;

 return *this;
}

///////////////////////////////////////////////////////////
matrix3x3 operator+(matrix3x3 const &m1, matrix3x3 const &m2)
{
 matrix3x3 result;
 int i,j;

        for (i=0; i<3; i++)
            for (j=0; j<3; j++)
                result.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];

 return result;
}

///////////////////////////////////////////////////////////
matrix3x3 operator-(matrix3x3 const &m1, matrix3x3 const &m2)
{
 matrix3x3 result;
 int i,j;

        for (i=0; i<3; i++)
            for (j=0; j<3; j++)
                result.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];

 return result;
}

///////////////////////////////////////////////////////////
matrix3x3 operator*(matrix3x3 const &m1, matrix3x3 const &m2)
{
 matrix3x3 result;
 int i,j;

  for (i=0; i<3; i++)
      for (j=0; j<3; j++)
            result.matrix[i][j] = m1.matrix[i][0] * m2.matrix[0][j]
                   + m1.matrix[i][1] * m2.matrix[1][j]
                   + m1.matrix[i][2] * m2.matrix[2][j];

  return result;

}

///////////////////////////////////////////////////////////
// we/wy
ostream& operator<<(ostream &s, matrix3x3 &matr)
{
 int i,j;

 for (i=0; i<3; i++)
 {
     for (j=0; j<3; j++)
         s << matr.matrix[i][j] << " ";

     s << "\n";
 }

 return s;
}
