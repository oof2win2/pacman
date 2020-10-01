//
//  main.c
//  pacman
//
//  Created by Honza on 17/09/2020.
//  Copyright © 2020 oof2win2. All rights reserved.
//

#include <stdio.h>
#include "../utils/rlutil.h"

#define WALL 1
#define FREE 0
#define X WALL
#define F FREE

#define MAXWIDTH    80
#define MAXHEIGHT   25

int area[MAXHEIGHT][MAXWIDTH] = {
    {X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},
    {X, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, X, X, X, X, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, X, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, X, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, 0, 0, 0, 0, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, 0, X, X, 0, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, 0, X, X, 0, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, X},
    {X, 0, 0, 0, 0, 0, 0, 0, 0, X, X, 0, 0, 0, 0, 0, 0, 0, 0, X},
    {X, 0, 0, 0, 0, X, 0, 0, 0, 0, 0, 0, 0, 0, X, 0, 0, 0, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, 0, 0, 0, 0, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, 0, 0, 0, 0, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, X},
    {X, 0, 0, 0, 0, X, 0, 0, 0, X, X, 0, 0, 0, X, 0, 0, 0, 0, X},
    {X, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, 0, X, X, 0, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, 0, X, X, 0, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, 0, 0, 0, 0, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, X, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, X, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, X, X, X, X, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, X},
    {X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},
};

struct areaSize {
    int w, h;
};

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

int main(int argc, const char * argv[]) {
    struct areaSize res = getAreaSize(area);
    printf("%d %d\n", res.w, res.h);
    return 0;
//    int w, h;
//    h = MAXHEIGHT-3;
//    w = MAXWIDTH-60;
//    cls();
//    saveDefaultColor();
//
//    for (int y = 0; y < h; y++) {
//        for (int x = 0; x < w; x++) {
//            if (area[y][x] == WALL) {
//                setColor(BLUE);
//                setBackgroundColor(RED);
//                printf("X ");
//                resetColor();
//            }
//            else if (area[y][x] == FREE) {
//                setColor(GREEN);
//                printf(". ");
//            }
//            else {
//                printf("? ");
//            }
//        }
//        printf("\n");
//    }
    return 0;
}
