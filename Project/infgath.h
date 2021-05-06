/* 
 * File:   infgath.h
 * Author: VPRamon
 *
 * Created on December 27, 2020, 3:17 PM
 */

#ifndef INFGATH_H
#define INFGATH_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/utsname.h>

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#include "lists.h"

#define ERR_CODE_PROCESS_FAIL "-1"
#define SIZE_BUFFER_UNAME 10
#define SIZE_SYS_INFO 50
#define NUMBER_OF_TOOLS 15
#define MAX_STRING_SIZE 20
#define N_KNOWN_BUGS 18
#define N_SEC_FLAGS 9
struct proc{
    unsigned int core_id;
    char cache[16];
    float cpu_MHz;
    unsigned int num_threads; 
};

struct cpu_flags{
    bool smep;          // Supervisor Mode Execution Protection
    bool smap;          // Supervisor Mode Access Prevention
    bool mpx;           // Memory Protection Extension
    bool rtm;           // Restricted Transactional Memory
    bool retpoline;     // Retpoline mitigation for Spectre variant 2 (indirect branches)
    bool retpoline_amd; // AMD Retpoline mitigation
    bool pti;           // Kernel Page Table Isolation (Kaiser)
    bool misalignsse;   // indicates if a general-protection exception (#GP) is generated when some legacy SSE instructions operate on unaligned data. Also depends on CR0 and Alignment Checking bit
    bool svm;           // “Secure virtual machine”: AMD-V
};

struct cpu_bugs{
    bool f00f;              // Intel F00F https://en.wikipedia.org/wiki/Pentium_F00F_bug
    bool fdiv;              // CPU FDIV https://en.wikipedia.org/wiki/Pentium_FDIV_bug
    bool coma;              // Cyrix 6x86 coma https://en.wikipedia.org/wiki/Cyrix_coma_bug
    bool amd_tlb_mmatch;    // tlb_mmatch AMD Erratum 383
    bool amd_apic_c1e;      // apic_c1e AMD Erratum 400
    bool _11ap;             // Bad local APIC aka 11AP
    bool fxsave_leak;       // FXSAVE leaks FOP/FIP/FOP
    bool clflush_monitor;   // AAI65, CLFLUSH required before MONITOR
    bool sysret_ss_attrs;   // SYSRET doesn't fix up SS attrs
    bool espfix;            // IRET to 16-bit SS corrupts ESP/RSP high bits
    bool null_seg;          // Nulling a selector preserves the base
    bool swapgs_fence;      // SWAPGS without input dep on GS
    bool monitor;           // IPI required to wake up remote CPU
    bool amd_e400;          // CPU is among the affected by Erratum 400
    bool cpu_meltdown;      // CPU is affected by meltdown attack and needs kernel page table isolation
    bool spectre_v1;        // CPU is affected by Spectre variant 1 attack with conditional branches
    bool spectre_v2;        // CPU is affected by Spectre variant 2 attack with indirect branches
    bool spec_store_bypass; // CPU is affected by the Speculative Store Bypass vulnerability (Spectre variant 4).
};

struct cpu{
    char model[100];
    char arch[8];
    unsigned int num_of_cpus;
    unsigned int num_of_cores;
    unsigned int threadsXcore;
    unsigned int num_of_sockets;
    struct proc cpus_details;
    struct cpu_flags flags;
    struct cpu_bugs bugs;
};

struct sys_inf{
    struct utsname *u_name;
    int num_of_cores;
    struct cpu _cpu;
};

typedef struct tool_struct{
    char name[MAX_STRING_SIZE];
    bool is_installed;
    char dir[MAX_STRING_SIZE];
}tool;

struct device{
    char name[256];
    mode_t st_mode;
    nlink_t st_nlink;
    off_t st_size;
    char pw_name[50];
    char gr_name[50];
};

//void get_system_info(struct system_info *sys_inf);
struct proc *get_proccessor_info();

void scan_installed_tools();
void scan_active_devices(list *devices);

struct sys_inf *get_system_info();

#endif /* INFGATH_H */
