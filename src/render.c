#include "render.h"

Key main_keyboard[] = {
    // Row 0 (Function Keys)
    { 2,  2, 7,  "ESC",   27 },
    { 2, 11, 6,  "F1",    KEY_F(1) },
    { 2, 18, 6,  "F2",    KEY_F(2) },
    { 2, 25, 6,  "F3",    KEY_F(3) },
    { 2, 32, 6,  "F4",    KEY_F(4) },
    { 2, 39, 6,  "F5",    KEY_F(5) },

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
    { 8,  2, 7,  "TAB",   '\t' }, 
    { 8,  9, 5,  "Q",     'q',  1,   0,   ZONE0 },
    { 8, 14, 5,  "W",     'w',  1,   0,   ZONE0 },
    { 8, 19, 5,  "E",     'e',  1,   0,   ZONE0 },
    { 8, 24, 5,  "R",     'r',  1,   0,   ZONE0 },
    { 8, 29, 5,  "T",     't',  1,   0,   ZONE0 },
    { 8, 34, 5,  "Y",     'y',  1,   0,   ZONE1 },
    { 8, 39, 5,  "U",     'u',  1,   0,   ZONE1 },
    { 8, 44, 5,  "I",     'i',  1,   0,   ZONE1 },
    { 8, 49, 5,  "O",     'o',  1,   0,   ZONE1 },
    { 8, 54, 5,  "P",     'p',  1,   0,   ZONE1 },
    { 8, 59, 5,  "[",     '['},
    { 8, 64, 5,  "]",     ']'},
    { 8, 69, 5,  "\\",    '\\'},

    // Row 3 (ASD...)
    { 11,  2, 8,  "CAPS",  10 },    
    { 11, 10, 5,  "A",     'a',  1,   0,   ZONE2 },
    { 11, 15, 5,  "S",     's',  1,   0,   ZONE2 },
    { 11, 20, 5,  "D",     'd',  1,   0,   ZONE2 },
    { 11, 25, 5,  "F",     'f',  1,   0,   ZONE2 },
    { 11, 30, 5,  "G",     'g',  1,   0,   ZONE2 },
    { 11, 35, 5,  "H",     'h',  1,   0,   ZONE2 },
    { 11, 40, 5,  "J",     'j',  1,   0,   ZONE2 },
    { 11, 45, 5,  "K",     'k',  1,   0,   ZONE2 },
    { 11, 50, 5,  "L",     'l',  1,   0,   ZONE2 },
    { 11, 55, 5,  ";",     ';', },
    { 11, 60, 5,  "\'",     '\'', },
    { 11, 65, 10, "ENTER", '\n' },  

    // Row 4 (ZXC...)
    { 14,  2, 10, "SHIFT", -10 },   // Left Shift
    { 14, 12, 5,  "Z",     'z',  1,   0,   ZONE3 },
    { 14, 17, 5,  "X",     'x',  1,   0,   ZONE3 },
    { 14, 22, 5,  "C",     'c',  1,   0,   ZONE3 },
    { 14, 27, 5,  "V",     'v',  1,   0,   ZONE3 },
    { 14, 32, 5,  "B",     'b',  1,   0,   ZONE3 },
    { 14, 37, 5,  "N",     'n',  1,   0,   ZONE3 },
    { 14, 42, 5,  "M",     'm',  1,   0,   ZONE3 },
    { 14, 47, 5,   ",",   ',' },
    { 14, 52, 5,   ".",   '.' },
    { 14, 57, 5,   "/",   '/' },
    { 14, 62, 10, "SHIFT", -10 },   // Right Shift

    // Row 5 (Spacebar)
    { 17, 2, 8, "CTRL", -10 },
    { 17, 10, 5, "WIN", -10 },
    { 17, 15, 5, "ALT", -10 },
    { 17, 20, 27, "SPACE", ' ' },
    { 17, 47, 5, "K/E", -10 },
    { 17, 52, 5, "HAN", -10 },
    { 17, 57, 5, "ALT", -10 },
    { 17, 62, 8, "CTRL", -10 },
};

