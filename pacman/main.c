#include <stdio.h>
#include <stdlib.h>
#include "../utils/rlutil.h"

#include "opts.c"
#include "area.c"


int main()
{
    struct areaSize as;
    int screen[HEIGHT][WIDTH], old_screen[HEIGHT][WIDTH];
    int i, key;
    game.totGhosts = sizeof(ghosts);
    setBackgroundColor(BLACK);
    cls();
    
        // Pacman nesmi mit pod sebou tecku na zacatku
    if (area[ghosts[0].y][ghosts[0].x] == DOT)
        area[ghosts[0].y][ghosts[0].x] = FREE;
    
    as = getAreaSize(area);
    game.height = as.h;
    putGhostsToArea(area, as, ghosts, 6, old_screen);
        //printf("%d %d\n", as.w, as.h);
    printArea(old_screen, as);
    
        //printGhostsPositions(screen, as);
    
    hidecursor();
    while (1) {
//        if (kbhit()) {
            key = getkey();
            
            for (i = 0; i < sizeof(key_moves)/sizeof(struct key_move); i++) {
                if (key_moves[i].key == key) {
                    movePacman(area, as, ghosts, key_moves[i].dx, key_moves[i].dy);
                    break;
                }
            }
            
            putGhostsToArea(area, as, ghosts, 6, screen);
            printAreaChanges(old_screen, screen, as);
//            printArea(screen, as);
            printMessage("hello there", as);
//        }
    }
    showcursor();
    setColor(GREY);
    setBackgroundColor(BLACK);
    
    return 0;
}
