#include "Life.h"


Life::Life(void)
{
	visable = true;
}
Life::Life(int ind)
{
	visable = true;
	index=ind;
	y=lifeNS::Y;
	x=(GAME_WIDTH*.05/**lifeNS::LIFE_SCALE*/)+(lifeNS::WIDTH/**lifeNS::LIFE_SCALE*/*index)+(.005*lifeNS::WIDTH/**lifeNS::LIFE_SCALE*/);
}

Life::~Life(void)
{
}
void Life::setVisable(bool val)
{
	visable = val;
	setVisable(visable);
}



bool Life::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
	spriteData.x=x;
	spriteData.y=y;
	setScale(lifeNS::LIFE_SCALE);
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}


void Life::draw()
{
    Image::draw();    
}
void Life::update(float frameTime)
{
    Entity::update(frameTime);
}