#include "common.h"
#include "player.h"
#include "render.h"
#include "save.h"

Player player;

void player_init() {
    // 실제
    // player.unlocked_zone = 0;
    // player.inv.money = 15;

    // 디버그용
    player.is_remove_open = false;
    player.is_inventory_open = false;
    player.is_store_open = false;
    player.inv.money = 200000;
    strcpy(player.ast_msg, "");

    load_game(&player); // 시작할 때 불러오기
    player.is_store_open = false;
    player.is_inventory_open = false;
    player.is_remove_open = false;
    strcpy(player.ast_msg, "");
}

void buy_item(Player *p, int shop_idx) {
    if (strcmp(shop_stock[shop_idx].name, "Land Deed") != 0 && shop_stock[shop_idx].zone > p->unlocked_zone) {
        sprintf(p->ast_msg, "아직 해금되지 않아서 살 수 없습니다!  ");
        return;
    }
    

    int real_buy_price = shop_stock[shop_idx].buy_price * (strcmp(shop_stock[shop_idx].name, "Land Deed") == 0 ? pow(5, p->unlocked_zone) : 1);

    if(p->inv.money < real_buy_price) {
        sprintf(p->ast_msg, "돈이 부족합니다! (현재 잔액: %d G)  ", p->inv.money);
        return;
    }

    // 땅 확장권인 경우
    if (strcmp(shop_stock[shop_idx].name, "Land Deed") == 0) {
        if(p->unlocked_zone >= 4) {
            sprintf(p->ast_msg, "더 이상 확장할 땅이 없습니다!  ");
            return;
        }

        int next_zone = p->unlocked_zone + 1; // 열어야 할 다음 구역 번호
        p->inv.money -= real_buy_price;
        p->unlocked_zone = next_zone;

        sprintf(p->ast_msg, "새로운 구역(Zone %d)이 해금되었습니다!", next_zone);
    }
    // 플래카드 해방
    else if(strcmp(shop_stock[shop_idx].name, "Placard") == 0) {
        p->is_placard = 1;
    }
    else {
        p->inv.money -= real_buy_price;
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

        sort_inventory(p); // 정렬
    }
}

void consume_selected_item() {
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
}

