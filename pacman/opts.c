#define AREA_BGCOLOR        BLUE
#define STATUS_BGCOLOR      BLACK
#define STATUS_TEXTCOLOR    GREY
#define STATUS_DIGITSCOLOR  LIGHTGREEN
#define SCORE_DIGITS    4
#define LIVES_DIGITS    1
#define LEVEL_DIGITS    1


    // zed ... 1
    // volne pole ... 2
    // tecka / dot ... 0
#define WALL  1
#define DOT   0
#define FREE  2
#define X   WALL
#define F   FREE
#define WIDTH    80
#define HEIGHT   25

    // Duchove
#define  GHOSTS_START    100
#define  GHOSTS_END      199
#define  A      101
#define  B      102
#define  C      103
#define  D      104
#define  E      105

    // Hrac
#define  PLAYER  GHOSTS_START
#define  P       PLAYER

int old_screen[HEIGHT][WIDTH]; // create screen

int area[HEIGHT][WIDTH] = {
    {X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,0,X,X,X,X,X,X,X,X,X,X,X},
    {X,0,0,0,0,0,0,X,0,0,0,X,0,0,X,X,0,X,0,0,0,0,X,0,0,0,0,X},
    {X,0,X,X,X,0,0,X,0,X,0,X,0,0,0,0,0,X,0,X,0,0,X,X,X,X,0,X},
    {X,0,X,0,0,0,0,X,0,X,0,X,0,X,0,0,0,0,0,X,0,0,0,0,0,0,0,X},
    {X,0,0,0,0,0,0,0,0,X,0,X,0,X,0,X,X,X,X,X,X,X,X,X,X,X,0,X},
    {X,X,X,X,X,X,X,0,0,X,0,0,0,X,0,X,0,0,0,0,0,X,0,0,0,X,0,X},
    {X,0,0,X,0,0,0,0,X,X,X,0,0,X,0,X,0,0,0,0,0,X,0,X,0,X,0,X},
    {X,0,0,X,0,0,0,0,0,0,X,X,X,X,0,X,0,0,0,0,0,0,0,X,0,0,0,X},
    {X,0,X,X,0,X,0,X,0,0,X,0,0,X,0,X,0,X,X,X,X,X,X,X,X,X,X,X},
    {X,0,0,X,0,X,0,X,0,X,X,0,0,X,0,X,0,0,0,0,0,0,0,X,0,0,0,0},
    {X,0,0,X,0,X,0,X,0,0,0,0,X,X,0,X,X,X,X,X,X,X,0,X,0,X,0,X},
    {X,0,0,X,0,X,0,X,0,X,X,X,X,0,0,0,0,X,0,0,0,X,0,X,0,X,0,X},
    {0,0,0,X,X,X,0,X,0,0,0,0,X,0,X,X,X,X,0,X,0,X,0,X,0,X,0,X},
    {0,0,0,0,0,0,0,X,0,0,X,0,0,0,0,0,0,0,0,X,0,0,0,0,0,X,0,X},
    {X,X,X,X,X,X,X,X,X,X,X,X,X,0,X,X,X,X,X,X,X,X,X,X,X,X,X,X},
};

struct areaSize {
    int w, h;
};

struct ghostSkin {
    char c[4]; // 3 znaky a nula
    int  color, bgcolor;
};

struct ghost {
    int x, y;
    int skin; // index do pole ghostSkins
};

struct ghostSkin ghostSkins[] = {
    {"@",  YELLOW, AREA_BGCOLOR}, // 0
    {"A",  RED,    AREA_BGCOLOR}, // 1
    {"B",  CYAN,   AREA_BGCOLOR}, // 2
    {"C",  GREEN,  YELLOW}        // 3
};

struct ghost ghosts[] = {
    {12, 5, 0}, // 0 = player
    {18, 6, 1}, // 1
    {24, 3, 1}, // 2
    {6,  6, 1}, // 3
    {5,  3, 2}, // 4
    {13,12, 3}, // 5
};

struct key_move {
    int key;
    int dx, dy;
};

struct key_move key_moves[] = {
    {KEY_UP, 0, -1},
    {KEY_DOWN, 0, 1},
    {KEY_LEFT, -1, 0},
    {KEY_RIGHT, 1, 0},
    {'w', 0, -1},
    {'s', 0, 1},
    {'a', -1, 0},
    {'d', 1, 0},
    {'W', 0, -1},
    {'S', 0, 1},
    {'A', -1, 0},
    {'D', 1, 0},
};

// modes:
//  1: before start
//  2: game playing
//  3: pause
//  4: win
//  5: dead
//  6: waiting for level starts
#define MODE_PRERUN 1   // before running the game
#define MODE_PLAY   2   // playing, only mode when moving
#define MODE_PAUSE  3   // when game is paused
#define MODE_WIN    4   // upon winning
#define MODE_CONFE  5   // confirm exit
#define MODE_DEAD   6   // when pacman fails and dies
#define MODE_WAITS  7   // wait when level starts

struct {
    int score;
    int level;
    int lives;
    int height; // map game height? not sure why its here, keep it there because it breaks otherwise
    int width;  // map width
    int totGhosts; //total number of ghosts + pacman
    int mode;
    int msgStartX;
    int msgStartY;
    int msgWidth;
    int msgHeight;
} game = {
    0,  // score
    1,  // level
    3,  // lives
    0,  // height
    0,  // width
    10, // total number of ghosts
    0,  // mode
    1,  // msg start x
    0,  // msg start y
    0,  // msg width
    0,  // msg height
};
