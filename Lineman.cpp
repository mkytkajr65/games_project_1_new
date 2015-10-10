#include "Lineman.h"


Lineman::Lineman(Entity* e,bool isRight)
{
	this->e=e;
	this->isRight;
}

void Lineman::draw()
{
    Image::draw();              //draw lineman
}
bool Lineman::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Lineman::update(float frameTime)
{
	spriteData.y=(e->getEdge()).bottom;
	if(isRight)
	{
		spriteData.x = (e->getEdge()).right;//set the X position*/
	}
	else
	{
		spriteData.x = (e->getEdge()).left - linemanns::WIDTH;//set the X position*/
	}
}
Lineman::Lineman()
{
}