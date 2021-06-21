/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fuzzer.h
 * Author: oem
 *
 * Created on May 12, 2021, 12:48 AM
 */

#ifndef FUZZER_H
#define FUZZER_H

#include <stdbool.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include "../../src/headers/lists.h"

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )
#define ALERT_BUF_LEN 1024
#define KASAN_BUG 1
#define KASAN_BUG 1

#define SYSLOG_DIR "/var/log/syslog"

#define IO      0
#define IOW     1
#define IOR     2
#define IOWR    3

#define DT_INT  0

#define ERR_OPEN_MODULE -1

#define KCOV_INIT_TRACE			_IOR('c', 1, unsigned long)
#define KCOV_ENABLE			_IO('c', 100)
#define KCOV_DISABLE			_IO('c', 101)
#define COVER_SIZE			(64<<10)

#define KCOV_TRACE_PC  0
#define KCOV_TRACE_CMP 1

#define WRITE   0
#define READ    1
#define IOCTL   2
#define LLSEEK  3

#define CODE_PREFIX "#include <stdio.h>\n\
#include <stdlib.h>\n\
#include <string.h>\n\
#include <fcntl.h>\n\
#include <unistd.h>\n\
#include <sys/ioctl.h>\n\
#define ERR_OPEN_MODULE -1\n\n\
int main(void){\n"
                    

#define CODE_MIDDLE "\tif(fd < 0){\n\
        return ERR_OPEN_MODULE;\n\
    }\n\
    int out;\n"

#define CODE_SUFIX  "\tclose(fd);\n\
    return out;\n}"

struct ioctlcmd{
    int op_type;
    int id;
    char in_dtype[5];
};

struct fileOperations{
    bool llseek;
    bool read;
    bool write;
    bool ioctl;
};

struct modconfig{
    char *name;
    struct fileOperations fops;
    char iocmagic;
    list *ioctlcmds;
};

    
struct modconfig *load_config();
int create_new_syscall(char* dev, char magic, int syscall, struct ioctlcmd *cmd, char *input, int count);


#endif /* FUZZER_H */

