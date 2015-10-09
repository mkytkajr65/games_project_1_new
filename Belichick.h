// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.h v1.0
#pragma once
#define WIN32_LEAN_AND_MEAN
#include "entity.h"
#include "constants.h"

namespace belichickns
{
	const float BELICHICK_SCALE = .1;
    const int WIDTH = 1024;                   // image width
    const int HEIGHT = 1024;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT-HEIGHT;
	const float SPEED = 100;                // 100 pixels per second
	const int TEXTURE_COLS=2;
	const int   START_FRAME = 1;        // starts at frame 1
    const int   END_FRAME = 1;          // no animation
	const float BELICHICK_ANIMATION_DELAY = 0.2f;
}

class Belichick : public Entity
{
private:
	bool hasLinemen;
	int speedChange;
public:
    // constructor
    Belichick();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);
};

