#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

extern Player player;

void player_init();
void buy_item(Player *p, int shop_idx);
void consume_selected_item();
void use_item();
void remove_item();
void sell_item(Player *p, int pressed_keycode);
void remove_pest(Player *p, int pressed_keycode);
int item_priority(const char* name);
void sort_inventory(Player *p);

#endif