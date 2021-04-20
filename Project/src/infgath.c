/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "infgath.h"



void uname(char *flag, char **var){
   
    char *syscall = (char *)malloc(SIZE_BUFFER_UNAME);
    
    strcpy(syscall,  "uname -");    
    
    strcat(syscall, flag);
    
    FILE *p;
    p = popen(syscall,"r");    
    if( p == NULL){
        puts("Unable to open process");
    }else{
        *var = (char *)malloc(SIZE_SYS_INFO);
        fgets(*var, SIZE_SYS_INFO, p);        
        pclose(p);
    }
}

void system_info(struct system_info *sys_inf){
    
    uname("r", &(sys_inf->k_rel));
    uname("v", &sys_inf->k_ver);
    uname("n", &sys_inf->l_dist);
    uname("p", &sys_inf->p_arch);
    
}
