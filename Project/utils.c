#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int valid_input(char input, int max){
    int ascii = input;
    //printf("char %c\n ascii %d\n",input, ascii);
    if(ascii >= 48 && ascii < 48+max)
        return ascii-48;
    return -1;
}
