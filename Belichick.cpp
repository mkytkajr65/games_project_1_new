#include "Belichick.h"


Belichick::Belichick()
{
	spriteData.width = belichickns::WIDTH;           // size of Belichick
    spriteData.height = belichickns::HEIGHT;
    spriteData.x = belichickns::X;                   // location on screen
    spriteData.y = belichickns::Y;
    spriteData.rect.bottom = belichickns::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = belichickns::WIDTH;
    velocity.x = 300;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = belichickns::BELICHICK_ANIMATION_DELAY;
	radius = belichickns::WIDTH/2.0;
    collisionType = entityNS::CIRCLE;

	hasLinemen = false;
}
void Belichick::draw()
{
    Image::draw();              // draw ship
}
bool Belichick::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
void Belichick::update(float frameTime)
{
}