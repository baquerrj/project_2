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
#include "unittest.h"
#include <CUnit/CUnit.h>
#define UNIT_TEST 

extern char DATA[100];

int entries( ring_t *ring )
{
  return ring->numElements;
}

ring_t* init( int length )
{
  //struct dyn_array* my_array = malloc(sizeof(struct dyn_array) + 100*sizeof(int));
 // ring_t *rtn = malloc(length+sizeof(*rtn));
  ring_t *rtn = malloc(sizeof(*rtn) + length*sizeof(char));
  if (rtn == NULL)
  {
    printf("malloc for struct failed\n\r");
    exit(1);
  }
  rtn->Buffer=  malloc(length+1);
  if( rtn->Buffer == NULL )
  {
    printf("malloc for buffer failed\n\r");
   exit(1);
  }

   rtn->Length = length;
  //rtn->Buffer=rtn+1;
  rtn->Ini=0;
  rtn->Outi=0;
  rtn->numElements=0;
  rtn->full=0;
  rtn->empty=1;
  return rtn;
}

int resize( ring_t* rtn, int length )
{
   int oldLength = rtn->Length;
   if( ( oldLength > length ) && rtn->full )
   {
      return -2;
   }

   rtn->Buffer = realloc( rtn->Buffer, length );
   if( rtn->Buffer == NULL )
   {
      return -1;
   }

   if( ( oldLength < length ) && rtn->full )
   {
     if( rtn->Outi == rtn->Ini )
     {
       rtn->Ini =  rtn->Ini + oldLength;
     }
     rtn->full = 0;
   }
   rtn->Length = length;
   return 1;
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
    else ring->empty = 0;

    if( !(ring->full) )
    {
      ring->numElements++;
      ring->Buffer[ring->Ini] = data;
      ring->Ini = (ring->Ini +1)% ring->Length; //if index==Length, index resets to 0
	
      if( ( ring->Ini == ring->Outi )&&(!(ring->empty)) )
        {
          printf("ring is full\n\r");
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
      ring->numElements--;
      *data = ring->Buffer[ring->Outi];
      ring->Outi = (ring->Outi + 1) % ring->Length;
      printf("ring->Out1= %u\n\r ring->Ini = %u\n\r", ring->Outi, ring->Ini);
      ring->full = 0;
      if(ring->Outi == ring->Ini) ring->empty = 1;
      return 1;
    }
    else return -1;
}

