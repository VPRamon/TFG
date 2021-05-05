/* 
 * File:   infgath.h
 * Author: VPRamon
 *
 * Created on December 27, 2020, 3:17 PM
 */

#ifndef INFGATH_H
#define INFGATH_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#include "lists.h"

#define ERR_CODE_PROCESS_FAIL "-1"
#define SIZE_BUFFER_UNAME 10
#define SIZE_SYS_INFO 50

#define NUMBER_OF_TOOLS 15
#define MAX_STRING_SIZE 20

struct system_info{
    char* k_rel;
    char* k_ver;
    char* p_arch;
    char* os;
    char* dist;
};

typedef struct tool_struct{
    char name[MAX_STRING_SIZE];
    bool is_installed;
    char dir[MAX_STRING_SIZE];
}tool;

struct device{
    char name[256];
    mode_t st_mode;
    nlink_t st_nlink;
    off_t st_size;
    char pw_name[50];
    char gr_name[50];
};


void get_system_info(struct system_info *sys_inf);
void display_network_info();
void scan_installed_tools();
void scan_active_devices(list *devices);
void display_device(struct device dev);
    
#endif /* INFGATH_H */
