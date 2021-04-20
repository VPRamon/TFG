/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: oem
 *
 * Created on December 27, 2020, 3:11 PM
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

