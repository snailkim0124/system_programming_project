#ifndef RENDER_H
#define RENDER_H

#include "common.h"

typedef struct {
    char name[25];
    int price;
    char explan[25];
} Store;

extern Store shop_stock[];
#define WIN_HEIGHT 12
#define WIN_WIDTH 40
#define SHOP_ITEM_COUNT 30

// 키보드 전체를 그리는 함수
void draw_keyboard(int pressed_keycode);
void draw_leftwindow(Player *player, int selected_idx);

// ncurses 초기화 및 종료 함수
void init_terminal();
void close_terminal();

#endif