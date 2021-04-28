
/* 
 * File:   main.c
 * Author: VPRamon
 *
 * Created on April 21, 2021, 4:17 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>  
//#include <unistd.h>

#include "infgath.h"
#include "lists.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    /*
    struct system_info sys_inf;
    get_system_info(&sys_inf);
    
    printf("Kernel release: %s", sys_inf.k_rel);
    printf("Kernel version: %s", sys_inf.k_ver);
    printf("Processor's architecture: %s", sys_inf.p_arch);
    printf("O.S.: %s", sys_inf.os);
    printf("Distribution.: %s", sys_inf.dist);
    */
    //display_network_info();
    
    //int err = system("ssh root@localhost -p 2222 -i ./resources/keys/root_id_rsa mkdir /home/fuzz/Desktop/new");
    
    //scan_installed_tools();
    
    
    list *l = new_list();
    
    l->push(1,l);
    l->push(2,l);
    l->push(7,l);
    l->pop(l);
    l->push(6,l);
    l->push(5,l);
    element *p = l->first_element;
    while(p != NULL){
        printf("%d\n",(int)p->content);
        p = p->next;
    }
    
    //l->first_element = (element *) malloc(sizeof(element));
    /* To do list:
     * gdb tools
     * loaded modules
     * software versions
     * Hardware devices
     * running remotely
     * ...
     */
    
    return (EXIT_SUCCESS);
}
