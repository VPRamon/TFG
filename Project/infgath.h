/* 
 * File:   infgath.h
 * Author: VPRamon
 *
 * Created on December 27, 2020, 3:17 PM
 */

#ifndef INFGATH_H
#define INFGATH_H

#define ERR_CODE_PROCESS_FAIL "-1"
#define SIZE_BUFFER_UNAME 10
#define SIZE_SYS_INFO 50

#define NUMBER_OF_TOOLS 15
#define MAX_STRING_SIZE 10

struct system_info{
    char* k_rel;
    char* k_ver;
    char* p_arch;
    char* os;
    char* dist;
};

struct tool{
    char name[MAX_STRING_SIZE];
    bool is_installed = false;
};

const char tools[NUMBER_OF_TOOLS][MAX_STRING_SIZE] =
    {   
        "awk",
        "perl",
        "python",
        "ruby",
        "gcc",
        "cc",
        "vi",
        "vim",
        "nmap",
        "find",
        "netcat",
        "nc",
        "wget",
        "tftp",
        "ftp",
    };

void get_system_info(struct system_info *sys_inf);
void display_network_info();
void scan_installed_tools();
#endif /* INFGATH_H */
