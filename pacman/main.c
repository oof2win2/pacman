#include <stdio.h>
#include <stdlib.h>
#include "../utils/rlutil.h"


// might be useful for mac/linux, the lib doesnt behave correctly
#ifndef _WIN32
    #undef  KEY_ENTER
    #define KEY_ENTER 10
    #undef  CLOCKS_PER_SEC
    #define CLOCKS_PER_SEC 15000
#endif


#include "opts.c"
#include "area.c"


int main()
{
    struct areaSize as;
    int i, key;
    int screen[HEIGHT][WIDTH];
    game.totGhosts = sizeof(ghosts);
    setBackgroundColor(BLACK);
    cls();
    
        // Pacman nesmi mit pod sebou tecku na zacatku
    if (area[ghosts[0].y][ghosts[0].x] == DOT)
        area[ghosts[0].y][ghosts[0].x] = FREE;
    
    as = getAreaSize(area);
    game.height = as.h;
    game.width = as.w;
    putGhostsToArea(area, as, ghosts, 6, old_screen);
        //printf("%d %d\n", as.w, as.h);
    printArea(old_screen, as);
    
        //printGhostsPositions(screen, as);
    
    hidecursor();
    while (1) {
        if (kbhit()) {
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
            printMessage("hellooooooooooooo");
//            msleep(2000);
            clearMessage();
//            msleep(1);
        }
        msleep(1);
    }
    showcursor();
    setColor(GREY);
    setBackgroundColor(BLACK);
    
    return 0;
}
