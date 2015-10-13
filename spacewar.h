// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 spacewar.h v1.0

#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "football.h"
#include "textureManager.h"
#include "image.h"
#include "graphics.h"
#include "Belichick.h"
#include "meter.h"
#include "Life.h"


//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:

	// My defines
	#define MY_IMAGE_SCALE .48
	#define BELICHICK_IMAGE_SCALE .10
// My vars

	float belichickXVel;
	float belichickYVel;
	TextureManager belichickTexture, myImageTexture, footballTexture,linemanTexture, meterTexture,lifeTexture;
	Image belichick, myImage;
	Football f1,f2,f3,f4,f5;
	Belichick bel;
	Football *footballs[FOOTBALL_COUNT];
	Life lives[MAX_LIVES];
	int livesLost;
	int score;
	int consecutiveFootballs;
	Meter meter;
	struct position{
		float xPos;
		float yPos;
		position() {xPos = 0; yPos = 0;}
	} belichickPos, myImagePos;

	struct velocity{
		float xVel;
		float yVel;
		velocity() { xVel = 0; yVel = 0;}
	} belichickVel;

	float belichickAirTime;
	double belichick_speed;
	bool backDown;
	
public:
    // Constructor
    Spacewar();

    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

//Stuff for physics


#endif
