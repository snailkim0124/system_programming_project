#include "render.h"

void draw_box(int start_y, int start_x, int height, int width, int color_pair, const char *title) {
    if (color_pair != 0) attron(COLOR_PAIR(color_pair));

    // 1. 상단 테두리 (제목이 있으면 중간에 삽입)
    mvaddch(start_y, start_x, ACS_ULCORNER);
    if (title != NULL && strlen(title) > 0) {
        int title_len = strlen(title);
        int side_bar = (width - 2 - title_len) / 2;
        for (int i = 0; i < side_bar; i++) addch(ACS_HLINE);
        printw("%s", title);
        for (int i = 0; i < (width - 2 - title_len - side_bar); i++) addch(ACS_HLINE);
    } else {
        for (int i = 0; i < width - 2; i++) addch(ACS_HLINE);
    }
    addch(ACS_URCORNER);

    // 2. 몸통 (좌우 테두리 + 빈 공간 지우기)
    for (int i = 1; i < height - 1; i++) {
        mvaddch(start_y + i, start_x, ACS_VLINE);
        for (int j = 0; j < width - 2; j++) {
            addch(' '); // 배경을 공백으로 덮어씌움
        }
        mvaddch(start_y + i, start_x + width - 1, ACS_VLINE);
    }

    // 3. 하단 테두리
    mvaddch(start_y + height - 1, start_x, ACS_LLCORNER);
    for (int i = 0; i < width - 2; i++) addch(ACS_HLINE);
    addch(ACS_LRCORNER);

    if (color_pair != 0) attroff(COLOR_PAIR(color_pair));
}

void draw_placard(Player *p) {
    if(!p->is_placard) return; 

    int start_y = 2;
    int start_x = 2;
    int height = 3;
    int width = 73; 

    draw_box(start_y, start_x, height, width, 4, "");

    // 내용 채우기
    attron(A_BOLD);
    mvprintw(start_y + 1, start_x + 2, "[ 누구의 농장 ]");
    mvprintw(start_y + 1, start_x + 20, "알림: %s", p->ast_msg);
    mvprintw(start_y + 1, start_x + width - 15, "잔액: %d 원", p->inv.money);
    attroff(A_BOLD);
}

int draw_quit() {
    erase(); // 화면 초기화

    // 키보드는 다시 그리기
    draw_keyboard(-1);

    int start_y = 23, start_x = 12;
    int height = 8, width = 40; // 창 크기 고정
    
    attron(COLOR_PAIR(2));
    
    // 박스 그리기
    draw_box(start_y, start_x, height, width, 2, " QUIT ");

    // 종료하시겠습니까? 글씨
    attron(A_BOLD);
    mvprintw(start_y + 2, start_x + 9, "정말 종료하시겠습니까?");
    mvprintw(start_y + 4, start_x + 15, "( Y / N )");
    attroff(A_BOLD);
    
    refresh();

    //  진짜 종료할지 판단하는 로직
    int q_quit = 0;
    int real_quit = 0;

    while(1) {
        q_quit = getch();
        if(q_quit == 'y' || q_quit == 'Y') {
            real_quit = 1;
            break;
        }
        else if(q_quit == 'n' || q_quit == 'N' || q_quit == 27) {
            real_quit = 0;
            break;
        }
    }

    return real_quit;
}

