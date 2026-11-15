//
//      W tym przykladzie wykorzysujemy do animacji i testow
//      dwa szesciany generowane automatycznie
//

#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>


#include "..\..\h\onyx3d.h"             // ONYX 3D header file

/* kopiuje wspolrzedne z coord do vertexes */
void main(int argc, char* argv[])
{
  object3d obj;
  fstream stream;

        cout << "A0 to BIN converter\n\n";

        if (argc!=3)
        {
          cout << "usage: a0bin [in] [out]" << endl;
          return;
        }

        if (!obj.loadA0(argv[1], (char *)0,0))
        {
          cout << "Can't load .a0 file\n";
          return;
        }

        stream.open(argv[2], ios::out + ios::binary);
        if (!stream)
        {
          cout << "Can't open '"<< argv[2] << "' file.\n";
          return;
        }
        obj.save(stream);
        stream.close();
}
