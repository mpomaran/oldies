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

#include "eos.h"
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
  char *text, *text2;
  char key;
  int mode;
  object3d obj, obj2,c1;
  int dummy;
  int sizeX, sizeY;
  fstream out;
  FILE *in;
  char *buff;

        init_eos(_psp);     // inicjalizacja eos'a

        cout << "    þ Choose mode:\n";
        cout << "    þ  [1] 320x200 true color\n";
        cout << "    þ  [2] 640x680 true color\n";
        key = '3';
        while (key != '1' && key != '2') key=getch();

        BehindClip = 50*0x10000;
        AftClip = 3000;
        if (key == '1')
        {
           mode = VMODE320x200x16m;
           scX=scY=scZ=0.08;
        }
        else
        {
             mode = VMODE640x480x16m;
             scX = scZ = 0.08*2;
             scY = 0.08 * 2.5;
        }

        text = new char [256*256*3];

        /* tworzenie tekstury */
        for (i=0; i<256; i++)
            for (j=0; j<256; j++)
            {
                text[i*256 + j] = i|j;
                text[i*256 + j + 0x10000] = i|j;
                text[i*256 + j + 0x20000] = i;
            }

        in = fopen ("bog18.ont", "rb");
        if (!in)
        {
          cout << "I/O !!!\n";
          return;
        }

        buff = new char [68000];
        fread(buff, 66304, 1, in);
        fclose(in);
        text2 = convertTexture (buff);
        if (!text2)
        {
            cout << "nie zaladowano tekst\n";
            return;
        }

        if (!obj.loadA0("duck.a0", text2,1) ||
            !obj2.loadA0("d1.a0", text,0) ||
            !c1.loadA0("c1.a0", text,0))
        {
          cout << "Can't load .a0 file\n";
          return;
        }

        obj.computeNormals();
        c1.computeNormals();
        obj2.computeNormals();
        detect_sound_card(1, &dummy, &dummy, &dummy, &dummy);
        load_module ("voodka.mod",1,44100,1);
        play_module();
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

        /* wlasciwy test */
        start=clock();
        while (!kbhit())
        {
                /* przeksztalcenia */
                obrot.clearMatrix();
                obrot.addRotation(0.02*j, 0.03*j, 0.02*j);
                obrot.addScale(scX,scY, scZ);
                w_tyl[2] = 1500 + 1500 * sin (0.02*j);
                obrot.vector = w_tyl;

                obj.transform(obrot);
                obj.rotateNormals(obrot);
                obj.perspective (100*2.5, sizeX, sizeY);
                obj.computeLight();
                obj.show(fr);

                for (int k=0; k<25; k++)
                {
                   obrot.clearMatrix();
                   obrot.addRotation(1.57, 0.06*j, 0);
                   obrot.addScale(10*scX,10*scY,10*scZ);
                   w_tyl2[0] = -2500 + k*300;
                   w_tyl2[1] = 250;
                   w_tyl2[2] = 1700 + 1200*sin (0.01*j);
                   obrot.vector = w_tyl2;

                   obj2.transform(obrot);
                   obj2.perspective (100*2.5, sizeX, sizeY);
                   obj2.rotateNormals(obrot);
                   obj2.computeLight();
                   obj2.show(fr);

                   w_tyl2[1] = 250;
                   w_tyl2[2] = 1700 + 1200*cos (0.01*j);
                   obrot.vector = w_tyl2;
                   c1.transform(obrot);
                   c1.perspective (100*2.5, sizeX, sizeY);
                   c1.rotateNormals(obrot);
                   c1.computeLight();
                   c1.show(fr);
                }
                fr.show();

                /* kasujemy buforki */
                fr.fill(0x0); fr.fillZBuff((int)AftClip);
                j++;
        }
        /* koniec testu */
        time = (float)(clock()-start)/CLOCKS_PER_SEC;

        getch();
        setTextMode();

        stop_module();
        clear_module();

        // test i/o
        out.open("out2.onx", ios::out);
        out << obj;
        out.close();
        out.open("duck.bin", ios::out+ios::binary);
        obj.save(out);
        out.close();

        cout << "Time: " << time << "s.\n";
        cout << "Framerate: " << (float)j/time << "\n";

        fr.deleteBuff(); fr.deleteZBuff();

        delete buff;
        delete text;
        delete text2;
}
