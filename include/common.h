#ifndef COMMON_H
#define COMMON_H
#define MAX_ITEMS 20
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <termio.h>
#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <locale.h>
#include <time.h>

typedef struct {
    int y, x;        
    int width;       
    char label[10];  
    int keycode;
    ////////////
    int is_soil; // 땅인지 아닌지
    int crop_state; // 작물 상태 (, > + > z > Z > 색 변경(녹색, 노란색))
    int zone_id; // 구역 표현
    int is_harm; // 병충해?

    int growth_timer; // 성장 타이머
    char planted_item_name[25]; // 무슨 씨앗?
} Key;

typedef struct {
    char name[20];
    int count;
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    int money;
    int selected_slot; // 인벤토리 안에서 선택 중인 칸
    int current_item_count; // 현재 가지고 있는 아이템 개수
} Inventory;

typedef struct {
    int cur_y, cur_x;
    Inventory inv;
    bool is_inventory_open; // 현재 인벤토리가 열려 있는지 확인
    bool is_store_open; // 현재 상점?
    bool is_farm_open; // 현재 농장?
    char ast_msg[256]; // 경고 메시지
    int unlocked_zone; // 현재 어디까지 해금?
} Player;

extern Player player;

#endif