#pragma once
#include "c:\users\fryees1\documents\visual studio 2012\projects\games_project_1_new\entity.h"
namespace lifeNS
{
	const float LIFE_SCALE = 0.12;  
	const int HEIGHT = 32;                  // image height
    const int Y = GAME_HEIGHT*.04;
	const int WIDTH = 32;                   // image width
}
class Life : public Entity
{
public:
	Life(void);
	Life(int ind);
	~Life(void);
	void setVisable(bool val);
	virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
    void update(float frameTime);
private:
	bool visable;
	int index;
	int x;//Location on screen.
	int y;
};

