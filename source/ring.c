/*
*ring.c
*Circular buffer
*ECEN5813
*
*
*/
#include "ring.h"
#include "stdlib.h"
/*
typedef struct
{
    char *Buffer;
    int Length;
    int Ini;
    int Outi;
    char full;
    char empty;
}ring_t;
*/

int entries( ring_t *ring )
{
	int num = -1;
	if( 1 == ring->empty )
	{
		return num;
	}
	num++;
	while( NULL != ring->Buffer++ )
	{
		num++;
	}
	return num;
}

int init( ring_t* rtn, int length )
{
	int size = length + sizeof( ring_t );
//    rtn = malloc( length + sizeof( *ring_t ) );
    rtn = malloc( size );
	if( NULL != rtn )
	{
		rtn->Buffer = (char*)rtn+1;
		rtn->Ini = 0;
		rtn->Outi = 0;
		rtn->full = 0;
		rtn->empty = 1;
		rtn->Length = 0;
		return 1;
	}
	else
	{
		return -1;
	}
}

int insert(ring_t *ring, char data)
{
    if( !(ring->full) )
    {
        ring->Buffer[ring->Ini] = data;
        ring->Ini++;
		ring->Length++;
        if( ring->Ini == ( ring->Length + ring->Outi ) )
		{
			ring->full = 1;
		}
		return 1;
    }
    else return -1;
}

int remove( ring_t *ring, char *data)
{
    if( !(ring->empty) )
    {
        *data = ring->Buffer[ring->Outi];
        ring->Outi++;
        ring->full = 0;
		return 1;
    }
    else return -1;
}

#ifdef UNIT_TEST
void test1(void)
{
    ring_t my_ring;
	ring_t* my_ringp = &my_ring;
    init(my_ringp, 100);
    for(int i = 0; i < 100; i ++)
    {
        assert(insert(my_ringp, 'a')== 0);
    }
    assert(insert(my_ringp, 'a')== -1);
	return void;
}
#endif
