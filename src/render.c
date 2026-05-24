#include "render.h"

Key main_keyboard[] = {
    // Row 0 (Function Keys)
    { 2,  2, 8,  "ESC",   27 },
    { 2, 13, 5,  "F1",    KEY_F(1) },
    { 2, 18, 5,  "F2",    KEY_F(2) },
    { 2, 23, 5,  "F3",    KEY_F(3) },
    { 2, 28, 5,  "F4",    KEY_F(4) },

    { 2, 34, 5,  "F5",    KEY_F(5) },
    { 2, 39, 5,  "F6",    KEY_F(6) },
    { 2, 44, 5,  "F7",    KEY_F(7) },
    { 2, 49, 5,  "F8",    KEY_F(8) },

    { 2, 55, 5,  "F9",    KEY_F(9) },
    { 2, 60, 5,  "F10",    KEY_F(10) },
    { 2, 65, 5,  "F11",    KEY_F(11) },
    { 2, 70, 5,  "F12",    KEY_F(12) },
    
    // Row 1 (Numbers) - 총 너비 55 (2~57)
    { 5,  2, 5,  "`",     '`' },
    { 5,  7, 5,  "1",     '1' },
    { 5, 12, 5,  "2",     '2' },
    { 5, 17, 5,  "3",     '3' },
    { 5, 22, 5,  "4",     '4' },
    { 5, 27, 5,  "5",     '5' },
    { 5, 32, 5,  "6",     '6' },
    { 5, 37, 5,  "7",     '7' },
    { 5, 42, 5,  "8",     '8' },
    { 5, 47, 5,  "9",     '9' },
    { 5, 52, 5,  "0",     '0' },
    { 5, 57, 5,  "-",     '-' },
    { 5, 62, 5,  "=",     '=' },
    { 5, 67, 8,  "BSP",   KEY_BACKSPACE },

    // Row 2 (QWE...)
    { 8,  2, 8,  "TAB",   '\t' }, 
    { 8, 10, 5,  "Q",     'q',  1,   0,   ZONE0 },
    { 8, 15, 5,  "W",     'w',  1,   0,   ZONE0 },
    { 8, 20, 5,  "E",     'e',  1,   0,   ZONE0 },
    { 8, 25, 5,  "R",     'r',  1,   0,   ZONE0 },
    { 8, 30, 5,  "T",     't',  1,   0,   ZONE0 },
    { 8, 35, 5,  "Y",     'y',  1,   0,   ZONE1 },
    { 8, 40, 5,  "U",     'u',  1,   0,   ZONE1 },
    { 8, 45, 5,  "I",     'i',  1,   0,   ZONE1 },
    { 8, 50, 5,  "O",     'o',  1,   0,   ZONE1 },
    { 8, 55, 5,  "P",     'p',  1,   0,   ZONE1 },
    { 8, 60, 5,  "[",     '['},
    { 8, 65, 5,  "]",     ']'},
    { 8, 70, 5,  "\\",    '\\'},

    // Row 3 (ASD...)
    { 11,  2, 9,  "CAPS",  -10 },    
    { 11, 11, 5,  "A",     'a',  1,   0,   ZONE2 },
    { 11, 16, 5,  "S",     's',  1,   0,   ZONE2 },
    { 11, 21, 5,  "D",     'd',  1,   0,   ZONE2 },
    { 11, 26, 5,  "F",     'f',  1,   0,   ZONE2 },
    { 11, 31, 5,  "G",     'g',  1,   0,   ZONE2 },
    { 11, 36, 5,  "H",     'h',  1,   0,   ZONE2 },
    { 11, 41, 5,  "J",     'j',  1,   0,   ZONE2 },
    { 11, 46, 5,  "K",     'k',  1,   0,   ZONE2 },
    { 11, 51, 5,  "L",     'l',  1,   0,   ZONE2 },
    { 11, 56, 5,  ";",     ';', },
    { 11, 61, 5,  "\'",     '\'', },
    { 11, 66, 9, "ENTER", '\n' },  

    // Row 4 (ZXC...)
    { 14,  2, 12, "SHIFT", -10 },   // Left Shift
    { 14, 14, 5,  "Z",     'z',  1,   0,   ZONE3 },
    { 14, 19, 5,  "X",     'x',  1,   0,   ZONE3 },
    { 14, 24, 5,  "C",     'c',  1,   0,   ZONE3 },
    { 14, 29, 5,  "V",     'v',  1,   0,   ZONE3 },
    { 14, 34, 5,  "B",     'b',  1,   0,   ZONE3 },
    { 14, 39, 5,  "N",     'n',  1,   0,   ZONE3 },
    { 14, 44, 5,  "M",     'm',  1,   0,   ZONE3 },
    { 14, 49, 5,   ",",   ',' },
    { 14, 54, 5,   ".",   '.' },
    { 14, 59, 5,   "/",   '/' },
    { 14, 64, 11, "SHIFT", -10 },   // Right Shift

    // Row 5 (Spacebar)
    { 17, 2, 9, "CTRL", -10 },
    { 17, 11, 5, "WIN", -10 },
    { 17, 16, 5, "ALT", -10 },
    { 17, 21, 27, "SPACE", ' ' },
    { 17, 48, 8, "KO/ENG", -10 },
    { 17, 56, 5, "HAN", -10 },
    { 17, 61, 5, "ALT", -10 },
    { 17, 66, 9, "CTRL", -10 },
};

