// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "football.h"

//=============================================================================
// default constructor
//=============================================================================
Football::Football() : Entity()
{
	int height = (int)(((BELICHICK_AIR_TIME_LIMIT*B_DEFAULT_SPEED) + (0.5*-9.8*(BELICHICK_AIR_TIME_LIMIT*BELICHICK_AIR_TIME_LIMIT))));
	height = rand() % height;
	spriteData.y = GAME_HEIGHT - height;
	char msgbuf[2048];
		
	sprintf(msgbuf, "My variable is %d\n", height);
	OutputDebugStringA(msgbuf);
	speedChange = rand() % MAX_FOOTBALL_SPEED_CHANGE;
	spriteData.width = footballNS::WIDTH * footballNS::FOOTBALL_SCALE;           // size of Football
    spriteData.height = footballNS::HEIGHT * footballNS::FOOTBALL_SCALE;
	this->setScale(footballNS::FOOTBALL_SCALE);
    spriteData.x = footballNS::X;                   // location on screen
    spriteData.rect.bottom = footballNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = footballNS::WIDTH;
	velocity.x = footballNS::X_SPEED;                           // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = footballNS::FOOTBALL_ANIMATION_DELAY;
    //startFrame = footballNS::SHIP1_START_FRAME;     // first frame of football animation
    //endFrame     = footballNS::SHIP1_END_FRAME;     // last frame of football animation
   // currentFrame = startFrame;
	radius = footballNS::WIDTH * footballNS::FOOTBALL_SCALE/2.0;
    //shieldOn = false;
    mass = footballNS::MASS;
    collisionType = entityNS::CIRCLE;

}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Football::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Football::draw()
{
    Image::draw();              // draw football
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Football::update(float frameTime)
{
    Entity::update(frameTime);
    
    spriteData.x += frameTime * velocity.x;         // move football along X 


	if(spriteData.x >= GAME_WIDTH)
	{
		if(rand()%3==0)this->visible = false;
		else { this->visible = true; }
		//calculate height Belichick can reach
		int height = (int)(((BELICHICK_AIR_TIME_LIMIT*B_DEFAULT_SPEED) + (0.5*-9.8*(BELICHICK_AIR_TIME_LIMIT*BELICHICK_AIR_TIME_LIMIT))));
		height = (rand() % height) + 30;
		spriteData.x = 0;
		spriteData.y = GAME_HEIGHT - height;
		
		if(rand()%2==0)speedChange *= -1;

		velocity.x = footballNS::X_SPEED + speedChange;
		
		speedChange = rand() % MAX_FOOTBALL_SPEED_CHANGE;
	}
}

