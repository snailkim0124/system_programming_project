#ifndef RENDER_H
#define RENDER_H

#include "common.h"

#define WIN_HEIGHT 12
#define WIN_WIDTH 40
#define SHOP_ITEM_COUNT 32
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
    ItemType item_type;
    ZoneType zone;
} Store;

extern Store shop_stock[];
extern Key main_keyboard[];

void draw_placard(Player *p);
int draw_quit();
void draw_single_key(Key* key, int highlighted);
void draw_keyboard(int pressed_keycode);
void draw_inventory(int start_y, int start_x);
void draw_store(int start_y, int start_x, int selected_idx, ItemType shop_now_tab);
void draw_main_window(Player *player, int selected_idx, ItemType shop_now_tab);
void draw_leftwindow(Player *player, int selected_idx, ItemType shop_now_tab);
void get_korean_name(const char *eng_name, char *kor_name);
void draw_info(Player *player, Store *item);

#endif