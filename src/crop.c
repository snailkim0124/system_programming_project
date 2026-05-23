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
            
            if(main_keyboard[i].crop_state >= 1 && main_keyboard[i].crop_state <= 4) pest_event(i);

            main_keyboard[i].growth_timer++; 

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