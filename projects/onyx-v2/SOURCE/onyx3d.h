//
//      ONYX 3D ver. 2 BETA, a nawet ALFA
//      (c) 2000 by Michal Pomaranski
//
//              Nie masz prawa miec tego pliku, ale jesli juz go masz,
//              i podoba Ci sie to, co mozesz osiagnac za pomoca tego
//              pakietu, to sproboj sciagnac z sieci wersje finalna
//              (gwarantuje, ze bedzie o wiele szybsza)
//
//      YOU ARE NOT ALLOWED TO HAVE THIS FILE. DELETE IT NOW!!!
//      YOU ARE NOT ALLOWED TO USE ANY OF THIS CODE IN YOUR PRODUCT
//

#ifndef __ONYX3D_H
#define __ONYX3D_H
/*
**      MATRIX.H                Definicja macierzy
**      Sarin/!ArisE
*/

#ifndef __MATRIX_H
#define __MATRIX_H

#include <assert.h>
#include <iostream.h>
#include <math.h>

class matrix3x3 {
      private:
               float matrix[3][3];
      public:

               matrix3x3();
               matrix3x3(float matr[3][3]);
               matrix3x3(float k);
               matrix3x3(matrix3x3 const &matr);

               // czyszczenie
               clear();

               // dostep do macierzy
               inline float& get(int const i, int const j);

               // operator przypisania
               matrix3x3& operator=(matrix3x3 const &matr);

               // operacje na macierzach
               matrix3x3& operator+=(matrix3x3 const &matr);
               matrix3x3& operator-=(matrix3x3 const &matr);
               matrix3x3& operator*=(matrix3x3 const &matr);
               matrix3x3& operator+=(float &k);
               matrix3x3& operator-=(float &k);
               matrix3x3& operator*=(float &k);
               matrix3x3& operator/=(float &k);

               friend matrix3x3 operator+(matrix3x3 const &m1, matrix3x3 const &m2);
               friend matrix3x3 operator-(matrix3x3 const &m1, matrix3x3 const &m2);
               friend matrix3x3 operator*(matrix3x3 const &m1, matrix3x3 const &m2);

               // we/wy
               friend ostream& operator<<(ostream &s, matrix3x3 &matr);
};

// dostep do macierzy
inline float& matrix3x3::get(int const i, int const j)
{
 assert(i<3);
 assert(j<3);
 return this->matrix[i][j];
}

#endif
/*
**      VECTOR3D.H                Definicja wektora
**
**      Sarin/!ArisE!
*/

#ifndef __VECTOR_H
#define __VECTOR_H

#include <assert.h>
#include <iostream.h>

#include "matrix.h"

class vector3d {
    protected:
      union {                            // do wspolrzednych mozna sie odwo-
            float coord[3];              // lywac jako do tablicy
            struct {                     // lub wspolrzednych x, y, z
                  float x,y,z;
            }xyz;
      };

    public:
            // konstruktory
            inline vector3d(float const *coordinates)
              {xyz.x = coordinates[0]; xyz.y = coordinates[1]; xyz.z = coordinates[2];};
            inline vector3d(float const &x, float const &y, float const &z)
              {xyz.x = x; xyz.y = y; xyz.z = z;};
            inline vector3d(float const k)
              {xyz.x = k; xyz.y = k; xyz.z = k;};
            inline vector3d()
              {xyz.x = 0; xyz.y = 0; xyz.z = 0;};

            inline float& x(void);
            inline float& y(void);
            inline float& z(void);
            inline float& operator[](int const index);

            // dzialania na wektorach
            inline vector3d& operator*=(matrix3x3 &matr);
            inline vector3d& operator*=(float const k);
            inline vector3d& operator*=(vector3d const &vect);  // ilcozyn wektorowy
            inline vector3d& operator/=(float const k);
            inline vector3d& operator+=(vector3d const &vect);
            inline vector3d& operator-=(vector3d const &vect);
            inline vector3d& operator+=(float const k);
            inline vector3d& operator-=(float const k);
            inline vector3d& operator=(vector3d const &vect);

