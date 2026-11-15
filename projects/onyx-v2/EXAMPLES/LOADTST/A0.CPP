//
//      W tym przykladzie wykorzysujemy do animacji i testow
//      dwa szesciany generowane automatycznie
//

#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <stdio.h>


#include "..\..\h\onyx3d.h"             // ONYX 3D header file

/* kopiuje wspolrzedne z coord do vertexes */
void main()
{
  object3d obj, obj2;
  fstream out;

        if (!obj.loadA0("duck.a0", (char *)0,1))
        {
          cout << "Can't load .a0 file\n";
          return;
        }

        out.open("duck.bin", ios::out + ios::binary);
        obj.save(out);
        out.close();

//        out.open ("out1.onx", ios::out);
//        out << obj;
//        out.close();

        out.open("duck.bin", ios::in + ios::binary);
        obj2.load(out);
        out.close();

        obj2.computeNormals();
        obj2.computeLight();

        out.open ("out2.onx", ios::out);
        out << obj2;
        out.close();
}