void draw_single_key(Key* key, int highlighted) {
    int y = key->y;
    int x = key->x;
    int w = key->width;

    if (highlighted) attron(A_REVERSE);

    // 병충해인 경우 강조
    if (key->is_harm > 0) {
        attron(COLOR_PAIR(7) | A_BOLD | A_BLINK); 
    }
    // 땅인 경우 갈색으로
    else if(key->is_soil) {
        attron(COLOR_PAIR(1));
    }
    
    // 상단 선
    mvaddch(y, x, ACS_ULCORNER);
    for (int i = 0; i < w - 2; i++) addch(ACS_HLINE);
    addch(ACS_URCORNER);

    // 중간 선 및 텍스트
    mvaddch(y + 1, x, ACS_VLINE);
    
    int label_len = strlen(key->label);
    int padding = (w - 2 - label_len) / 2;
    for(int i=0; i<padding; i++) addch(' ');

    if(key->zone_id > player.unlocked_zone) {
        printw("#");
    }
    else if(key->is_soil) {
        // 흰색
        int now_color = 0; 

        if (key->crop_state == 98) {
            now_color = 5; // 주황색
        }
        else if(key->crop_state == 99) {
            now_color = 6; // 
        }
        else if (key->crop_state == 7) {
            now_color = 4; // 황금 작물 (노란색)
        } 
        else if (key->crop_state == 5) {
            now_color = 3; // 다 자란 작물 (초록색)
        }
        else if (key->crop_state == 6) {
            now_color = 8; 
        }
        

        if (key->is_harm == 0) {
            attroff(COLOR_PAIR(1));
            if (now_color != 0) {
                attron(COLOR_PAIR(now_color));
            }
        }

        switch (key->crop_state) {
            case 1: 
                printw(","); 
                break;
            case 2: 
                printw("+"); 
                break;
            case 3: 
                printw("%c", tolower(key->planted_item_name[0])); 
                break;
            case 4:
            case 5:
            case 6:
            case 7: 
                printw("%c", toupper(key->planted_item_name[0])); 
                break;
            case 98:
                 printw("&"); 
                break;
            case 99:
                printw("%%"); 
                break;
            default: 
                printw(" "); // 빈 땅
                break;
        }

        if (key->is_harm == 0) {
            if (now_color != 0) {
                attroff(COLOR_PAIR(now_color));
            }
            attron(COLOR_PAIR(1));
        }
    }
    else {
        printw("%s", key->label);
    }
    
    for(int i=0; i< (w - 2 - label_len - padding); i++) addch(' ');

    mvaddch(y + 1, x + w - 1, ACS_VLINE);

    // 하단 선
    mvaddch(y + 2, x, ACS_LLCORNER);
    for (int i = 0; i < w - 2; i++) addch(ACS_HLINE);
    addch(ACS_LRCORNER);

    if (key->is_harm > 0) {
        attroff(COLOR_PAIR(7) | A_BOLD | A_BLINK);
    }
    else if(key->is_soil) {
        attroff(COLOR_PAIR(1));
    }
    
    if (highlighted) attroff(A_REVERSE);
}

void draw_keyboard(int pressed_keycode) {
    mvprintw(0, 2, "농장게임 (종료: ESC)");
    
    for (int i = 0; i < NUM_KEYS; i++) {
        int is_pressed = (main_keyboard[i].keycode == pressed_keycode);
        draw_single_key(&main_keyboard[i], is_pressed);
    }

    mvprintw(20, 2, "F1: 인벤토리 / F2: 상점 / F3: 농장 / F4: 제거\t\t현재 잔액: %d G", player.inv.money);

    //  경고 메시지가 있는 경우
    if (strlen(player.ast_msg) > 0) {
        // 알림 창 비우기
        mvprintw(21, 3, "                                                                  ");
        // space 2번인 경우 빨간색 출력
        if(strstr(player.ast_msg, "  ") != NULL) {
            attron(COLOR_PAIR(2));
            mvprintw(21, 3, "알림: %s", player.ast_msg); 
            attroff(COLOR_PAIR(2));
        }
        else if (strstr(player.ast_msg, "사용") != NULL) {
            attron(COLOR_PAIR(3));
            mvprintw(21, 3, "알림: %s", player.ast_msg); 
            attroff(COLOR_PAIR(3));
        }
        else if (strstr(player.ast_msg, "럭키") != NULL) {
            attron(COLOR_PAIR(4));
            mvprintw(21, 3, "알림: %s", player.ast_msg); 
            attroff(COLOR_PAIR(4));
        }
        else {
            mvprintw(21, 3, "알림: %s", player.ast_msg); 
        }
    }
}

