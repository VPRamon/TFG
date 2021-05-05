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


void display_device(struct device dev){
  
    switch (dev.st_mode & S_IFMT) {
        case S_IFBLK:  printf("b "); break;
        case S_IFCHR:  printf("c "); break; 
        case S_IFDIR:  printf("d "); break; //It's a (sub)directory 
        case S_IFIFO:  printf("p "); break; //fifo
        case S_IFLNK:  printf("l "); break; //Sym link
        case S_IFSOCK: printf("s "); break;
        //Filetype isn't identified
        default:       printf("- "); break;
            }
    //[permissions]
    //Same for the permissions, we have to test the different rights
    //READ http://linux.die.net/man/2/chmod 
    printf( (dev.st_mode & S_IRUSR) ? " r" : " -");
    printf( (dev.st_mode & S_IWUSR) ? "w" : "-");
    printf( (dev.st_mode & S_IXUSR) ? "x" : "-");
    printf( (dev.st_mode & S_IRGRP) ? "r" : "-");
    printf( (dev.st_mode & S_IWGRP) ? "w" : "-");
    printf( (dev.st_mode & S_IXGRP) ? "x" : "-");
    printf( (dev.st_mode & S_IROTH) ? "r" : "-");
    printf( (dev.st_mode & S_IWOTH) ? "w" : "-");
    printf( (dev.st_mode & S_IXOTH) ? "x" : "-");

    // [number of hard links]
    printf("\t%ld ", dev.st_nlink);

    //[owner] 
    printf("\t%s ", dev.pw_name);

    //[group]
    printf("\t%s ", dev.gr_name);

    //[size in bytes] [filename]
    printf("%zu", dev.st_size);
    printf(" %s", dev.name);    
    printf("\n");  
}



void scan_active_devices(list *devices){
    
    //The file: when a file is found in the directory readdir loop, it's going to be called this way.
    struct dirent *dev;

    //Creating a placeholder for the string. 
    //We create this so later it can be properly adressed.
    //It's reasonnable here to consider a 512 maximum lenght, as we're just going to use it to display a path to a file, 
    //but we could have used a strlen/malloc combo and declared a simple buf[] at this moment
    char buf[512];

    //It's time to assign thedirectory to the argument: this way the user will be able to browse any folder simply by mentionning it 
    //when launching the lsd program.
    DIR *thedirectory = opendir("/dev");

    //If a file is found (readdir returns a NOT NULL value), the loop starts/keep going until it has listed all of them. 
    while((dev = readdir(thedirectory)) != NULL) 
    {   
        //We sprint "thedirectory/dev" which defines the path to our file 
        sprintf(buf, "%s/%s", "/dev", dev->d_name);

        //The stat: It's how we'll retrieve the stats associated to the file. 
        //Then we use stat function in order to retrieve information about the file
        struct stat thestat;
        stat(buf, &thestat);
                
        //will be used to determine the file owner & group
        struct passwd *tf = getpwuid(thestat.st_uid);
        struct group *gf = getgrgid(thestat.st_gid);
                
        struct device *d = (struct device *) malloc(sizeof(struct device));
        
        //d = (struct device){NULL, thestat.st_mode, thestat.st_nlink, thestat.st_size, tf->pw_name, gf->gr_name};
        //d = (struct device){NULL, NULL, NULL, NULL, NULL, NULL};

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