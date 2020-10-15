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

//ghosts
#define GHOSTS_START 100
#define GHOSTS_END   199 //preparation if anything
#define A   0+GHOSTS_START
#define B   1+GHOSTS_START
#define C   2+GHOSTS_START
#define D   3+GHOSTS_START
#define E   4+GHOSTS_START

#define PLAYER GHOSTS_START
#define P      PLAYER


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
    {X, 0, 0, 0, 0, X, 0, A, B, X, X, 0, 0, 0, X, 0, 0, 0, 0, X},
    {X, 0, 0, 0, 0, 0, 0, 0, C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, D, X, X, 0, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, E, X, X, 0, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, 0, 0, 0, 0, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, X, 0, 0, 0, 0, 0, P, 0, 0, 0, 0, 0, 0, 0, 0, X, 0, X},
    {X, 0, X, 0, 0, 0, 0, X, X, X, X, X, X, 0, 0, 0, 0, X, 0, X},
    {X, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, X},
    {X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},
};

struct areaSize {
    int w, h;
};

struct ghostSkin {
    char c[4];
    int color, bgcolor;
};

struct ghost {
    int x, y; // xy coordinates of the ghost
    int skin; // index into the array ghostSkins
};

struct ghostSkin ghostSkins[] = {
    {"@", RED, AREA_BGCOLOR},
    {"#", RED, AREA_BGCOLOR},
    {"!", CYAN, AREA_BGCOLOR},
    {"$", RED, CYAN},
};

struct ghost ghosts[] = {
    {-1, -1, 0},
    {-1, -1, 1},
    {-1, -1, 1},
    {-1, -1, 1},
    {-1, -1, 2},
    {-1, -1, 3},
};