            inline friend vector3d& operator/(vector3d &vect, float const k);
            inline friend vector3d& operator*(vector3d &vect, float const k);
            inline friend vector3d& operator+(vector3d &vect, float const k);
            inline friend vector3d& operator-(vector3d &vect, float const k);

            inline friend vector3d& operator*(vector3d &v1, vector3d const &v2);
            inline friend vector3d& operator+(vector3d &v1, vector3d const &v2);
            inline friend vector3d& operator-(vector3d &v1, vector3d const &v2);

            inline friend vector3d& operator*(vector3d &vect, matrix3x3 &matr);

            // funkcje we/wy
            inline friend ostream& operator<<(ostream &s, vector3d const &vect);
            inline friend istream& operator>>(istream &s, vector3d &vect);

            // zapis i odczyt binarny
            inline ostream& save (ostream &s);
            inline istream& load (istream &s);

            // inne metody

            // dlugosc wektora
            inline float lenght(void);
            // kopiuje zapis binarny z pamieci do struktury
            inline void get(char const *buff);
};


/////////////////////////////////////////////
// dzialania na wektorach
//  rozwinalem petle, aby bylo szybciej
inline vector3d& vector3d::operator*=(matrix3x3 &matr)
{
  static float x,y,z;
  x = this->xyz.x;
  y = this->xyz.y;
  z = this->xyz.z;

  this->xyz.x = x*matr.get(0,0) + y*matr.get(1,0) + z*matr.get(2,0);
  this->xyz.y = x*matr.get(0,1) + y*matr.get(1,1) + z*matr.get(2,1);
  this->xyz.z = x*matr.get(0,2) + y*matr.get(1,2) + z*matr.get(2,2);

  return *this;
}

inline vector3d& vector3d::operator*=(float const k)
{
  this->xyz.x *= k;
  this->xyz.y *= k;
  this->xyz.z *= k;
  return *this;
}

inline vector3d& vector3d::operator*=(vector3d const &vect)
{
  static float x,y,z;
  x=this->xyz.x; y=this->xyz.y; z=this->xyz.z;
  this->xyz.x = y*vect.xyz.z - z*vect.xyz.y;
  this->xyz.y = z*vect.xyz.x - x*vect.xyz.z;
  this->xyz.z = x*vect.xyz.y - y*vect.xyz.x;
  return *this;
}

inline vector3d& vector3d::operator/=(float const k)
{
  this->xyz.x /= k;
  this->xyz.y /= k;
  this->xyz.z /= k;
  return *this;
}

inline vector3d& vector3d::operator+=(vector3d const &vect)
{
  this->xyz.x += vect.xyz.x;
  this->xyz.y += vect.xyz.y;
  this->xyz.z += vect.xyz.z;
  return *this;
}

inline vector3d& vector3d::operator-=(vector3d const &vect)
{
  this->xyz.x -= vect.xyz.x;
  this->xyz.y -= vect.xyz.y;
  this->xyz.z -= vect.xyz.z;
  return *this;
}

inline vector3d& vector3d::operator+=(float const k)
{
  this->xyz.x += k;
  this->xyz.y += k;
  this->xyz.z += k;
  return *this;
}

inline vector3d& vector3d::operator-=(float const k)
{
  this->xyz.x -= k;
  this->xyz.y -= k;
  this->xyz.z -= k;
  return *this;
}

inline vector3d& vector3d::operator=(vector3d const &vect)
{
  this->xyz.x = vect.xyz.x;
  this->xyz.y = vect.xyz.y;
  this->xyz.z = vect.xyz.z;
  return *this;
}

inline vector3d& operator/(vector3d &vect, float const k)
{
  static vector3d result;

  result.xyz.x = vect.xyz.x / k;
  result.xyz.y = vect.xyz.y / k;
  result.xyz.z = vect.xyz.z / k;
  return result;
}

inline vector3d& operator*(vector3d &vect, float const k)
{
  static vector3d result;

  result.xyz.x = vect.xyz.x * k;
  result.xyz.y = vect.xyz.y * k;
  result.xyz.z = vect.xyz.z * k;
  return result;
}

