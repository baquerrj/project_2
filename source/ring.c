/*
*ring.c
*Circular buffer
*ECEN5813
*
*
*/
#include "ring.h"


typedef struct
{
    char *Buffer;
    int Length;
    int Ini;
    int Outi;
    char full;
    char empty;
}ring_t;


int entries( ring_t *ring)
{

}

ring_t *init(int length)
{
    ring_t *rtn = malloc(length+sizeof(*rtn));
    rtn->Buffer = rtn+1;
    rtn->Ini = 0;
    rtn->Outi = 0;
    rtn->full = 0;
    rtn->empty = 1;
    return rtn;
}

int insert(ring_t *ring, char data)
{
    if (!(ring->full))
    {
        ring->Buffer[ring->Ini] = data;
        ring->Ini++;
        if (ring->Ini == (ring->Length + ring->Outi))ring->full = 1;
    }
    else return -1;
}
int remove( ring_t *ring, char *data)
{
    if (!(ring->empty))
    {
        *data = ring->Buffer[ring->Outi];
        ring->Outi++;
        ring->full = 0;
    }
    else return -1;
}

test1(void)
{
    ring_t my_ring, *my_ringp = &my_ring;
    init(my_ringp, 100);
    for(int i = 0; i < 100; i ++)
    {
        assert(insert(my_ringp, 'a')== 0);
    }
    assert(insert(my_ringp, 'a')== -1);
}