void use_item() {
    // 현재 선택한 아이템 정보 가져오기
    char *item_name = player.inv.items[player.inv.selected_slot].name;
    if (strlen(item_name) == 0) return;


    if (strcmp(item_name, "Fertilizer") == 0) {
        player.buff_fertilizer_time += 10; 
        sprintf(player.ast_msg, "비료 사용! 10초 동안 성장 속도가 2배가 됩니다!");
        consume_selected_item();
        return;
    } 
    else if (strcmp(item_name, "Pesticide") == 0) {
        player.buff_pesticide_time += 20; 
        sprintf(player.ast_msg, "농약 사용! 20초 동안 병충해가 생기지 않습니다!");
        consume_selected_item();
        return; 
    }

    // x타입 확인
    int item_type = -1;
    for (int i = 0; i < SHOP_ITEM_COUNT; i++) {
        if (strcmp(shop_stock[i].name, item_name) == 0) {
            item_type = shop_stock[i].item_type;
            break;
        }
    }

    // 심을 땅은 있는가?
    int is_valid_soil = 0;
    for (int i = 0; i < NUM_KEYS; i++) {
        if (main_keyboard[i].is_soil == 1 && main_keyboard[i].zone_id <= player.unlocked_zone) {
            // 씨앗, 스프링쿨러, 허수아비: 빈 땅에만
            if ((item_type == TYPE_SEED || strcmp(item_name, "Sprinkler") == 0 || strcmp(item_name, "Scarecrow") == 0) && main_keyboard[i].crop_state == 0) {
                is_valid_soil = 1;
                break;
            }
        }
    }

    //  심을 땅이 없는 경우 나가기
    if(!is_valid_soil) {
        if (item_type == TYPE_SEED) sprintf(player.ast_msg, "심을 빈 땅이 없습니다!  ");
        else sprintf(player.ast_msg, "이 도구를 쓸 땅이 없습니다!  ");
        return;
    }

    // 키보드를 선택할 수 있도록 커서를 옮겨야 함
    erase(); 
    draw_keyboard(-1);
    if (item_type == TYPE_SEED) mvprintw(21, 3, "심을 곳을 키보드로 누르세요! (취소: ESC)");
    else mvprintw(21, 3, "설치할 곳을 키보드로 누르세요! (취소: ESC)");    
    refresh();

    flushinp(); // 이전 입력 버퍼 지우기
            
    int target_keycode = -1; // 내가 설치할 키보드

    while(1) {
        int pressed_keycode = getch();
        if (pressed_keycode == ERR) {
            continue; 
        }

        if(pressed_keycode == 27) { // ESC 취소
            sprintf(player.ast_msg, "설치를 취소했습니다.");
            return;
        }

        pressed_keycode = tolower(pressed_keycode);

        // 심을 수 있는 땅인가 검사
        int is_valid_soil = 0;
        int soil_idx = -1; // 찾은 밭의 인덱스

        for (int i = 0; i < NUM_KEYS; i++) {
            if (main_keyboard[i].keycode == pressed_keycode) {
                if (main_keyboard[i].is_soil == 1 && 
                    main_keyboard[i].zone_id <= player.unlocked_zone &&
                    main_keyboard[i].crop_state == 0) {
                    
                    is_valid_soil = 1;
                    soil_idx = i;
                }
                break;
            }
        }

        // 유효하지 않은 땅을 누른 경우
        if (is_valid_soil == 0) {
            attron(COLOR_PAIR(2));
            mvprintw(21, 3, "                                                               "); // 기존 줄 지우기
            if (item_type == TYPE_SEED) mvprintw(21, 3, "그곳에는 심을 수 없습니다! 다시 누르세요. (취소: ESC)   ");
            else mvprintw(21, 3, "그곳에는 설치할 수 없습니다! 다시 누르세요. (취소: ESC)   ");
            attroff(COLOR_PAIR(2));
            refresh();
            continue;
        }

        // 처음 눌렀거나, 다른 밭을 누른 경우
        if (target_keycode == -1 || target_keycode != pressed_keycode) {
            target_keycode = pressed_keycode; // 타겟 바꾸기

            // 키보드 하이라이트 표시 갱신
            for (int i = 0; i < NUM_KEYS; i++) {
                int is_pressed = (main_keyboard[i].keycode == target_keycode);
                draw_single_key(&main_keyboard[i], is_pressed);
            }

            mvprintw(21, 3, "                                                               ");
            attron(A_BOLD | COLOR_PAIR(2));
            mvprintw(21, 3, "이 자리가 맞으십니까? (같은 곳을 한 번 더 누르세요!)");
            attroff(A_BOLD | COLOR_PAIR(2));
            refresh();
        } 
        else if (target_keycode == pressed_keycode) {
            if (item_type == TYPE_SEED) {
                main_keyboard[soil_idx].crop_state = 1;
                main_keyboard[soil_idx].growth_timer = 0;
                strcpy(main_keyboard[soil_idx].planted_item_name, item_name);
                sprintf(player.ast_msg, "%s을(를) 심었습니다!", item_name);
            } 
            else if (strcmp(item_name, "Sprinkler") == 0 || strcmp(item_name, "Scarecrow") == 0) {
                if(strcmp(item_name, "Sprinkler") == 0) main_keyboard[soil_idx].crop_state = 99;
                else main_keyboard[soil_idx].crop_state = 98;

                strcpy(main_keyboard[soil_idx].planted_item_name, item_name);
                sprintf(player.ast_msg, "%s을(를) 설치했습니다!", item_name);
            }
            consume_selected_item();

            break;
        }
    }
}

void remove_item() {
    erase(); 
    draw_keyboard(-1);
    mvprintw(21, 3, "철거할 곳을 키보드로 누르세요! (취소: ESC)");    
    refresh();

    flushinp(); // 이전 입력 버퍼 지우기

    int pressed_keycode = 0;
    while(1) {
        pressed_keycode = getch();
        if (pressed_keycode == ERR) {
            continue; 
        }
        if(pressed_keycode == 27 || pressed_keycode == KEY_F(4)) {
            mvprintw(21, 3, "                                                                           ");
            refresh();
            return;
        }

        if (pressed_keycode == KEY_F(1) || pressed_keycode == KEY_F(2) || pressed_keycode == KEY_F(3)) {
            mvprintw(21, 3, "                                                                           ");
            refresh();
            
            // 방금 삼킨 키를 다시 입력 버퍼에 넣음
            ungetch(pressed_keycode); 
            return; 
        }

        pressed_keycode = tolower(pressed_keycode);

        int is_valid_soil = 0;
        for (int i = 0; i < NUM_KEYS; i++) {
            if (main_keyboard[i].keycode == pressed_keycode) {
                if (main_keyboard[i].is_soil == 1 && main_keyboard[i].crop_state > 0) {
                    is_valid_soil = 1;
                }
                break;
            }
        }

        if (is_valid_soil == 1) {
            break; 
        } else {
            attron(COLOR_PAIR(2));
            mvprintw(21, 3, "그곳에는 철거할 것이 없습니다! 다시 누르세요. (취소: ESC)   ");
            attroff(COLOR_PAIR(2));
            refresh();
        }
    }

    // 선택한 키보드 표시
    for (int i = 0; i < NUM_KEYS; i++) {
        int is_pressed = (main_keyboard[i].keycode == pressed_keycode);
        draw_single_key(&main_keyboard[i], is_pressed);
    }

    mvprintw(21, 3, "                                                                           ");
    attron(A_BOLD | COLOR_PAIR(2));
    mvprintw(21, 3, "정말 철거하시겠습니까? (같은 곳을 한 번 더 누르세요!)");
    attroff(A_BOLD | COLOR_PAIR(2));
    refresh();

    flushinp();

    int check = 0;
    while(1) {
        check = getch();
        if (check == ERR) {
            continue; 
        }

        if(check == pressed_keycode) {
            
            for (int i = 0; i < NUM_KEYS; i++) {
                if (main_keyboard[i].keycode == pressed_keycode) {
                    main_keyboard[i].crop_state = 0;
                    main_keyboard[i].growth_timer = 0;
                    main_keyboard[i].is_harm = 0;
                    strcpy(main_keyboard[i].planted_item_name, ""); 
                    
                    sprintf(player.ast_msg, "철거를 완료했습니다!");
                    break;
                }
            }
            break;
        }
        else {
            break;
        }
    }
}

