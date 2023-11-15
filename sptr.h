#include <stdlib.h>

#define smart __attribute__ ((__cleanup__(sptr_clean_up__)))

typedef struct mem_node_t {
    void *ptr;
    size_t count;
    struct mem_node_t *next;
} ref_node;

typedef struct mem_head_t {
    struct mem_node_t *head;
} ref_head;

void *make_shared(void *);
void *ref(void *);
void sptr_clean_up__(void *);