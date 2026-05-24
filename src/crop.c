#include "crop.h"
#include "render.h"

int get_crop_growth_time(char* crop_name) {
    for (int i = 0; i < SHOP_ITEM_COUNT; i++) {
        if (strcmp(shop_stock[i].name, crop_name) == 0) {
            return shop_stock[i].growth_time;
        }
    }
    return 30; // 예외용
}

void update_crops() {
    for (int i = 0; i < NUM_KEYS; i++) {
        if (main_keyboard[i].is_soil == 1 && 
            main_keyboard[i].crop_state > 0 && 
            main_keyboard[i].crop_state < 5) {

            int near_sprinkler = 0;
            int near_scarecrow = 0;

            for (int j = 0; j < NUM_KEYS; j++) {
                // 장비 설치 됐다면?
                if (main_keyboard[j].crop_state >= 98) {
                    
                    // 두 밭 거리 차이
                    int dx = abs(main_keyboard[i].x - main_keyboard[j].x);
                    int dy = abs(main_keyboard[i].y - main_keyboard[j].y);

                    // 인접한 지?
                    if ((dy == 0 && dx == 5) || (dy == 3 && dx <= 6)) {
                        if (main_keyboard[j].crop_state == 99) {
                            near_sprinkler = 1;
                        }
                        else if (main_keyboard[j].crop_state == 98) {
                            near_scarecrow = 1;
                        }
                    }
                }
            }
            
            // 농약 효과, 허수아비 효과
            if (player.buff_pesticide_time <= 0 && !near_scarecrow) pest_event(i);

            // 비료 효과, 스프링쿨러 효과
            if (player.buff_fertilizer_time > 0 || near_sprinkler) {
                main_keyboard[i].growth_timer += 2; // 2배 빨라짐
            }
            else main_keyboard[i].growth_timer++; 

            int total_time = get_crop_growth_time(main_keyboard[i].planted_item_name);

            int required_time = total_time / 3; 
            // int required_time = 1; // 디버그용

            // 성장이 단계별로 되는 경우
            if (main_keyboard[i].growth_timer >= required_time) {
                main_keyboard[i].crop_state++;
                if (main_keyboard[i].crop_state == 5) {
                    if(rand() % 100 < 10) {
                        main_keyboard[i].crop_state = 7; // 황금 작물
                    } 
                }
                main_keyboard[i].growth_timer = 0; 
            }
        }
    }
}

void pest_event(int selected_idx) {
    if(rand() % 100 < 1) {
        main_keyboard[selected_idx].is_harm = 1;
    }
}