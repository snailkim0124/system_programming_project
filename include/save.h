#ifndef SAVE_H
#define SAVE_H

#include "player.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void save_game(Player *p);
void load_game(Player *p);

#endif