#include "ring.h"
#include "unittest.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#define UNIT_TEST

char* DATA[1000];

int main(void)
{
    //char* data;
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("test1_test_suite", 0, 0);

    CU_add_test(suite, "test_add", test1);
    CU_add_test(suite, "test_remove", test2);
    

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
  //test1();
    return 0;
}
