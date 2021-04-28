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
    cmd("uname -r", &sys_inf->k_rel);
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

void scan_installed_tools(list *tools){

    tool *tools_struct = (tool *) malloc(sizeof(tool)*NUMBER_OF_TOOLS);
    
    tools_struct[0]  = (tool){"awk",    false};
    tools_struct[1]  = (tool){"perl",   false};
    tools_struct[2]  = (tool){"python", false};
    tools_struct[3]  = (tool){"ruby",   false};
    tools_struct[4]  = (tool){"gcc",    false};
    tools_struct[5]  = (tool){"cc",     false};
    tools_struct[6]  = (tool){"vi",     false};
    tools_struct[7]  = (tool){"vim",    false};
    tools_struct[8]  = (tool){"nmap",   false};
    tools_struct[9]  = (tool){"find",   false};
    tools_struct[10] = (tool){"netcat", false};
    tools_struct[11] = (tool){"nc",     false};
    tools_struct[12] = (tool){"wget",   false};
    tools_struct[13] = (tool){"tftp",   false};
    tools_struct[14] = (tool){"ftp",    false};
           
    char which[MAX_STRING_SIZE+6];
    char* out;    
    for(int i=0;i<NUMBER_OF_TOOLS;i++){
        sprintf(which, "which %s", tools_struct[i].name);
        cmd(which, &out);
        if(strcmp(out, "")){
            tools_struct[i].is_installed = true;
            strcpy(tools_struct[i].dir, out);
        }
        push(tools, &tools_struct[i]);
    }
        
}