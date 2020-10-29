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

// dark magic to make unix systems work
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
            // the sizeof(keys) gets the byte size of array
            for (int i = 0; i < (sizeof(keys)/sizeof(key)); i++) {
                if (keys[i].key == key) {
                    movePacman(area, as, ghosts, keys[i].dx, keys[i].dy);
                    putGhostsToArea(area, as, ghosts, 6, screen);
                    cls();
                    printArea(screen, as);
                    break;
                }
            }
        }
        msleep(10);
    }
    setColor(GREY);
    setBackgroundColor(BLACK);
    
    return 0;
}



