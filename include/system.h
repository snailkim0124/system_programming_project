#ifndef SYSTEM_H
#define SYSTEM_H

#include <signal.h>
#include <sys/time.h>
#include <stdlib.h> 
#include <locale.h>

extern int game_tick;

void handle_sigint(int sig);
void handle_sigalrm(int sig);
void init_terminal();
void close_terminal();

#endif