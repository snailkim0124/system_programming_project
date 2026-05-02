#ifndef RENDER_H
#define RENDER_H

#include "common.h"

// 키보드 전체를 그리는 함수
void draw_keyboard(int pressed_keycode);

// ncurses 초기화 및 종료 함수 (main을 깔끔하게 만들기 위함)
void init_terminal();
void close_terminal();

#endif