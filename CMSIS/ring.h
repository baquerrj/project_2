/*
*ring.h
*Circular buffer
*ECEN5813
*
*
*/
#ifndef RING_H
#define RING_H

typedef struct
{
  int Length;
  int Ini;
  int Outi;
  int numElements;
  char full;
  char empty;
  char *Buffer;
} ring_t;

ring_t* init(  int length );
int insert( ring_t *ring, char data );
int removeData( ring_t *ring, char *data );
int entries( ring_t *ring );
int resize( ring_t* rtn, int length );


#endif
