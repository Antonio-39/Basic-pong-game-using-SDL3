#pragma once
#include "SDLState.h"
#include "Env.h"

struct position {
	float x, y;
};

class Item
{
protected:
	position pos;
	int pHeight, pWidth;
	float xVelocity;
	float yVelocity;
public:
	SDL_Texture* texture;

	float getXVelocity() const { return xVelocity; }
	void setXVelocity(float velocity) { this->xVelocity = velocity; }

	float getYVelocity() const { return yVelocity; }
	void setYVelocity(float velocity) { this->yVelocity = velocity; }
	
	position getPos() const { return pos; }

	int getPHeight() const { return pHeight; }
	int getPWidth() const { return pWidth; }

	SDL_Texture* getTexture() const { return texture; }
	
	void drawItem(const SDLState& state, float deltaTime);
	static bool checkCollision(const Item&, const Item&);
	virtual void resetPosition() {};
};


