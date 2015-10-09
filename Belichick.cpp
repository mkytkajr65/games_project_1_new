#include "Belichick.h"


Belichick::Belichick(void)
{
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