Store shop_stock[] = {
    // { 이름, 구매가, 판매가, 성장시간, 설명, 타입 }
    {"Asparagus", 3, 5, 20, "", TYPE_SEED},
    {"Broccoli", 5, 8, 20, "", TYPE_SEED},
    {"Carrot", 5, 15, 30, "", TYPE_SEED},
    {"Dandelion", 10, 20, 30, "", TYPE_SEED},
    {"Eggplant", 10, 30, 60, "", TYPE_SEED},
    {"Fern", 10, 20, 120, "물없이 자람", TYPE_SEED},
    {"Garlic", 20, 40, 120, "병충해 면역", TYPE_SEED},
    {"Herb", 20, 100, 600, "", TYPE_SEED},
    {"Iris", 50, 100, 300, "황금작물 확률", TYPE_SEED},
    {"Jalapeno", 50, 80, 300, "절대 안 썩음", TYPE_SEED},
    {"Kale", 70, 150, 360, "", TYPE_SEED},
    {"Lettuce", 100, 200, 600, "", TYPE_SEED},
    {"Mushroom", 100, 150, 200, "밤에 2배 빠름", TYPE_SEED},
    {"Nettle", 50, 200, 600, "수확시 5번 클릭", TYPE_SEED},
    {"Onion", 100, 200, 1200, "병충해 면역", TYPE_SEED},
    {"Potato", 150, 160, 600, "수확시 씨앗리필", TYPE_SEED},
    {"Quinoa", 200, 500, 3600, "", TYPE_SEED},
    {"Radish", 300, 700, 3600, "", TYPE_SEED},
    {"Spinach", 300, 1000, 7200, "", TYPE_SEED},
    {"Tomato", 50, 100, 100, "30분뒤 썩음", TYPE_SEED},
    {"Ulluco", 300, 350, 3600, "수확시 씨앗리필", TYPE_SEED},
    {"Vanilla", 500, 1000, 4800, "", TYPE_SEED},
    {"Watercress", 300, 1000, 600, "물없으면 썩음", TYPE_SEED},
    {"Xylosma", 500, 600, 3600, "인접방향 퍼짐", TYPE_SEED},
    {"Yam", 1000, 2000, 7200, "", TYPE_SEED},
    {"Zucchini", 2000, 4000, 36000, "", TYPE_SEED},

    // 장비류
    {"Land Deed", 1000, 0, 0, "다음 구역 해금", TYPE_EQUIP},
    {"Pesticide", 500, 0, 0, "병충해 0%", TYPE_EQUIP},
    {"Sprinkler", 10000, 0, 0, "자동 물주기", TYPE_EQUIP}
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
            default: 
                printw(" "); // 0(빈 땅)이거나 그 외
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

        // 선택된 아이템 강조
        if (item_idx == selected_idx) {
            attron(A_REVERSE | A_BOLD);
        }
        
        mvprintw(start_y + i, start_x + 4, "[%02d] %-15s : %2d 개", 
                 item_idx + 1, item_name, player.inv.items[item_idx].count);
        
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
        
        // 아이템 출력
        mvprintw(start_y + i, start_x + 4, "[%02d] %-15s | %3d G", 
                 item_idx + 1, shop_stock[real_idx].name, shop_stock[real_idx].buy_price);
        
        if (item_idx == selected_idx) {
            attroff(A_REVERSE | A_BOLD);
            // 선택된 아이템의 설명도 하단에 띄우기
            mvprintw(start_y + WIN_HEIGHT - 6, start_x + 4, "설명: %s", shop_stock[real_idx].explan);
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

    draw_rightwindow(player);
}

void draw_rightwindow(Player *player) {
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
}

void close_terminal() {
    endwin(); 
}