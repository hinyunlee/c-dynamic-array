/*
 * A simple header-only macro-based dynamic array library for C.
 *   by: Hin Yun Lee
 *
 * Include this file and call DECLARE_DYNAMIC_ARRAY(<name>, <type>) to generate structure and functions.
 * Example:
 *   DECLARE_DYNAMIC_ARRAY(ivec, int);
 *
 * The following will be declared:
 *   struct:
 *     <name>
 *   typedef:
 *     <name>_t
 *   functions:
 *     create_<name>,
 *     destroy_<name>,
 *     <name>_length,
 *     <name>_capacity,
 *     <name>_array,
 *     <name>_realloc,
 *     <name>_reserve,
 *     <name>_grow,
 *     <name>_push,
 *     <name>_pop,
 *     <name>_shift,
 *     <name>_unshift,
 *     <name>_insert,
 *     <name>_delete,
 *     <name>_get,
 *     <name>_set
 */

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <stdlib.h>
#include <string.h>

#define DECLARE_DYNAMIC_ARRAY(NAME, TYPE) \
typedef struct NAME { \
  size_t length; \
  size_t capacity; \
  TYPE *array; \
} NAME##_t; \
NAME##_t *create_##NAME() { \
  NAME##_t *v = malloc(sizeof(NAME##_t)); \
  v->length = 0; \
  v->capacity = 0; \
  v->array = NULL; \
  return v; \
} \
void destroy_##NAME(NAME##_t *v) { \
  free(v->array); \
  free(v); \
} \
size_t NAME##_length(NAME##_t *v) { \
  return v->length; \
} \
size_t NAME##_capacity(NAME##_t *v) { \
  return v->capacity; \
} \
TYPE *NAME##_array(NAME##_t *v) { \
  return v->array; \
} \
TYPE *NAME##_realloc(NAME##_t *v, size_t capacity) { \
  TYPE *new_array = realloc(v->array, capacity*sizeof(TYPE)); \
  if (new_array) { \
    if (capacity < v->length) v->length = capacity; \
    v->capacity = capacity; \
    v->array = new_array; \
  } \
  return new_array; \
} \
TYPE *NAME##_reserve(NAME##_t *v, size_t length) { \
  size_t capacity = v->capacity; \
  if (length <= capacity) return v->array; \
  if (capacity <= 0) capacity = 1; \
  while (capacity < length) capacity *= 2; \
  return NAME##_realloc(v, capacity); \
} \
TYPE *NAME##_grow(NAME##_t *v) { \
  size_t capacity = v->capacity; \
  capacity = capacity <= 0 ? 1 : capacity*2; \
  return NAME##_realloc(v, capacity); \
} \
int NAME##_insert(NAME##_t *v, size_t i, TYPE val) { \
  TYPE *array = v->length < v->capacity ? v->array : NAME##_grow(v); \
  if (!array) return -1; \
  memmove(array + i + 1, array + i, (v->length++ - i)*sizeof(TYPE)); \
  array[i] = val; \
  return 0; \
} \
TYPE NAME##_delete(NAME##_t *v, size_t i) { \
  TYPE *array = v->array; \
  TYPE val = v->array[i]; \
  memmove(array + i, array + i + 1, (--v->length - i)*sizeof(TYPE)); \
  return val; \
} \
int NAME##_push(NAME##_t *v, TYPE val) { \
  TYPE *array = v->length < v->capacity ? v->array : NAME##_grow(v); \
  if (!array) return -1; \
  array[v->length++] = val; \
  return 0; \
} \
TYPE NAME##_pop(NAME##_t *v) { \
  return v->array[--v->length]; \
} \
int NAME##_shift(NAME##_t *v, TYPE val) { \
  TYPE *array = v->length < v->capacity ? v->array : NAME##_grow(v); \
  if (!array) return -1; \
  memmove(array + 1, array, v->length++*sizeof(TYPE)); \
  array[0] = val; \
  return 0; \
} \
TYPE NAME##_unshift(NAME##_t *v) { \
  TYPE *array = v->array; \
  TYPE val = array[0]; \
  memmove(array, array + 1, --v->length*sizeof(TYPE)); \
  return val; \
} \
TYPE NAME##_get(NAME##_t *v, size_t i) { \
  return v->array[i]; \
} \
void NAME##_set(NAME##_t *v, size_t i, TYPE val) { \
  v->array[i] = val; \
}
#endif /* DYNAMIC_ARRAY_H */
