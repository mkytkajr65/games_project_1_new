// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.h v1.0

#ifndef _FOOTBALL_H                 // Prevent multiple definitions if this 
#define _FOOTBALL_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <ctime>
#include <random>

namespace footballNS
{
	const float FOOTBALL_SCALE = 0.3;
    const int WIDTH = 32;                   // image width
    const int HEIGHT = 32;                  // image height
    const int X = 0;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI/4; // radians per second
    const float X_SPEED = 200;                // 100 pixels per second
    const float MASS = 300.0f;              // mass
    const int   TEXTURE_COLS = 8;           // texture has 8 columns
    //const int   SHIP1_START_FRAME = 0;      // ship1 starts at frame 0
   // const int   SHIP1_END_FRAME = 3;        // ship1 animation frames 0,1,2,3
   // const int   SHIP2_START_FRAME = 8;      // ship2 starts at frame 8
   // const int   SHIP2_END_FRAME = 11;       // ship2 animation frames 8,9,10,11
    const float FOOTBALL_ANIMATION_DELAY = 0.2f;    // time between frames
    //const int   SHIELD_START_FRAME = 24;    // shield start frame
    //const int   SHIELD_END_FRAME = 27;      // shield end frame
    //const float SHIELD_ANIMATION_DELAY = 0.1f; // time between frames
}

// inherits from Entity class
class Football : public Entity
{
private:
	int speedChange;
public:
    // constructor
    Football();
	

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);
	std::normal_distribution<double> distribution;
	std::default_random_engine generator;
    //void damage(WEAPON);
};
#endif

