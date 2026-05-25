
#include "save.h"
#include "render.h"
#include "crop.h"

double time_diff_ms(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
}

void save_game(Player *p) {
    int fd = open("save.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        sprintf(p->ast_msg, "저장 실패!");
        return;
    }

    write(fd, p, sizeof(Player));
    write(fd, main_keyboard, sizeof(Key) * NUM_KEYS);

    // 게임 종료 시간 저장
    struct timeval exit_tv;
    gettimeofday(&exit_tv, NULL); 

    write(fd, &exit_tv, sizeof(struct timeval));

    close(fd);
}

void load_game(Player *p) {
    int fd = open("save.dat", O_RDONLY);
    if (fd == -1) return;

    read(fd, p, sizeof(Player));
    read(fd, main_keyboard, sizeof(Key) * NUM_KEYS);

    struct timeval exit_tv;

    if(read(fd, &exit_tv, sizeof(struct timeval)) == sizeof(struct timeval)) {
        struct timeval now_tv;
        gettimeofday(&now_tv, NULL);
        
        int elapsed_seconds = (int)(time_diff_ms(exit_tv, now_tv) / 1000.0);

        if (elapsed_seconds < 0) elapsed_seconds = 0;

        // 나갔다 온 시간동안 자동 성장
        for(int i = 0; i < NUM_KEYS; i++) {
            if(main_keyboard[i].is_soil) {
                if(main_keyboard[i].crop_state > 0 && main_keyboard[i].crop_state < 5) {
                    int total_time = get_crop_growth_time(main_keyboard[i].planted_item_name);

                    int required_time = total_time / 4;
                    if (required_time <= 0) required_time = 1; 
        
                    int near_sprinkler = check_near_equip(i, 99);
                    int elapsed_now = elapsed_seconds;

                    if(near_sprinkler) {
                        elapsed_now *= 2;
                    }

                    // 방치된 시간 계산
                    int rem_stages = 5 - main_keyboard[i].crop_state;
                    int time_to_max = (rem_stages * required_time) - main_keyboard[i].growth_timer;

                    int sum_time = main_keyboard[i].growth_timer + elapsed_now;

                    int stage = sum_time / required_time; // 몇 단계 오를 수 있음?
                    int rest_time = sum_time % required_time; // 남은 시간

                    main_keyboard[i].crop_state += stage;

                    if (main_keyboard[i].crop_state >= 5) {

                        // 방치된 시간
                        int unattended_time = elapsed_now - time_to_max;

                        if (unattended_time >= 30) {
                            main_keyboard[i].crop_state = 6;
                            main_keyboard[i].growth_timer = 0;
                        }
                        else {
                            if (rand() % 100 < 10) {
                                main_keyboard[i].crop_state = 7;
                            } else {
                                main_keyboard[i].crop_state = 5;
                            }
                            main_keyboard[i].growth_timer = unattended_time; // 방치된 시간 넣기
                        }
                    } 
                    else {
                        // 아직 성장 남음
                        main_keyboard[i].growth_timer = rest_time;
                    }
                }
                // 썩는 로직
                else if (main_keyboard[i].crop_state == 5 || main_keyboard[i].crop_state == 7) {
                    main_keyboard[i].growth_timer += elapsed_seconds;
                    // 30초 지나면 썩게
                    if (main_keyboard[i].growth_timer >= 30) {
                        main_keyboard[i].crop_state = 6;
                        main_keyboard[i].growth_timer = 0; 
                        
                        sprintf(p->ast_msg, "제때 수확하지 않아 작물이 썩어버렸습니다!  ");
                    }
                }
            }
        }

    }

    close(fd);
}