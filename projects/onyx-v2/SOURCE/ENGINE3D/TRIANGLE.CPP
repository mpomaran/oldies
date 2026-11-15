//
//      TRIANGLE.CPP    -       opis trojkata
//

#include "object.h"
#include <string.h>
#include <iomanip.h>
#include <assert.h>

char tex[256][256][3];

ostream& operator << (ostream &s, triangle &tr)
{
  s << tr.v1 << " " << tr.v2 << " " << tr.v3 << " ";
  s << tr.type << " " << (unsigned)tr.textureNo << "\n";

  return s;
}

istream& operator >> (istream &s, triangle &tr)
{
  static unsigned v, numb;

  s >> v; tr.v1=v; s >> v; tr.v2=v; s >> v; tr.v3=v;
  s >> numb; tr.type=numb;
  s >> numb; tr.textureNo=numb;

  return s;
}

ostream& triangle::save (ostream &s)
{
  s.write ( (char *)(&v1), sizeof (v1));
  s.write ( (char *)(&v2), sizeof (v2));
  s.write ( (char *)(&v3), sizeof (v3));

  s.write ( (char *)(&type), sizeof (type));
  s.write ( (char *)(&textureNo), sizeof (textureNo));
  return s;
}

istream& triangle::load (istream &s)
{
  s.read ( (char *)(&v1), sizeof (v1));
  assert (!s.fail());
  s.read ( (char *)(&v2), sizeof (v2));
  assert (!s.fail());
  s.read ( (char *)(&v3), sizeof (v3));
  assert (!s.fail());

  s.read ( (char *)(&type), sizeof (type));
  assert (!s.fail());
  s.read ( (char *)(&textureNo), sizeof (textureNo));
  assert (!s.fail());

  texture = (char *)tex;
  
  return s;
}
