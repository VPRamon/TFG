/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   infgath.h
 * Author: oem
 *
 * Created on December 27, 2020, 3:17 PM
 */

#ifndef INFGATH_H
#define INFGATH_H

#define ERR_CODE_PROCESS_FAIL "-1"
#define SIZE_BUFFER_UNAME 10
#define SIZE_SYS_INFO 50


struct system_info{
    char* k_rel;
    char* k_ver;
    char* p_arch;
    char* l_dist;
};


void system_info(struct system_info *sys_inf);


#endif /* INFGATH_H */

