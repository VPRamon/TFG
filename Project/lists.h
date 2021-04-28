/* 
 * File:   lists.h
 * Author: VPRamon
 *
 * Created on April 28, 2021, 1:20 AM
 */

#ifndef LISTS_H
#define LISTS_H

#include <stdbool.h>  

typedef struct element_struct{
    void *content;
    struct element_struct * next;
    struct element_struct * prev;
}element;

typedef struct list_struct{
    int len;
    element * first_element;
    element * last_element;
}list;

list *new_list();
element *new_element(void *content);

void push(list *l, void *content);
void pop(list *l); 

#endif /* LISTS_H */

