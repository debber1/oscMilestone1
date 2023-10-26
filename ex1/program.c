#define _GNU_SOURCE
/**
 * \author Bert Lagaisse
 *
 * main method that executes some test functions (without check framework)
 */

#include <stdio.h>
#include "dplist.h"

void ck_assert_msg(bool result, char * msg){
    if(!result) printf("%s\n", msg);
}
int main(void)
{
  // Own tests

  /*
  * Tests for dpl_get_reference_at_index
  */
  dplist_t *testing = NULL;
  ck_assert_msg(dpl_get_reference_at_index(testing, 100) == NULL, "dpl_get_reference_at_index should return NULL when presented with a NULL pointer");
  testing = dpl_create();
  ck_assert_msg(dpl_get_reference_at_index(testing, 100) == NULL, "dpl_get_reference_at_index should return NULL when presented with an empty list");
  dpl_insert_at_index(testing, 'a', 0);
  ck_assert_msg(dpl_get_reference_at_index(testing, 100) != NULL, "dpl_get_reference_at_index should not return NULL when presented with an unrealistic index");
  ck_assert_msg(dpl_get_reference_at_index(testing, -100) != NULL, "dpl_get_reference_at_index should not return NULL when presented with a negative index");
  ck_assert_msg(dpl_get_reference_at_index(testing, 0) != NULL, "dpl_get_reference_at_index should not return NULL when presented with a realistic index");
  dplist_node_t *a0 = dpl_get_reference_at_index(testing, 0);
  dplist_node_t *aN = dpl_get_reference_at_index(testing, -100);
  dplist_node_t *aL = dpl_get_reference_at_index(testing, 100);
  ck_assert_msg(aN == aL, "dpl_get_reference_at_index should return the same for first and last element if the dpl only has one element");
  ck_assert_msg(aN == a0, "dpl_get_reference_at_index should return the same for a negative index and index 0");
  dpl_free(&testing);


  // Tests by the TA
    dplist_t *numbers = NULL;
    numbers = dpl_create();

    ck_assert_msg(numbers != NULL, "numbers = NULL, List not created");
    ck_assert_msg(dpl_size(numbers) == 0, "Numbers may not contain elements.");

    dpl_insert_at_index(numbers, 'a', 0);
    ck_assert_msg(dpl_size(numbers) == 1, "Numbers must contain 1 element.");

    dpl_insert_at_index(numbers, '\e', -1);
    ck_assert_msg(dpl_size(numbers) == 2, "Numbers must contain 2 elements.");

    dpl_insert_at_index(numbers, 'b', 100);
    ck_assert_msg(dpl_size(numbers) == 3, "Numbers must contain 3 elements.");

    dpl_free(&numbers);

    return 0;
}