inline vector3d& operator+(vector3d &vect, float const k)
{
  static vector3d result;

  result.xyz.x = vect.xyz.x + k;
  result.xyz.y = vect.xyz.y + k;
  result.xyz.z = vect.xyz.z + k;
  return result;
}

inline vector3d& operator-(vector3d &vect, float const k)
{
  static vector3d result;

  result.xyz.x = vect.xyz.x - k;
  result.xyz.y = vect.xyz.y - k;
  result.xyz.z = vect.xyz.z - k;
  return result;
}

inline vector3d& operator*(vector3d &v1, vector3d const &v2)
{
  static vector3d result;

  result.xyz.x = v1.xyz.y*v2.xyz.z - v1.xyz.z*v2.xyz.y;
  result.xyz.y = v1.xyz.z*v2.xyz.x - v1.xyz.x*v2.xyz.z;
  result.xyz.z = v1.xyz.x*v2.xyz.y - v1.xyz.y*v2.xyz.x;
  return result;
}

inline vector3d& operator+(vector3d &v1, vector3d const &v2)
{
  static vector3d result;

  result.xyz.x = v1.xyz.x + v2.xyz.x;
  result.xyz.y = v1.xyz.y + v2.xyz.y;
  result.xyz.z = v1.xyz.z + v2.xyz.x;
  return result;
}

inline vector3d& operator-(vector3d &v1, vector3d const &v2)
{
  static vector3d result;

  result.xyz.x = v1.xyz.x - v2.xyz.x;
  result.xyz.y = v1.xyz.y - v2.xyz.y;
  result.xyz.z = v1.xyz.z - v2.xyz.x;
  return result;
}

inline vector3d& operator*(vector3d &vect, matrix3x3 &matr)
{
  static int x,y,z;
  static vector3d result;

  result.xyz.x = vect.xyz.x*matr.get(0,0)
                     + vect.xyz.y*matr.get(1,0) + vect.xyz.z*matr.get(2,0);
  result.xyz.y = vect.xyz.x*matr.get(0,1)
                     + vect.xyz.y*matr.get(1,1) + vect.xyz.z*matr.get(2,1);
  result.xyz.z = vect.xyz.x*matr.get(0,2)
                     + vect.xyz.y*matr.get(1,2) + vect.xyz.z*matr.get(2,2);
  return result;
}

/////////////////////////////////////////////
// Dostep do skladowych
inline float& vector3d::x(void)
{
 return this->coord[0];
}

inline float& vector3d::y(void)
{
 return this->coord[1];
}

inline float& vector3d::z(void)
{
 return this->coord[2];
}

inline float& vector3d::operator[](int const index)
{
  assert (index < 3);
  assert (index >= 0);
  return this->coord[index];
}

/////////////////////////////////////////////
// inne
inline float vector3d::lenght(void)
{
  double k = this->xyz.x * this->xyz.x + this->xyz.y * this->xyz.y
                + this->xyz.z * this->xyz.z;
  assert (k>=0);
  return sqrt (k);
}

// zapis i odczyt w postaci ASCII
inline ostream& operator<<(ostream &s, vector3d const &vect)
{
  s << " " << vect.xyz.x << " " << vect.xyz.y << " " << vect.xyz.z << " ";
  return s;
}

inline istream& operator>>(istream &s, vector3d &vect)
{
  static float x,y,z;

  s >> x; s >> y; s >> z;
  vect.xyz.x = x;
  vect.xyz.y = y;
  vect.xyz.z = z;
  return s;
}

// zapis binarny
inline ostream& vector3d::save (ostream &s)
{
  s.write( (char *)coord, sizeof (coord));
  return s;
}

// odczyt binarny
inline istream& vector3d::load (istream &s)
{
 char buff[sizeof (coord)];

  s.read((char *)buff, sizeof (coord));
  assert (!s.fail());
  this->get (buff);
  return s;
}

// kopiowanie z pamieci
inline void vector3d::get (char const *mem)
{
  memcpy (coord, mem, sizeof (coord));
}

#endif/*
**      TRANSFORM.H             Przeksztalcenie w 3d ukladze wspolrzednych
**      Sarin/!ArisE!
*/

#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include "matrix.h"
#include "vector3d.h"

