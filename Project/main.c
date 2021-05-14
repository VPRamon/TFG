
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
#include "exploit.h"

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
    char input[10];
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

void start_fuzzing(){
    system("ssh root@localhost -p 2222 -i ./resources/keys/root_id_rsa mkdir /home/fuzz/fuzzer");
    system("scp -P 2222 -i ./resources/keys/root_id_rsa ./fuzzer/fuzzer ./resources/configs/example_module.conf ./resources/configs/run_fuzzer.sh root@localhost:/home/fuzz/fuzzer");
    //system("ssh root@localhost -p 2222 -i ./resources/keys/root_id_rsa nohup /home/fuzz/fuzzer/fuzzer && wait");
    FILE* remf = popen("ssh root@localhost -p 2222 -i ./resources/keys/root_id_rsa /home/fuzz/fuzzer/fuzzer", "w");
    char *A;
    fgets(A);
    // system("scp -P 2222 -i ./resources/keys/root_id_rsa ./resources/configs/example_module.conf root@localhost:/home/fuzz/fuzzer");
    //system("ssh root@localhost -p 2222 -i ./resources/keys/root_id_rsa cat /home/fuzz/fuzzer/bug_report.txt");
}

int main(int argc, char** argv) {
    start_fuzzing();
    /*struct sys_inf *system_info = get_system_info();
    //system_info->processors = get_proccessor_info(system_info->num_of_cores);
    
    list *devices = new_list();
    scan_active_devices(devices);
    
    
    //list *tools = new_list();
    //scan_installed_tools(tools);
    
    //for(int i=0; i<7; i++)
    //    printf("core %d: threads = %d\n",system_info->processors[i].core_id, system_info->processors[i].num_threads);
    
    
    //display_installed_tools(tools);
    
    //menu(system_info, devices);
    printf("%s\n",system_info->u_name->release);
    
    char buffer[_UTSNAME_RELEASE_LENGTH];
    strcpy(buffer, system_info->u_name->release);
    char * flag = strtok(buffer, "-");
    printf("%s\n",flag);
    */
    
    //int err = system("ssh root@localhost -p 2222 -i ./resources/keys/root_id_rsa mkdir /home/fuzz/Desktop/new");
    //syslog_monitor();
    //fuzzing_device("/dev/scull");
    /*FILE * ssh = popen("ssh root@localhost -p 2222 -i ./resources/keys/root_id_rsa", "w");
    //system("ssh root@localhost -p 2222 -i ./resources/keys/root_id_rsa");
    
    char input[100];
    //while(1){
        fgets(input, 100 , stdin);
        fprintf(ssh, input);
        //fputc('\n',ssh);
    
    //}
    fclose(ssh);
    */
    
    
    //struct VM vm = {"./resources/keys/root_id_rsa"};
    
    /* To do list:
     * gdb tools
     * loaded modules
     * software versions
     * Hardware devices
     * running remotely
     * exploits DB
     * ...
     */
    //system("./resources/vm/run \"/home/oem/Desktop/gitRepos/TFG/VM/ubuntu-desktop/ubuntu-21-04.img\"");
    
    //struct modconfig *modconf = load_config("./resources/configs/example_module.conf");
    
    //element *p = modconf->ioctlcmds->first_element->next;
    //struct ioctlcmd *cmd = p->content;
    //printf("%d, %d, %d",cmd->id, cmd->in_dtype, cmd->type );

    //create_new_syscall("scull", 'c', IOCTL, cmd, "TEST", 5);
    
    return (EXIT_SUCCESS);
}
