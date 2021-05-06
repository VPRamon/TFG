
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
#include "lists.h"
#include "display.h"
#include "utils.h"

/*
 * 
 */
void sys_info_menu(struct sys_inf *system_info){
    system("clear");
    
    display_sys_info(system_info);
    printf("<< press any key to continue >>");
    fgetc(stdin);
}

void menu(struct sys_inf *system_info){
    char input[2];
    int _input;
    
    while(true){
        system("clear");
        printf( "##########################################\n"
                "################  MENU  ##################\n"
                "##########################################\n\n"
                "[0] System Information\n"
                "[1] Fuzz Module\n"
                "[2] Manual Debug\n"
                "[3] Exploitation lab\n");
        
        printf("Select an option [0-3]:\t");
        fgets(input, 10 , stdin);
        _input = valid_input(input[0], 4);
        switch(_input){
            case SYS_INFO:
                sys_info_menu(system_info);
                break;

            case FUZZER:
                break;
                
            case DEBUGGER:
                break;

            case EXPLOIT:
                break;

            default:
                system("clear");
                printf("The input must be an integer from 0 to 1!\n");
                printf("<< press any key to continue >>");
                fgetc(stdin);
                break;
        }
    }
}

int main(int argc, char** argv) {
    
    
    struct sys_inf *system_info = get_system_info();
    //system_info->processors = get_proccessor_info(system_info->num_of_cores);
    /*
    list *devices = new_list();
    scan_active_devices(devices);
    
    list *tools = new_list();
    scan_installed_tools(tools);
    
    
    /*for(int i=0; i<7; i++)
        printf("core %d: threads = %d\n",system_info->processors[i].core_id, system_info->processors[i].num_threads);
    *///display_network_info();
    
    //display_devices(devices);

    
    //display_installed_tools(tools);
    
   
    //menu(system_info);
    display_sys_info(system_info);
    
    
    //int err = system("ssh root@localhost -p 2222 -i ./resources/keys/root_id_rsa mkdir /home/fuzz/Desktop/new");
    /*
    
   
    
   
    
    /* To do list:
     * gdb tools
     * loaded modules
     * software versions
     * Hardware devices
     * running remotely
     * exploits DB
     * ...
     */

    return (EXIT_SUCCESS);
}
