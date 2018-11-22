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

ring_t* ring_init(  int length );
int ring_insert( ring_t *ring, char data );
int ring_removeData( ring_t *ring, char *data );
int ring_entries( ring_t *ring );
int ring_resize( ring_t* rtn, int length );


#endif