class transformation {
      public:
              matrix3x3 matrix;
              vector3d vector;

              void addRotation(float angleX, float angleY, float angleZ);
              void addRotation(vector3d &x, vector3d &y, vector3d &z);
              void addScale(float const scaleX, float const scaleY,
                                  float const scaleZ);
              void clearMatrix(void);
};

#endif
/*
**      VERTEX3D.H              Definicja punktu w przestrzeni 3d
**
**      Sarin/!ArisE!
*/

#ifndef __VERTEX3D_H
#define __VERTEX3D_H

#include <iostream.h>

#include "vector3d.h"
#include "transform.h"

class vertex3d : public vector3d {
      public:
              unsigned char u,v;        // wspolrzedne bitmapy
              unsigned char color;      // intensywnosc koloru

              vector3d norm;            // wektor normalny do wierzcholka

              vertex3d(float const coordinates[3]);
              vertex3d(float const &x, float const &y, float const &z);
              vertex3d(float const k);
              vertex3d(void);
              vertex3d(vector3d &vect);

              vertex3d& transform(transformation &t);
              vector3d& transformNorm(transformation &t);

              inline vertex3d& operator =(vertex3d &vert)
              {
                this->xyz.x = vert[0]; this->xyz.y = vert[1]; this->xyz.z = vert[2];
                this->u = vert.u; this->v = vert.v;
                this->color = vert.color;
                this->norm = vert.norm;
                return *this;
              }
              inline vertex3d& operator =(vector3d &vect)
              {
                this->xyz.x = vect[0]; this->xyz.y = vect[1]; this->xyz.z = vect[2];
                return *this;
              }

              // we/wy
              friend ostream& operator << (ostream &s, vertex3d &vert);
              friend istream& operator >> (istream &s, vertex3d &vert);

              ostream& save (ostream &s);
              istream& load (istream &s);
              void get (char const *buff);
};

#endif//
//      Definicje potrzebne dla mapperkow
//
//

#ifndef __DEFS_H
#define __DEFS_H

#define VISIBLE     0
#define TOP         1
#define BOT         2
#define LEFT        4
#define RIGHT       8

// granice obcinania
extern float LeftClip;
extern float RightClip;
extern float TopClip;
extern float BotClip;

extern int BehindClip;

/* dlugosc linii ekranu w bajtach */
extern unsigned scanlineLen;

#endif//
//      texture lib
//                  procedury zarzadzajace teksturami
//
//      Onyx 3d ver. 2  (c) 2000 by Michal Pomaranski
//           If you want to use any of this code, please contact me:
//           mpomaranski@poczta.onet.pl or phone me: +4860463719

#ifndef __TEXTLIB_H
#define __TEXTLIB_H

// funkcja konweruje z pliku ONT do tekstury
//   we: bufor z danymi
//   wy: tekstura
char* convertTexture(char *buffer);

#endif
/*
**      Wspolne definicje dla wszystkich moich mapperow
**
**      (c) 2000 by Michal Pomaranski
*/

#ifndef _MAPPER_H
#define _MAPPER_H

#include "..\math\vertex3d.h"
#include "..\math\vector3d.h"

class vertex2d{
        public:
                int x,y;
                int z;          /* z-bufor       */
                unsigned char color;
                unsigned char u,v;        /* wsp. tekstury */
                int visible;    /* do obcinania  */

                inline vertex2d& operator=(vertex3d &vert)
                {
                  x = (int)vert[0]; y = (int)vert[1]; z = (int)vert[2];
                  u = vert.u; v = vert.v;
                  color = vert.color;
                  return *this;
                }

                inline vertex2d& operator=(vertex2d const &vert)
                {
                  x = vert.x; y = vert.y; z = vert.z;
                  u = vert.u; v = vert.v;
                  color = vert.color;
                  return *this;
                }
};

extern unsigned char colorTable[256][256];      /* tablica definiujaca cienie */
extern int BehindClip;                        /* obcinanie przed obs. */

