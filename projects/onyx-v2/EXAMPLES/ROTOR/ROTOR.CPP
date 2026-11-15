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

#include <eos.h>

#include "..\..\h\onyx3d.h"             // ONYX 3D header file


/* kopiuje wspolrzedne z coord do vertexes */
void main()
{
  vertex2d a,b,c;
  vector3d w_tyl(160,100,500);
  int i,j;
  transformation obrot;
  frameBuffer16m fr;
  char *text;
  char key;
  int mode;
  object3d obj;
  int dummy;
  int sizeX, sizeY;
  fstream ins;
  FILE *in;
  char *buff;
  long len;

        init_eos (_psp);

        BehindClip = 1;
        AftClip = 3000;
        mode = VMODE320x200x16m;

        buff=load_internal_file("face.ont", &len);
        text = convertTexture (buff);
        if (!text)
        {
            cout << "Nie zaladowano tekstury\n";
            return;
        }

        cout << "obj. loading...\n";

        ins.open("kwadrat.onx", ios::in);
        ins >> obj;
        obj.getTexture(text);
        ins.close();

        ins.open("kwadrat.bin", ios::out);
        obj.save(ins);
        ins.close();

        cout << "music loading...\n";

        detect_sound_card(1, &dummy, &dummy, &dummy, &dummy);
        load_module ("beingthe.mod",0,44100,1);
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
        if (kbhit()) getch();
        while (!kbhit())
        {
                /* przeksztalcenia */
                obrot.clearMatrix();
                obrot.addRotation(0.0, 0, 0.05*j);
                obrot.addScale(1, 1, 1);
                w_tyl[0] = 160+20*cos(j*0.025);
                w_tyl[1] = 100+20*sin(j*0.025);
                w_tyl[2] = 100 + 99.9*sin(j*0.025);
                obrot.vector = w_tyl;

                obj.transform(obrot);
                obj.perspective (100*2.5, 320, 200);
                obj.show(fr);
                fr.show();

                /* kasujemy buforki */
                fr.fill(0x0); fr.fillZBuff((int)AftClip);
                j++;
        }
        /* koniec testu */
        getch();
        setTextMode();

        stop_module();
        clear_module();

        fr.deleteBuff(); fr.deleteZBuff();

        delete buff;
        delete text;
}
