#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "infgath.h"

void cmd(char *input, char **output){
    FILE *p;
    p = popen(input,"r");    
    if( p == NULL){
        puts("Unable to open process");
    }else{
        *output = (char *)malloc(SIZE_SYS_INFO);
        fgets(*output, SIZE_SYS_INFO, p);        
        pclose(p);
    }
}


void get_system_info(struct system_info *sys_inf){
    cmd("uname -r", &(sys_inf->k_rel));
    cmd("uname -v", &sys_inf->k_ver);
    cmd("uname -p", &sys_inf->p_arch);
    cmd("uname -o", &sys_inf->os);
    cmd("cat /etc/issue", &sys_inf->dist);
}

void display_network_info(){
    printf("\n## Network Information ##\n");
    
    printf("\n --> Interfaces:\n\n");
    system("/sbin/ifconfig -a");
    
    printf("\n --> Routes:\n\n");
    system("route");
    
    printf("\n --> Netstat:\n\n");
    system("netstat -antup | grep -v 'TIME_WAIT'");
}

void scan_installed_tools(){
    // "which awk perl python ruby gcc cc vi vim nmap find netcat nc wget tftp ftp 2>/dev/null"
}