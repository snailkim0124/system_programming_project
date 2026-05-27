#include "player.h"
#include "render.h"
#include "system.h"
#include "weather.h"

int game_tick = 0;

void handle_sigint(int sig) {
    save_game(&player); 

    close_terminal(); 

    printf("강제 종료 : 데이터를 자동 저장 합니다!\n");
    exit(0);
}

void handle_sigalrm(int sig) {
    game_tick = 1; // 1초 지났다고 체크
}

void init_terminal() {
    // 시그널 등록
    signal(SIGINT, handle_sigint);
    signal(SIGALRM, handle_sigalrm);

    // 타이머 셋업
    struct itimerval timer;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);

    weather_is_what(now_weather, &now_wind, &now_temp); // 날씨 설정
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
    init_pair(7, COLOR_WHITE, COLOR_RED); // 흰색 - 빨간색 > 병충해
    init_pair(8, COLOR_BLACK, COLOR_YELLOW); // 썩음
}

void close_terminal() {
    endwin(); 
}