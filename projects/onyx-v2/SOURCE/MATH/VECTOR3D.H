/*
**      VECTOR3D.H                Definicja wektora
**
**      Sarin/!ArisE!
*/

#ifndef __VECTOR_H
#define __VECTOR_H

#include <assert.h>
#include <iostream.h>

#include "matrix.h"

class vector3d {
    protected:
      union {                            // do wspolrzednych mozna sie odwo-
            float coord[3];              // lywac jako do tablicy
            struct {                     // lub wspolrzednych x, y, z
                  float x,y,z;
            }xyz;
      };

    public:
            // konstruktory
            inline vector3d(float const *coordinates)
              {xyz.x = coordinates[0]; xyz.y = coordinates[1]; xyz.z = coordinates[2];};
            inline vector3d(float const &x, float const &y, float const &z)
              {xyz.x = x; xyz.y = y; xyz.z = z;};
            inline vector3d(float const k)
              {xyz.x = k; xyz.y = k; xyz.z = k;};
            inline vector3d()
              {xyz.x = 0; xyz.y = 0; xyz.z = 0;};

            inline float& x(void);
            inline float& y(void);
            inline float& z(void);
            inline float& operator[](int const index);

            // dzialania na wektorach
            inline vector3d& operator*=(matrix3x3 &matr);
            inline vector3d& operator*=(float const k);
            inline vector3d& operator*=(vector3d const &vect);  // ilcozyn wektorowy
            inline vector3d& operator/=(float const k);
            inline vector3d& operator+=(vector3d const &vect);
            inline vector3d& operator-=(vector3d const &vect);
            inline vector3d& operator+=(float const k);
            inline vector3d& operator-=(float const k);
            inline vector3d& operator=(vector3d const &vect);

            inline friend vector3d& operator/(vector3d &vect, float const k);
            inline friend vector3d& operator*(vector3d &vect, float const k);
            inline friend vector3d& operator+(vector3d &vect, float const k);
            inline friend vector3d& operator-(vector3d &vect, float const k);

            inline friend vector3d& operator*(vector3d &v1, vector3d const &v2);
            inline friend vector3d& operator+(vector3d &v1, vector3d const &v2);
            inline friend vector3d& operator-(vector3d &v1, vector3d const &v2);

            inline friend vector3d& operator*(vector3d &vect, matrix3x3 &matr);

            // funkcje we/wy
            inline friend ostream& operator<<(ostream &s, vector3d const &vect);
            inline friend istream& operator>>(istream &s, vector3d &vect);

            // zapis i odczyt binarny
            inline ostream& save (ostream &s);
            inline istream& load (istream &s);

            // inne metody

            // dlugosc wektora
            inline float lenght(void);
            // kopiuje zapis binarny z pamieci do struktury
            inline void get(char const *buff);
};


/////////////////////////////////////////////
// dzialania na wektorach
//  rozwinalem petle, aby bylo szybciej
inline vector3d& vector3d::operator*=(matrix3x3 &matr)
{
  static float x,y,z;
  x = this->xyz.x;
  y = this->xyz.y;
  z = this->xyz.z;

  this->xyz.x = x*matr.get(0,0) + y*matr.get(1,0) + z*matr.get(2,0);
  this->xyz.y = x*matr.get(0,1) + y*matr.get(1,1) + z*matr.get(2,1);
  this->xyz.z = x*matr.get(0,2) + y*matr.get(1,2) + z*matr.get(2,2);

  return *this;
}

inline vector3d& vector3d::operator*=(float const k)
{
  this->xyz.x *= k;
  this->xyz.y *= k;
  this->xyz.z *= k;
  return *this;
}

inline vector3d& vector3d::operator*=(vector3d const &vect)
{
  static float x,y,z;
  x=this->xyz.x; y=this->xyz.y; z=this->xyz.z;
  this->xyz.x = y*vect.xyz.z - z*vect.xyz.y;
  this->xyz.y = z*vect.xyz.x - x*vect.xyz.z;
  this->xyz.z = x*vect.xyz.y - y*vect.xyz.x;
  return *this;
}

inline vector3d& vector3d::operator/=(float const k)
{
  this->xyz.x /= k;
  this->xyz.y /= k;
  this->xyz.z /= k;
  return *this;
}

inline vector3d& vector3d::operator+=(vector3d const &vect)
{
  this->xyz.x += vect.xyz.x;
  this->xyz.y += vect.xyz.y;
  this->xyz.z += vect.xyz.z;
  return *this;
}

inline vector3d& vector3d::operator-=(vector3d const &vect)
{
  this->xyz.x -= vect.xyz.x;
  this->xyz.y -= vect.xyz.y;
  this->xyz.z -= vect.xyz.z;
  return *this;
}

inline vector3d& vector3d::operator+=(float const k)
{
  this->xyz.x += k;
  this->xyz.y += k;
  this->xyz.z += k;
  return *this;
}

