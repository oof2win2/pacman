struct areaSize getAreaSize(int a[][WIDTH])
{
    struct areaSize s;
    int i, j;
    
    s.w = -1;
    for (i = WIDTH - 1; i >= 0; i--) {
        for (j = 0; j < HEIGHT; j++) {
            if (a[j][i] != 0) {
                s.w = i + 1;
                break;
            }
        }
        if (s.w != -1)
            break;
    }
    
    s.h = -1;
    for (i = HEIGHT - 1; i > 0; i--) {
        for (j = 0; j < WIDTH; j++) {
            if (a[i][j] != 0) {
                s.h = i + 1;
                return s;
            }
        }
    }
    
    return s;
}

void printArea(int a[][WIDTH], struct areaSize s)
{
    int i, j;
    
    for (i = 0; i < s.h; i++) {
        for (j = 0; j < s.w; j++) {
            if (a[i][j] == WALL) {
                setBackgroundColor(RED);
                setColor(LIGHTBLUE);
                printf(" ");
            }
            else if (a[i][j] == DOT) {
                setBackgroundColor(AREA_BGCOLOR);
                setColor(YELLOW);
                printf(".");
            }
            else if (a[i][j] == FREE) {
                setBackgroundColor(AREA_BGCOLOR);
                printf(" ");
            }
            else if (a[i][j] >= GHOSTS_START && a[i][j] <= GHOSTS_END) {
                setColor(ghostSkins[ ghosts[ a[i][j] - GHOSTS_START ].skin ].color);
                setBackgroundColor(ghostSkins[ ghosts[ a[i][j] - GHOSTS_START ].skin ].bgcolor);
                printf("%s", ghostSkins[ ghosts[ a[i][j] - GHOSTS_START ].skin ].c);
            }
            else {
                setBackgroundColor(AREA_BGCOLOR);
                setColor(RED);
                printf("?");
            }
        }
        printf("\n");
    }
    
    setBackgroundColor(BLACK);
    setColor(GREY);
}

/*
 Vezmeme pole a_in[] a zkopírujeme ho do pole a_out[].
 Vezmeme duchy z pole ghosts[] a zkopírujeme je do pole a_out[].
 */
void putGhostsToArea(int a_in[][WIDTH], struct areaSize s, struct ghost ghosts[], int ghosts_num, int a_out[][WIDTH])
{
    int i, j;
    
    for (i = 0; i < s.h; i++) {
        for (j = 0; j < s.w; j++) {
            a_out[i][j] = a_in[i][j];
        }
    }
    
    for (i = 0; i < ghosts_num; i++) {
        a_out[ ghosts[i].y ][ ghosts[i].x ] = GHOSTS_START + i;
    }
}


void printGhostsPositions(int a[][WIDTH], struct areaSize s)
{
    int i, j;
    
    for (i = 0; i < s.h; i++) {
        for (j = 0; j < s.w; j++) {
            if (a[i][j] >= GHOSTS_START && a[i][j] <= GHOSTS_END) {
                printf("Ghost ID: %d, x: %d, y: %d\n", a[i][j] - GHOSTS_START, j, i);
            }
        }
    }
}

void movePacman(int a[][WIDTH], struct areaSize s, struct ghost ghosts[], int dx, int dy)
{
    ghosts[0].x += dx;
    ghosts[0].y += dy;
}
