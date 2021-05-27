#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "display.h"
#include <string.h>


void system_cmd2(char *input, char **output, int size){
    FILE *p;
    p = popen(input,"r");    
    if( p == NULL){
        puts("Unable to open process");
    }else{
        *output = (char *)malloc(sizeof(char)*size);
        fgets(*output, sizeof(char)*size, p);        
        pclose(p);
    }
}

char *system_cmd(char *input, int chunk_size){
    if(chunk_size < 1) return NULL;
    FILE *fp = popen(input,"r");    
    if( fp == NULL){
        puts("Unable to open process");
    }else{
        int len = 0;
        char *out = NULL;
        char c;
        int i = 0;
        int strl = 0;
        while((c = getc(fp)) != EOF){
            if( i+1 >= len || len < chunk_size){
                out = (char *)realloc( out, (len + chunk_size)*sizeof(char) );
                len += chunk_size;
            }
            strl = strlen(out);
            strncat(out, &c, 1);
            i++;  
        }
        pclose(fp);
        return out;
    }
}


int valid_input(char input, int max){
    int ascii = input;
    //printf("char %c\n ascii %d\n",input, ascii);
    if(ascii >= 48 && ascii < 48+max)
        return ascii-48;
    if(input == 'q' || input == 'Q')
        return EXIT_MENU;
    return INVALID_INPUT;
}

int getRandom(int lower, int upper)
{
    srand(time(0));
    return (rand() % (upper - lower + 1)) + lower;
}


char *parse_release(char *release){
    if(!release)
        return NULL;

    char *tmp = (char *)malloc(strlen(release)*sizeof(char));
    strcpy(tmp, release);
    char *r = strtok(tmp, "-");

    return(r);
}