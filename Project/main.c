
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
    printf("\n\n<< press any key to go back");
    fgetc(stdin);
}

void net_info_menu(){
    system("clear");
    display_network_info();
    printf("\n\n<< press any key to go back");
    fgetc(stdin);
}

void dev_info_menu(list *devices){
    system("clear");
    display_devices(devices);
    printf("\n\n<< press any key to go back");
    fgetc(stdin);
}

void menu(struct sys_inf *system_info, list *devices){
    char input[2];
    int _input;
    
    while(true){
        system("clear");
        printf( "##########################################\n"
                "################  MENU  ##################\n"
                "##########################################\n\n"
                " [0] System Information\n"
                " [1] Network Details\n"
                " [2] Modules\n"
                " [3] Devices\n"
                " [4] Fuzzer\n"
                " [5] Debugger\n"
                " [6] Exploitation lab\n"
                " [q|Q] Quit\n");
        
        printf("\n>> Select an option [0-%d]: ", MENU_OPTIONS-1);
        fgets(input, 10 , stdin);
        _input = valid_input(input[0], MENU_OPTIONS);
        switch(_input){
            case SYS_INFO:
                sys_info_menu(system_info);
                break;
                
            case NET_INFO:
                net_info_menu();
                break;
            
            case RUNNING_MODULES:
                break;
                
            case RUNNING_DEVICES:
                dev_info_menu(devices);
                break;
                
            case FUZZER:
                break;
                
            case DEBUGGER:
                break;

            case EXPLOIT:
                break;
             
            case EXIT_MENU:
                exit(0);
                break;

            default:
                system("clear");
                printf("The input must be an integer from [0-%d]: ", MENU_OPTIONS-1);
                printf("\n<< press any key to continue >>");
                fgetc(stdin);
                break;
        }
    }
}

int main(int argc, char** argv) {
    
    struct sys_inf *system_info = get_system_info();
    //system_info->processors = get_proccessor_info(system_info->num_of_cores);
    
    list *devices = new_list();
    scan_active_devices(devices);
    
    
    list *tools = new_list();
    scan_installed_tools(tools);
    /*
    /*for(int i=0; i<7; i++)
        printf("core %d: threads = %d\n",system_info->processors[i].core_id, system_info->processors[i].num_threads);
    */
    
    //display_installed_tools(tools);
    
    menu(system_info, devices);
    
    
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
