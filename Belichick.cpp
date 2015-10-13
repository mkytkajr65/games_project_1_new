#include "Belichick.h"

Belichick::Belichick()
:l(this,false), r(this, true)
{
	spriteData.width = belichickns::WIDTH;           // size of Belichick
    spriteData.height = belichickns::HEIGHT;
    spriteData.x = belichickns::X/**belichickns::BEL_SCALE*/;                   // location on screen
    spriteData.y = belichickns::Y/**belichickns::BEL_SCALE*/;


    spriteData.rect.bottom = belichickns::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = belichickns::WIDTH;
    velocity.x = B_DEFAULT_SPEED;                             // velocity X
    velocity.y = 0;    
	// velocity Y
	setScale(belichickns::BEL_SCALE);
    frameDelay = belichickns::BELICHICK_ANIMATION_DELAY;
	radius = (belichickns::WIDTH)/2.0;
    collisionType = entityNS::CIRCLE;
	dirX = 0;
	dirY = 0;//Belichick initially starts at rest.
	airTime=0;
	backDown=true;//Belichick starts on the ground.
	g=NULL;
}
void Belichick::draw()
{
    Image::draw();              //draw Belichick
}
bool Belichick::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
	g=gamePtr;
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
	
}
void Belichick::update(float frameTime)
{
	Entity::update(frameTime);
	l.update(frameTime);
	r.update(frameTime);
	dirX=0;
	dirY=0;
	bool arrowLeft = input->isKeyDown(VK_LEFT)&&!input->isKeyDown(VK_RIGHT);
	bool arrowRight = !input->isKeyDown(VK_LEFT)&&input->isKeyDown(VK_RIGHT);
	bool arrowUp = input->isKeyDown(VK_UP)&&!input->isKeyDown(VK_DOWN);
	bool arrowDown = !input->isKeyDown(VK_UP)&&input->isKeyDown(VK_DOWN);

	if(arrowLeft)//arrow left
	{
		if(spriteData.x > 0)
		{
			dirX = -1;
		}
	}

	if(arrowRight)//arrow right
	{
		if(spriteData.x <= (GAME_WIDTH - (belichickns::WIDTH * belichickns::BEL_SCALE)))
		{
			dirX = 1;
		}
	}
	if(arrowDown)//arrow down
	{
		if(spriteData.y < (GAME_HEIGHT - (belichickns::HEIGHT * belichickns::BEL_SCALE)))
		{
			dirY = 1;
			backDown = true;
		}
	}
	if(arrowUp)//arrow up
	{
		if(spriteData.y > 0 && airTime < BELICHICK_AIR_TIME_LIMIT)
		{
			dirY = -1;
		}
	}
	if((airTime >= BELICHICK_AIR_TIME_LIMIT || backDown) && spriteData.y < (GAME_HEIGHT - (belichickns::HEIGHT * belichickns::BEL_SCALE)))
	{
		//if belichick has reached its max air time or its already going back down, GO DOWN
		dirY = 1;
	}
	else if(airTime > 0.0 && airTime<BELICHICK_AIR_TIME_LIMIT && !arrowDown && !backDown)
	{
		//else if belichick's air time is in flux and hes not going back down, GO UP
		dirY = -1;
	}
	if(spriteData.y < (GAME_HEIGHT - (belichickns::HEIGHT * belichickns::BEL_SCALE)))
	{
		//increase airtime if in the air still
		
		airTime += frameTime;
	}
	else
	{
		//if on the ground
		airTime = 0.0;
		velocity.y = B_DEFAULT_SPEED;
		backDown = false;
	}

	if(dirY==-1)//if hes going up
	{
		if((velocity.y - (GRAVITY*frameTime)) > 0)velocity.y = velocity.y - (GRAVITY*frameTime);
	}
	else if(dirY==1)//if hes going down
	{
		velocity.y = velocity.y + (GRAVITY*frameTime);
	}
	

	if(dirX+dirY!=0)//normalize
	{
		float newDirX;
		float newDirY;
		newDirX= dirX/(sqrt(dirX*dirX+dirY*dirY));
		newDirY= dirY/(sqrt(dirX*dirX+dirY*dirY));
		dirX=newDirX;
		dirY=newDirY;
	}

	/*char msgbu[2048];
		
	sprintf(msgbu, "x val %f <=", getX());
	OutputDebugStringA(msgbu);*/
	if(linemen)
	{ 
		giveLinemen();
	}
	else{ removeLinemen(); }

	spriteData.y = spriteData.y + (dirY * velocity.y) * frameTime;//set the Y position
	spriteData.x = spriteData.x + (dirX * velocity.x) * frameTime;//set the X position*/
	l.setPos(spriteData.y,spriteData.x-linemanns::WIDTH*linemanns::LINEMAN_SCALE);//set position of the linemen
	r.setPos(spriteData.y,spriteData.x+belichickns::WIDTH*belichickns::BEL_SCALE);
}
void Belichick::giveLinemen()
{
	l.setVisible(true);
	r.setVisible(true);
}
Lineman* Belichick::getRightLineman()
{
	return &r;
}
Lineman* Belichick::getLeftLineman()
{
	return &l;
}
bool Belichick::hasLinemen()
{
	return linemen;
}
void Belichick::removeLinemen()
{
	l.setVisible(false);
	r.setVisible(false);
}