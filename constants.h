// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 constants.h v1.0
#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// graphic images
const char NEBULA_IMAGE[] = "..\\games_project_1_new\\pictures\\orion.jpg";  // photo source NASA/courtesy of nasaimages.org 
const char PLANET_IMAGE[] = "..\\games_project_1_new\\pictures\\planet.png"; // picture of planet
const char SONY_IMAGE[] = "..\\games_project_1_new\\pictures\\sony.png";
const char MY_IMAGE[] = "..\\games_project_1_new\\pictures\\1.png";
const char BELICHICK_IMAGE[] = "..\\games_project_1_new\\pictures\\bScaled.png";
const char FOOTBALL_IMAGE[] = "..\\games_project_1_new\\pictures\\football.png";
const char LINEMAN_IMAGE[] = "..\\games_project_1_new\\pictures\\lineman2.png";
const char METER_SPRITE_SHEET[] = "..\\games_project_1_new\\pictures\\metersheetreal.png";

// window
const char CLASS_NAME[] = "Spacewar";
const char GAME_TITLE[] = "Spacewar";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  640;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels
 
// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float Y_SPEED = 0.4;
const UINT FLOOR_HEIGHT = 50;
const float B_DEFAULT_SPEED = 200;
const float BELICHICK_AIR_TIME_LIMIT = 1.5;
const int MAX_FOOTBALL_SPEED_CHANGE = 100;
const float DEFAULT_SPEED = 80;
const int FOOTBALL_COUNT = 4;
const int CONSECUTIVE_FOOTBALLS_LINEMEN_THRESHOLD = 10;
const int MAX_LIVES = 3;
const float GRAVITY = 10.0;

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key



#endif
