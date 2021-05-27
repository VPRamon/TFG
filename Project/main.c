
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

void mod_info_menu(){
    system("clear");
    display_modules();
    printf("\n\n<< press any key to go back");
    fgetc(stdin);
}

void fuzzer_menu(){
    system("clear");
    printf("First you must give some information about the device to be fuzzed.\n"
         "Do you want modify the device.conf file [y/n/q]? ");
    char input[10];
    fgets(input, 10 , stdin);
    while(input[0] != 'y' && input[0] != 'n' && input[0] != 'q'){
        printf("\n'y' to continue, 'n' to go back.");
        fgets(input, 10 , stdin);
    }
      
    if(input[0] == 'y'){
        system("vim resources/configs/device.conf");
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
            system("python3 fuzzer_ssh/main.py");
            system("clear");
            system("cat resources/bug_reports/bug_report.txt");
            printf("\n\n<< press any key to go back");
            fgetc(stdin);
        }
    }
}

void exploits_menu(struct sys_inf *system_info){
    
    system("clear");
    printf("[0] Default search\n"
           "[1] Personalized Search\n"
           "[2] Load exploit");
    
    list *exploits;
    char input[10];
    int _input;
    printf("\n>> Select an option [0-%d]: ", 2);
    fgets(input, 10 , stdin);
    _input = valid_input(input[0], 3);
    
    switch(_input){
        case 0:
            system("clear");
            char *r = parse_release(system_info->u_name->release);
            exploits = search_exploit(r);
            display_exploits(exploits);
            goto opt;
            //free_exploits(exploits);
            break;
            
        case 1:
            system("clear");
            printf("Search exploit: ");
            char in[20];
            fgets(in, 20 , stdin);
            exploits = search_exploit(in);
            goto opt;
            //free_exploits(exploits);
            break;
        
        case 2:
            system("clear");
            printf("Give the path to the exploit: ");
            char path[100];
            fgets(path, 100 , stdin);
            char *dir = strtok(path, "\n");
            while(access( dir, F_OK ) != 0 ) {
                puts(dir);
                printf("Exploit not found! Make sure the path is correct and try again [q/quit]: ");
                fgets(path, 50 , stdin);
                dir = strtok(path, "\n");
                if(path[0] == 'q')
                    return;
            }
            
            exploits = new_list();
            load_exploit(exploits, path);
            goto opt;
            //free_exploits(exploits);
            break;
    }  
    
    opt:
        if(exploits->len == 0)
            return;
        system("clear");
        display_exploits(exploits);
        printf("\n>> Pick exploit [0-%d]/[q]: ", exploits->len-1);
        char index[5];
        fgets(index, 5 , stdin);

        if(index[0] == 'q')
            return;

        element *el = get_element_from_list(exploits, atoi(index));
        struct exploit *xplt = (struct exploit *)el->content; 


        printf("\n\n[0] View exploit\n"
               "[1] Edit exploit\n"
               "[2] Change exploit\n"
               "[q] Quit\n");            

        printf("\n>> Select an option [0-%d]: ", 3);
        fgets(input, 10 , stdin);
        if(input[0] == 'q')
            return;
        _input = valid_input(input[0], 3);


        switch(_input){
            case 0:
                system("clear");
                display_exploit(xplt);
                printf("\n\n<< press any key to go back");
                fgetc(stdin);
                goto opt;
                break;

            case 1:
                system("clear");
                edit_exploit(xplt);
                goto opt;
                break;

            case 2:
                goto opt;
                break;
        }
    
        printf("\n\n<< press any key to go back");
        fgetc(stdin);
}

void menu(struct sys_inf *system_info){
    char input[10];
    int _input;
    
    list *devices;//, *exploits;
    //char *r;
    
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
                mod_info_menu();
                break;
                
            case RUNNING_DEVICES:
                devices = new_list();
                scan_active_devices(devices);
                dev_info_menu(devices);
                break;
                
            case FUZZER:
                fuzzer_menu();
                break;
                
            case DEBUGGER:
                break;

            case EXPLOIT:
                //r = parse_release(system_info->u_name->release);
                //exploits = search_exploit(r);
                exploits_menu(system_info);
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
    //start_fuzzing();
   
    struct sys_inf *system_info = get_system_info();
    
    //list *tools = new_list();
    //scan_installed_tools(tools);
    //display_installed_tools(tools);
    
    menu(system_info);
    
    
    //printf("%s\n",system_info->u_name->release);
    /*
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
