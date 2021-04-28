/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lists.h"


element *new_element(void *content){
    element *el = (element *) malloc(sizeof(element));
    el->content = content;
    el->next = NULL;
    el->prev = NULL;
    return el;
}

void function_push(void *content, list *l){
    element *el = new_element(content);
    if(l->len == 0){
        l->first_element = el;
        l->last_element = el;
        l->len++;
    }else if(l->len > 0){
        el->prev = l->last_element;
        l->last_element->next = el;
        l->last_element = el;
        l->len++;
    }
}

void function_pop(list *l){  
    if(l->len == 1){
        free(l->last_element);
        l->last_element = NULL;
        l->first_element = NULL;
        l->len--;
    } if(l->len > 1){
        element *last = l->last_element;
        element *prev = last->prev;
        prev->next = NULL;
        l->last_element = prev;
        free(last);
        l->len--;
    }
}

list *new_list(){
    list *l = (list *) malloc(sizeof(list));
    l->first_element = NULL;
    l->last_element = NULL;
    l->len = 0;
    
    l->push = &function_push;
    l->pop  = &function_pop;
    
    return l;
}