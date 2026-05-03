#include "common.h"
#include "player.h"

Player player;

void player_init() {
    player.is_inventory_open = false;
    player.inv.money = 1000;
    strcpy(player.inv.items[0].name, "carrot");
    player.inv.items[0].count = 5;
}