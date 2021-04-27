#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "infgath.h"

void cmd(char *input, char **output){

    FILE *p;
    p = popen(input,"r");    
    if( p == NULL){
        puts("Unable to open process");
    }else{
        *output = (char *)malloc(SIZE_SYS_INFO);
        fgets(*output, SIZE_SYS_INFO, p);        
        pclose(p);
    }
}


void system_info(struct system_info *sys_inf){
    
    cmd("uname -r", &(sys_inf->k_rel));
    cmd("uname -v", &sys_inf->k_ver);
    cmd("uname -p", &sys_inf->p_arch);
    cmd("uname -o", &sys_inf->os);
    cmd("cat /etc/issue", &sys_inf->dist);
    
}