#include "Item.h"

void Item :: drawItem(const SDLState& state, float deltaTime) {
	const float spriteHeight = pHeight;
	const float spriteWidth = pWidth;
	SDL_FRect src{ 0, 0, spriteWidth,  spriteHeight }; 
    // the portion of the source image which should be used -- params: x, y, w, h

	SDL_FRect dst{ pos.x, pos.y, spriteWidth,  spriteHeight }; 
    // the portion of the window the image should be drawn in -- params: x, y, w, h

	SDL_RenderTextureRotated(state.renderer, texture, &src, &dst, 0, nullptr, SDL_FLIP_NONE);	
}

bool Item::checkCollision(const Item& a, const Item& b)
{
    //Calculate the sides of rect A
    float aMinX{ a.pos.x };
    float aMaxX{ a.pos.x + a.pWidth };
    float aMinY{ a.pos.y };
    float aMaxY{ a.pos.y + a.pHeight };

    //Calculate the sides of rect B
    float bMinX{ b.pos.x };
    float bMaxX{ b.pos.x + b.pWidth };
    float bMinY{ b.pos.y };
    float bMaxY{ b.pos.y + b.pHeight };

    //If left side of A is the the right of B
    if (aMinX >= bMaxX)
    {
        return false;
    }

    //If the right side of A to the left of B
    if (aMaxX <= bMinX)
    {
        return false;
    }

    //If the top side of A is below B
    if (aMinY >= bMaxY)
    {
        return false;
    }

    //If the bottom side of A is above B
    if (aMaxY <= bMinY)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

