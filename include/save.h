#ifndef SAVE_H
#define SAVE_H

#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#include "player.h"

double time_diff_ms(struct timeval start, struct timeval end);
void save_game(Player *p);
void load_game(Player *p);

#endif