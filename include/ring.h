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
    char *Buffer;
    int Length;
    int Ini;
    int Outi;
    char full;
    char empty;
} ring_t;

int init( ring_t* ring, int length );
int insert( ring_t *ring, char data );
int remove( ring_t *ring, char *data );
int entries( ring_t *ring );






#endif