/* nazewnictwo jest nastepujace:
**  pierwsze litery: g - gorouatd, t - teksturowanie
**  kolejny wyraz - Clip albo Noclip - czy obcinane czy tez nie
**  jesli wystepuje literka Z - to znaczy ze jest zbufor
**  kolejny czlon - 256c lub 16m - w ilu kolorach mapper dziala */
void gtClipZ16mTriangle (vertex2d *a, vertex2d *b, vertex2d *c, char *buff,
                         char *text, int *zbuff);
void gtClip16mTriangle  (vertex2d *a, vertex2d *b, vertex2d *c, char *buff,
                         char *text);
void tClipZ16mTriangle  (vertex2d *a, vertex2d *b, vertex2d *c, char *buff,
                         char *text, int *zbuff);
void tClip16mTriangle   (vertex2d *a, vertex2d *b, vertex2d *c, char *buff,
                         char *text);

#endif//
//      FrameBuffer
//                  klasa podstawowa dla frameBufferkow
//
//      Onyx 3d ver. 2  (c) 2000 by Michal Pomaranski
//           If you want to use any of this code, please contact me:
//           mpomaranski@poczta.onet.pl or phone me: +4860463719

#ifndef __VFB_H
#define __VFB_H

#include "mappers.h"

class virtualFrameBuffer{
        protected:
                 int x,y;               // rozmiary bufora
                 char *buff;            // pamiëç przeznaczona na ten bufor
                 int  *zbuffer;         // pamiëc przeznaczona na z-bufor
        public:
                 // jesli zwroci false - nic z tego, tryb nieobslugiwany,
                 //       przynajmniej nie przez ten framebuffer
                 virtual bool init(int mode) = 0;
                 virtual bool initZBuff() = 0;

                 virtual void deleteBuff() = 0;
                 virtual void deleteZBuff() = 0;

                 // ustawia parametry obcinania
                 virtual void setClip(unsigned left, unsigned right,
                                        unsigned top, unsigned bottom) = 0;

                 virtual void fill(int color) = 0;
                 virtual void copy(char *buff) = 0;
                 virtual void show(void) = 0;
                 virtual void fillZBuff(int value) = 0;

                 virtual void initVideoMode(void) = 0;

                 virtual void getSize (int &sizeX, int &sizeY);

                 // rysowanie trojkatow
                 // przyjalem nastepujaca konwencje nazywania funkcji
                 //  g,t - Gouraud i/lub teksturowanie
                 //  Z - Z-bufor
                 virtual inline void gtTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text)=0;
                 virtual inline void gtZTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text)=0;
                 virtual inline void tTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text)=0;
                 virtual inline void tZTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text)=0;
};

#endif//
//      frameBuffer16m
//                  frameBuffer dla trybow truecolor
//
//      Onyx 3d ver. 2  (c) 2000 by Michal Pomaranski
//           If you want to use any of this code, please contact me:
//           mpomaranski@poczta.onet.pl or phone me: +4860463719

#ifndef __FB16M_H
#define __FB16M_H

#include "mappers.h"                    // po prostu mappery
#include "vfb.h"                        // virtual frame buffer - klasa
                                        // podstawowa

#include <iostream.h>

class frameBuffer16m : virtual public virtualFrameBuffer{
        public:
                 bool init(int mode);
                 bool initZBuff();

                 void deleteBuff();
                 void deleteZBuff();

                 // ustawia parametry obcinania
                 void setClip(unsigned left, unsigned right,
                                        unsigned top, unsigned bottom);

                 void fill(int color);
                 void copy(char *buff);
                 void show(void);
                 void fillZBuff(int value);

                 void initVideoMode(void);

                 void getSize (int &sizeX, int &sizeY)
                 {
                   sizeX = x; sizeY = y;
                 }

                 // rysowanie trojkatow
                 // przyjalem nastepujaca konwencje nazywania funkcji
                 //  g,t - Gouraud i/lub teksturowanie
                 //  Z - Z-bufor
                 inline void gtZTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text);
                 inline void gtTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text);
                 inline void tZTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text);
                 inline void tTriangle(vertex2d &a, vertex2d &b,
                                              vertex2d &c, char *text);

};

inline void frameBuffer16m::gtZTriangle(vertex2d &a, vertex2d &b, vertex2d &c, char *text)
{
  gtClipZ16mTriangle(&a, &b, &c, this->buff, text, this->zbuffer);
}

