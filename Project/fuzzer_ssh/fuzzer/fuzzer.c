#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <sys/mman.h>
#include <string.h>

#include "fuzzer.h"


pthread_t tid;
int bug_detected = 0;

struct modconfig *load_config(){
    
    struct modconfig *modconf = (struct modconfig *)malloc(sizeof(struct modconfig));
    struct fileOperations fops = {false,false,false,false};
    modconf->fops = fops;
    modconf->ioctlcmds = NULL;
    
    int lvl = 0;
    FILE *fp = fopen("/tmp/fuzzer/device.conf", "r");
    if (fp == NULL){
        puts("ERROR LOADING CONFIGFILE");
        exit(EXIT_FAILURE);
    }
    size_t len = 0;
    char * line = NULL;
    ssize_t read;
    char opt[1000];
    char buf[1000];
    
    while ((read = getline(&line, &len, fp)) != -1){
        sscanf(line, "%[^:]:%s", opt, buf);
        if(opt[0] == '{' || opt[0] == '}')
            continue;
        
        else if(!strncmp(opt, "\tname", sizeof("\tname"))){
            char *name = (char *)malloc(sizeof(char)*(len-5));
            strncpy(name, buf, len-5);
            modconf->name = name;
        }
        
        else if(!strncmp(opt, "\tfile_operations", sizeof("\tfile_operations"))){
            char * op = strtok(buf, ";");
            while( op != NULL ) {
                if(!strncmp(op, "llseek", sizeof("llseek")))
                    modconf->fops.llseek = true;
                else if(!strncmp(op, "read", sizeof("read")))
                    modconf->fops.read = true;
                else if(!strncmp(op, "write", sizeof("write")))
                    modconf->fops.write = true;
                else if(!strncmp(op, "unlocked_ioctl", sizeof("unlocked_ioctl"))){
                    modconf->fops.ioctl = true;
                    modconf->ioctlcmds = new_list();
                }
                
                op = strtok(NULL, ";");
            }
        }
        
        else if(!strncmp(opt, "\tioc_magic", sizeof("\tioc_magic")))
            modconf->iocmagic = buf[0];
        
        else if(!strncmp(opt, "\tioctl_cmd", sizeof("\tioctl_cmd"))){
            char op_type[5];
            char in_dtype[5];
            char id[3];

            read = getline(&line, &len, fp);
            while(line[1] != '}'){
                sscanf(line, "\t\t%[^;];%[^;];%s", op_type, id, in_dtype);
                
                struct ioctlcmd *cmd = (struct ioctlcmd *)malloc(sizeof(struct ioctlcmd));

                cmd->id = atoi(id);
                
                if(!strncmp(op_type, "IO", sizeof("IO")))
                    cmd->op_type = IO;
                else if(!strncmp(op_type, "IOR", sizeof("IOR")))
                    cmd->op_type = IOR;
                else if(!strncmp(op_type, "IOW", sizeof("IOW")))
                    cmd->op_type = IOW;
                else if(!strncmp(op_type, "IOWR", sizeof("IOWR")))
                    cmd->op_type = IOWR;
                
                strcpy(cmd->in_dtype, in_dtype);
                
                push(modconf->ioctlcmds, cmd);
                
                read = getline(&line, &len, fp);
            }
            
        }
            
    }
    
    fclose(fp);
    if (line)
        free(line);
    return modconf;
}

int parse(char * string){
    char t1[50], t2[ALERT_BUF_LEN];
    sscanf(string, "%[^=]%[^\n]\n", t1, t2);
    if(!strncmp(t2, "==================================================================", 10))
        return KASAN_BUG;
    return 0;
}

void report_bug(FILE **fd_read){
    FILE *fd_rep;
    if( (fd_rep = fopen("/tmp/fuzzer/bug_report.txt", "a")) < 0) {
        perror("Problem in opening the file in append mode");
        exit(1);
    }
    char buf[ALERT_BUF_LEN];
    fgets(buf, sizeof(buf), *fd_read);
    while(parse(buf) != KASAN_BUG){
        fputs(buf, fd_rep);
        fgets(buf, ALERT_BUF_LEN, *fd_read);
    }
    fclose(fd_rep);
}

