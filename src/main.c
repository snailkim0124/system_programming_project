#include "render.h"
#include "player.h"
#include "crop.h"

int shop_idx = 0;
ItemType shop_now_tab = TYPE_SEED;

int main() {
    init_terminal();
    player_init();

    int ch = 0;
    draw_keyboard(-1);  // 처음에만 렌더링 (깜박거림 방지)

    timeout(1000); // 1초씩 흐르게 하기 => 1초 동안 유저 입력을 기다림

    int count_down = 0;
    time_t last_time = time(NULL); // 시작 시간 기록

    while (1) {
        ch = getch(); 

        time_t current_time = time(NULL);        
        // 키보드 연타 방지 및 현실 1초가 지난 경우
        if (current_time - last_time >= 1) {
            last_time = current_time;
            count_down++;

            // 도구 효과
            if (player.buff_fertilizer_time > 0) {
                player.buff_fertilizer_time--;
                if (player.buff_fertilizer_time == 0) {
                    strcpy(player.ast_msg, "비료 효과가 끝났습니다!");
                }
            }
            if (player.buff_pesticide_time > 0) {
                player.buff_pesticide_time--;
                if (player.buff_pesticide_time == 0) {
                    strcpy(player.ast_msg, "농약 효과가 끝났습니다!");
                }
            }
            
            update_crops();

            // 10초마다
            if (count_down % 10 == 0) {
                save_game(&player);
                if (strlen(player.ast_msg) ==  0) strcpy(player.ast_msg, "자동 저장 완료!");
                count_down = 0;
            }
        }

        erase();

        // getch()가 -1을 내는 것을 방지
        if (ch != ERR) {
            flushinp(); // 이전 입력 버퍼 지우기 (막 입력하는거 방지)

            if (ch == 27) {
                if (draw_quit() == 1)  {
                    save_game(&player);
                    break; // 종료하기 전 저장
                }
            }

            if (ch == KEY_F(1)) {
                player.is_inventory_open = !player.is_inventory_open;
                player.is_store_open = false;
                strcpy(player.ast_msg, ""); // 메시지 초기화
            }
            else if (ch == KEY_F(2)) {
                player.is_store_open = !player.is_store_open;
                player.is_inventory_open = false;
                strcpy(player.ast_msg, ""); // 메시지 초기화
            }
            else if (ch == KEY_F(3)) {
                player.is_store_open = false;
                player.is_inventory_open = false;
                strcpy(player.ast_msg, ""); // 메시지 초기화
            }
        }

        if(player.is_inventory_open) {
            int max_slot = player.inv.current_item_count > 0 ? player.inv.current_item_count - 1 : 0;

            if (ch == KEY_UP && player.inv.selected_slot > 0) {
                player.inv.selected_slot--;
                strcpy(player.ast_msg, ""); // 메시지 초기화
            }
            if (ch == KEY_DOWN && player.inv.selected_slot < max_slot) {
                player.inv.selected_slot++;
                strcpy(player.ast_msg, ""); // 메시지 초기화
            } 

            if (ch == '\n') {
                use_item();
            }

            draw_keyboard(-1); 
            draw_leftwindow(&player, -1, -1);
        }
        else if (player.is_store_open) {
            // 현재 상점 탭의 아이템 개수 세기
            int tab_item_count = 0;
            for (int i = 0; i < SHOP_ITEM_COUNT; i++) {                
                if (shop_stock[i].item_type == shop_now_tab) { 
                    tab_item_count++;
                }
            }

            if (ch == KEY_UP && shop_idx > 0) {
                shop_idx--;
                strcpy(player.ast_msg, ""); // 메시지 초기화
            }
            if (ch == KEY_DOWN && shop_idx < tab_item_count - 1) {
                shop_idx++;
                strcpy(player.ast_msg, ""); // 메시지 초기화
            }

            // 상점 탭 이동
            if (ch == KEY_LEFT && shop_now_tab != TYPE_SEED) {
                shop_now_tab = TYPE_SEED;
                shop_idx = 0; 
                strcpy(player.ast_msg, "");
            }
            if (ch == KEY_RIGHT && shop_now_tab != TYPE_EQUIP) {
                shop_now_tab = TYPE_EQUIP;
                shop_idx = 0;
                strcpy(player.ast_msg, "");
            }

            if(ch == '\n') {
                int selected_idx = 0;
                int count = 0;

                for(int i = 0 ; i < SHOP_ITEM_COUNT; i++) {
                    if(shop_stock[i].item_type == shop_now_tab) {
                        if(count == shop_idx) {
                            selected_idx = i;
                            break;
                        }
                        count++;
                    }
                }

                buy_item(&player, selected_idx);
            }

            draw_keyboard(-1); 
            draw_leftwindow(&player, shop_idx, shop_now_tab);
        }
        else {
            if(ch != ERR) {
                remove_pest(&player, ch); // 병충해 없애기
                sell_item(&player, ch); // 팔기
            }
            draw_keyboard(ch == ERR ? -1 : ch);
        }

        refresh();
    }

    close_terminal();

    return 0;
}