inline void frameBuffer16m::gtTriangle(vertex2d &a, vertex2d &b, vertex2d &c, char *text)
{
  gtClip16mTriangle(&a, &b, &c, this->buff, text);
}

inline void frameBuffer16m::tZTriangle(vertex2d &a, vertex2d &b, vertex2d &c, char *text)
{
  tClipZ16mTriangle(&a, &b, &c, this->buff, text, this->zbuffer);
}

inline void frameBuffer16m::tTriangle(vertex2d &a, vertex2d &b, vertex2d &c, char *text)
{
  tClip16mTriangle(&a, &b, &c, this->buff, text);
}


#endif/*
**      RMI.H                   Real Mode Int
**                              Funkcje sluzace do wywolywania
**                              przerwan w REAL MODE
**      Sarin/!ArisE!
*/

#ifndef __RMI_H
#define __RMI_H

#include <i86.h>

// Struktura zwracana przez rmAlloc
struct rmAddr {
       short selector;
       short segment;
};

// Struktura przekazujaca informacje do REAL MODE
struct rmInfo {
       long edi;
       long esi;
       long ebp;
       long reserved;
       long ebx;
       long edx;
       long ecx;
       long eax;
       short flags;
       short es, ds, fs, gs, ip, cs, sp, ss;
};

// Alokacja pamieci ponizej 1 mb. Rozmiar podajemy w paragrafach.
// Jeden paragraf ma 16 bajtow
rmAddr rmAlloc(int parAmount);

// Wywolanie przerwania REAL MODE
// zwracana zawartosc rejestru EAX
int rmInt(int intNo, union REGS *inRegs, union REGS *outRegs, struct SREGS *segRegs);

#endif/*
**      VESA.H          Obsluga VESA 1.2
**
**      Sarin/!ArisE!
*/

#ifndef __VESA_H
#define __VESA_H

/* Wlaczyc czy wylaczyc przeszkadzanie */
//#define SHAREWARE

#define VIDEO_INT 0x10

// Ilosc trybow graficznych
#define MODE_NO 9

// Struktura opisujaca tryb
struct __modeInfo{
       int modeNo;
       int resX, resY;
       unsigned colors;
       char bytesPerPixel;
};

extern __modeInfo modes[MODE_NO];

// Nazwy trybow graficznych
#define VMODE320x200x256    0
#define VMODE640x480x256    1
#define VMODE800x600x256    2
#define VMODE320x200x64k    3
#define VMODE640x480x64k    4
#define VMODE800x600x64k    5
#define VMODE320x200x16m    6
#define VMODE640x480x16m    7
#define VMODE800x600x16m    8

// Funkcje
int        vesaInit();                  // sprawdza dostepnosc trybow. Zwraca -1 jesli nie ma VESA 1.2
int        setVideoMode(int modeNo);    // ustawia tryb (korzystaj ze zdefiniowanych nazw)
void       setTextMode(void);

int        getModeAuto();               // zwraca numer najlepszego mozliwego trybu
int        getModeUser();               // jw. ale uzytkownik wybiera z MENU

int        checkMode(int modeNo);       // zwraca 1 jesli tryb jest,
                                        // 0 jesli go nie ma

void       copyToScreen(int *src);

#pragma aux setTextMode = \
        "mov ax, 03h"     \
        "int 10h"         \
        modify [eax];

#endif//      LIST.H                  Lista dwukierunkowa
//      coded by Sarin/!ArisE!  (sarin@czart.pulawy.pl)
//
//      13.12.1997 Pulawy/Poland

//      I didn't want to use list from standard c++ lib, 'coz
//      i don't know c++ very much and I wanted to optimize it

#ifndef __LIST_H
#define __LIST_H

#ifndef NULL
 #define NULL 0
#endif

class   listElem {              // klasa reprezentujaca element listy
        public:
                 listElem(void *elem);
                 listElem();
                 ~listElem();
//        protected:
                 listElem *prev;// previous element
                 listElem *next;// next element
                 void *data;    // this value is stored in the list

};

