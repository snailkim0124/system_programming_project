#include "common.h"
#include "player.h"
#include "render.h"

Player player;

void player_init() {
    player.is_inventory_open = false;
    player.is_store_open = false;
    player.inv.money = 1000;
    strcpy(player.inv.items[0].name, "carrot");
    player.inv.items[0].count = 5;
    strcpy(player.ast_msg, "");
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