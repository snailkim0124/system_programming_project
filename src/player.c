#include "common.h"
#include "player.h"
#include "render.h"

Player player;

void player_init() {
    player.is_inventory_open = false;
    player.is_store_open = false;
    player.inv.money = 1000;
    strcpy(player.inv.items[0].name, "Carrot");
    player.inv.items[0].count = 5;
    strcpy(player.ast_msg, "");
    player.inv.current_item_count = 1;
}

void buy_item(Player *p, int shop_idx) {
    // 상점 아이템 가져오기
    if(p->inv.money >= shop_stock[shop_idx].price) {
        p->inv.money -= shop_stock[shop_idx].price;
        // 아이템 인벤토리에 추가하기

        int item_add = 0;

        for(int i = 0; i < MAX_ITEMS; i++) {
            if(strcmp(p->inv.items[i].name, shop_stock[shop_idx].name) == 0) {
                p->inv.items[i].count++;
                item_add = 1;
                break;
            }
        }

        // 같은 아이템 없으면 빈 공간에 넣기
        if(!item_add) {
            for(int i = 0; i < MAX_ITEMS; i++) {
                if(p->inv.items[i].count == 0) {
                    strcpy(p->inv.items[i].name, shop_stock[shop_idx].name);
                    p->inv.items[i].count = 1;
                    p->inv.current_item_count++;
                    break;
                }
            }
        }

        sprintf(p->ast_msg, "%s 구매 완료! (잔액: %d G)", shop_stock[shop_idx].name, p->inv.money);

    }
    else {
        sprintf(p->ast_msg, "돈이 부족합니다! (현재 잔액: %d G)", player.inv.money);
    }
}

void plant_seed() {
    // 엔터를 누름
    printf("농작물 심기!!\n");

    // 키보드를 선택할 수 있도록 커서를 옮겨야 함
    int pressed_keycode = getch();

    printf("%d\n", pressed_keycode);

    // for (int i = 0; i < NUM_KEYS; i++) {
    //     int is_pressed = (main_keyboard[i].keycode == pressed_keycode);
    //     draw_single_key(&main_keyboard[i], is_pressed);
    // }

    // 확인하셨습니까?

    // 다시 렌더링
}