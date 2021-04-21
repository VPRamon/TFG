
/* 
 * File:   main.c
 * Author: VPRamon
 *
 * Created on April 21, 2021, 4:17 PM
 */
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>

#include "infgath.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    struct system_info sys_inf;
    system_info(&sys_inf);
    
    printf("%s", sys_inf.k_rel);
    printf("%s", sys_inf.k_ver);
    printf("%s", sys_inf.l_dist);
    printf("%s", sys_inf.p_arch);

    return (EXIT_SUCCESS);
}