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
#define TRANSCOLOR SETCOLOR_ARGB(0,255,0,255)

//-----------------------------------------------
// Constants
//-----------------------------------------------
const float SCALE = 2.0f;
const float TILE_SIZE = 32 * SCALE;
const float VIEW_RANGE = 7;

// Window
const char CLASS_NAME[] = "ThreeChances";
const char GAME_TITLE[] = "ThreeChances";
const bool FULLSCREEN = false;
const UINT GAME_WIDTH = TILE_SIZE * VIEW_RANGE;
const UINT GAME_HEIGHT = TILE_SIZE * VIEW_RANGE;

// Game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;
const float MIN_FRAME_RATE = 10.0f;
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;

// Key Mappings
const UCHAR ESC_KEY = VK_ESCAPE;
const UCHAR ALT_KEY = VK_MENU;
const UCHAR ENTER_KEY = VK_RETURN;
const UCHAR LEFT_KEY = VK_LEFT;
const UCHAR RIGHT_KEY = VK_RIGHT;
const UCHAR UP_KEY = VK_UP;
const UCHAR DOWN_KEY = VK_DOWN;

// Sprites
const char MAP_1_IMAGE[] = "sprites\\level1.png";
const char MAP_2_IMAGE[] = "sprites\\level2.png";

#endif
