//
// Created by oleg on 11.10.23.
//

#ifndef XV6_RISCV_BUDDY_H
#define XV6_RISCV_BUDDY_H
#include "list.h"
typedef struct list Bd_list;
struct sz_info {
    Bd_list free;
    char *alloc;
    char *split;
};
void bd_init(void *base, void *end);
void bd_mark(void *start, void *stop);
void *bd_malloc(uint64 nbytes);
void bd_free(void *p);
#endif //XV6_RISCV_BUDDY_H