void draw_inventory(int start_y, int start_x) {
    // 아이템 목록 출력
    int total_items = (player.inv.current_item_count > 5) ? player.inv.current_item_count : 5;
    int selected_idx = player.inv.selected_slot;

    // 스크롤 시작 위치 계산 (위아래 2개씩 보이게)
    int start_idx = selected_idx - 2;
    if (start_idx < 0) start_idx = 0;

    // 총 아이템 개수가 5개보다 적을 때
    if (total_items <= 5) {
        start_idx = 0;
    }
    else if (start_idx + 5 > total_items) {
        start_idx = total_items - 5;
    }

    // 딱 5개만 출력
    for (int i = 0; i < 5; i++) {
        int item_idx = start_idx + i;
        if (item_idx >= total_items) break;

        // 빈 슬롯 이름 처리
        char item_name[25];
        strcpy(item_name, player.inv.items[item_idx].name);
        if (strlen(item_name) == 0) strcpy(item_name, "(빈 슬롯)");

        if (item_idx == selected_idx) {
            if (strlen(player.inv.items[item_idx].name) > 0 && player.inv.items[item_idx].count > 0) {
                
                int found_shop_idx = -1;
                for (int s = 0; s < SHOP_ITEM_COUNT; s++) { 
                    if (strcmp(shop_stock[s].name, player.inv.items[item_idx].name) == 0) {
                        found_shop_idx = s;
                        break;
                    }
                }
                
                if (found_shop_idx != -1) {
                    draw_info(&player, &shop_stock[found_shop_idx]);
                }
            } 
            else {
                int info_y = 23, info_x = 45;
                for (int h = 0; h < 12; h++) {
                    mvprintw(info_y + h, info_x, "                    ");
                }
            }

            // 선택된 아이템 강조
            attron(A_REVERSE | A_BOLD);
        }

        if(strcmp(item_name, "(빈 슬롯)") != 0) {
            mvprintw(start_y + i, start_x + 4, "[%02d] %-15s : %2d 개", 
                 item_idx + 1, item_name, player.inv.items[item_idx].count);
        }
        else {
            mvprintw(start_y + i, start_x + 4, "[%02d] %-15s", item_idx + 1, item_name);
        }

        if (item_idx == selected_idx) {
            attroff(A_REVERSE | A_BOLD);
        }
    }

    mvprintw(start_y + WIN_HEIGHT - 5, start_x, "현재 잔액: %d G", player.inv.money);
    mvprintw(start_y + WIN_HEIGHT - 4, start_x, "(닫기: F1 / 이동: ↑ ↓)");
}

void draw_store(int start_y, int start_x, int selected_idx, ItemType shop_now_tab) {
    int tab_items[100]; 
    int tab_item_count = 0;

    for (int i = 0; i < SHOP_ITEM_COUNT; i++) {
        if (shop_stock[i].item_type == shop_now_tab) {
            tab_items[tab_item_count] = i; // 진짜 번호(i)를 지도에 기록!
            tab_item_count++;
        }
    }

    // 판매 목록 출력
    int total_items = tab_item_count;

    // 스크롤 시작 위치 계산
    int start_idx = selected_idx - 2;
    if (start_idx < 0) start_idx = 0;

    // 총 아이템 개수가 5개보다 적을 때
    if (total_items <= 5) {
        start_idx = 0;
    }
    else if (start_idx + 5 > total_items) {
        start_idx = total_items - 5;
    }

    // 딱 5개만 출력
    for (int i = 0; i < 5; i++) {
        int item_idx = start_idx + i;
        if (item_idx >= total_items) break;

        int real_idx = tab_items[item_idx];

        // 선택된 아이템 강조
        if (item_idx == selected_idx) {
            attron(A_REVERSE | A_BOLD);
        }
        
        // 땅 확장권인 경우
        if(strcmp(shop_stock[real_idx].name, "Land Deed") == 0) {
            if (player.unlocked_zone >= 4) {
                mvprintw(start_y + i, start_x + 4, "[%02d] %-15s | END", 
                 item_idx + 1, shop_stock[real_idx].name);
            }
            else {
                mvprintw(start_y + i, start_x + 4, "[%02d] %-15s | %3d G", 
                 item_idx + 1, shop_stock[real_idx].name, (int)(shop_stock[real_idx].buy_price * pow(5, player.unlocked_zone)));
            }
        }
        // 아이템 출력
        else if(shop_stock[real_idx].zone <= player.unlocked_zone) {
            mvprintw(start_y + i, start_x + 4, "[%02d] %-15s | %3d G", 
                 item_idx + 1, shop_stock[real_idx].name, shop_stock[real_idx].buy_price);
        }
        else {
           attron(COLOR_PAIR(2));
            mvprintw(start_y + i, start_x + 4, "[%02d] 텃밭 %d단계 해금", 
                 item_idx + 1, shop_stock[real_idx].zone);
            attroff(COLOR_PAIR(2));
        }
        
        if (item_idx == selected_idx) {
            attroff(A_REVERSE | A_BOLD);
            // 선택된 아이템의 설명도 하단에 띄우기
            if(shop_stock[real_idx].zone <= player.unlocked_zone) {
                mvprintw(start_y + WIN_HEIGHT - 6, start_x + 4, "설명: %s", shop_stock[real_idx].explan);
                draw_info(&player, &shop_stock[real_idx]);
            }
        }
    }

    mvprintw(start_y + WIN_HEIGHT - 5, start_x, "현재 잔액: %d G", player.inv.money);
    mvprintw(start_y + WIN_HEIGHT - 4, start_x, "(닫기: F2 / 이동: ↑ ↓ / 상점탭: ← →)");
}

