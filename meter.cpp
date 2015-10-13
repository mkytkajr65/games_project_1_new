// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "meter.h"

//=============================================================================
// default constructor
//=============================================================================
Meter::Meter() : Entity()
{
	counter=0;
}
Meter::Meter(Football* f[FOOTBALL_COUNT]) : Entity()
{
	counter=0;
	for(int i=0;i<FOOTBALL_COUNT;i++)
	{
		footballs[i]=f[i];
	}
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Meter::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Meter::draw()
{
    Image::draw();              // draw meter
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Meter::update(float frameTime)
{
    Entity::update(frameTime);
	/*for(int i = 0; i < FOOTBALL_COUNT; i++)
		if((*footballs[i]).getDidLeaveScreen())
			counter++;*/
	/*if(counter==15)
		set(0);*/
	if(counter>15)
	{
		char msgbu[2048];	
		sprintf(msgbu, "Error: meter overflow\n");
		OutputDebugStringA(msgbu);
	}
	setCurrentFrame(meterNS::FRAMES[counter]);
}
void Meter::set(int i)
{
	counter = i;
}
int Meter::get()
{
	return counter;
}
