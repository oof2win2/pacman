//
//  opts.c
//  pacman
//
//  Created by Honza on 15/10/2020.
//  Copyright © 2020 oof2win2. All rights reserved.
//

#include <stdio.h>

#define WALL 1
#define FREE 2
#define DOT  0
#define X WALL
#define F FREE

#define MAXWIDTH    80
#define MAXHEIGHT   25

#define AREA_BGCOLOR BLACK


// 0s are dots, Fs are free spaces
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
    {X, 0, 0, 0, 0, X, 0, 0, 0, F, F, 0, 0, 0, X, 0, 0, 0, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, F, F, F, F, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, F, F, F, F, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, 0, 0, 0, 0, 0, 0, 0, F, F, 0, 0, 0, 0, 0, 0, 0, 0, X},
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

struct ghostSkin {
    char c;
    int bgcolor, color;
};

struct ghost {
    int x, y;
    
};

struct ghostSkin ghostSkins[] = {
    {'A', RED, AREA_BGCOLOR},
};
