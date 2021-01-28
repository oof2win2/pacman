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

// prints one sign from the area, x y pos needs to be done already
void printAreaChar(int f)
{
    if (f == WALL) {
        setBackgroundColor(RED);
        setColor(LIGHTBLUE);
        printf(" ");
    }
    else if (f == DOT) {
        setBackgroundColor(AREA_BGCOLOR);
        setColor(YELLOW);
        printf(".");
    }
    else if (f == FREE) {
        setBackgroundColor(AREA_BGCOLOR);
        printf(" ");
    }
    else if (f >= GHOSTS_START && f <= GHOSTS_END) {
        setColor(ghostSkins[ ghosts[ f - GHOSTS_START ].skin ].color);
        setBackgroundColor(ghostSkins[ ghosts[ f - GHOSTS_START ].skin ].bgcolor);
        printf("%s", ghostSkins[ ghosts[ f - GHOSTS_START ].skin ].c);
    }
    else {
        setBackgroundColor(AREA_BGCOLOR);
        setColor(RED);
        printf("?");
    }
}

// annoying stuff
void home() {
    fflush(stdout);
    gotoxy(1, HEIGHT+15);
}

// prints the changes in area
void printAreaChanges(int o[][WIDTH], int n[][WIDTH], struct areaSize s)
{
    int i, j;
    
    for (i = 0; i < s.h; i++) {
        for (j = 0; j < s.w; j++) {
            if (o[i][j] != n[i][j]) {
                gotoxy(j + 1, i + 1);
                printAreaChar(n[i][j]);
                home();
                o[i][j] = n[i][j];
            }
        }
    }
    home();
    
    setBackgroundColor(BLACK);
    setColor(GREY);
}


// prints $num to the screen, adds enough spaces so the number is $length long
void printNum(int num, int length)
{
    int digits = 1, mulTen = 10, i;
    // get the amount of digits from that the number has
    for (; num >= mulTen; digits++, mulTen *= 10)
    for (i = 0; i < length - digits; i++)
        printf(" "); // print the spaces before it
    printf("%d", num);
    home();
}

// prints the whole area and stats
void printArea(int a[][WIDTH], struct areaSize s)
{
    int i, j;
    
    for (i = 0; i < s.h; i++) {
        for (j = 0; j < s.w; j++) {
            printAreaChar(a[i][j]);
        }
        printf("\n");
    }
    
    setBackgroundColor(STATUS_BGCOLOR);
    setColor(STATUS_TEXTCOLOR);
    printf("LEVEL: ");
    setColor(STATUS_DIGITSCOLOR);
    printNum(game.level, LEVEL_DIGITS);
    setColor(STATUS_TEXTCOLOR);
    printf(" LIVES: ");
    setColor(STATUS_DIGITSCOLOR);
    printNum(game.lives, LIVES_DIGITS);
    setColor(STATUS_TEXTCOLOR);
    printf(" SCORE: ");
    setColor(STATUS_DIGITSCOLOR);
    printNum(game.score, SCORE_DIGITS);
    home();
}

// changes the score and prints digits
void changeScore(int points)
{
    game.score += points; // add points
    // go to the correct position on-screen
    gotoxy(24 + LEVEL_DIGITS + LIVES_DIGITS, game.height + 1);
    setBackgroundColor(STATUS_BGCOLOR);
    setColor(STATUS_DIGITSCOLOR);
    // print the actual digits on the spot, the xy cursor is already prset above
    printNum(game.score, SCORE_DIGITS);
    home();
}

void putGhostsToArea(int a_in[][WIDTH], struct areaSize s, struct ghost ghosts[], int ghosts_num, int a_out[][WIDTH])
{
    int i, j;
    
    for (i = 0; i < s.h; i++) {
        for (j = 0; j < s.w; j++) {
            a_out[i][j] = a_in[i][j];
        }
    }
    
    for (i = 0; i < ghosts_num; i++) {
        a_out[ghosts[i].y][ghosts[i].x] = GHOSTS_START + i;
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
    int x, y;
    
    // cant go out of game area
    x = ghosts[0].x + dx;
    y = ghosts[0].y + dy;
    if (x < 0 || y < 0 || x >= s.w || y >= s.h)
        return;
    
    // walls stop pacman
    if (a[y][x] == WALL)
        return;
    
    // collect dots and add 10 pts for each dot
    if (a[y][x] == DOT) {
        a[y][x] = FREE;
        changeScore(10);
    }
    
    ghosts[0].x += dx;
    ghosts[0].y += dy;
}

void printMessage(char msg[])
{
    saveDefaultColor();
    setColor(MSG_COLOR);
    setBackgroundColor(MSG_BGCOLOR);
    int totLineNum = 0, maxLineLen = 0;
    
    int currLineLen = 0;
    int i = 0;
    do {
        if (msg[i] == '\n' || msg[i] == '\0') {
            totLineNum++;
            if (maxLineLen < currLineLen) maxLineLen = currLineLen;
            currLineLen = 0;
        } else {
            currLineLen++;
        }
    } while ( msg[i++] != '\0');
    
    int startx, starty;
    if (maxLineLen + 6 >= game.width) startx = 1;
    else startx = 1 + (game.width - (maxLineLen + 6))/2;
    if (totLineNum + 4 >= game.height) starty = 1;
    else starty = 1 + (game.height - (totLineNum + 4))/2;
    
    // box top
    gotoxy(startx, starty);
    for (int i = 0; i < maxLineLen + 6; i++) printf("*");
    gotoxy(startx, starty+1);
    printf("*");
    for (int i = 0; i < maxLineLen + 4; i++) printf(" ");
    printf("*");
    
    int c_i = 0;
    for (int lineNum = 1; lineNum <= totLineNum; lineNum++) {
        gotoxy(startx, starty+lineNum+1);
        printf("*  ");
        for (int i = 0; i < maxLineLen; i++) {
            if (msg[c_i] != '\n' && msg[c_i] != '\0')
                printf("%c", msg[c_i++]);
            else
                printf(" ");
        }
        c_i++;
        printf("  *");
    }
    gotoxy(startx, starty+totLineNum+2);
    printf("*");
    for (int i = 0; i < maxLineLen + 4; i++) printf(" ");
    printf("*");
    gotoxy(startx, starty+totLineNum+3);
    for (int i = 0; i < maxLineLen + 6; i++) printf("*");
    
    game.msgStartX = startx;
    game.msgStartY = starty;
    game.msgHeight = totLineNum + 4;
    game.msgWidth  = maxLineLen + 6;
    home();
    resetColor();
}

void clearMessage()
{
    for (int y = game.msgStartY; y < (game.msgHeight+game.msgStartY); y++) {
        gotoxy(game.msgStartX, y);
        for (int x = game.msgStartX; x < (game.msgWidth+game.msgStartX); x++) {
            if (x <= game.width && y <= game.height) {
                printAreaChar(old_screen[y-1][x-1]);
            } else {
                setBackgroundColor(STATUS_BGCOLOR);
                printf(" ");
            }
        }
    }
    home();
}

void changeMode(int newMode)
{
    if (game.mode == 3) {
        clearMessage();
    }

    if (newMode == 3) {
        printMessage("Game is paused\nPress SPACE to unpause");
    }

    game.mode = newMode;
    home();
    return;
}

void confirmExit()
{
    printMessage("Are you sure you want to exit the game?\nPress ESC again to confirm");
    int key = getkey();
    clearMessage();
    if (key == KEY_ESCAPE) exit(0);
}
