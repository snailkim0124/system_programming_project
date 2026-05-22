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
        sprintf(p->ast_msg, "돈이 부족합니다! (현재 잔액: %d G)  ", player.inv.money);
    }
}

void plant_seed() {
    // 심을 땅은 있는가?
    int is_valid_soil = 0;

    for (int i = 0; i < NUM_KEYS; i++) {
        if (main_keyboard[i].is_soil == 1 && 
            main_keyboard[i].is_locked == 0 && 
            main_keyboard[i].crop_state == 0) {
                    
            is_valid_soil = 1;
            break;
        }
    }

    //  심을 땅이 없는 경우 나가기
    if(!is_valid_soil) {
        sprintf(player.ast_msg, "심을 땅이 꽉 찼거나 없습니다!  ");
        return;
    }

    // 키보드를 선택할 수 있도록 커서를 옮겨야 함
    mvprintw(21, 3, "심을 곳을 키보드로 누르세요!");
    int pressed_keycode = 0;
    while(1) {
        pressed_keycode = getch();
        pressed_keycode = tolower(pressed_keycode);

        // 심을 수 있는 땅인가?
        int is_valid_soil = 0;

        for (int i = 0; i < NUM_KEYS; i++) {
            if (main_keyboard[i].keycode == pressed_keycode) {
                if (main_keyboard[i].is_soil == 1 && 
                    main_keyboard[i].is_locked == 0 && 
                    main_keyboard[i].crop_state == 0) {
                    
                    is_valid_soil = 1;
                }
                break;
            }
        }

        if (is_valid_soil == 1) {
            break; 
        }
        else {
            attron(COLOR_PAIR(2));
            mvprintw(21, 3, "그곳에는 심을 수 없습니다! 다시 누르세요.    ");
            attroff(COLOR_PAIR(2));
        }
    }

    // 키보드 표시
    for (int i = 0; i < NUM_KEYS; i++) {
        int is_pressed = (main_keyboard[i].keycode == pressed_keycode);
        draw_single_key(&main_keyboard[i], is_pressed);
    }

    // 확인하셨습니까?
    mvprintw(21, 3, "                                                   ");
    attron(A_BOLD && COLOR_PAIR(2));
    mvprintw(21, 3, "이 자리에 심으시겠습니까? (같은 곳을 한 번 더 누르세요!)");
    attroff(A_BOLD && COLOR_PAIR(2));
    
    refresh();

    int check = 0;
    while(1) {
        check = getch();
        // 한번더 똑같은 알파벳을 누른 경우
        if(check == pressed_keycode) {
            // 농작물 심기 (화면에 표시 -> ,)
            for (int i = 0; i < NUM_KEYS; i++) {
                if (main_keyboard[i].keycode == pressed_keycode) {
                    main_keyboard[i].crop_state = 1;
                    break;
                }
            }

            // 인벤토리에 있는 씨앗 감소
            player.inv.items[player.inv.selected_slot].count--;

            // 개수를 뺐는데 0개? 슬롯을 완전히 비우기
            if (player.inv.items[player.inv.selected_slot].count <= 0) {
                // 슬롯 당겨오기
                for (int i = player.inv.selected_slot; i < MAX_ITEMS - 1; i++) {
                    player.inv.items[i] = player.inv.items[i + 1];
                }

                strcpy(player.inv.items[MAX_ITEMS - 1].name, "");
                player.inv.items[MAX_ITEMS - 1].count = 0;
                player.inv.current_item_count--; 

                // 마지막 아이템 쓴 경우 커서가 허공을 가리키게 되므로 한 칸 올리기
                if (player.inv.selected_slot >= player.inv.current_item_count && player.inv.selected_slot > 0) {
                    player.inv.selected_slot--;
                }
            }
            break;
        }
        else {
            break;
        }
    }
}