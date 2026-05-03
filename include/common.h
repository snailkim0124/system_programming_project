#ifndef COMMON_H
#define COMMON_H
#define MAX_ITEMS 5

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
    ////////////
    int is_soil; // 땅인지 아닌지
    int is_locked; // 땅이 잠겼는지
    int crop_state; // 작물 상태
} Key;

typedef struct {
    char name[20];
    int count;
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    int money;
    int selected_slot; // 인벤토리 안에서 선택 중인 칸
} Inventory;

typedef struct {
    int cur_y, cur_x;
    Inventory inv;
    bool is_inventory_open; // 현재 인벤토리가 열려 있는지 확인
} Player;

extern Player player;

#endif