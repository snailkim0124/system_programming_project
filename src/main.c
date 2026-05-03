#include "render.h"
#include "player.h"

int main() {
    init_terminal();
    player_init();

    int ch = 0;

    draw_keyboard(-1); 

    while (1) {
        ch = getch(); 
        if (ch == 27) break; 

        if (ch == KEY_F(1)) {
            player.is_inventory_open = !player.is_inventory_open;
        }

        if(player.is_inventory_open) {
            if (ch == KEY_UP && player.inv.selected_slot > 0) player.inv.selected_slot--;
            if (ch == KEY_DOWN && player.inv.selected_slot < MAX_ITEMS - 1) player.inv.selected_slot++;

            draw_keyboard(-1); // 배경 깔아주기
            draw_inventory(&player);
        }
        else {
            draw_keyboard(ch);
        }
    }

    close_terminal();

    return 0;
}