Store shop_stock[] = {
    // { 이름, 구매가, 판매가, 성장시간, 설명, 타입 }
    {"Asparagus", 3, 5, 20, "", TYPE_SEED, ZONE0},
    {"Broccoli", 5, 8, 20, "", TYPE_SEED, ZONE0},
    {"Carrot", 5, 15, 30, "", TYPE_SEED, ZONE0},
    {"Dandelion", 10, 20, 30, "", TYPE_SEED, ZONE0},
    {"Eggplant", 10, 30, 60, "", TYPE_SEED, ZONE0},
    {"Fern", 10, 20, 120, "물없이 자람", TYPE_SEED, ZONE1},
    {"Garlic", 20, 40, 120, "병충해 면역", TYPE_SEED, ZONE1},
    {"Herb", 20, 100, 600, "", TYPE_SEED, ZONE1},
    {"Iris", 50, 100, 300, "황금작물 확률", TYPE_SEED, ZONE1},
    {"Jalapeno", 50, 80, 300, "절대 안 썩음", TYPE_SEED, ZONE1},
    {"Kale", 70, 150, 360, "", TYPE_SEED, ZONE2},
    {"Lettuce", 100, 200, 600, "", TYPE_SEED, ZONE2},
    {"Mushroom", 100, 150, 200, "밤에 2배 빠름", TYPE_SEED, ZONE2},
    {"Nettle", 50, 200, 600, "수확시 5번 클릭", TYPE_SEED, ZONE2},
    {"Onion", 100, 200, 1200, "병충해 면역", TYPE_SEED, ZONE2},
    {"Potato", 150, 160, 600, "수확시 씨앗리필", TYPE_SEED, ZONE2},
    {"Quinoa", 200, 500, 3600, "", TYPE_SEED, ZONE2},
    {"Radish", 300, 700, 3600, "", TYPE_SEED, ZONE2},
    {"Spinach", 300, 1000, 7200, "", TYPE_SEED, ZONE2},
    {"Tomato", 50, 100, 100, "30분뒤 썩음", TYPE_SEED, ZONE2},
    {"Ulluco", 300, 350, 3600, "수확시 씨앗리필", TYPE_SEED, ZONE3},
    {"Vanilla", 500, 1000, 4800, "", TYPE_SEED, ZONE3},
    {"Watercress", 300, 1000, 600, "물없으면 썩음", TYPE_SEED, ZONE3},
    {"Xylosma", 500, 600, 3600, "인접방향 퍼짐", TYPE_SEED, ZONE3},
    {"Yam", 1000, 2000, 7200, "", TYPE_SEED, ZONE3},
    {"Zucchini", 2000, 4000, 36000, "", TYPE_SEED, ZONE3},

    // 장비류 
    {"Land Deed", 100, 0, 0, "다음 구역 해금", TYPE_EQUIP, ZONE0}, // 땅 확장
    {"Fertilizer", 1000, 0, 0, "작물 성장속도 증가", TYPE_EQUIP, ZONE0}, // 비료
    {"Pesticide", 500, 0, 0, "병충해 0%", TYPE_EQUIP, ZONE1}, // 농약
    {"Sprinkler", 2000, 0, 0, "자동 물주기", TYPE_EQUIP, ZONE1}, // 스프링쿨러
    {"Scarecrow", 2000, 0, 0, "병충해 영구 제거", TYPE_EQUIP, ZONE2}, // 허수아비
    {"Placard", 100000, 0, 0, "텃밭 꾸미기", TYPE_EQUIP, ZONE3}, // 플래카드(엔딩)
};

