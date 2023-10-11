//
// Created by oleg on 11.10.23.
//

#ifndef XV6_RISCV_LIST_H
#define XV6_RISCV_LIST_H
struct list {
    struct list *next;
    struct list *prev;
};

// list.c
void lst_init(struct list*);
void lst_remove(struct list*);
void lst_push(struct list*, void *);
void *lst_pop(struct list*);
void lst_print(struct list*);
int lst_empty(struct list*);
#endif //XV6_RISCV_LIST_H
