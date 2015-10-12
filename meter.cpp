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
Meter::Meter(Football f[FOOTBALL_COUNT])//Other constructor taking an array of footballs
{
	for(int i=0;i<FOOTBALL_COUNT;i++)
		footballs[i]=&f[i];
}
//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Meter::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM,Football* f)
{
	for(int i=0;i<FOOTBALL_COUNT;i++)
		footballs[i]=&f[i];
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
	/*setCurrentFrame(meterNS::FRAMES[counter]);
	if(isCrossing(*footballs[0]))
		counter=((counter+1)%16);
	*/
}
bool Meter::isCrossing(Football f)
{
	return f.isCrossing();
}
void Meter::set(int i)
{
	counter = i;
}
int Meter::get()
{
	return counter;
}
