
#include "save.h"
#include "render.h"

void save_game(Player *p) {
    int fd = open("save.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        sprintf(p->ast_msg, "저장 실패!");
        return;
    }

    write(fd, p, sizeof(Player));
    write(fd, main_keyboard, sizeof(Key) * NUM_KEYS);

    close(fd);
}

void load_game(Player *p) {
    int fd = open("save.dat", O_RDONLY);
    if (fd == -1) return;

    read(fd, p, sizeof(Player));
    read(fd, main_keyboard, sizeof(Key) * NUM_KEYS);

    close(fd);
}