
typedef struct
{
    void* data;
    size_t element_size;
    u_int32_t length;
} array_list_t;

array_list_t *array_list_create(const size_t element_size);
void array_list_free(array_list_t* list);
void array_list_add(array_list_t* list, const void* element);
void array_list_remove(array_list_t* list, const u_int32_t index);
void *array_list_get(array_list_t* list, const u_int32_t index);
void array_list_set(array_list_t* list, const u_int32_t index, const void* element);
