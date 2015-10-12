// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.h v1.0

#ifndef _METER_H                 // Prevent multiple definitions if this 
#define _METER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "football.h"
#include <ctime>
#include <random>

namespace meterNS
{
	const float METER_SCALE = 1;
    const int WIDTH = 16;                   // image width
    const int HEIGHT = 128;                  // image height
    const int X = 0;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const int   TEXTURE_COLS = 16;           // texture has 16 columns
	const int FRAMES[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    //const int   SHIP1_START_FRAME = 0;      // ship1 starts at frame 0
   // const int   SHIP1_END_FRAME = 3;        // ship1 animation frames 0,1,2,3
   // const int   SHIP2_START_FRAME = 8;      // ship2 starts at frame 8
   // const int   SHIP2_END_FRAME = 11;       // ship2 animation frames 8,9,10,11
    const float METER_ANIMATION_DELAY = 0.2f;    // time between frames
    //const int   SHIELD_START_FRAME = 24;    // shield start frame
    //const int   SHIELD_END_FRAME = 27;      // shield end frame
    //const float SHIELD_ANIMATION_DELAY = 0.1f; // time between frames
}

// inherits from Entity class
class Meter : public Entity
{
private:
	short int counter;
	Football* footballs[FOOTBALL_COUNT];
	bool crossedYet[FOOTBALL_COUNT];//True if football has already gone off the end of the screen.
	bool isCrossing(Football f);//returns true if football is currently going off the end of the screen.

public:
    // constructor
    Meter();
	Meter(Football f[FOOTBALL_COUNT]);

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM,Football*);
    void update(float frameTime);
	void set(int i);
	int get();
};
#endif

