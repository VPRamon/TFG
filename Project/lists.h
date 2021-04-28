/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lists.h
 * Author: oem
 *
 * Created on April 28, 2021, 1:20 AM
 */

#ifndef LISTS_H
#define LISTS_H


typedef struct element_struct{
    void *content;
    int type;
    struct element_struct * next;
    struct element_struct * prev;
}element;

typedef struct list_struct{
    int len;
    element * first_element;
    element * last_element;
    void (*push)();
    void (*pop)();
}list;

void initialize_list();
list *new_list();

#endif /* LISTS_H */

