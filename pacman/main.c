//
//  main.c
//  pacman
//
//  Created by Honza on 17/09/2020.
//  Copyright © 2020 oof2win2. All rights reserved.
//



#include <stdio.h>
#include <stdlib.h>
#include "../utils/rlutil.h"

#define NUM_KEYS 8 //the number of total keys in the game

#include "opts.c"
#include "area.c"


int main()
{
    int w,h;
    int i,j;
    int key;
    struct areaSize as;
    int screen[HEIGHT][WIDTH];
    
    setBackgroundColor(BLACK);
    cls();
    
    as = getAreaSize(area);
    putGhostsToArea(area, as, ghosts, 6, screen);
//    printf("%d %d\n", as.w, as.h);
    
    printArea(screen, as);
//    printGhostsPositions(screen, as);
    
    while (1)
    {
        if (kbhit()) {
            key = getkey();
            for (int i = 0; i < 8; i++) {
                if (keys[i].key == key) {
                    movePacman(area, as, ghosts, keys[i].dx, keys[i].dy);
                    putGhostsToArea(area, as, ghosts, 6, screen);
                    cls();
                    printArea(screen, as);
                }
            }
        }
        msleep(10);
    }
    setColor(GREY);
    setBackgroundColor(BLACK);
    
    return 0;
}



