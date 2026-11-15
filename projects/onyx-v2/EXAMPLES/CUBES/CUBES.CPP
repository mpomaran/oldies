//
//      W tym przykladzie wykorzysujemy do animacji i testow
//      dwa szesciany generowane automatycznie
//

#include <iostream.h>
#include <fstream.h>
#include <conio.h>
#include <time.h>

#include "..\..\h\onyx3d.h"             // ONYX 3D header file

/* kopiuje wspolrzedne z coord do vertexes */
void makeObject(object3d &obj, char *);
int  quality;

void main()
{
  vertex2d a,b,c;
  vector3d w_tyl1(160,100,699);
  vector3d w_tyl2(160,100,700);
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
  object3d szescian;
  fstream s;


        cout << "Choose mode:\n";
        cout << "[1] 320x200 true color\n";
        cout << "[2] 640x680 true color\n";
        key = 0;
        while (key != '1' && key != '2') key=getch();

        if (key == '1')
        {
           mode = VMODE320x200x16m;
           scX=scY=scZ=70;
        }
        else
        {
             mode = VMODE640x480x16m;
             scX = scZ = 70*2;
             scY = 70 * 2.5;
             w_tyl1 *= 2; w_tyl1[1] = 240;
             w_tyl2 *= 2; w_tyl2[1] = 240;
        }

        cout << "\nChoose mapper:\n";
        cout << "[1] texture + Gouraud mapper\n";
        cout << "[2] texture mapper \n";
        key = 0;
        while (key != '1' && key != '2') key=getch();

        if (key == '1')
           quality = gtz;
        else
           quality = tz;


        text = new char [256*256*3];

        /* tworzenie tekstury */
        for (i=0; i<256; i++)
            for (j=0; j<256; j++)
            {
                text[i*256 + j] = (i+j)>>1;
                text[i*256 + j + 0x10000] = i|j;
                text[i*256 + j + 0x20000] = 255-j;
            }

        makeObject(szescian, text);
        szescian.computeNormals();

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

        j=0;
        /* wlasciwy test */

        if (kbhit())
           getch();
        start=clock();
        while (!kbhit())
        {
                /* przeksztalcenia */
                obrot.clearMatrix();
                obrot.addRotation(0.03*j, 0.02*j, 0.01*j);
                obrot.addScale(scX, scY, scZ);
                obrot.vector = w_tyl1;

                szescian.transform(obrot);
                szescian.rotateNormals(obrot);
                szescian.computeLight();
                szescian.show(fr);

                /* przeksztalcenia */
                obrot.clearMatrix();
                obrot.addRotation(-0.051*j, 0.063*j, -0.073*j);
                obrot.addScale(scX, scY, scZ);
                obrot.vector = w_tyl2;

                szescian.transform(obrot);
                szescian.rotateNormals(obrot);
                szescian.computeLight();
                szescian.show(fr);
                fr.show();

                /* kasujemy buforki */
                fr.fill(0x3d1a00); fr.fillZBuff(5000);
                j++;
        }
        /* koniec testu */
        time = (float)(clock()-start)/CLOCKS_PER_SEC;

        getch();
        setTextMode();

        cout << "Time: " << time << "s.\n";
        cout << "Framerate: " << (float)j/time << "\n";

        fr.deleteBuff(); fr.deleteZBuff();
        delete text;
}

/* wspolrzedne x, y, z, u, v */
int coord[8][5] =  { {-1, -1, -1, 0, 255}, {1, -1, -1, 255, 255},
                     {1, 1, -1, 255, 0}, {-1, 1, -1, 0, 0},
                     {-1, -1, 1, 0, 0}, {1, -1, 1, 255, 0},
                     {1, 1, 1, 0, 255}, {-1, 1, 1, 255, 255} };

/* definiuje krawedzie */
unsigned triangles[12][3] = {
                   {1, 3, 0}, {1, 3, 2}, {1, 6, 5}, {1, 6, 2},
                   {4, 6, 5}, {4, 6, 7}, {7, 0, 3}, {7, 0, 4},
                   {1, 4, 0}, {1, 4, 5}, {2, 7, 3}, {2, 7, 6}};

void makeObject(object3d &obj, char *text)
{
  vertex3d *vert;
  triangle *tr;

  vert = new vertex3d [8];
  obj.getVertexes() = vert;
  obj.getVertexesNo() = 8;


  // tworzenie wierzcholkow
  for (int i=0; i<8; i++)
  {
    for (int j=0; j<3; j++)
        vert[i][j] = coord[i][j];
    vert[i].u = coord[i][3];
    vert[i].v = coord[i][4];
    vert[i].color = i*30;
  }

  // tworzenie trojkatow
  for (i=0; i<12; i++)
  {
    tr = new triangle;

        tr->v1 = triangles[i][0];
        tr->v2 = triangles[i][1];
        tr->v3 = triangles[i][2];
        tr->type = quality;               // rodzaj trojkata - gouraud + tekstura
        tr->texture = text;
        tr->textureNo = 0;
        (obj.getTriangleList()).addElemFirst ((void *)tr);
  }
  obj.position[0] = obj.position[1] = obj.position[2] = 0;
  obj.scaleX = obj.scaleY = obj.scaleZ = 1;
}
