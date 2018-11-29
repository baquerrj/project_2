/*
*ring.h
*Circular buffer
*ECEN5813
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

/* Returns pointer to Ring Buffer with buffer
 * size specified by length input.
 * @param	length:	Buffer Size
 * @ret:	  			Pointer to initialized ring buffer
 */
ring_t* ring_init( int length );

/* Inserts char at end of input ring buffer
 * @param		*ring: Pointer to ring buffer
 * @param		data:  data to insert
 * @retVal	1 if successful
 * 					-1 if not successful
 */
int ring_insert( ring_t *ring, char data );

/* Removes data from circular buffer
 * @param		*ring: Pointer to ring buffer
 * @param		*data: Pointer to char to place popped data
 * @retVal	1 if successful
 * 					-1 if not successful
 */
int ring_removeData( ring_t *ring, char *data );

/* Returns number of elements contained in ring buffer
 * @param		*ring:	Pointer to ring buffer
 * @ret:		ring->numElements:	Number of elements
 */
int ring_entries( ring_t *ring );

/* Resizes input ring buffer
 * @param 	*ring:	Pointer to ring buffer to resize
 * @param		length:	New length of ring buffer
 * @retVal	1 if successful
 * 					-1 memory reallocation fails (realloc returns NULL)
 * 					-2 New length is less than original and buffer is full
 * 					-3 New length cannot hold elements currently in ring buffer
 */
int ring_resize( ring_t* ring, int length );


#endif
