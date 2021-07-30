#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "display.h"
#include <string.h>

char *system_cmd(char *input, int chunk_size){
    if(chunk_size < 1)
        exit(1);
    
    FILE *fp = popen(input,"r");    
    if( fp == NULL){
        printf("Unable to open process %s", input);
        exit(1);        
    }
    int out_size = 0, i = 0;
    char *out = NULL;
    char c;
    while((c = getc(fp)) != EOF){
        if( i+1 >= out_size){
            out = (char *)realloc( out, (out_size + chunk_size)*sizeof(char) );
            out_size += chunk_size;
        }
        strncat(out, &c, 1);
        i++;  
    }
    pclose(fp);
    
    return out;    
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


char *read_stdin(){
    FILE* fp = stdin;
    size_t size = 10;
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str)*size);
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(*str)*len);
}