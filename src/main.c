#include "render.h"
#include "player.h"

int shop_idx = 0;

int main() {
    init_terminal();
    player_init();

    int ch = 0;

    draw_keyboard(-1); 

    while (1) {
        ch = getch(); 
        if (ch == 27) {
            if(draw_quit() == 1) {
                break;
            }
            else clear();
        } 

        if (ch == KEY_F(1)) {
            player.is_inventory_open = !player.is_inventory_open;
            player.is_store_open = false;
        }
        else if (ch == KEY_F(2)) {
            player.is_store_open = !player.is_store_open;
            player.is_inventory_open = false;
        }
        else if (ch == KEY_F(3)) {
            player.is_store_open = false;
            player.is_inventory_open = false;
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
                plant_seed();
            }

            draw_keyboard(-1); 
            draw_leftwindow(&player, player.inv.selected_slot);
        }
        else if (player.is_store_open) {
            if (ch == KEY_UP && shop_idx > 0) {
                shop_idx--;
                strcpy(player.ast_msg, ""); // 메시지 초기화
            }
            if (ch == KEY_DOWN && shop_idx < SHOP_ITEM_COUNT - 1) {
                shop_idx++;
                strcpy(player.ast_msg, ""); // 메시지 초기화
            }

            if(ch == '\n') {
                buy_item(&player, shop_idx);
            }

            draw_keyboard(-1); 
            draw_leftwindow(&player, shop_idx);
        }
        else {
            draw_keyboard(ch);
        }
    }

    close_terminal();

    return 0;
}
