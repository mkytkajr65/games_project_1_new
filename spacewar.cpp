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
    Game::initialize(hwnd); // throws GameError

	if (!myImageTexture.initialize(graphics, MY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "My texture initialization failed"));
	if (!myImage.initialize(graphics, 0,0,0, &myImageTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init my image"));
	//
	if (!bel.initialize(this, belichickns::WIDTH, belichickns::HEIGHT, 2, &belichickTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));
	//
	myImage.setX(GAME_WIDTH/2 - (myImage.getWidth()*MY_IMAGE_SCALE)/2);
	myImage.setY(GAME_HEIGHT/2 - (myImage.getHeight()*MY_IMAGE_SCALE)/2);
	myImage.setScale(MY_IMAGE_SCALE);

	if (!f1Texture.initialize(graphics, FOOTBALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "My football texture initialization failed"));

	if (!f1.initialize(this, 0, 0,0, &f1Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jere"));
	
	f1.setScale(footballNS::FOOTBALL_SCALE);
	
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
	if (!belichick.initialize(graphics, 0,0,0, &belichickTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init my image"));
	belichick.setX(GAME_WIDTH/2 - (belichick.getWidth()*BELICHICK_IMAGE_SCALE)/2);
	belichick.setY((GAME_HEIGHT - (belichick.getHeight() * BELICHICK_IMAGE_SCALE)));
	belichick.setScale(BELICHICK_IMAGE_SCALE);

	belichickPos.xPos = belichick.getX();
	belichickPos.yPos = belichick.getY();

	
	belichickVel.xVel = DEFAULT_SPEED;
	belichickVel.yVel = DEFAULT_SPEED;

	belichickAirTime = 0.0f;


	backDown = false;
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{

	belichick.update(frameTime);
	f1.update(frameTime);

	float dirX=0;
	float dirY=0;

	bool arrowLeft = input->isKeyDown(VK_LEFT)&&!input->isKeyDown(VK_RIGHT);
	bool arrowRight = !input->isKeyDown(VK_LEFT)&&input->isKeyDown(VK_RIGHT);
	bool arrowUp = input->isKeyDown(VK_UP)&&!input->isKeyDown(VK_DOWN);
	bool arrowDown = !input->isKeyDown(VK_UP)&&input->isKeyDown(VK_DOWN);

	if(arrowLeft)//arrow left
	{
		if(belichick.getX() > 0)
		{
			dirX = -1;
		}
	}

	

	if(arrowRight)//arrow right
	{
		if(belichick.getX() <= (GAME_WIDTH - (belichick.getWidth() * BELICHICK_IMAGE_SCALE)))
		{
			dirX = 1;
		}
	}

	if(arrowDown)//arrow down
	{
		if(belichick.getY() < (GAME_HEIGHT - (belichick.getHeight() * BELICHICK_IMAGE_SCALE)))
		{
			dirY = 1;
			backDown = true;
		}
	}

	if(arrowUp)//arrow up
	{
		if(belichick.getY() > 0 && belichickAirTime < BELICHICK_AIR_TIME_LIMIT)
		{
			dirY = -1;
		}
	}

	if(belichickAirTime >= BELICHICK_AIR_TIME_LIMIT || backDown)
	{
		//if belichick has reached its max air time or its already going back down, GO DOWN
		dirY = 1;
		char msgbuf[2048];

		sprintf(msgbuf, "Top height %f\n", belichick.getX());
		OutputDebugStringA(msgbuf);
	}
	else if(belichickAirTime > 0.0 && belichickAirTime<BELICHICK_AIR_TIME_LIMIT && !arrowDown && !backDown)
	{
		//else if belichick's air time is in flux and hes not going back down, GO UP
		dirY = -1;
	}

	if(belichick.getY() < (GAME_HEIGHT - (belichick.getHeight() * BELICHICK_IMAGE_SCALE)))
	{
		//increase airtime if in the air still
		belichickAirTime += frameTime;
	}
	else
	{
		//if on the ground
		belichickAirTime = 0.0;
		belichickVel.yVel = DEFAULT_SPEED;
		backDown = false;
	}

	if(dirY==-1)//if hes going up
	{
		if((belichickVel.yVel - (9.8*frameTime)) > 0)belichickVel.yVel = belichickVel.yVel - (9.8*frameTime);
	}
	else if(dirY==1)//if hes going down
	{
		belichickVel.yVel = belichickVel.yVel + (9.8*frameTime);
	}
	

	if(dirX+dirY!=0)//normalize
	{
		dirX/= sqrt(dirX*dirX+dirY*dirY);
		dirY/= sqrt(dirX*dirX+dirY*dirY);
	}

	belichickPos.yPos = belichick.getY() + (dirY * belichickVel.yVel) * frameTime;//set the Y position
	belichickPos.xPos = belichick.getX() + (dirX * belichickVel.xVel) * frameTime;//set the X position

		
	belichick.setX(belichickPos.xPos);
	belichick.setY(belichickPos.yPos);


//WRAP

 

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
{}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	myImage.draw();
	belichick.draw();
	f1.draw();

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
