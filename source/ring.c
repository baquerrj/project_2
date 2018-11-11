/*
*ring.c
*Circular buffer
*ECEN5813
*REFS:https://stackoverflow.com/questions/2060974/how-to-include-a-dynamic-array-inside-a-struct-in-c 
*
*/
#include "ring.h"
#include "stdlib.h"
#include "stdio.h"
#include "test.h"
#include <CUnit/CUnit.h>
#define UNIT_TEST 


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

ring_t* init( int length )
{
  //struct dyn_array* my_array = malloc(sizeof(struct dyn_array) + 100*sizeof(int));
 // ring_t *rtn = malloc(length+sizeof(*rtn));
  ring_t *rtn = malloc(sizeof(*rtn) + length*sizeof(char));
  if (rtn == NULL)
  {
    printf("malloc failed");
    exit(1);
  }
  rtn->Length = length;
  //rtn->Buffer=rtn+1;
  rtn->Ini=0;
  rtn->Outi=0;
  rtn->full=0;
  rtn->empty=1;
  return rtn;
}

int insert(ring_t *ring, char data)
{
  if (!((data == ' ')||
       (data >= 'a' && data <= 'z') ||
       (data >='0' && data <='9')||
       (data >= 'A' && data <= 'Z')))
    {
      return -2; //invalid entry
    }
  if( !(ring->full) )
    {
      printf("ring-Ini: %d\n\r",ring->Ini); 
      printf("ring-empty: %d\n\r",ring->empty); 
      ring->Buffer[ring->Ini] = (char*)data;
      ring->Ini = (ring->Ini +1) % ring->Length;//if index==Length, index resets to 0
	
      if( ring->Ini == ( ring->Length + ring->Outi ) )
        {
	  ring->full = 1;
	}
	return 1;
		
    }
    else return -1;
}

int removeData( ring_t *ring, char *data)
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

//#ifdef UNIT_TEST
void test1(void)
{
    ring_t my_ring;
    ring_t* my_ringp = &my_ring;
    my_ringp = init(100);
    for(int i = 0; i < 100; i ++)
    {
        CU_ASSERT(insert(my_ringp, 'a')== 0);
    }
    CU_ASSERT(insert(my_ringp, 'a')== -1);
}
//#endif
