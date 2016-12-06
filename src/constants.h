#ifndef _CONSTANTS_H
#define _CONSTANTS_H
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr) { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr) { if (ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if (ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr) { if (ptr) { (ptr)->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr) { if (ptr) { (ptr)->onResetDevice(); } }
// Color which should be transparent
#define TRANSCOLOR D3DCOLOR_XRGB(255, 0, 255)

//-----------------------------------------------
// Constants
//-----------------------------------------------
const int SCALE = 2;

// Images are of 2x of screen size
const int SCALE_2X_ARR[] = { 0.5, 1, 1.5 };
const int SCALE_2X = SCALE_2X_ARR[SCALE - 1];

const int TILE_SIZE = 32;
const int LEVEL_SIZE = TILE_SIZE * 32;
const int VIEW_RANGE = 7;

// Window
const char CLASS_NAME[] = "ThreeChances";
const char GAME_TITLE[] = "ThreeChances";
const bool FULLSCREEN = false;
const UINT GAME_WIDTH = TILE_SIZE * VIEW_RANGE * SCALE;
const UINT GAME_HEIGHT = TILE_SIZE * VIEW_RANGE * SCALE;

// Game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;
const float MIN_FRAME_RATE = 10.0f;
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;
const float VELOCITY = 200.0f;
const float ROTATION_RATE = 720.0f;

// Key Mappings
const UCHAR ESC_KEY = VK_ESCAPE;
const UCHAR ALT_KEY = VK_MENU;
const UCHAR ENTER_KEY = VK_RETURN;
const UCHAR LEFT_KEY = VK_LEFT;
const UCHAR RIGHT_KEY = VK_RIGHT;
const UCHAR UP_KEY = VK_UP;
const UCHAR DOWN_KEY = VK_DOWN;
const UCHAR SPACE_KEY = VK_SPACE;

// Action integers
const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;
const int ATTACK = 4;
const int STAY = 5;

// Screen key pressed
const int ESC = 100;
const int SPACE = 101;

// Sprites
const char LEVEL_1_IMAGE[] = "sprites\\LEVEL1_Final.png";
const char LEVEL_2_IMAGE[] = "sprites\\level2.png";
const char PLAYER_MALE_IMAGE[] = "sprites\\Male_Player.png";
const char DUCK_IMAGE[] = "sprites\\Psyduck.png";
const char GHOST_IMAGE[] = "sprites\\Duskull.png";
const char SLUG_IMAGE[] = "sprites\\Slugma.png";
const char SWORD_IMAGE[] = "sprites\\sword.png";
const char MOVES_HEADER_IMAGE[] = "sprites\\Moves_Header.png";
const char MOVE_IMAGE[] = "sprites\\Move_Circle.png";
const char EMPTY_MOVE_IMAGE[] = "sprites\\Empty_Move_Circle.png";
const char HEALTH_HEADER_IMAGE[] = "sprites\\Health_Header.png";
const char HEART_IMAGE[] = "sprites\\Heart.png";
const char HALF_HEART_IMAGE[] = "sprites\\Half_Heart.png";
const char EMPTY_HEART_IMAGE[] = "sprites\\Empty_Heart.png";
const char ENEMIES_LEFT_HEADER_IMAGE[] = "sprites\\Enemies_Left_Header.png";
const char FONT_TEXTURE[] = "resources\\silkscreen.png";
const char FONT_TEXTURE_INFO[] = "resources\\silkscreen.dat";

const char HUD_BG_IMAGE[] = "sprites\\hud-bg.png";
const char MOVE_ICON[] = "sprites\\white-circle.png";
const char MOVE_OVER_ICON[] = "sprites\\black-circle.png";

const UINT PAUSE_SCREEN_WIDTH = 96 * SCALE;
const UINT PAUSE_SCREEN_HEIGHT = 128 * SCALE;
const char PAUSE_SCREEN_IMAGE[] = "resources\\Pause_Menu.png";
const char START_SCREEN_IMAGE[] = "resources\\Start_Menu.png";
const char GAME_OVER_SCREEN_IMAGE[] = "resources\\Game_Over.png";
const char GAME_CLEAR_SCREEN_IMAGE[] = "resources\\Game_Clear.png";

const int LEVEL_COLS = 2;

const int PLAYER_STANDING_FRAME = 0;
const int PLAYER_WALK_START_FRAME = 0;
const int PLAYER_WALK_END_FRAME = 4;
const float PLAYER_ANIMATION_DELAY = 0.2f;
const int PLAYER_ATK_START_FRAME = 5;
const int PLAYER_ATK_END_FRAME = 6;
const int PLAYER_COLS = 7;
const int PLAYER_ID = 1;

const int DUCK_STANDING_FRAME = 0;
const int DUCK_WALK_START_FRAME = 0;
const int DUCK_WALK_END_FRAME = 3;
const int DUCK_ATK_START_FRAME = 4;
const int DUCK_ATK_END_FRAME = 5;
const float DUCK_ANIMATION_DELAY = 0.2f;
const int DUCK_COLS = 7;

const int GHOST_STANDING_FRAME = 0;
const int GHOST_WALK_START_FRAME = 0;
const int GHOST_WALK_END_FRAME = 3;
const int GHOST_ATK_START_FRAME = 4;
const int GHOST_ATK_END_FRAME = 5;
const float GHOST_ANIMATION_DELAY = 0.2f;
const int GHOST_HURT_FRAME = 6;
const int GHOST_COLS = 7;

const int SLUG_STANDING_FRAME = 0;
const int SLUG_WALK_START_FRAME = 0;
const int SLUG_WALK_END_FRAME = 2;
const int SLUG_ATK_START_FRAME = 3;
const int SLUG_ATK_END_FRAME = 4;
const float SLUG_ANIMATION_DELAY = 0.2f;
const int SLUG_COLS = 6;

#endif
