// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw planet with transparency
// Chapter 5 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"
#include "d3dx9math.h"
#include "Belichick.h"
#include <cmath>
//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
	srand(time(NULL));
    Game::initialize(hwnd); // throws GameError
	
	if (!myImageTexture.initialize(graphics, MY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "My texture initialization failed"));
	if (!myImage.initialize(graphics, 0,0,0, &myImageTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init my image"));
	//
	if (!bel.initialize(this, belichickns::WIDTH, belichickns::HEIGHT, 2, &belichickTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Belichick"));
	bel.giveLinemen();
	//bel.removeLinemen();
	if(!(*(bel.getLeftLineman())).initialize(this, linemanns::WIDTH, linemanns::HEIGHT, 2, &linemanTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing left lineman"));
	if(!(*(bel.getRightLineman())).initialize(this, linemanns::WIDTH, linemanns::HEIGHT, 2, &linemanTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing right lineman"));
	//
	myImage.setX(GAME_WIDTH/2 - (myImage.getWidth()*MY_IMAGE_SCALE)/2);
	myImage.setY(GAME_HEIGHT/2 - (myImage.getHeight()*MY_IMAGE_SCALE)/2);
	myImage.setScale(MY_IMAGE_SCALE);

	if (!f1Texture.initialize(graphics, FOOTBALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "My football texture initialization failed"));

	if (!meterTexture.initialize(graphics, METER_SPRITE_SHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Meter sprite sheet initialization failed"));

	if (!f1.initialize(this, 0, 0, 0, &f1Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jere"));
	

	if (!f3.initialize(this, 0, 0, 0, &f1Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jere"));
	

	if (!f2.initialize(this,  0, 0, 0, &f1Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jere"));

	/*if (!meter.initialize(this, 16, 128, 16, &meterTexture,footballs))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing meter"));*/
	
	//Stuff for physics
	myImagePos.xPos = myImage.getX();
	myImagePos.yPos = myImage.getY();

	if (!myImageTexture.initialize(graphics, MY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "My texture initialization failed"));
	if (!myImage.initialize(graphics, 0,0,0, &myImageTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init my image"));
	myImage.setX(GAME_WIDTH/2 - (myImage.getWidth()*MY_IMAGE_SCALE)/2);
	myImage.setY(GAME_HEIGHT/2 - (myImage.getHeight()*MY_IMAGE_SCALE)/2);
	myImage.setScale(MY_IMAGE_SCALE);
	
	//Stuff for physics
	myImagePos.xPos = myImage.getX();
	myImagePos.yPos = myImage.getY();


	if (!belichickTexture.initialize(graphics, BELICHICK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "My texture initialization failed"));
	if (!linemanTexture.initialize(graphics, LINEMAN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Lineman texture initialization failed"));
	
	footballs[0] = &f1;
	footballs[1] = &f2;
	footballs[2] = &f3;

	backDown = false;
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	
	bel.update(frameTime);
	f1.update(frameTime);
	f2.update(frameTime);
	f3.update(frameTime);
	meter.update(frameTime);

//REFLECT
 

 ////////////////
// INPUT MODS
 ////////////////

 int directionX = 0;
 int directionY = 0;

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{
	VECTOR2 collisionVector;
	for(int i = 0;i<FOOTBALL_COUNT;i++)
	{
		if((*footballs[i]).collidesWith(bel, collisionVector))//if the collision has occured
		{
			(*footballs[i]).setVisible(false);
		}
	}
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	myImage.draw();
	//belichick.draw();
	f1.draw();
	f2.draw();
	f3.draw();
	meter.draw();
	if(bel.hasLinemen())
	{
		(*(bel.getLeftLineman())).draw();
		(*(bel.getRightLineman())).draw();
	}
	bel.draw();

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	belichickTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
   
	belichickTexture.onResetDevice();
	

    Game::resetAll();
    return;
}
