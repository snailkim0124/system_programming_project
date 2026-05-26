#include "crop.h"
#include "render.h"
#include "common.h"

int get_crop_growth_time(char* crop_name) {
    for (int i = 0; i < SHOP_ITEM_COUNT; i++) {
        if (strcmp(shop_stock[i].name, crop_name) == 0) {
            return shop_stock[i].growth_time;
        }
    }
    return 30; // 예외용
}

int check_near_equip(int i, int found_state) {
    for (int j = 0; j < NUM_KEYS; j++) {
        // 장비 설치 됐다면?
        if (main_keyboard[j].crop_state >= 98) {
                    
            // 두 밭 거리 차이
            int dx = abs(main_keyboard[i].x - main_keyboard[j].x);
            int dy = abs(main_keyboard[i].y - main_keyboard[j].y);

            // 인접한 지?
            if ((dy == 0 && dx == 5) || (dy == 3 && dx <= 6)) {
                if (main_keyboard[j].crop_state == found_state) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void update_crops() {
    for (int i = 0; i < NUM_KEYS; i++) {
        if (main_keyboard[i].is_soil == 1) {
            if (main_keyboard[i].crop_state > 0 && main_keyboard[i].crop_state < 5) {
                if (main_keyboard[i].is_harm > 0) {
                    main_keyboard[i].harm_timer++; // 1초마다 방치 시간 1씩 증가!
                    
                    // 15초 동안 병충해 방치하면 사라짐
                    if (main_keyboard[i].harm_timer >= 15) {
                        main_keyboard[i].crop_state = 0;
                        main_keyboard[i].growth_timer = 0;
                        main_keyboard[i].is_harm = 0;
                        main_keyboard[i].harm_timer = 0;
                        strcpy(main_keyboard[i].planted_item_name, ""); 
                        
                        sprintf(player.ast_msg, "벌레를 방치해서 작물이 죽어버렸습니다!  ");
                        continue; // 죽었으니 아래의 성장 로직 스킵
                    }
                }

                int near_sprinkler = check_near_equip(i, 99);
                int near_scarecrow = check_near_equip(i, 98);
                
                // 농약 효과, 허수아비 효과, 28도 이하인 경우
                if (player.buff_pesticide_time <= 0 && !near_scarecrow && (now_temp <= 28)) pest_event(i);

                // 비료 효과, 스프링쿨러 효과, 비옴
                if (player.buff_fertilizer_time > 0 || near_sprinkler || now_weather == 2) {
                    main_keyboard[i].growth_timer += 2; // 2배 빨라짐
                }
                else main_keyboard[i].growth_timer++; 

                int total_time = get_crop_growth_time(main_keyboard[i].planted_item_name);

                int required_time = total_time / 4; 
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
            // 썩는 로직
            else if (main_keyboard[i].crop_state == 5 || main_keyboard[i].crop_state == 7) {
                main_keyboard[i].growth_timer++;
                
                // 30초 지나면 썩게
                if (main_keyboard[i].growth_timer >= 30) {
                    main_keyboard[i].crop_state = 6;
                    main_keyboard[i].growth_timer = 0; 
                    
                    sprintf(player.ast_msg, "제때 수확하지 않아 작물이 썩어버렸습니다!  ");
                }
            }
        }
    }
}

void pest_event(int selected_idx) {
    if(rand() % 100 < 1) {
        main_keyboard[selected_idx].is_harm = 1;
    }
}