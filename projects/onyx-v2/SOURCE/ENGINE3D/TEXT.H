//
//      text.h  -       teksty uzywane podczas zapisu/odczytu pliku
//
//      ONYX 3D (c) 2000 by Michal Pomaranski
//

#ifndef __TEXT_H

#define __TEXT_H

#define ONYX3D_SYSTEM_VERSION 200
extern char *O3DString[];

#define BANNER_FILE_STR (O3DString[0])
#define SYS_VER_STR (O3DString[1])
#define VERTEXES_NO_STR (O3DString[2])
#define OBJECTS_NO_STR (O3DString[3])
#define FACES_NO_STR (O3DString[4])
#define VERTEXES_LIST_STR (O3DString[5])
#define FACES_LIST_STR (O3DString[6])
#define OBJECTS_LIST_STR (O3DString[7])

#endif