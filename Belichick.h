// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.h v1.0
#pragma once
#define WIN32_LEAN_AND_MEAN
#include "Lineman.h"
#include "entity.h"
#include "constants.h"

namespace belichickns
{
	const float BEL_SCALE = 0.5;
    const int WIDTH = 128;                   // image width
    const int HEIGHT = 128;                  // image height
    const double X = GAME_WIDTH/2 - WIDTH*BEL_SCALE/2;   // location on screen
    const double Y = (GAME_HEIGHT - (belichickns::HEIGHT * belichickns::BEL_SCALE));
	const int TEXTURE_COLS=2;
	const int   START_FRAME = 1;        // starts at frame 1
    const int   END_FRAME = 1;          // no animation
	const float BELICHICK_ANIMATION_DELAY = 0.2f;
	
}

class Belichick : public Entity
{
private:
	bool linemen;
	int speedChange;
	float dirX;
	float dirY;
	double airTime;
	bool backDown;
	int counter;//This keeps track of how many footballs Belichick has dodged since the last time he was hit.
	Lineman l;//left lineman
	Lineman r;//right lineman
	Game* g;
	int debugNum;
public:
    // constructor
    Belichick();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);
	void giveLinemen();
	bool hasLinemen();
	Lineman* getLeftLineman();
	Lineman* getRightLineman();
	void removeLinemen();
};

