#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "display.h"



void system_cmd(char *input, char **output, int size){
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


