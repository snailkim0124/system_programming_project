#ifndef CROP_H
#define CROP_H

#include <stdlib.h>
#include <string.h>

int get_crop_growth_time(char* crop_name);
int check_near_equip(int i, int found_state);
void update_crops();
void pest_event(int selected_idx);

#endif