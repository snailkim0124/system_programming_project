#ifndef RENDER_H
#define RENDER_H

#include "common.h"

#define WIN_HEIGHT 12
#define WIN_WIDTH 40

void draw_box(int start_y, int start_x, int height, int width, int color_pair, const char *title);
void draw_placard(Player *p);
int draw_quit();
void draw_single_key(Key* key, int highlighted);
void draw_keyboard(int pressed_keycode);
void draw_inventory(int start_y, int start_x);
void draw_store(int start_y, int start_x, int selected_idx, ItemType shop_now_tab);
void draw_main_window(Player *player, int selected_idx, ItemType shop_now_tab);
void draw_leftwindow(Player *player, int selected_idx, ItemType shop_now_tab);
void draw_info(Player *player, Store *item);

#endif