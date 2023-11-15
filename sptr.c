#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "sptr.h"

static ref_head *ref_list = NULL;
void sptr_init__() {
    ref_list = (ref_head *)calloc(1, sizeof(ref_head));
    if (ref_list == NULL) {
        perror("mem_ref_init failed");
        abort();
        return;
    }
}

void *make_shared(void *ptr) {
    if (ptr == NULL) {
        return NULL;
    }

    if (ref_list == NULL) {
        sptr_init__();
    }

    ref_node *node = (ref_node *)calloc(1, sizeof(ref_node));
    if (node == NULL) {
        perror("make_shared failed");
        return NULL;
    }

    node->ptr = ptr;
    node->count = 1;
    node->next = ref_list->head;
    ref_list->head = node;

    return ptr;
}

void *ref(void *ptr) {
    for (ref_node *cursor = ref_list->head; cursor != NULL; cursor = cursor->next) {
        if (cursor->ptr == ptr) {
            cursor->count += 1;
            return ptr;
        }
    }

    return NULL;
}

void sptr_clean_up__(void *ptr) {
    void **p = (void **)ptr;
    ref_node *prev = NULL;

    if (ptr == NULL) {
        return;
    }

    if (ref_list == NULL) {
        return;
    }

    for (ref_node *cursor = ref_list->head; cursor != NULL; cursor = cursor->next) {
        if (cursor->ptr == *p) {
            cursor->count -= 1;
            if (cursor->count == 0) {
                free(cursor->ptr);
                if (prev != NULL) {
                    prev->next = cursor->next;
                }

                if (ref_list->head == cursor) {
                    ref_list->head = cursor->next;
                }
                free(cursor);
                break;
            }
        }
        prev = cursor;
    }

    if (ref_list->head == NULL) {
        free(ref_list);
    }
}

