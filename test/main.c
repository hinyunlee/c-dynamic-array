#include <stdio.h>
#include <assert.h>
#include "vector.h"

DECLARE_DYNAMIC_ARRAY(ivec, int);

void print_ivec(ivec_t *v) {
  int i;

  for (i = 0; i < ivec_length(v); ++i) {
    int val = ivec_get(v, i);
    printf("%d", val);

    if (i != ivec_length(v) - 1) printf(", ");
    else printf("\n");
  }
}

int main(int argc, char *argv[]) {
  ivec_t *v = create_ivec();

  int i;

  for (i = 0; i < 10; ++i) {
    printf("push: %d; length: %d; capacity: %d\n", i, ivec_length(v),  ivec_capacity(v));
    ivec_push(v, i);
  }

  assert(ivec_length(v) == 10);
  assert(ivec_capacity(v) == 16); /* 2x growth */

  printf("Initial contents:\n");

  for (i = 0; i < ivec_length(v); ++i) {
    int val = ivec_get(v, i);
    assert(val == i);
  }

  print_ivec(v);

  ivec_pop(v); /* length = 9 */
  assert(ivec_get(v, ivec_length(v) - 1) == 8);
  assert(ivec_unshift(v) == 0); /* length = 8 */
  ivec_shift(v, 10); /* length = 9 */
  assert(ivec_get(v, 0) == 10);
  ivec_set(v, 1, 20);
  assert(ivec_get(v, 1) == 20);
  assert(ivec_length(v) == 9);
  int deleted = ivec_delete(v, 1); /* length = 8 */
  assert(deleted == 20);
  assert(ivec_length(v) == 8);
  assert(ivec_get(v, 1) != 20);
  ivec_insert(v, 0, 30); /* length = 9 */
  assert(ivec_get(v, 0) == 30);
  ivec_insert(v, ivec_length(v), 40); /* length = 10 */
  assert(ivec_get(v, ivec_length(v) - 1) == 40);

  printf("Contents after test:\n");

  print_ivec(v);

  for (i = 0; i < 1000; ++i) {
    ivec_push(v, i);
    ivec_shift(v, i);
  }

  assert(ivec_length(v) == 10 + 1000*2);
  /*print_ivec(v);*/

  destroy_ivec(v);
  v = NULL;
  printf("Test OK\n");
  return 0;
}