void draw_main_window(Player *player, int selected_idx, ItemType shop_now_tab) {
    if (player->is_inventory_open && player->is_store_open) return;

    int start_y = 23, start_x = 3;
    int height = 12, width = 40; // 창 크기 고정
    char subtitle[20];

    // 제목 및 색상 결정
    int color = 1;
    if (player->is_inventory_open) {
        strcpy(subtitle, " INVENTORY ");
        color = 1; // 금색
    } else if (player->is_store_open) {
        if(shop_now_tab == TYPE_SEED) {
            strcpy(subtitle, " SEED STORE ");
        }
        else if(shop_now_tab == TYPE_EQUIP) {
            strcpy(subtitle, " EQUIP STORE ");
        }
        color = 1; // 상점용 다른 색
    }

    // 박스 그리기
    draw_box(start_y, start_x, height, width, color, subtitle);

    // 내용물 그리기
    if (player->is_inventory_open) {
        draw_inventory(start_y + 2, start_x + 2);
    } else if (player->is_store_open) {
        draw_store(start_y + 2, start_x + 2, selected_idx, shop_now_tab);
    }
}

void draw_info(Player *player, Store *item) {
    if (player->is_inventory_open && player->is_store_open) return;

    int start_y = 23, start_x = 45;
    int height = 12, width = 30; // 창 크기 고정

    // 박스 그리기
    draw_box(start_y, start_x, height, width, 2, " INFO ");
    
    // 정보 적기
    attron(A_BOLD);
    mvprintw(start_y + 2, start_x + 2, "%-16s", item->kor_name); 
    attroff(A_BOLD);

    // 아이템 종류
    if (item->item_type == TYPE_SEED) {
        mvprintw(start_y + 4, start_x + 2, "Type: 씨앗");
    } else {
        mvprintw(start_y + 4, start_x + 2, "Type: 도구");
    }
 
    // 가격 정보
    int display_price = item->buy_price;
    if (strcmp(item->name, "Land Deed") == 0) {
        display_price = item->buy_price * (int)pow(5, player->unlocked_zone);
    }
    mvprintw(start_y + 5, start_x + 2, "Price: %d G", display_price);

    // 판매가
    if (item->item_type == TYPE_EQUIP) {
        mvprintw(start_y + 6, start_x + 2, "Sell: -"); 
    } else {
        mvprintw(start_y + 6, start_x + 2, "Sell: %d G", item->sell_price);
    }

    // 성장 시간 출력
    if (item->item_type == TYPE_SEED) {
        mvprintw(start_y + 7, start_x + 2, "Time: %d Sec", item->growth_time); 
    } else {
        mvprintw(start_y + 7, start_x + 2, "Time: -");
    }

    // 아이템 설명
    mvprintw(start_y + 9, start_x + 2, "[ Info ]");
    mvprintw(start_y + 10, start_x + 2, "%s", item->explan);
}