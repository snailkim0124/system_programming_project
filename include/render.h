#ifndef RENDER_H
#define RENDER_H

#include "common.h"

#define WIN_HEIGHT 12
#define WIN_WIDTH 40
#define SHOP_ITEM_COUNT 40
#define NUM_KEYS 67

typedef enum {
    TYPE_SEED = 0,
    TYPE_EQUIP,
} ItemType;

typedef enum {
    ZONE0 = 0, ZONE1,
    ZONE2, ZONE3
} ZoneType;

typedef struct {
    char name[25];
    int buy_price;
    int sell_price; 
    int growth_time;
    char explan[25];
    ItemType item_type; // 씨앗, 장비
    ZoneType zone;
} Store;

extern Store shop_stock[];
extern Key main_keyboard[];

// 키보드 전체를 그리는 함수
void draw_keyboard(int pressed_keycode);
void draw_leftwindow(Player *player, int selected_idx, ItemType shop_now_tab);

// ncurses 초기화 및 종료 함수
void init_terminal();
void close_terminal();

#endif