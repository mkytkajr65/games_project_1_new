#include "Lineman.h"


Lineman::Lineman(Entity* e,bool isRight)
{
	this->e=e;
	this->isRight = isRight;
	if(!isRight)
		flipHorizontal(true);
	setScale(linemanns::LINEMAN_SCALE);
	width=linemanns::WIDTH*linemanns::LINEMAN_SCALE;
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
	spriteData.y= 20;
	if(isRight)
	{
		spriteData.x = 50;//set the X position*/
	}
	{
		spriteData.x = 50;
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