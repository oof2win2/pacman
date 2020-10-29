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

#include "opts.c"
#include "area.c"


int main()
{
    int w,h;
    int i,j;
    struct areaSize as;
    int screen[HEIGHT][WIDTH];
    
    setBackgroundColor(BLACK);
    cls();
    
    as = getAreaSize(area);
    putGhostsToArea(area, as, ghosts, 6, screen);
//    printf("%d %d\n", as.w, as.h);
    
    printArea(screen, as);
//    printGhostsPositions(screen, as);
    
    getch();
    cls();
    movePacman(area, as, ghosts, 5, 5);
    putGhostsToArea(area, as, ghosts, 6, screen);
    printArea(screen, as);
    
    setColor(GREY);
    setBackgroundColor(BLACK);
    
    return 0;
}