void sell_item(Player *p, int pressed_keycode) {
    // 다 자랐으면 팔기
    int i = 0;
    for (i = 0; i < NUM_KEYS; i++) {
        if (main_keyboard[i].keycode == pressed_keycode) {
            break;
        }
    }

    if (i == NUM_KEYS) return;

    if(main_keyboard[i].crop_state < 5 || main_keyboard[i].crop_state >= 98 || main_keyboard[i].is_harm ) {
        return;
    }

    int selling_money = 0;
    // 썩은 작물은 1원
    if(main_keyboard[i].crop_state == 6) {
        selling_money = 1;
    }
    else {
        for(int j = 0; j < SHOP_ITEM_COUNT; j++) {
            if(strcmp(shop_stock[j].name, main_keyboard[i].planted_item_name) == 0) {
                selling_money = shop_stock[j].sell_price * (main_keyboard[i].crop_state == 7 ? 2 : 1); // 황금 작물이면 2배
                break;
            }
        }
    }

    // 수익 증가
    p->inv.money += selling_money;
    // 알림 추가
    if (main_keyboard[i].crop_state == 7) {
        sprintf(p->ast_msg, "럭키! 판매 완료! (+ %d G)", selling_money);
    }
    else sprintf(p->ast_msg, "판매 완료! (+ %d G)", selling_money);

    // 빈 땅으로 바꾸기
    main_keyboard[i].crop_state = 0;
    main_keyboard[i].growth_timer = 0;
    strcpy(main_keyboard[i].planted_item_name, "");
}

void remove_pest(Player *p, int pressed_keycode) {
    // 병충해인 경우
    int i = 0;
    for (i = 0; i < NUM_KEYS; i++) {
        if (main_keyboard[i].keycode == pressed_keycode) {
            break;
        }
    }
    if (i == NUM_KEYS) return;

   if (main_keyboard[i].is_soil && main_keyboard[i].is_harm) {
        main_keyboard[i].is_harm++;

        // 다섯 번 눌러야 사라짐
        if(main_keyboard[i].is_harm > 5) {
            main_keyboard[i].is_harm = 0;
            main_keyboard[i].harm_timer = 0;
        }
   } 
}

int item_priority(const char* name) {
    if (strlen(name) == 0) return 3; // 빈 슬롯은 맨 뒤로
    for (int i = 0; i < SHOP_ITEM_COUNT; i++) { 
        if (strcmp(shop_stock[i].name, name) == 0) {
            if (shop_stock[i].item_type == TYPE_EQUIP) return 1; // 장비 1순위
            if (shop_stock[i].item_type == TYPE_SEED) return 2;  // 씨앗 2순위
        }
    }
    return 3;
}

void sort_inventory(Player *p) {
    for (int i = 0; i < MAX_ITEMS - 1; i++) {
        for (int j = 0; j + i < MAX_ITEMS - 1; j++) {
            
            int pj = item_priority(p->inv.items[j].name);
            int pnxt = item_priority(p->inv.items[j+1].name);

            bool need_swap = false;

            if (pj > pnxt) {
                need_swap = true;
            } 
            // 2. 만약 같은 종류(둘 다 장비거나, 둘 다 씨앗)라면 알파벳 순서대로 정렬
            else if (pj == pnxt && pj != 3) {
                if (strcmp(p->inv.items[j].name, p->inv.items[j+1].name) > 0) {
                    need_swap = true;
                }
            }

            if (need_swap) {
                Item temp = p->inv.items[j];
                p->inv.items[j] = p->inv.items[j+1];
                p->inv.items[j+1] = temp;
            }
        }
    }
}