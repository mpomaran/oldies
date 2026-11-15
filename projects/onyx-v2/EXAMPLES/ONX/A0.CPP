//
//      W tym przykladzie wykorzysujemy do animacji i testow
//      dwa szesciany generowane automatycznie
//

#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>

#include "..\..\h\onyx3d.h"             // ONYX 3D header file

/* kopiuje wspolrzedne z coord do vertexes */
void main()
{
  vertex2d a,b,c;
  vector3d w_tyl(320,100,500);
  vector3d w_tyl2(360,100,500);
  int i,j;
  transformation obrot;
  float t;
  clock_t start;
  float time;
  float scX, scY, scZ;
  frameBuffer16m fr;
  char *text;
  char key;
  int mode;
  object3d obj, obj2,c1;
  int dummy;
  int sizeX, sizeY;
  fstream ins;
  FILE *in;
  char *buff;

        BehindClip = 50*0x10000;
        AftClip = 3000;
        mode = VMODE320x200x16m;
        scX=scY=scZ=0.100;

        in = fopen ("bog18.ont", "rb");
        if (!in)
        {
          cout << "I/O !!!\n";
          return;
        }

        buff = new char [68000];
        fread(buff, 66304, 1, in);
        fclose(in);
        text = convertTexture (buff);
        if (!text)
        {
            cout << "nie zaladowano tekst\n";
            return;
        }

        cout << "obj. loading...\n";

        ins.open("out.onx", ios::in);
        ins >> obj;
        obj.getTriangleList().init();
        while (!obj.getTriangleList().viewed())
          ((triangle *)obj.getTriangleList().getNext())->texture = text;
        ins.close();

        vesaInit();
        if (fr.init(mode) != true)
        {
          cout << "No mode present\n";
          return;
        }
        if (fr.initZBuff() != true)
        {
          cout << "No memory\n";
          return;
        }
        fr.initVideoMode();
        fr.getSize(sizeX, sizeY);
        j=0;

        obj.computeNormals();

        /* wlasciwy test */
        start=clock();
        if (kbhit()) getch();
        while (!kbhit())
        {
                /* przeksztalcenia */
                obrot.clearMatrix();
                obrot.addRotation(0.02*j, 0.03*j, 0.02*j);
                obrot.addScale(scX,scY, scZ);
                w_tyl[2] = 400 + 150 * sin (0.02*j);
                obrot.vector = w_tyl;

                obj.transform(obrot);
                obj.rotateNormals(obrot);
                obj.computeLight();
                obj.perspective (50*2.5, sizeX, sizeY);
                obj.show(fr);
                fr.show();

                /* kasujemy buforki */
                fr.fill(0x0); fr.fillZBuff((int)AftClip);
                j++;
        }
        /* koniec testu */
        time = (float)(clock()-start)/CLOCKS_PER_SEC;

        getch();
        setTextMode();

        cout << "Time: " << time << "s.\n";
        cout << "Framerate: " << (float)j/time << "\n";

        fr.deleteBuff(); fr.deleteZBuff();

        delete buff;
        delete text;
}
