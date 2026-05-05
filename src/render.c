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
    { 5, 57, 8,  "BSP",   KEY_BACKSPACE },

    // Row 2 (QWE...)
    { 8,  2, 7,  "TAB",   '\t' }, 
    { 8,  9, 5,  "Q",     'q',  1,  0 },
    { 8, 14, 5,  "W",     'w',  1,  1 },
    { 8, 19, 5,  "E",     'e',  1,  1 },
    { 8, 24, 5,  "R",     'r',  1,  1 },
    { 8, 29, 5,  "T",     't',  1,  1 },
    { 8, 34, 5,  "Y",     'y',  1,  1 },
    { 8, 39, 5,  "U",     'u',  1,  1 },
    { 8, 44, 5,  "I",     'i',  1,  1 },
    { 8, 49, 5,  "O",     'o',  1,  1 },
    { 8, 54, 5,  "P",     'p',  1,  1 },

    // Row 3 (ASD...)
    { 11,  2, 8,  "CAPS",  10 },    
    { 11, 10, 5,  "A",     'a',  1,  0 },
    { 11, 15, 5,  "S",     's',  1,  1 },
    { 11, 20, 5,  "D",     'd',  1,  1 },
    { 11, 25, 5,  "F",     'f',  1,  1 },
    { 11, 30, 5,  "G",     'g',  1,  1 },
    { 11, 35, 5,  "H",     'h',  1,  1 },
    { 11, 40, 5,  "J",     'j',  1,  1 },
    { 11, 45, 5,  "K",     'k',  1,  1 },
    { 11, 50, 5,  "L",     'l',  1,  1 },
    { 11, 55, 10, "ENTER", '\n' },  

    // Row 4 (ZXC...)
    { 14,  2, 10, "SHIFT", -1 },   // Left Shift
    { 14, 12, 5,  "Z",     'z',  1,  0 },
    { 14, 17, 5,  "X",     'x',  1,  1 },
    { 14, 22, 5,  "C",     'c',  1,  1 },
    { 14, 27, 5,  "V",     'v',  1,  1 },
    { 14, 32, 5,  "B",     'b',  1,  1 },
    { 14, 37, 5,  "N",     'n',  1,  1 },
    { 14, 42, 5,  "M",     'm',  1,  1 },
    { 14, 47, 10, "SHIFT", -1 },   // Right Shift

    // Row 5 (Spacebar)
    { 17, 2, 8, "CTRL", 162 },
    { 17, 10, 5, "WIN", 162 },
    { 17, 15, 27, "SPACE", ' ' },
};

Store shop_stock[] = {
    {"당근 씨앗", 50, "평범한 당근이다."},
    {"감자 씨앗", 80, "강원도의 힘!"},
    {"황금 씨앗", 500, "매우 비싼 작물."},
    {"비료", 30, "성장 속도 UP"}
};

#define NUM_KEYS (sizeof(main_keyboard) / sizeof(Key))

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
    printw("%s", key->is_locked ? "#" : key->label);
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
    erase(); 
    mvprintw(0, 2, "농장게임 (종료: ESC)");
    
    for (int i = 0; i < NUM_KEYS; i++) {
        int is_pressed = (main_keyboard[i].keycode == pressed_keycode);
        draw_single_key(&main_keyboard[i], is_pressed);
    }

    mvprintw(20, 2, "F1 : 인벤토리\tF2 : 상점\tF3 : 농장");

    refresh();
}

void draw_inventory(int start_y, int start_x) {
    // 아이템 목록 출력
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (i == player.inv.selected_slot) {
            attron(A_REVERSE); // 선택된 칸 강조
        }
        mvprintw(start_y + i, start_x + 4, "[%d] %-15s : %d 개", 
                 i + 1, player.inv.items[i].name, player.inv.items[i].count);
        if (i == player.inv.selected_slot) {
            attroff(A_REVERSE);
        }
    }

    mvprintw(start_y + WIN_HEIGHT - 5, start_x, "현재 잔액: %d G", player.inv.money);
    mvprintw(start_y + WIN_HEIGHT - 4, start_x, "(닫기: F1 / 이동: 화살표)");
}

void draw_store(int start_y, int start_x, int selected_idx) {
    // 2. 판매 목록 출력
    for (int i = 0; i < SHOP_ITEM_COUNT; i++) {
        if (i == selected_idx) attron(A_REVERSE); // 현재 선택된 물건
        
        mvprintw(start_y + i, start_x + 4, "[%d] %-15s | 가격: %3d G", 
                 i + 1, shop_stock[i].name, shop_stock[i].price);
        
        if (i == selected_idx) {
            attroff(A_REVERSE);
            // 선택된 아이템의 설명을 하단에 출력
            mvprintw(start_y + WIN_HEIGHT - 6, start_x + 4, "설명: %s", shop_stock[i].explan);
        }
    }

    mvprintw(start_y + WIN_HEIGHT - 5, start_x, "현재 잔액: %d G", player.inv.money);
    mvprintw(start_y + WIN_HEIGHT - 4, start_x, "(닫기: F2 / 이동: 화살표)");
}

void draw_subwindow(Player *player, int selected_idx) {
    if (player->is_inventory_open && player->is_store_open) return;

    int start_y = 23, start_x = 10;
    int height = 12, width = 40; // 창 크기 고정
    char subtitle[20];

    // 1. 제목 및 색상 결정
    int color = 1;
    if (player->is_inventory_open) {
        strcpy(subtitle, " INVENTORY ");
        color = 1; // 금색
    } else if (player->is_store_open) {
        strcpy(subtitle, " SEED STORE ");
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

    // 3. 내용물 그리기 (프레임 안쪽 좌표를 넘겨주면 더 좋음)
    if (player->is_inventory_open) {
        draw_inventory(start_y + 2, start_x + 2);
    } else if (player->is_store_open) {
        draw_store(start_y + 2, start_x + 2, selected_idx);
    }
}

void init_terminal() {
    setlocale(LC_ALL, ""); 
    initscr();
    cbreak();             
    noecho();             
    keypad(stdscr, TRUE); 
    curs_set(0);   
    // 색깔 부분
    start_color();
    use_default_colors();
    init_pair(1, 94, -1); // 94번은 갈색 계열, -1은 투명 배경
}

void close_terminal() {
    endwin(); 
}