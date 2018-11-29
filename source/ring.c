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

/* Returns pointer to Ring Buffer with buffer
 * size specified by length input.
 * @param	length:	Buffer Size
 * @ret:	  			Pointer to initialized ring buffer
 */
ring_t* ring_init( int length )
{
	ring_t *ring = malloc(sizeof(*ring) + length*sizeof(char));
	if (ring == NULL)
	{
		printf("malloc for struct failed\n\r");
		exit(1);
	}
	ring->Buffer=  malloc(length+1);
	if( ring->Buffer == NULL )
	{
		printf("malloc for buffer failed\n\r");
		exit(1);
	}
	ring->Length = length;
	ring->Ini=0;
	ring->Outi=0;
	ring->numElements=0;
	ring->full=0;
	ring->empty=1;
	return ring;
}

/* Removes data from circular buffer
 * @param		*ring: Pointer to ring buffer
 * @param		*data: Pointer to char to place popped data
 * @retVal	1 if successful
 * 					-1 if not successful
 */
int ring_insert(ring_t *ring, char data)
{
	if( !(ring->full) )
	{
		ring->numElements++;
		ring->Buffer[ring->Ini] = data;
		ring->Ini = (ring->Ini +1)% ring->Length; //if index==Length, index resets to 0
		ring->empty = 0;
		//if( ( ring->Ini == ring->Outi )&&(!(ring->empty)) )
		if( ring->numElements == ring->Length && !(ring->empty) )
		{
			ring->full = 1;
		}
		return 1;
	}
  else return -1;
}

/* Returns number of elements contained in ring buffer
 * @param		*ring:	Pointer to ring buffer
 * @ret:		ring->numElements:	Number of elements
 */
int ring_removeData( ring_t *ring, char *data)
{
	if( !(ring->empty) )
  {
		ring->numElements--;
		*data = ring->Buffer[ring->Outi];
		ring->Outi = (ring->Outi + 1) % ring->Length;
		//if(ring->Outi == ring->Ini)
		ring->full = 0;
		if( ring->numElements == 0 )
		{
			ring->full = 0;
			ring->empty = 1;
		}
		return 1;
  }
	else return -1;
}

/* Returns number of elements contained in ring buffer
 * @param		*ring:	Pointer to ring buffer
 * @ret:		ring->numElements:	Number of elements
 */
int ring_entries( ring_t *ring )
{
	return ring->numElements;
}

/* Resizes input ring buffer
 * @param 	*ring:	Pointer to ring buffer to resize
 * @param		length:	New length of ring buffer
 * @retVal	1 if successful
 * 					-1 memory reallocation fails (realloc returns NULL)
 * 					-2 New length is less than original and buffer is full
 * 					-3 New length cannot hold elements currently in ring buffer
 */
int ring_resize( ring_t* ring, int length )
{
	int oldLength = ring->Length;
	if( ( oldLength > length ) && ring->full )
  {
		return -2;
  }

	if( ring->numElements > length )
  {
		return -3;
  }

   ring->Buffer = realloc( ring->Buffer, length );
   if( ring->Buffer == NULL )
   {
      return -1;
   }

   if( ( oldLength < length ) && ring->full )
   {
  	 if( ring->Outi == ring->Ini )
     {
  		 ring->Ini =  ring->Ini + oldLength;
     }
  	 ring->full = 0;
   }
   ring->Length = length;
   return 1;
}