void *syslog_monitor()
{
    int length, i = 0;
    int nbytes;
    int fd_inot;
    FILE *fd_read;
    int wd;
    char buffer[EVENT_BUF_LEN];
    char buf[ALERT_BUF_LEN];
    // Monitor SYSLOG file 
    fd_inot = inotify_init();
    if( fd_inot < 0 )
        perror( "inotify_init error" );
    wd = inotify_add_watch( fd_inot, SYSLOG_DIR, IN_MODIFY );
    
    // Catch new SYSLOG messages 
    fd_read = fopen(SYSLOG_DIR, "r" );
    if( !fd_read )
        perror("open(SYSLOG) failed");

    // Go to End of file
    if( fseek(fd_read, 0, SEEK_END)<0 )
        perror("fseek() failed");
    
    while(1){
        // For each new system message, copy to buf
        length = read( fd_inot, buffer, EVENT_BUF_LEN ); 
        // checking for error 
        if ( length < 0 )
              perror( "read(inotify) failed" );
        
        while(fgets(buf, sizeof(buf), fd_read) != NULL){
            if(parse(buf) == KASAN_BUG){
                report_bug(&fd_read);
                inotify_rm_watch( fd_inot, wd );
                close( fd_inot );
                fclose( fd_read );
                bug_detected = KASAN_BUG;
                return (void *)KASAN_BUG;
            }
        }
        
        if( fseek(fd_read, 0, SEEK_END)<0 )
            perror("fseek() failed");
    }
    
    inotify_rm_watch( fd_inot, wd );
    close( fd_inot );
    fclose( fd_read );
    return (void *)0;    
}

/*void *create_new_syscall()
{   
    sleep(1);
    char dev[] = "/dev/scull";
    int fd = open(dev, O_RDWR);
    if (fd < 0) {
        printf("[-] open %s failed\n", dev);
        exit(0);
    }

    write(fd, "AAAAABBBBBAAAAA", 15);

    close(fd);
}*/


int kcov_fd;
unsigned long *cover;

