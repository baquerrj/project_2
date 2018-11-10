#include "ring.h"

int main( void )
{
	ring_t ring;
	if( -1 != init( &ring, 5 ) )
	{
		return 0;
	}
	else
	{
		return -1;
	}
}
