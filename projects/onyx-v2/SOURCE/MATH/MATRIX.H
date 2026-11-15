/*
**      MATRIX.H                Definicja macierzy
**      Sarin/!ArisE
*/

#ifndef __MATRIX_H
#define __MATRIX_H

#include <assert.h>
#include <iostream.h>
#include <math.h>

class matrix3x3 {
      private:
               float matrix[3][3];
      public:

               matrix3x3();
               matrix3x3(float matr[3][3]);
               matrix3x3(float k);
               matrix3x3(matrix3x3 const &matr);

               // czyszczenie
               clear();

               // dostep do macierzy
               inline float& get(int const i, int const j);

               // operator przypisania
               matrix3x3& operator=(matrix3x3 const &matr);

               // operacje na macierzach
               matrix3x3& operator+=(matrix3x3 const &matr);
               matrix3x3& operator-=(matrix3x3 const &matr);
               matrix3x3& operator*=(matrix3x3 const &matr);
               matrix3x3& operator+=(float &k);
               matrix3x3& operator-=(float &k);
               matrix3x3& operator*=(float &k);
               matrix3x3& operator/=(float &k);

               friend matrix3x3 operator+(matrix3x3 const &m1, matrix3x3 const &m2);
               friend matrix3x3 operator-(matrix3x3 const &m1, matrix3x3 const &m2);
               friend matrix3x3 operator*(matrix3x3 const &m1, matrix3x3 const &m2);

               // we/wy
               friend ostream& operator<<(ostream &s, matrix3x3 &matr);
};

// dostep do macierzy
inline float& matrix3x3::get(int const i, int const j)
{
 assert(i<3);
 assert(j<3);
 return this->matrix[i][j];
}

#endif
