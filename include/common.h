#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <termio.h>
#include <ncurses.h>
#include <locale.h>
#include <string.h>

typedef struct {
    int y, x;        
    int width;       
    char label[10];  
    int keycode;     
} Key;


#endif