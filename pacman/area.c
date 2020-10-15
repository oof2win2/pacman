//
//  area.c
//  pacman
//
//  Created by Honza on 15/10/2020.
//  Copyright © 2020 oof2win2. All rights reserved.
//

#include <stdio.h>


struct areaSize getAreaSize(int area[][MAXWIDTH]) {
    struct areaSize res;
    res.w = 0;              // just in case values not found
    res.h = 0;              // -''-
    int numFree = 0;        // number of free spaces found
    for (int y = MAXHEIGHT - 1; y >= 0 && !res.h; y--) { // to calculate max height
        numFree = 0;
        for (int x = MAXWIDTH - 1; x >= 0; x--) {
            if (area[y][x] == 0)
                numFree++;          // add to the number of free spaces
        }
        if (numFree != MAXWIDTH) {
            res.h = y + 1;          // the height of the game
            numFree = 0;
            break;
        }
    }
    
    for (int x = MAXWIDTH - 1; x >= 0 && !res.w; x--) { // calculate max width
        numFree = 0;
        for (int y = MAXHEIGHT - 1; y >= 0; y--) {
            if (area[y][x] == 0)
                numFree++;          // add to the number of free spaces
        }
        if (numFree != MAXHEIGHT) {
            res.w = x + 1;          // the width of the game
            break;
        }
    }
    return res;
}

void printArea(int area[][MAXWIDTH], struct areaSize lvlDat) {
    int w = lvlDat.w;
    int h = lvlDat.h;
    
    cls();
    saveDefaultColor();
    
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (area[y][x] == WALL) {
                setColor(BLUE);
                setBackgroundColor(RED);
                printf("X");
                resetColor();
            }
            else if (area[y][x] == DOT) {
                setColor(WHITE);
                setBackgroundColor(AREA_BGCOLOR);
                printf(".");
            }
            else if (area[y][x] == FREE) {
                setBackgroundColor(CYAN);
                setColor(GREEN);
                printf(" ");
            }
            else {
                printf("?");
            }
        }
        printf("\n");
    }
}

