// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.h v1.0
#pragma once
#define WIN32_LEAN_AND_MEAN
#include "entity.h"
#include "constants.h"

namespace linemanns
{
	const float Lineman_SCALE = .5;
    const int WIDTH = 128;                   // image width
    const int HEIGHT = 128;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT-HEIGHT-1;//*BEL_SCALE;
	const int TEXTURE_COLS=2;
	const int   START_FRAME = 1;        // starts at frame 1
    const int   END_FRAME = 1;          // no animation
	const float LINEMAN_ANIMATION_DELAY = 0.2f;
	const float LINEMAN_SCALE=.5;
}
class Lineman : public Entity
{
private:
	Entity* e;
	bool isRight;
public:
    // constructor
	Lineman();
    Lineman(Entity* e,bool isRight);//Belichick will be parameter. isRight is true if this is the right lineman, and false for the left lineman.

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);
	void setPos(double x, double y);
};

