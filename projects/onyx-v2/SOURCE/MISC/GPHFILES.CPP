#include <stdio.h>

#include <malloc.h>
#include <eos.h>
#include "gphfiles.h"

#ifndef NULL
#define NULL 0
#endif

gphHandle* loadGphFile(char *name,int mode) /* mode - 0 - internal, 1 - external */
{
  gphHandle *handle;
  datFile *dat;
  long    size;

  handle = (gphHandle *)malloc(sizeof(gphHandle));    /* alokacja pamieci */
  if (handle == NULL) return NULL;      /* brak pamieci?    */

//  handle->memHandle = load_external_file_handle(name,&size,handle->handleFile);
  handle->memHandle = load_internal_file(name,&size);
  if (handle->memHandle == NULL) return NULL;

  dat =(datFile*)handle->memHandle;    // wypelnienie struktury gphHandle
  handle->x = dat->x;
  handle->y = dat->y;
  handle->colors = dat->colors;
  handle->no = (size-sizeof(datFile))/(handle->x*handle->y);
  handle->image = handle->memHandle + sizeof(datFile);

  return handle;
}

// zwalnianie zajetej pamieci
void    gphFree(gphHandle *handle)
{
  free(handle->handleFile);
  free(handle);
}

/* Pobierz strukture opisujaca obrazek o numerze no */
void       getDatImageInfo(gphHandle const  *packHandle, datImage *dat, int no)
{
  int offset;

  offset = packHandle->x * packHandle->y * no;
  dat->image = packHandle->image + offset;

  dat->x = packHandle->x;
  dat->y = packHandle->y;
  dat->colors = packHandle->colors;
}