void init_kcov(void)
{
	kcov_fd = open("/sys/kernel/debug/kcov", O_RDWR);
	if (kcov_fd == -1) {
		perror("open");
		exit(1);
	}

	/* Setup trace mode and trace size. */
	if (ioctl(kcov_fd, KCOV_INIT_TRACE, COVER_SIZE)) {
		perror("ioctl");
		exit(1);
	}

	/* Mmap buffer shared between kernel- and user-space. */
	cover = (unsigned long*)mmap(NULL, COVER_SIZE * sizeof(unsigned long), PROT_READ | PROT_WRITE, MAP_SHARED, kcov_fd, 0);
	if ((void*)cover == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
}

void close_kcov(void)
{
	/* Free resources. */
	if (munmap(cover, COVER_SIZE * sizeof(unsigned long))) {
		perror("munmap");
		exit(1);
	}
	if (close(kcov_fd)) {
		perror("close");
		exit(1);
	}
}

void start_kcov(void)
{
	/* Enable coverage collection on the current thread. */
	if (ioctl(kcov_fd, KCOV_ENABLE, KCOV_TRACE_PC)) {
		perror("ioctl");
		exit(1);
	}

	/* Reset coverage from the tail of the ioctl() call. */
	__atomic_store_n(&cover[0], 0, __ATOMIC_RELAXED);
}

void stop_kcov(void)
{
	unsigned long n;

	/* Read number of PCs collected. */
	n = __atomic_load_n(&cover[0], __ATOMIC_RELAXED);
	printf("Coverage (The number of PCs) : %ld\n", n);

	/* Disable coverage collection for the current thread. After this call
	 * coverage can be enabled for a different thread.
	 */
	if (ioctl(kcov_fd, KCOV_DISABLE, 0)) {
		perror("ioctl");
		exit(1);
	}
}

int create_new_syscall(char* dev, char magic, int syscall, struct ioctlcmd *cmd, char *input, int count)
{   
    remove("fuzz.c");
    int fd = open("fuzz.c", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if(fd < 0)
        return ERR_OPEN_MODULE;
    
    char *buff = (char*)malloc(count+512);
    
    write(fd, CODE_PREFIX, strlen(CODE_PREFIX));
    sprintf(buff, "\tint fd = open(\"%s\", O_WRONLY);\n", dev);
    write(fd, buff, strlen(buff));
    write(fd, CODE_MIDDLE, strlen(CODE_MIDDLE));
    
    switch(syscall){
        case(WRITE):
            sprintf(buff, "\tout = write(fd, \"%s\", %d);\n", input, count);
            write(fd, buff, strlen(buff));
            break;
            
        case(READ):
            sprintf(buff, "\tvoid *tmp = malloc(count);\n\tread(fd, tmp, %d);\n", count);
            write(fd, buff, strlen(buff));
            break;
            
        case(IOCTL):
            switch(cmd->op_type){
                case IO:
                    sprintf(buff, "\tout = ioctl(fd, _IO(\'%c\',%d));\n", magic, cmd->id);
                    write(fd, buff, strlen(buff));
                    break;
                    
                case IOW:
                    sprintf(buff, "\tout = ioctl(fd, _IOW(\'%c\',%d, %s), \"%s\");\n", magic, cmd->id, cmd->in_dtype, input);
                    write(fd, buff, strlen(buff));
                    break;
                 
                case IOR:
                    sprintf(buff, "\tout = ioctl(fd, _IOW(\'%c\',%d, %s), \"%s\");\n", magic, cmd->id, cmd->in_dtype, input);
                    write(fd, buff, strlen(buff));
                    break;
                    
                case IOWR:
                    sprintf(buff, "\tout = ioctl(fd, _IOW(\'%c\',%d, %s), \"%s\");\n", magic, cmd->id, cmd->in_dtype, input);
                    write(fd, buff, strlen(buff));
                    break;
            }
            
            break;
            
        case(LLSEEK):
            //do write
            break;
    }
    
    write(fd, CODE_SUFIX, strlen(CODE_SUFIX));
    close(fd);
}

int main(){
    
    struct modconfig *modconf = load_config();
      
    
    char dev[] = "/dev/";
    strcat(dev,modconf->name);
    
    if(access( dev, F_OK )) {
        puts("Device not found");
        exit(1);
    }
    
    char magic;
    int num_of_cmd = 0;
    if(modconf->fops.ioctl){
        num_of_cmd = modconf->ioctlcmds->len;
        magic = modconf->iocmagic;
    }
    
    int syscall;
    int cmd;
    char *input;
    int count = 0;
    srand(time(0));
    
    //init_kcov();
    int err = pthread_create(&tid, NULL, &syslog_monitor, NULL);
    while(bug_detected != KASAN_BUG){
        
        // increase input
        count++;
        
        //create new instructions;
        input = (char*)malloc(count);
        memset(input, 'A', count);
        
        syscall = (rand() % (4));
        
        //create_new_syscall;
        for(int i=0; i<4; i++){
            if((syscall == WRITE) && modconf->fops.write){
                create_new_syscall(dev, magic, syscall, NULL, input, count);
            }else if((syscall == READ) && modconf->fops.read){
                create_new_syscall(dev, magic, syscall, NULL, input, count);
            }else if((syscall == IOCTL) && modconf->fops.ioctl){
                cmd = (rand() % (num_of_cmd));  // get cmd form list randomly
                create_new_syscall(dev, magic, syscall, NULL, input, count);
            }else if((syscall == LLSEEK) && modconf->fops.llseek){
                create_new_syscall(dev, magic, syscall, NULL, input, count);
            }else{
                syscall += 1;
                syscall = syscall%4;
            }
        }
        
        //compile;
        system("gcc fuzz.c -o fuzz.out");
        
        
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        
        //execute
        //start_kcov();
        int out = system("./fuzz.out");
        //stop_kcov();
        
        
        free(input);
    }
    
    //close_kcov();

    exit(0);
}
