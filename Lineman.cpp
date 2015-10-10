#include "Lineman.h"


Lineman::Lineman(Entity* e,bool isRight)
{
	this->e=e;
	this->isRight;
	if(!isRight)
		flipHorizontal(true);
	setScale(linemanns::LINEMAN_SCALE);
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
Lineman::Lineman()//Please do not remove this; it has a purpose.
{
}
void Lineman::setPos(double y, double x)
{
	spriteData.x=x;
	spriteData.y=y;
}