inline vector3d& vector3d::operator-=(float const k)
{
  this->xyz.x -= k;
  this->xyz.y -= k;
  this->xyz.z -= k;
  return *this;
}

inline vector3d& vector3d::operator=(vector3d const &vect)
{
  this->xyz.x = vect.xyz.x;
  this->xyz.y = vect.xyz.y;
  this->xyz.z = vect.xyz.z;
  return *this;
}

inline vector3d& operator/(vector3d &vect, float const k)
{
  static vector3d result;

  result.xyz.x = vect.xyz.x / k;
  result.xyz.y = vect.xyz.y / k;
  result.xyz.z = vect.xyz.z / k;
  return result;
}

inline vector3d& operator*(vector3d &vect, float const k)
{
  static vector3d result;

  result.xyz.x = vect.xyz.x * k;
  result.xyz.y = vect.xyz.y * k;
  result.xyz.z = vect.xyz.z * k;
  return result;
}

inline vector3d& operator+(vector3d &vect, float const k)
{
  static vector3d result;

  result.xyz.x = vect.xyz.x + k;
  result.xyz.y = vect.xyz.y + k;
  result.xyz.z = vect.xyz.z + k;
  return result;
}

inline vector3d& operator-(vector3d &vect, float const k)
{
  static vector3d result;

  result.xyz.x = vect.xyz.x - k;
  result.xyz.y = vect.xyz.y - k;
  result.xyz.z = vect.xyz.z - k;
  return result;
}

inline vector3d& operator*(vector3d &v1, vector3d const &v2)
{
  static vector3d result;

  result.xyz.x = v1.xyz.y*v2.xyz.z - v1.xyz.z*v2.xyz.y;
  result.xyz.y = v1.xyz.z*v2.xyz.x - v1.xyz.x*v2.xyz.z;
  result.xyz.z = v1.xyz.x*v2.xyz.y - v1.xyz.y*v2.xyz.x;
  return result;
}

inline vector3d& operator+(vector3d &v1, vector3d const &v2)
{
  static vector3d result;

  result.xyz.x = v1.xyz.x + v2.xyz.x;
  result.xyz.y = v1.xyz.y + v2.xyz.y;
  result.xyz.z = v1.xyz.z + v2.xyz.x;
  return result;
}

inline vector3d& operator-(vector3d &v1, vector3d const &v2)
{
  static vector3d result;

  result.xyz.x = v1.xyz.x - v2.xyz.x;
  result.xyz.y = v1.xyz.y - v2.xyz.y;
  result.xyz.z = v1.xyz.z - v2.xyz.x;
  return result;
}

inline vector3d& operator*(vector3d &vect, matrix3x3 &matr)
{
  static int x,y,z;
  static vector3d result;

  result.xyz.x = vect.xyz.x*matr.get(0,0)
                     + vect.xyz.y*matr.get(1,0) + vect.xyz.z*matr.get(2,0);
  result.xyz.y = vect.xyz.x*matr.get(0,1)
                     + vect.xyz.y*matr.get(1,1) + vect.xyz.z*matr.get(2,1);
  result.xyz.z = vect.xyz.x*matr.get(0,2)
                     + vect.xyz.y*matr.get(1,2) + vect.xyz.z*matr.get(2,2);
  return result;
}

/////////////////////////////////////////////
// Dostep do skladowych
inline float& vector3d::x(void)
{
 return this->coord[0];
}

inline float& vector3d::y(void)
{
 return this->coord[1];
}

inline float& vector3d::z(void)
{
 return this->coord[2];
}

inline float& vector3d::operator[](int const index)
{
  assert (index < 3);
  assert (index >= 0);
  return this->coord[index];
}

/////////////////////////////////////////////
// inne
inline float vector3d::lenght(void)
{
  double k = this->xyz.x * this->xyz.x + this->xyz.y * this->xyz.y
                + this->xyz.z * this->xyz.z;
  assert (k>=0);
  return sqrt (k);
}

// zapis i odczyt w postaci ASCII
inline ostream& operator<<(ostream &s, vector3d const &vect)
{
  s << " " << vect.xyz.x << " " << vect.xyz.y << " " << vect.xyz.z << " ";
  return s;
}

inline istream& operator>>(istream &s, vector3d &vect)
{
  static float x,y,z;

  s >> x; s >> y; s >> z;
  vect.xyz.x = x;
  vect.xyz.y = y;
  vect.xyz.z = z;
  return s;
}

// zapis binarny
inline ostream& vector3d::save (ostream &s)
{
  s.write( (char *)coord, sizeof (coord));
  return s;
}

// odczyt binarny
inline istream& vector3d::load (istream &s)
{
 char buff[sizeof (coord)];

  s.read((char *)buff, sizeof (coord));
  assert (!s.fail());
  this->get (buff);
  return s;
}

// kopiowanie z pamieci
inline void vector3d::get (char const *mem)
{
  memcpy (coord, mem, sizeof (coord));
}

#endif