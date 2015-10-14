// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw planet with transparency
// Chapter 5 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"
#include "d3dx9math.h"
#include "Belichick.h"
#include <string>
#include <cmath>
//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{
	dxFontSmall	= new TextDX();     // DirectX fonts
	dxFontMedium = new TextDX();
	dxFontLarge	= new TextDX();
}

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
	for(int i = 0; i < MAX_LIVES;i++)
	{
		lives[i] = Life(i);
	}
	//

	game_over = false;

	if (!bel.initialize(this, belichickns::WIDTH, belichickns::HEIGHT, 2, &belichickTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Belichick"));
	if(!(*(bel.getLeftLineman())).initialize(this, linemanns::WIDTH, linemanns::HEIGHT, 2, &linemanTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing left lineman"));
	if(!(*(bel.getRightLineman())).initialize(this, linemanns::WIDTH, linemanns::HEIGHT, 2, &linemanTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing right lineman"));
	//
	myImage.setX(GAME_WIDTH/2 - (myImage.getWidth()*MY_IMAGE_SCALE)/2);
	myImage.setY(GAME_HEIGHT/2 - (myImage.getHeight()*MY_IMAGE_SCALE)/2);
	myImage.setScale(MY_IMAGE_SCALE);

	if (!footballTexture.initialize(graphics, FOOTBALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "My football texture initialization failed"));

	if (!meterTexture.initialize(graphics, METER_SPRITE_SHEET))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Meter sprite sheet initialization failed"));
	if (!lifeTexture.initialize(graphics, LIFE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Life texture initialization failed"));

	if (!f1.initialize(this, 0, 0, 0, &footballTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jere"));

	if (!f2.initialize(this,  0, 0, 0, &footballTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jere"));
	

	if (!f3.initialize(this, 0, 0, 0, &footballTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jere"));

	if (!f4.initialize(this, 0, 0, 0, &footballTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jere"));
	
	if (!f5.initialize(this, 0, 0, 0, &footballTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing jere"));
	for(int i=0;i<MAX_LIVES;i++)
		if (!(lives[i]).initialize(this, 0, 0, 0, &lifeTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing life"));
	footballs[0] = &f1;
	footballs[1] = &f2;
	footballs[2] = &f3;
	footballs[3] = &f4;
	footballs[4] = &f5;
	if (!meter.initialize(this, 16, 128, 16, &meterTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing meter"));
	
	myImagePos.xPos = myImage.getX();
	myImagePos.yPos = myImage.getY();

	if (!myImageTexture.initialize(graphics, MY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "My texture initialization failed"));
	if (!myImage.initialize(graphics, 0,0,0, &myImageTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init my image"));
	myImage.setX(GAME_WIDTH/2 - (myImage.getWidth()*MY_IMAGE_SCALE)/2);
	myImage.setY(GAME_HEIGHT/2 - (myImage.getHeight()*MY_IMAGE_SCALE)/2);
	myImage.setScale(MY_IMAGE_SCALE);

	myImagePos.xPos = myImage.getX();
	myImagePos.yPos = myImage.getY();


	if (!belichickTexture.initialize(graphics, BELICHICK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "My texture initialization failed"));
	if (!linemanTexture.initialize(graphics, LINEMAN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Lineman texture initialization failed"));
	

	consecutiveFootballs = 0;

	livesLost = 0;
	scoreMsg="";
	score = 0;

	backDown = false;
	if(dxFontLarge->initialize(graphics, 40, true, false, "Calibri")== false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	if(dxFontMedium->initialize(graphics, 20, true, false, "Calibri")== false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	if(!game_over)
	{
		bel.update(frameTime);
		f1.update(frameTime);
		f2.update(frameTime);
		f3.update(frameTime);
		f4.update(frameTime);
		f5.update(frameTime);
	
		for(int i = 0; i < MAX_LIVES;i++)
		{
			lives[i].update(frameTime);
		}
	
		if(consecutiveFootballs<=CONSECUTIVE_FOOTBALLS_LINEMEN_THRESHOLD)meter.set(consecutiveFootballs);
		meter.update(frameTime);
		for(int i = 0;i<FOOTBALL_COUNT;i++)
		{
			if((*footballs[i]).getWasVisible() && (*footballs[i]).getDidLeaveScreen())
			{
				consecutiveFootballs++;
				if(consecutiveFootballs>=CONSECUTIVE_FOOTBALLS_LINEMEN_THRESHOLD){score += 2;}
				else { score++; }
			}
		}
		if(consecutiveFootballs>=CONSECUTIVE_FOOTBALLS_LINEMEN_THRESHOLD)
		{
			//give BB linemen
			bel.setLinemen(true);
			//bonus score for being over threshold
		}
		else
		{
			//remove BB's linemen
			bel.setLinemen(false);
		}
		scoreMsg= "Score: "+std::to_string(score);
		/*char msgbu[2048];
		sprintf(msgbu, "ScoreMsg: %d\n", scoreMsg);
		OutputDebugStringA(msgbu);*/
	
	//REFLECT
 

	 ////////////////
	// INPUT MODS
	 ////////////////

	 int directionX = 0;
	 int directionY = 0;
	}

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
		if(!bel.hasLinemen())
		{
			if((*footballs[i]).collidesWith(bel, collisionVector) && (*footballs[i]).getVisible())//if the collision has occured
			{
				//make that football disappear
				(*footballs[i]).setVisible(false);

				//set consecutive footballs to 0
				consecutiveFootballs = 0;
				//1 life lost
				livesLost++;
				audio->playCue("beep1");
			}
		}
		else
		{
			if(((*footballs[i]).collidesWith(*bel.getLeftLineman(), collisionVector) || (*footballs[i]).collidesWith(*bel.getRightLineman(), collisionVector)) && (*footballs[i]).getVisible())//if the collision has occured
			{
				//make that football disappear
				(*footballs[i]).setVisible(false);
				//set consecutive footballs to 0
				consecutiveFootballs = 0;
				//make linemen disappear
				bel.setLinemen(false);
				audio->playCue("hit");
			}
			else if((*footballs[i]).collidesWith(bel, collisionVector) && (*footballs[i]).getVisible())
			{
				//make that football disappear
				(*footballs[i]).setVisible(false);
				//set consecutive footballs to 0
				consecutiveFootballs = 0;
				//make linemen disappear
				bel.setLinemen(false);
				livesLost++;
				audio->playCue("beep1");
			}
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
	f1.draw();
	f2.draw();
	f3.draw();
	f4.draw();
	f5.draw();
	dxFontMedium->print(scoreMsg,SCORE_X_POS,SCORE_Y_POS);
	if(MAX_LIVES <= livesLost)//GAME OVER
	{
		dxFontLarge->print(GAME_OVER_MESSAGE,GAME_OVER_X_POS,GAME_OVER_Y_POS);
		game_over = true;
	}
	meter.draw();
	int numLives=MAX_LIVES-livesLost;
	for(int i = 0;i < numLives;i++)
	{
		lives[i].draw();
	}
	bel.draw();

	bel.getLeftLineman()->draw();
	bel.getRightLineman()->draw();

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	belichickTexture.onLostDevice();
	footballTexture.onLostDevice();
	myImageTexture.onLostDevice();
	linemanTexture.onLostDevice();
	meterTexture.onLostDevice();
	lifeTexture.onLostDevice();
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
	footballTexture.onResetDevice();
	myImageTexture.onResetDevice();
	linemanTexture.onResetDevice();
	meterTexture.onResetDevice();
	lifeTexture.onResetDevice();
    Game::resetAll();
    return;
}
