#include "crop.h"
#include "render.h"

int get_crop_growth_time(char* crop_name) {
    for (int i = 0; i < SHOP_ITEM_COUNT; i++) {
        if (strcmp(shop_stock[i].name, crop_name) == 0) {
            return shop_stock[i].growth_time;
        }
    }
    return 30;
}

void update_crops() {
    for (int i = 0; i < NUM_KEYS; i++) {
        if (main_keyboard[i].is_soil == 1 && 
            main_keyboard[i].crop_state > 0 && 
            main_keyboard[i].crop_state < 4) {
            
            main_keyboard[i].growth_timer++; 

            int total_time = get_crop_growth_time(main_keyboard[i].planted_item_name);

            int required_time = total_time / 3; 
            // int required_time = 1; // 디버그용

            if (required_time <= 0) required_time = 1; 

            if (main_keyboard[i].growth_timer >= required_time) {
                main_keyboard[i].crop_state++;     
                main_keyboard[i].growth_timer = 0; 
            }
        }
    }
}