#define NUM_KEYS (sizeof(main_keyboard) / sizeof(Key))

int draw_quit() {
    erase(); // 화면 초기화

    // 키보드는 다시 그리기
    draw_keyboard(-1);

    int start_y = 23, start_x = 12;
    int height = 8, width = 40; // 창 크기 고정
    
    attron(COLOR_PAIR(2));
    
    // 박스 그리기
    int title_len = strlen(" QUIT ");
    int side_bar = (width - 2 - title_len) / 2;
    
    mvaddch(start_y, start_x, ACS_ULCORNER);
    for(int i=0; i<side_bar; i++) addch(ACS_HLINE);
    printw("%s", " QUIT ");
    for(int i=0; i < (width - 2 - title_len - side_bar); i++) addch(ACS_HLINE);
    addch(ACS_URCORNER);

    for (int i = 1; i < height - 1; i++) {
        mvaddch(start_y + i, start_x, ACS_VLINE);
        for(int j=0; j < width - 2; j++) mvaddch(start_y + i, start_x + 1 + j, ' '); // 배경 지우기
        mvaddch(start_y + i, start_x + width - 1, ACS_VLINE);
    }

    mvaddch(start_y + height - 1, start_x, ACS_LLCORNER);
    for (int i = 0; i < width - 2; i++) addch(ACS_HLINE);
    addch(ACS_LRCORNER);
    
    attroff(COLOR_PAIR(2));

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

    // 땅인 경우 갈색으로
    if(key->is_soil) {
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
        attroff(COLOR_PAIR(1));

        // 흰색
        int now_color = 0; 

        if (key->is_harm) {
            now_color = 2; // 빨간색
        } 
        else if (key->crop_state == 98) {
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
        
        attron(COLOR_PAIR(now_color));

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

        attroff(COLOR_PAIR(now_color));
        attron(COLOR_PAIR(1));
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

    if(key->is_soil) {
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

    mvprintw(20, 2, "F1 : 인벤토리\tF2 : 상점\tF3 : 농장\t현재 잔액 : %d G", player.inv.money);

    //  경고 메시지가 있는 경우
    if (strlen(player.ast_msg) > 0) {
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
                    draw_rightwindow(&player, &shop_stock[found_shop_idx]);
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
            mvprintw(start_y + i, start_x + 4, "[%02d] %-15s | %s ", 
                 item_idx + 1, "???", "???");
        }

        
        if (item_idx == selected_idx) {
            attroff(A_REVERSE | A_BOLD);
            // 선택된 아이템의 설명도 하단에 띄우기
            if(shop_stock[real_idx].zone <= player.unlocked_zone) {
                mvprintw(start_y + WIN_HEIGHT - 6, start_x + 4, "설명: %s", shop_stock[real_idx].explan);
                draw_rightwindow(&player, &shop_stock[real_idx]);
            }
        }
    }

    mvprintw(start_y + WIN_HEIGHT - 5, start_x, "현재 잔액: %d G", player.inv.money);
    mvprintw(start_y + WIN_HEIGHT - 4, start_x, "(닫기: F2 / 이동: ↑ ↓ / 상점탭: ← →)");
}

void draw_leftwindow(Player *player, int selected_idx, ItemType shop_now_tab) {
    if (player->is_inventory_open && player->is_store_open) return;

    int start_y = 23, start_x = 3;
    int height = 12, width = 40; // 창 크기 고정
    char subtitle[20];

    // 1. 제목 및 색상 결정
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

    // 2. 외곽 박스 그리기
    attron(COLOR_PAIR(color));
    
    // 상단 (제목 포함)
    int title_len = strlen(subtitle);
    int side_bar = (width - 2 - title_len) / 2;
    
    mvaddch(start_y, start_x, ACS_ULCORNER);
    for(int i=0; i<side_bar; i++) addch(ACS_HLINE);
    printw("%s", subtitle);
    for(int i=0; i < (width - 2 - title_len - side_bar); i++) addch(ACS_HLINE);
    addch(ACS_URCORNER);

    // 몸통
    for (int i = 1; i < height - 1; i++) {
        mvaddch(start_y + i, start_x, ACS_VLINE);
        for(int j=0; j < width - 2; j++) mvaddch(start_y + i, start_x + 1 + j, ' '); // 배경 지우기
        mvaddch(start_y + i, start_x + width - 1, ACS_VLINE);
    }

    // 하단
    mvaddch(start_y + height - 1, start_x, ACS_LLCORNER);
    for (int i = 0; i < width - 2; i++) addch(ACS_HLINE);
    addch(ACS_LRCORNER);
    
    attroff(COLOR_PAIR(color));

    // 3. 내용물 그리기
    if (player->is_inventory_open) {
        draw_inventory(start_y + 2, start_x + 2);
    } else if (player->is_store_open) {
        draw_store(start_y + 2, start_x + 2, selected_idx, shop_now_tab);
    }
}

void get_korean_name(const char *eng_name, char *kor_name) {
    // 씨앗류 (A ~ Z)
    if (strcmp(eng_name, "Asparagus") == 0) strcpy(kor_name, "아스파라거스");
    else if (strcmp(eng_name, "Broccoli") == 0) strcpy(kor_name, "브로콜리");
    else if (strcmp(eng_name, "Carrot") == 0) strcpy(kor_name, "당근");
    else if (strcmp(eng_name, "Dandelion") == 0) strcpy(kor_name, "민들레");
    else if (strcmp(eng_name, "Eggplant") == 0) strcpy(kor_name, "가지");
    else if (strcmp(eng_name, "Fern") == 0) strcpy(kor_name, "고사리");
    else if (strcmp(eng_name, "Garlic") == 0) strcpy(kor_name, "마늘");
    else if (strcmp(eng_name, "Herb") == 0) strcpy(kor_name, "허브");
    else if (strcmp(eng_name, "Iris") == 0) strcpy(kor_name, "붓꽃");
    else if (strcmp(eng_name, "Jalapeno") == 0) strcpy(kor_name, "할라피뇨");
    else if (strcmp(eng_name, "Kale") == 0) strcpy(kor_name, "케일");
    else if (strcmp(eng_name, "Lettuce") == 0) strcpy(kor_name, "상추");
    else if (strcmp(eng_name, "Mushroom") == 0) strcpy(kor_name, "버섯");
    else if (strcmp(eng_name, "Nettle") == 0) strcpy(kor_name, "쐐기풀");
    else if (strcmp(eng_name, "Onion") == 0) strcpy(kor_name, "양파");
    else if (strcmp(eng_name, "Potato") == 0) strcpy(kor_name, "감자");
    else if (strcmp(eng_name, "Quinoa") == 0) strcpy(kor_name, "퀴노아");
    else if (strcmp(eng_name, "Radish") == 0) strcpy(kor_name, "무");
    else if (strcmp(eng_name, "Spinach") == 0) strcpy(kor_name, "시금치");
    else if (strcmp(eng_name, "Tomato") == 0) strcpy(kor_name, "토마토");
    else if (strcmp(eng_name, "Ulluco") == 0) strcpy(kor_name, "울루코");
    else if (strcmp(eng_name, "Vanilla") == 0) strcpy(kor_name, "바닐라");
    else if (strcmp(eng_name, "Watercress") == 0) strcpy(kor_name, "물냉이");
    else if (strcmp(eng_name, "Xylosma") == 0) strcpy(kor_name, "산유자나무");
    else if (strcmp(eng_name, "Yam") == 0) strcpy(kor_name, "마");
    else if (strcmp(eng_name, "Zucchini") == 0) strcpy(kor_name, "애호박");
    
    // 장비류
    else if (strcmp(eng_name, "Land Deed") == 0) strcpy(kor_name, "텃밭 확장");
    else if (strcmp(eng_name, "Fertilizer") == 0) strcpy(kor_name, "비료");
    else if (strcmp(eng_name, "Pesticide") == 0) strcpy(kor_name, "농약");
    else if (strcmp(eng_name, "Sprinkler") == 0) strcpy(kor_name, "스프링클러");
    else if (strcmp(eng_name, "Scarecrow") == 0) strcpy(kor_name, "허수아비");
    else if (strcmp(eng_name, "Placard") == 0) strcpy(kor_name, "플래카드");
    
    // 혹시 매칭 안 되는 게 있으면 원래 영어 이름 그대로 출력
    else strcpy(kor_name, eng_name); 
}

void draw_rightwindow(Player *player, Store *item) {
    if (player->is_inventory_open && player->is_store_open) return;

    int start_y = 23, start_x = 45;
    int height = 12, width = 20; // 창 크기 고정
    char subtitle[20];

    // 1. 제목 및 색상 결정
    strcpy(subtitle, " INFO ");
    int color = 2; // 상점용 다른 색

    // 2. 외곽 박스 그리기
    attron(COLOR_PAIR(color));
    
    // 상단 (제목 포함)
    int title_len = strlen(subtitle);
    int side_bar = (width - 2 - title_len) / 2;
    
    mvaddch(start_y, start_x, ACS_ULCORNER);
    for(int i=0; i<side_bar; i++) addch(ACS_HLINE);
    printw("%s", subtitle);
    for(int i=0; i < (width - 2 - title_len - side_bar); i++) addch(ACS_HLINE);
    addch(ACS_URCORNER);

    // 몸통
    for (int i = 1; i < height - 1; i++) {
        mvaddch(start_y + i, start_x, ACS_VLINE);
        for(int j=0; j < width - 2; j++) mvaddch(start_y + i, start_x + 1 + j, ' '); // 배경 지우기
        mvaddch(start_y + i, start_x + width - 1, ACS_VLINE);
    }

    // 하단
    mvaddch(start_y + height - 1, start_x, ACS_LLCORNER);
    for (int i = 0; i < width - 2; i++) addch(ACS_HLINE);
    addch(ACS_LRCORNER);
    
    attroff(COLOR_PAIR(color));

    // 정보 적기

    // 아이템 이름 한국어로 (강조)
    char kor_name[50];
    get_korean_name(item->name, kor_name);

    attron(A_BOLD);
    mvprintw(start_y + 2, start_x + 2, "%-16s", kor_name); 
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

    // 4. 판매가(Sell) 출력
    if (strcmp(item->name, "Land Deed") == 0) {
        mvprintw(start_y + 6, start_x + 2, "Sell: -"); 
    } else {
        mvprintw(start_y + 6, start_x + 2, "Sell: %d G", item->sell_price);
    }

    // 성장 시간(Time) 출력
    // 씨앗일 때만 시간을 보여주고, 도구나 확장권은 '-'로 표시합니다.
    if (item->item_type == TYPE_SEED) {
        mvprintw(start_y + 7, start_x + 2, "Time: %d Sec", item->growth_time); 
    } else {
        mvprintw(start_y + 7, start_x + 2, "Time: -");
    }

    // 아이템 설명
    mvprintw(start_y + 9, start_x + 2, "[ Info ]");
    mvprintw(start_y + 10, start_x + 2, "%.16s", item->explan);
}

void init_terminal() {
    setlocale(LC_ALL, ""); // 한글 설정
    initscr();
    cbreak();             
    noecho();             
    keypad(stdscr, TRUE); 
    curs_set(0);
    set_escdelay(0); // esc 딜레이 없애기

    // 색깔 부분
    start_color();
    use_default_colors();
    init_pair(1, 94, -1); // 94번은 갈색 계열, -1은 투명 배경
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK); // 황금 작물용
    init_pair(5, 208, COLOR_BLACK); // 주황색 - 허수아비
    init_pair(6, COLOR_BLUE, COLOR_BLACK); // 파란색 - 스프링쿨러
}

void close_terminal() {
    endwin(); 
}