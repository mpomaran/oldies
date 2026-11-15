/*
**      VERTEX3D.CPP            Definicja punktu w przestrzeni 3d
**
**      Sarin/!ArisE!
*/

#include "vector3d.h"
#include "vertex3d.h"
#include <string.h>
#include <iomanip.h>

vertex3d::vertex3d(float const coordinates[3])
{
  this->coord[0] = coordinates[0];
  this->coord[1] = coordinates[1];
  this->coord[2] = coordinates[2];
}

vertex3d::vertex3d(float const &x, float const &y, float const &z)
{
 this->coord[0] = x;
 this->coord[1] = y;
 this->coord[2] = z;
}

vertex3d::vertex3d(float const k)
{
  this->coord[0] = this->coord[1] = this->coord[2] = k;
}

vertex3d::vertex3d(void) {}

vertex3d::vertex3d(vector3d &vect)
{
 this->coord[0] = vect[0];
 this->coord[1] = vect[2];
 this->coord[2] = vect[3];
}

vertex3d& vertex3d::transform(transformation &t)
{
 *this *= t.matrix;
 *this += t.vector;

 return *this;
}

vector3d& vertex3d::transformNorm(transformation &t)
{
 norm *= t.matrix;

 return norm;
}

ostream& operator << (ostream &s, vertex3d &vert)
{
  s << (vector3d &)vert << " " << (int)vert.u;
  s << " " << (int)vert.v << " " << (int)vert.color << " " << vert.norm << "\n";
  return s;
}

istream& operator >> (istream &s, vertex3d &vert)
{
  int i;
  static vector3d vect;
  int u, v, color;

  s >> vect; vert=vect;
  s >> u; s >> v; s >> color;
  s >> vect;
  vert.u = u; vert.v = v; vert.color = color; vert.norm = vect;

  return s;
}

// zapis binarny
ostream& vertex3d::save (ostream &s)
{
  vector3d::save(s);
  s.write( (char *)&this->u, sizeof (this->u));
  s.write( (char *)&this->v, sizeof (this->v));
  s.write( (char *)&this->color, sizeof (this->color));
  norm.save (s);
  assert(!s.fail());
  return s;
}

istream& vertex3d::load (istream &s)
{
  vector3d::load(s);
  s.read( (char *)&this->u, sizeof (this->u));
  s.read( (char *)&this->v, sizeof (this->v));
  s.read( (char *)&this->color, sizeof (this->color));
  norm.load (s);
  assert(!s.fail());
  return s;
}

void vertex3d::get (char const *buff)
{
  const char *mem=buff;

  vector3d::get(mem);
  mem += sizeof(coord);

  memcpy ( (void *)u, mem, sizeof(u));
  mem += sizeof(u);
  memcpy ( (void *)v, mem, sizeof(v));
  mem += sizeof(v);
  memcpy ( (void *)color, mem, sizeof(color));
  mem += sizeof(color);

  norm.get (buff);
}