class   list : private listElem {
        private:
                 listElem *first;// pierwszy element listy
                 listElem *last; // ostatni element listy
                 listElem *current;
        public:
                 list(void *elem);
                 list(void);

                 void addElemFirst(void *elem); // dodaje element na poczatek
                 void addElemLast(void *elem); // dodaje element na koniec
                 void init();                  // inicjuje przegladanie
                 void *getFirst();    // zwraca pierwszy element listy
                 void *getLast();     // zwraca ostatni element listy
                 void *getNext();
                 void *getPrev();
                 void *getCurr();


                 void *delFirst();    // jw. ale kasuje z listy
                 void *delLast();     // jw. ale kasuje z listy
                 void *delNext();
                 void *delPrev();
                 void *delCurr();

                 bool empty();        // czy lista pusta?
                 bool viewed();       // czy juz przejrzana?
};

#endif


//
//      OBJECT.H        -       definicja objektu
//
//      ONYX 3D (c) 2000 by Michal Pomaranski
//

#ifndef __OBJECT_H
#define __OBJECT_H

#include "..\math\vector3d.h"           // aparat matematyczny
#include "..\math\vertex3d.h"
#include "..\math\matrix.h"
#include "..\math\transform.h"

#include "..\video\vfb.h"               // wyswietlanie

#include "list.h"                       // do listy obiektow

#include <stdio.h>
#include <iostream.h>                   // i/o

// t - tekstura, z - zbufor, g - Gouraud
enum {t, gt, tz, gtz};

// plaszczyzna obcinajaca widziana przez obserwatora
// (druga plaszczyzna ma rownanie z=BehindClip i jest niewidzialna (automatyczne
// obcinanie przez z-bufor)
extern float AftClip;
extern int BehindClip;

class triangle {
     public:
       unsigned v1, v2, v3;             // offsety (numery) wierzcholkow
       unsigned type;                   // rodzaj trojkata
       char     *texture;               // tekstura nalozona na trojkat
       int      textureNo;              // numer tekstury

       vector3d norm;                   // normalna do trojkata

       friend ostream& operator << (ostream &s, triangle &tr);
       friend istream& operator >> (istream &s, triangle &tr);

       ostream& save (ostream &s);
       istream& load (istream &s);
       void get (char const *buff);
};

class object3d{
      private:
               list     objectList;
               list     triangleList;  // lista trojkotow
               unsigned vertexesNo;     // ilosc wierzcholkow
               vertex3d *vertexes;      // lista wierzcholkow
               vertex3d *tempVert;      // tutaj beda przeksztalcone vertexy
               vertex3d boundary[6];    // ograniczenie

               int loadA0 (const char *fname, char *text, int textureNo);
      public:
               vector3d position;
               float    scaleX, scaleY, scaleZ;

               object3d  ();
               ~object3d ();

               // mode = 0 - nowa transformacja, 1 = na bazie starej tr.
               object3d& transform(transformation &tr, int mode=0);
               object3d& rotateNormals(transformation &tr);

               // przeksztalcenie perspektywiczne k-wsp. persp., sizeX, sizeY - wielkosc obrazu
               object3d& perspective(int k, int sizeX, int sizeY);
               void     show(virtualFrameBuffer &frBuffer);

               void     findBoundary();
               void     computeNormals();       // liczy normalne w objekcie
               void     computeLight();         // liczy swiatlo

               // dostep do listy objektow, vertexow, trojkatow
               inline list& getObjectList(void) { return objectList; };
               inline vertex3d*& getVertexes(void) { return vertexes; };
               inline unsigned& getVertexesNo(void) { return vertexesNo; };
               inline list& getTriangleList(void) { return triangleList; };

               // we/wy
               // ladowanie pliku ASC
               int loadA0 (FILE *in, char *text, int textureNo);

               // zapis i odczyt w formacie onx (ASCII)
               friend ostream& operator<<(ostream &s, object3d &obj);
               friend istream& operator>>(istream &s, object3d &obj);

               // zapis i odczyt w postaci binarnej
               istream& load (istream &s);
               ostream& save (ostream &s);

               // kopiuje dane objektu z pamieci do struktury wewnetrznej
               void get (char const *buff);
};

#endif
#endif