#ifndef __INTDEF_H__
#define __INTDEF_H__

typedef unsigned char  Uint8;
typedef unsigned short Uint16;
typedef unsigned int   Uint32;
typedef signed   char  Sint8;
typedef signed   short Sint16;
typedef signed   int   Sint32; 

#define LOW           0
#define HIGH          (!LOW)
#define FALSE         0
#define TRUE		  (!FALSE)	
#define OUTPUT		  0
#define INPUT		  (!OUTPUT)

#endif
