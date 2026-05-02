#include "render.h"

// 우측 끝이 x=57에 딱 맞도록 정밀하게 계산된 배열입니다.
Key main_keyboard[] = {
    // Row 0 (Function Keys)
    { 2,  2, 7,  "ESC",   27 },
    { 2, 11, 6,  "F1",    KEY_F(1) },
    { 2, 18, 6,  "F2",    KEY_F(2) },
    { 2, 25, 6,  "F3",    KEY_F(3) },
    { 2, 32, 6,  "F4",    KEY_F(4) },

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

    // Row 2 (QWE...)
    { 7,  2, 7,  "TAB",   '\t' }, 
    { 7,  9, 5,  "Q",     'q' },
    { 7, 14, 5,  "W",     'w' },
    { 7, 19, 5,  "E",     'e' },
    { 7, 24, 5,  "R",     'r' },
    { 7, 29, 5,  "T",     't' },
    { 7, 34, 5,  "Y",     'y' },
    { 7, 39, 5,  "U",     'u' },
    { 7, 44, 5,  "I",     'i' },
    { 7, 49, 8,  "BSP",   KEY_BACKSPACE }, // 너비 조정으로 우측 끝 맞춤

    // Row 3 (ASD...)
    { 9,  2, 8,  "CTRL",  26 },    
    { 9, 10, 5,  "A",     'a' },
    { 9, 15, 5,  "S",     's' },
    { 9, 20, 5,  "D",     'd' },
    { 9, 25, 5,  "F",     'f' },
    { 9, 30, 5,  "G",     'g' },
    { 9, 35, 5,  "H",     'h' },
    { 9, 40, 5,  "J",     'j' },
    { 9, 45, 12, "ENTER", '\n' },  // 너비 조정으로 우측 끝 맞춤

    // Row 4 (ZXC...) - 요청하신 Z열 추가!
    { 11,  2, 10, "SHIFT", -1 },   // Left Shift
    { 11, 12, 5,  "Z",     'z' },
    { 11, 17, 5,  "X",     'x' },
    { 11, 22, 5,  "C",     'c' },
    { 11, 27, 5,  "V",     'v' },
    { 11, 32, 5,  "B",     'b' },
    { 11, 37, 5,  "N",     'n' },
    { 11, 42, 5,  "M",     'm' },
    { 11, 47, 10, "SHIFT", -1 },   // Right Shift

    // Row 5 (Spacebar)
    { 13, 15, 27, "SPACE", ' ' }   // 스페이스바 추가
};

#define NUM_KEYS (sizeof(main_keyboard) / sizeof(Key))

void draw_single_key(Key* key, int highlighted) {
    int y = key->y;
    int x = key->x;
    int w = key->width;

    if (highlighted) attron(A_REVERSE);

    // 상단 선
    mvaddch(y, x, ACS_ULCORNER);
    for (int i = 0; i < w - 2; i++) addch(ACS_HLINE);
    addch(ACS_URCORNER);

    // 중간 선 및 텍스트
    mvaddch(y + 1, x, ACS_VLINE);
    
    int label_len = strlen(key->label);
    int padding = (w - 2 - label_len) / 2;
    for(int i=0; i<padding; i++) addch(' ');
    printw("%s", key->label);
    for(int i=0; i< (w - 2 - label_len - padding); i++) addch(' ');

    mvaddch(y + 1, x + w - 1, ACS_VLINE);

    // 하단 선
    mvaddch(y + 2, x, ACS_LLCORNER);
    for (int i = 0; i < w - 2; i++) addch(ACS_HLINE);
    addch(ACS_LRCORNER);

    if (highlighted) attroff(A_REVERSE);
}

void draw_keyboard(int pressed_keycode) {
    erase(); 
    mvprintw(0, 2, "Z열과 스페이스바가 추가된 키보드 (종료: 'q' 두 번 또는 ESC)");
    
    for (int i = 0; i < NUM_KEYS; i++) {
        int is_pressed = (main_keyboard[i].keycode == pressed_keycode);
        draw_single_key(&main_keyboard[i], is_pressed);
    }
    refresh();
}

void init_terminal() {
    setlocale(LC_ALL, ""); 
    initscr();
    cbreak();             
    noecho();             
    keypad(stdscr, TRUE); 
    curs_set(0);   
}

void close_terminal() {
    endwin(); 
}