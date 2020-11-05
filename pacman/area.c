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

void printAreaChar(int currChar)
{
    // This function prints a single character from the array of the map, single point
    
    if (currChar == WALL) {
        setBackgroundColor(RED);
        setColor(LIGHTBLUE);
        printf(" ");
    }
    else if (currChar == DOT) {
        setBackgroundColor(AREA_BGCOLOR);
        setColor(YELLOW);
        printf(".");
    }
    else if (currChar == FREE) {
        setBackgroundColor(AREA_BGCOLOR);
        printf(" ");
    }
    else if (currChar >= GHOSTS_START && currChar <= GHOSTS_END) {
        setColor(ghostSkins[ghosts[currChar - GHOSTS_START ].skin].color);
        setBackgroundColor(ghostSkins[ghosts[currChar - GHOSTS_START].skin ].bgcolor);
        printf("%s", ghostSkins[ghosts[currChar - GHOSTS_START].skin].c);
    }
    else {
        setBackgroundColor(AREA_BGCOLOR);
        setColor(RED);
        printf("?");
    }
    
    setBackgroundColor(BLACK);
    setColor(GREY);
}

void printArea(int a[][WIDTH], struct areaSize s)
{
    for (int y = 0; y < s.h; y++) {
        for (int x = 0; x < s.w; x++) {
            printAreaChar(a[y][x]);
        }
        printf("\n");
    }
    return;
}

void printAreaChanges(int newA[][WIDTH], int oldA[][WIDTH], struct areaSize s)
{
    // This function prints only the changes in the game
    
    for (int y = 0; y < s.h; y++) {
        for (int x = 0; x < s.w; x++) {
            if (newA[y][x] != oldA[y][x]) {
                gotoxy(x+1, y+1);
                printAreaChar(newA[y][x]);
                oldA[y][x] = newA[y][x];
            }
        }
        printf("\n");
    }
    return;
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
