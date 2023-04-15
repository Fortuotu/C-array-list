#include <stdlib.h>
#include <string.h>

#include "array_list.h"

array_list_t*
array_list_create(const size_t element_size)
{
    array_list_t* list = malloc(sizeof(array_list_t));

    list->data = NULL;
    list->element_size = element_size;
    list->length = 0;

    return list;
}

void
array_list_free(array_list_t* list)
{
    free(list->data);
    free(list);
}

void
array_list_add(array_list_t* list, const void* element)
{
    list->data = realloc(list->data, (list->length + 1) * list->element_size);

    memcpy(
        list->data + list->element_size * list->length,
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

    list->data = realloc(list->data, list->element_size * (list->length - 1));

    list->length--;
}

void*
array_list_get(array_list_t* list, const u_int32_t index)
{
    return list->data + list->element_size * index;
}

void
array_list_set(array_list_t* list, const u_int32_t index, const void* element)
{
    memcpy(
        array_list_get(list, index),
        element,
        list->element_size);
}
