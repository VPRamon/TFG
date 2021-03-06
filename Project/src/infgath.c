#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infgath.h"
#include "utils.h"
#include "display.h"


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


struct cpu_flags get_cpu_flags(){
    
    char *flags_buff = search("flags\t\t: ", "/proc/cpuinfo");
      
    struct cpu_flags flags = {false, false, false, false, false, false, false, false, false};
    
    char *flag = strtok(flags_buff, " ");
    while( flag != NULL ) {
        if(!strncmp(flag, "smep", sizeof("smep")-1))
            flags.smep = true;
        else if(!strncmp(flag, "smap", sizeof("smap")-1))
            flags.smap = true;
        else if(!strncmp(flag, "mpx", sizeof("mpx")-1))
            flags.mpx = true;
        else if(!strncmp(flag, "rtm", sizeof("rtm")-1))
            flags.rtm = true;
        else if(!strncmp(flag, "retpoline", sizeof("retpoline")-1))
            flags.retpoline = true;
        else if(!strncmp(flag, "retpoline_amd", sizeof("retpoline_amd")-1))
            flags.retpoline_amd = true;
        else if(!strncmp(flag, "pti", sizeof("pti")-1))
            flags.pti = true;
        else if(!strncmp(flag, "misalignsse", sizeof("misalignsse")-1))
            flags.misalignsse = true;
        else if(!strncmp(flag, "svm", sizeof("svm")-1))
            flags.svm = true;
        
        flag = strtok(NULL, " ");
    }
    
    free(flags_buff);
    return flags;
}

struct cpu_bugs get_cpu_bugs(){
    
    char *bugs_buff = search("bug", "/proc/cpuinfo");
    
    struct cpu_bugs bugs = {false, false, false, false, false, false, false, false, false, 
                            false, false, false, false, false, false, false, false, false};
    
    char * bug = strtok(bugs_buff, " ");
    while( bug != NULL ) {
        if(!strncmp(bug, "f00f", sizeof("f00f")-1))
            bugs.f00f = true;
        else if(!strncmp(bug, "fdiv", sizeof("fdiv")-1))
            bugs.fdiv = true;
        else if(!strncmp(bug, "coma", sizeof("coma")-1))
            bugs.coma = true;
        else if(!strncmp(bug, "amd_tlb_mmatch", sizeof("amd_tlb_mmatch")-1))
            bugs.amd_tlb_mmatch = true;
        else if(!strncmp(bug, "amd_apic_c1e", sizeof("amd_apic_c1e")-1))
            bugs.amd_apic_c1e = true;
        else if(!strncmp(bug, "_11ap", sizeof("_11ap")-1))
            bugs._11ap = true;
        else if(!strncmp(bug, "fxsave_leak", sizeof("fxsave_leak")-1))
            bugs.fxsave_leak = true;
        else if(!strncmp(bug, "clflush_monitor", sizeof("clflush_monitor")-1))
            bugs.clflush_monitor = true;
        else if(!strncmp(bug, "sysret_ss_attrs", sizeof("sysret_ss_attrs")-1))
            bugs.sysret_ss_attrs = true;
        else if(!strncmp(bug, "espfix", sizeof("espfix")-1))
            bugs.espfix = true;
        else if(!strncmp(bug, "null_seg", sizeof("null_seg")-1))
            bugs.null_seg = true;
        else if(!strncmp(bug, "swapgs_fence", sizeof("swapgs_fence")-1))
            bugs.swapgs_fence = true;
        else if(!strncmp(bug, "monitor", sizeof("monitor")-1))
            bugs.monitor = true;
        else if(!strncmp(bug, "amd_e400", sizeof("amd_e400")-1))
            bugs.amd_e400 = true;
        else if(!strncmp(bug, "cpu_meltdown", sizeof("cpu_meltdown")-1))
            bugs.cpu_meltdown = true;
        else if(!strncmp(bug, "spectre_v1", sizeof("spectre_v1")-1))
            bugs.spectre_v1 = true;
        else if(!strncmp(bug, "spectre_v2", sizeof("spectre_v2")-1))
            bugs.spectre_v2 = true;
        else if(!strncmp(bug, "spec_store_bypass", sizeof("spec_store_bypass")-1))
            bugs.spec_store_bypass = true;
        
        bug = strtok(NULL, " ");
    }
    
    free(bugs_buff);
    return bugs;
}

struct sys_inf *get_system_info(){
    
    struct sys_inf *system_info = (struct sys_inf *)malloc(sizeof(struct sys_inf));
    struct utsname *u_name = (struct utsname *)malloc(sizeof(struct utsname));
    
    int r = uname(u_name);    
    if(r == -1)
    {
        fprintf(stderr,"%s:uname(2)\n",strerror(errno));
        exit(1);
    }
    
    system_info->u_name = u_name;
    
    char *tmp;
    size_t len;
        
    tmp = system_cmd("lscpu | grep '^CPU(s)'", 100);
    len = strlen(tmp);
    {        
        char buff_name[len];
        char buff_value[len];
        sscanf(tmp, "%[^:]:%s", buff_name, buff_value);

        // CHECK IF INTEGER VALUES !!
        system_info->_cpu.num_of_cpus = atoi(buff_value);
    }
    free(tmp);
    
