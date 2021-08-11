
/* 
 * File:   main.c
 * Author: VPRamon
 *
 * Created on April 21, 2021, 4:17 PM
 */
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>

#include "infgath.h"
#include "lists.h"
#include "display.h"
#include "utils.h"
#include "exploits.h"

/*
 * 
 */

void fuzzer_menu(){
    system("clear");
    printf("First you must give some information about the device to be fuzzed.\n"
         "Do you want modify the device.conf file [y/n/q]? ");
    char *input;
    input = read_stdin();
    while(input[0] != 'y' && input[0] != 'n' && input[0] != 'q'){
        printf("\n'y' to continue, 'n' to go back.");
        fgets(input, 10 , stdin);
    }
      
    if(input[0] == 'y'){
        system("vim ../resources/configs/device.conf");
        system("clear");
    }else if(input[0] == 'n'){
        printf("Make sure the VM is up, and your ssh key is in resources/keys.\n"
         "Do you want to continue [y/n]? ");
        fgets(input, 10 , stdin);
        while(input[0] != 'y' && input[0] != 'n'){
            printf("\n'y' to continue, 'n' to go back.");
            fgets(input, 10 , stdin);
        }
        if(input[0] == 'y'){
            system("python3 ../fuzzer_ssh/main.py");
            system("clear");
            system("cat ../resources/bug_reports/bug_report.txt");
            printf("\n\n<< press any key to go back");
            fgetc(stdin);
        }
    }
    free(input);
}


void menu(struct sys_inf *system_info){
    
    char *input;
    int _input;
    list *devices = new_list();;
    
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
                " [5] Exploitation lab\n"
                " [q|Q] Quit\n");
        
        printf("\n>> Select an option [0-%d]: ", MENU_OPTIONS-1);
        input = read_stdin();
        _input = valid_input(input[0], MENU_OPTIONS);
        free(input);
        
        switch(_input){
            
            case SYS_INFO:
                sys_info_menu(system_info);
                break;
                
            case NET_INFO:
                net_info_menu();
                break;
            
            case RUNNING_MODULES:
                mod_info_menu();
                break;
                
            case RUNNING_DEVICES:
                scan_active_devices(devices);
                dev_info_menu(devices);
                break;
                
            case FUZZER:
                fuzzer_menu();
                break;

            case EXPLOIT:
                exploits_menu(system_info);
                break;
             
            case EXIT_MENU:
                exit(0);

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
       
    menu(system_info);
    
    return (EXIT_SUCCESS);
}
