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

extern vector3d sceneLight;

/* kopiuje wspolrzedne z coord do vertexes */
void main()
{
  vertex2d a,b,c;
  vector3d w_tyl(200,100,500);
  int i,j;
  transformation obrot;
  float t;
  clock_t start;
  float time;
  float scX, scY, scZ;
  frameBuffer16m fr;
  char *text;
  char key;
  object3d obj;
  int dummy;
  int sizeX, sizeY;
  fstream out;
  FILE *in;
  char *buff;
  fstream stream;
  char *object;
  long len;

  sceneLight.x()=sceneLight.y() = 0.0;
  sceneLight[2] = 1;

        init_eos(_psp);     // inicjalizacja eos'a

         BehindClip = 50*0x10000;
        AftClip = 1000;
        scX=scY=scZ=0.08;

        // ladowanie tekstury
        buff=load_internal_file("yellow.ont", &len);
        if (!len)
        {
            cout << "nie zaladowano tekstury\n";
            return;
        }

        text = convertTexture (buff);
        delete buff;

        // ladowanie objektu
        buff=load_internal_file("duck.bin", &len);
        obj.get(buff, len);
        obj.getTexture (text);
        obj.computeNormals();

        // muzyka + tryb graficzny
//        detect_sound_card(1, &dummy, &dummy, &dummy, &dummy);
//        load_module ("fireball.mod",1,44100,1);
//        play_module();
        vesaInit();
        if (fr.init(VMODE320x200x16m) != true)
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
//                if (j<1600)
//                {
//                  AftClip = 400+j/4;
//                  w_tyl[2] = 500;
//                }
//                else
                  AftClip = 5000;
                  w_tyl[2] = 500 + 300*sin(j*0.01);

                /* przeksztalcenia */
                obrot.clearMatrix();
                obrot.addRotation(0.013*j, 0.006*j, 0.02);
                obrot.addScale(scX,scY, scZ);
                obrot.vector = w_tyl;

                obj.transform(obrot);
                obj.rotateNormals(obrot);
                obj.perspective (100*2.5, sizeX, sizeY);
                obj.computeLight();
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

//        stop_module();
//        clear_module();

        cout << "FPS: " << (float)j/time << "\n";
        cout << "\nTo byl tylko program testowy mojego systemu ONYX3d\n";
        cout << "Kaczuszka miala ok. 600 trojkatow i byla wyswietona w true colorze.\n";
        cout << "Objekt z programu 3d studio, muzyka z gry Crusader: No regret.\n";
        cout << "UWAGA:    Program dziala na NVIDIA RIVA 128ZX, nie wiem jak na innych kartach\n";
        cout << "          (nie jestem pewny obslugi VESA 1.2)\n";
        cout << "\n\nmpomaran@lew.elka.pw.edu.pl\n";


        fr.deleteBuff(); fr.deleteZBuff();

        delete buff;
        delete text;
}
