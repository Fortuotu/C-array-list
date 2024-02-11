#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "array_list.h"

#define ARRAY_LIST_RESIZE_MULTIPLIER 2
#define ARRAY_LIST_RESIZE_DIVISOR 4

#define ARRAY_LIST_REALLOC(list) \
    list->elements = realloc(list->elements, list->max_length * list->element_size) \

array_list_t*
array_list_create(const size_t element_size)
{
    array_list_t* list = malloc(sizeof(array_list_t));

    list->elements = malloc(element_size * ARRAY_LIST_RESIZE_DIVISOR);
    list->element_size = element_size;
    list->length = 0;
    list->max_length = ARRAY_LIST_RESIZE_DIVISOR;
    list->min_length = 1;

    return list;
}

void
array_list_free(array_list_t* list)
{
    free(list->elements);
    free(list);
}

void
array_list_append(array_list_t* list, const void* element)
{
    if (list->length == list->max_length)
    {
        list->max_length *= ARRAY_LIST_RESIZE_MULTIPLIER;
        list->min_length *= ARRAY_LIST_RESIZE_MULTIPLIER;

        ARRAY_LIST_REALLOC(list);
    }

    memcpy(
        list->elements + list->element_size * list->length,
        element,
        list->element_size);

    list->length++;
}

void
array_list_remove(array_list_t* list, const u_int32_t index)
{
    memmove(
        array_list_get(list, index),
        array_list_get(list, index + 1),
        list->element_size * (list->length - index + 1));

    if (--(list->length) == list->min_length && list->min_length != 1)
    {
        list->max_length /= ARRAY_LIST_RESIZE_MULTIPLIER;
        list->min_length /= ARRAY_LIST_RESIZE_MULTIPLIER;

        ARRAY_LIST_REALLOC(list);
    }
}

void*
array_list_get(array_list_t* list, const u_int32_t index)
{
    return list->elements + list->element_size * index;
}

void
array_list_set(array_list_t* list, const u_int32_t index, const void* element)
{
    memcpy(
        array_list_get(list, index),
        element,
        list->element_size);
}
