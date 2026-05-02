#include "render.h"

int main() {
    init_terminal();

    int ch = 0;
    
    draw_keyboard(-1); 

    while (1) {
        ch = getch(); 
        if (ch == 'q' || ch == 27) break; 

        draw_keyboard(ch);
        napms(100); 
        draw_keyboard(-1);
    }

    close_terminal();

    return 0;
}
