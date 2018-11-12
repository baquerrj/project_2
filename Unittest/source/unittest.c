/*
*unittest.c
*test cases for project 2
*ECEN5813
*REFS: 
*
*/
#include "ring.h"
#include "stdlib.h"
#include "stdio.h"
#include "unittest.h"
#include <CUnit/CUnit.h>
#define UNIT_TEST 



//Test Description: Fill buffer with data and test to see if buffer
//can be written to after full
void test1(void)
{
    ring_t my_ring;
    ring_t* my_ringp = &my_ring;
    my_ringp = init(100);
    for(int i = 0; i < 100; i ++)
    {
        CU_ASSERT(insert(my_ringp, 'a') == 1);
    }
    CU_ASSERT(insert(my_ringp, 'a') == -1);
}

//Test Description: Remove data from buffer, ensure that remove will not
//execute after buffer is empty
void test2(void)
{
  ring_t my_ring2;
  ring_t* my_ringp2 = &my_ring2;
  my_ringp2 = init(100);

  for(int i = 0; i < 100; i ++)
  {
      insert(my_ringp2, 'a');
  }

  for(int i = 0; i < 100; i ++)
  {
      CU_ASSERT(removeData(my_ringp2, DATA)== 1);
  }
  CU_ASSERT(removeData(my_ringp2, DATA)== -1);
}

//Test Description: Fill buffer and then attempt to increase size.
void test3(void)
{
  ring_t my_ring3;
  ring_t* my_ringp3 = &my_ring3;
  my_ringp3 = init(100);

  for(int i = 0; i < 100; i ++)
  {
    printf("filling up iter %u\n\r", i);
      CU_ASSERT(insert(my_ringp3, 'a') == 1 );
  }
  // Add another element - this should fail
  CU_ASSERT(insert(my_ringp3, 'a') == -1);

  CU_ASSERT(resize(my_ringp3, 110) == 1);

  printf("Length of buffer after resize is %u\n\r", my_ringp3->Length);
  printf("After resize should not be full %u\n\r", my_ringp3->full);

  printf("Outi = %u and Ini = %u\n\r", my_ringp3->Outi, my_ringp3->Ini);
  // Attempt to add additional elements
  for( int i = 0; i < 10; i++)
  {
    printf("Iteration after resize %u\n\r", i);
    CU_ASSERT(insert(my_ringp3, 'a') == 1);
  }

  // One more element should fail again
  CU_ASSERT(insert(my_ringp3, 'a') == -1);
}

//Test Description: Test shrinking the size of the buffer
void test4(void)
{
  ring_t my_ring4;
  ring_t* my_ringp4 = &my_ring4;
  my_ringp4 = init(100);

  for(int i = 0; i < 100; i ++)
  {
      printf("filling up iter %u\n\r", i);
      CU_ASSERT(insert(my_ringp4, 'a') == 1 );
  }

  // Add another element - this should fail
  CU_ASSERT(insert(my_ringp4, 'a') == -1);

  // Attempt to shrink after buffer is full
  CU_ASSERT(resize(my_ringp4, 90) == -2);

  printf("Length of buffer after resize is %u\n\r", my_ringp4->Length);

  printf("Outi = %u and Ini = %u\n\r", my_ringp4->Outi, my_ringp4->Ini);

  // Remove ten items
  for( int i = 0; i < 10; i++)
  {
    printf("Iteration after resize %u\n\r", i);
    CU_ASSERT(removeData(my_ringp4, DATA) == 1);
  }

  printf("After removing items, buffer should not be full %u\n\r", my_ringp4->full);
  // Attempt shrink again
  CU_ASSERT(resize(my_ringp4, 90) == 1);

  int elm = entries(my_ringp4);
  // Should not be able to shrink 
  CU_ASSERT(resize(my_ringp4, elm-1) == -3);
  CU_ASSERT(resize(my_ringp4, elm-20) == -3);
}

void test5(void)
{
  ring_t my_ring5;
  ring_t* my_ringp5 = &my_ring5;
  my_ringp5 = init(100);

  // Add 15 elements
  for( int i  = 0; i < 15; i++)
  {
    CU_ASSERT(insert(my_ringp5, 'a') == 1);
    CU_ASSERT(entries(my_ringp5) == i+1);
  }
  CU_ASSERT(entries(my_ringp5) == 15);
}

