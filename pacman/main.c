//
//  main.c
//  pacman
//
//  Created by Honza on 17/09/2020.
//  Copyright © 2020 oof2win2. All rights reserved.
//

#include <stdio.h>
#include "../utils/rlutil.h"

#include "opts.c"
#include "area.c"

int main(int argc, const char * argv[]) {
    struct areaSize levlDat = getAreaSize(area);
    printArea(area, levlDat);
    printf("w:%d h:%d\n", levlDat.w, levlDat.h);
    return 0;
}