    tmp = system_cmd("lscpu | grep -E '^Core'", 100);
    len = strlen(tmp);
    {
        char buff_name[len];
        char buff_value[len];
        sscanf(tmp, "%[^:]:%s", buff_name, buff_value);
        system_info->_cpu.num_of_cores = atoi(buff_value);
    }
    free(tmp);
    
    
    tmp = system_cmd("lscpu | grep -E '^Thread'", 100);
    len = strlen(tmp);
    {
        char buff_name[len];
        char buff_value[len];
        sscanf(tmp, "%[^:]:%s", buff_name, buff_value);
        system_info->_cpu.threadsXcore = atoi(buff_value);
    } 
    free(tmp);
    
    
    tmp = system_cmd("lscpu | grep -E '^Socket'", 100);
    len = strlen(tmp);
    {
        char buff_name[len];
        char buff_value[len];
        sscanf(tmp, "%[^:]:%s", buff_name, buff_value);
        system_info->_cpu.num_of_sockets = atoi(buff_value);
    }
    free(tmp);
    
    tmp = system_cmd("lscpu | grep -E '^Architecture'", 100);
    len = strlen(tmp);
    {
        char buff_name[len];
        char buff_value[len];
        sscanf(tmp, "%[^:]:\t%[^\n]\n", buff_name, buff_value);
        memcpy(system_info->_cpu.arch, buff_value, 16);
    }
    free(tmp);
    
    tmp = system_cmd("lscpu | grep -E '^Model name'", 100);
    len = strlen(tmp);
    {
        char buff_name[len];
        char buff_value[len];
        sscanf(tmp, "%[^:]:\t%[^\n]\n", buff_name, buff_value);
        memcpy(system_info->_cpu.model, buff_value, 100);
    }
    free(tmp);
    

    system_info->_cpu.flags = get_cpu_flags();
    system_info->_cpu.bugs  = get_cpu_bugs();
    
    return system_info;
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
        out = system_cmd(which, MAX_STRING_SIZE);
        if(strcmp(out, "")){
            tools_struct[i].is_installed = true;
            strcpy(tools_struct[i].dir, out);
        }
        free(out);
        push(tools, &tools_struct[i]);
    }
        
}

void scan_active_devices(list *devices){
    
    struct dirent *dev;
    char buf[512];
    DIR *thedirectory = opendir("/dev");

    while((dev = readdir(thedirectory)) != NULL) 
    {   
        sprintf(buf, "%s/%s", "/dev", dev->d_name);

        struct stat thestat;
        stat(buf, &thestat);
                
        struct passwd *tf = getpwuid(thestat.st_uid);
        struct group *gf = getgrgid(thestat.st_gid);
                
        struct device *d = (struct device *) malloc(sizeof(struct device));
        
        memcpy(d->name, dev->d_name, sizeof(char)*256);
        d->st_mode = thestat.st_mode;
        d->st_nlink = thestat.st_nlink;
        d->st_size = thestat.st_size;
        memcpy(d->pw_name, tf->pw_name, sizeof(char)*50);
        memcpy(d->gr_name, gf->gr_name, sizeof(char)*50);
        
        push(devices, d);
    }
    closedir(thedirectory);
}

struct proc *get_proccessor_info(unsigned int num_of_proc){
    FILE * fp;
    char * line = NULL;
    
    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    struct proc *processors = (struct proc *)malloc(sizeof(struct proc)*num_of_proc);
    
    int pos[num_of_proc];
    for(int i=0; i<num_of_proc;i ++){
        pos[i] = -1;
        processors[i].num_threads = 0;
    }
    
    struct proc temp_proc; temp_proc.num_threads = 0;
    char buff[1024];
    char property[50];
    int id=-1;
    int i;
    while(fscanf(fp, "%[^:]:%[^\n]\n", property, buff)!=EOF){
        if(!strncmp(property,"processor", sizeof("processor")-1 )){
            if(id >= 0){
                for(i=0;i<num_of_proc;i++)
                    if(pos[i] == id || pos[i] == -1) break;
                pos[i] = id;
                if(processors[i].num_threads == 0)
                    processors[i] = temp_proc;
                processors[i].num_threads += 1;
            }
        }
        else if(!strncmp(property,"core id", sizeof("core id")-1 ))
            temp_proc.core_id = id = atoi(buff);
        
        else if(!strncmp(property,"cpu MHz", sizeof("cpu MHz")-1 ))
            temp_proc.cpu_MHz = atof(buff);
        
        else if(!strncmp(property,"cache size", sizeof("cache size")-1 ))
            strncpy(processors[id].cache, buff, 16);
        
        /*else if(!strncmp(property,"processor", sizeof("processor")-1 ))
        else if(!strncmp(property,"processor", sizeof("processor")-1 ))
        else if(!strncmp(property,"processor", sizeof("processor")-1 ))*/
    }
    
    if(id >= 0){
        for(i=0;i<num_of_proc;i++)
            if(pos[i] == id || pos[i] == -1) break;
        pos[i] = id;
        if(processors[i].num_threads == 0)
            processors[i] = temp_proc;
        processors[i].num_threads += 1;
    }
    
    fclose(fp);
    return processors;
}