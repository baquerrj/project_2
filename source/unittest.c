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
      CU_ASSERT(insert(my_ringp, 'a')== 1);
  }
  CU_ASSERT(insert(my_ringp, 'a')== -1);
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
//Test Description: Fill buffer with data and test to see if buffer
//can be written to after full
