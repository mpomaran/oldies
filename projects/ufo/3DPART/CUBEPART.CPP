/*
 *      CUBEPART.H              funkcja cubepart
 * Sarin/!ArisE!
 */

#include <eos.h>
#include <sar3d.h>

#include "cubepart.h"
#include "cube.h"

void    initCubes()
{
   char *raw,*bitmap;
   vertex3d sr;
   int i=0,j;
   long handle;
   long size = 256*256;

   // 1. Inicjacja pamieci
   memInit(512*300 + 300000 + 256*256*2);
   initVirtualScreen(512,300);

   // Ladowanie bitmapy

   raw = load_internal_file_handle("bmp.raw",&size,&handle);
   bitmap = (char *)memAlloc(256*256*2);
   bitmap = (char *)( ((int)bitmap+0xffff) & 0xffff0000);
   for (i=0; i<64000/4; i++)
      *((int *)bitmap+i) = *((int *)raw+i);

   deallocate_memory_handle(handle);

   // 2. stworzenie sceny
   scene3d.objectsTab = (object3d *)memAlloc(sizeof(object3d) * 1 * 25*1);
   scene3d.vertexesTab = (vertex3d *)memAlloc(sizeof(vertex3d) * 8 * 25*1);

   scene3d.vertexCounter = 8*25*1;
   scene3d.allBitmaps = bitmap;
   scene3d.objectCounter = 1*25;
   scene3d.bitmapCounter = 1;
   scene3d.faceCounter = 12 * 25*1;

   // 3. stworzenie objektow
   sr.x = -500; sr.y = 300; sr.z = 800;
   for (i=0; i<5; i++){
       sr.x = 400*i - 800;
       sr.z = 00;
       for (j=0; j<5; j++){
           sr.z+=400;
           makeCube(scene3d.vertexesTab + 8*(i*5+j), scene3d.objectsTab+i*5+j, bitmap, &sr,200,1);
       }
   }
   perK = 100;
}


void    showCubesFrame(char *screen)
{
  vertex3d sr;
  int i,j;

     sr.x = -500; sr.y = 300; sr.z = 800;
     for (i=0; i<5; i++){
       sr.x = 400*i - 800;
       sr.z = -0;
       for (j=0; j<5; j++){
           sr.z+=400;
           rotateObject(scene3d.objectsTab + i*5 + j,0.1,0.1-0.2*(j&1),0.1-0.2*(j&1),&sr);
         }
      }
      drawScene();
      showVirtualScreen((char *)screen);
}

void    uninitCubes()
{
  memCleanUp();
}
