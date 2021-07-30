#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "display.h"
#include "infgath.h"
#include "utils.h"
#include "exploits.h"

void display_sys_info(struct sys_inf *system_info){
    printf( "##########################################\n"
            "################  SYSTEM  ################\n"
            "##########################################\n\n");
    printf(" [*] Name:\t\t%s\n", system_info->u_name->sysname);
    printf(" [*] User:\t\t%s\n", system_info->u_name->nodename);
    printf(" [*] Kernel release:\t%s\n", system_info->u_name->release);
    printf(" [*] Kernel version:\t%s\n", system_info->u_name->version);
    printf(" [*] Machine arch:\t%s\n", system_info->u_name->machine);
    printf(" [*] Processor:\n");
    printf(" \t[+] Model Name:\t\t%s;\n", system_info->_cpu.model);
    printf(" \t[+] Architecture:\t%s;\n", system_info->_cpu.arch);
    printf(" \t[+] Number of CPUs:\t%u;\n", system_info->_cpu.num_of_cpus);
    printf(" \t[+] Number of Cores\t%u;\n", system_info->_cpu.num_of_cores);
    printf(" \t[+] Number of Sockets:\t%u;\n", system_info->_cpu.num_of_sockets);
    printf(" \t[+] threads per core:\t%u;\n", system_info->_cpu.threadsXcore);
    printf(" \t[+] Security flags:\t");
    if(system_info->_cpu.flags.smep)
        printf(" smep");
    if(system_info->_cpu.flags.smap)
        printf(" smap");
    if(system_info->_cpu.flags.mpx)
        printf(" mpx");
    if(system_info->_cpu.flags.rtm)
        printf(" rtm");
    if(system_info->_cpu.flags.retpoline)
        printf(" retpoline");
    if(system_info->_cpu.flags.retpoline_amd)
        printf(" retpoline_amd");
    if(system_info->_cpu.flags.pti)
        printf(" pti");
    if(system_info->_cpu.flags.misalignsse)
        printf(" misalignsse");
    if(system_info->_cpu.flags.svm)
        printf(" svm");
    
    printf("\n \t[+] Bugs:\t\t");
    if(system_info->_cpu.bugs.f00f)
        printf(" f00f");
    if(system_info->_cpu.bugs.fdiv)
        printf(" fdiv");
    if(system_info->_cpu.bugs.coma)
        printf(" coma");
    if(system_info->_cpu.bugs.amd_tlb_mmatch)
        printf(" amd_tlb_mmatch");
    if(system_info->_cpu.bugs.amd_apic_c1e)
        printf(" amd_apic_c1e");
    if(system_info->_cpu.bugs._11ap)
        printf(" _11ap");
    if(system_info->_cpu.bugs.fxsave_leak)
        printf(" fxsave_leak");
    if(system_info->_cpu.bugs.clflush_monitor)
        printf(" clflush_monitor");
    if(system_info->_cpu.bugs.sysret_ss_attrs)
        printf(" sysret_ss_attrs");
    if(system_info->_cpu.bugs.espfix)
        printf(" espfix");
    if(system_info->_cpu.bugs.null_seg)
        printf(" null_seg");
    if(system_info->_cpu.bugs.swapgs_fence)
        printf(" swapgs_fence");
    if(system_info->_cpu.bugs.monitor)
        printf(" monitor");
    if(system_info->_cpu.bugs.amd_e400)
        printf(" amd_e400");
    if(system_info->_cpu.bugs.cpu_meltdown)
        printf(" cpu_meltdown");
    if(system_info->_cpu.bugs.spectre_v1)
        printf(" spectre_v1");
    if(system_info->_cpu.bugs.spectre_v2)
        printf(" spectre_v2");
    if(system_info->_cpu.bugs.spec_store_bypass)
        printf(" spec_store_bypass");
    
    
    //printf(" \t[+] Max speed (MHz):\t%s;\n", system_info->);
    //printf(" \t[+] threads per core:\t%u;\n", system_info->_cpu.num_of_cores);
}

void display_network_info(){
    printf("##########################################\n"
           "################  NETWORK  ###############\n"
           "##########################################\n");
    char* out;
    out = system_cmd("which ifconfig", 100);
    if(strcmp(out, "")){
        printf("\n[*] Interfaces:\n\n");
        system("/sbin/ifconfig -a");
    }
    free(out);
    
    out = system_cmd("which route", 100);
    if(strcmp(out, "")){
        printf("\n[*] Routes:\n\n");
        system("route");
    }
    free(out);
    
    out = system_cmd("which netstat", 100);
    if(strcmp(out, "")){
        printf("\n[*] Netstat:\n\n");
        system("netstat -antup | grep -v 'TIME_WAIT'");
    }
    free(out);
}

void display_device(struct device dev){
  
    switch (dev.st_mode & S_IFMT) {
        case S_IFBLK:  printf("b "); break;
        case S_IFCHR:  printf("c "); break; 
        case S_IFDIR:  printf("d "); break;
        case S_IFIFO:  printf("p "); break;
        case S_IFLNK:  printf("l "); break;
        case S_IFSOCK: printf("s "); break;
        default:       printf("- "); break;
    }
    // [permissions]
    printf( (dev.st_mode & S_IRUSR) ? " r" : " -");
    printf( (dev.st_mode & S_IWUSR) ? "w" : "-");
    printf( (dev.st_mode & S_IXUSR) ? "x" : "-");
    printf( (dev.st_mode & S_IRGRP) ? "r" : "-");
    printf( (dev.st_mode & S_IWGRP) ? "w" : "-");
    printf( (dev.st_mode & S_IXGRP) ? "x" : "-");
    printf( (dev.st_mode & S_IROTH) ? "r" : "-");
    printf( (dev.st_mode & S_IWOTH) ? "w" : "-");
    printf( (dev.st_mode & S_IXOTH) ? "x" : "-");
    
    printf("\t%lu ", dev.st_nlink); // [number of hard links]
    printf("\t%s ", dev.pw_name);   // [owner] 
    printf("\t%s ", dev.gr_name);   // [group]
    printf("%ld", dev.st_size); // [size in bytes]
    printf(" %s\n", dev.name);    // [device name]
}

void display_devices(list *devices){
    printf( "##########################################\n"
            "################  SYSTEM  ################\n"
            "##########################################\n\n");
    element *p = devices->first_element;
    while(p != NULL){
        struct device *d = p->content;
        display_device(*d);
        p = p->next;
    }
}

void display_modules(){
    system("lsmod");
}

void display_installed_tools(list *tools){
    element *p = tools->first_element;
    while(p != NULL){
        tool *t = p->content;
        if(t->is_installed)
            printf("name: %s,\tdir: %s",t->name, t->dir);
        p = p->next;
    }
}

void display_exploits(list *exploits){
    printf( "##########################################\n"
            "###############  EXPLOITS  ###############\n"
            "##########################################\n\n");
    if(exploits->len>0){
        int i=0;
        element *p = exploits->first_element;
        while(p != NULL){
            struct exploit *xplt = p->content;
            printf("[%d] :: [%s]\t:: %s\n", i++, xplt->type, xplt->title);
            p = p->next;
        }
    }
    else{
        puts("NO EXPLOIT AVAILABLE");
    }
}

void display_exploit(struct exploit *xplt){
    //puts(xplt->path);
    char path[50] = "cat ";
    strcat(path, xplt->path);
    system(path);
}

