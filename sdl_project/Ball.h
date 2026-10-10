#pragma once
#include "Item.h"
#include <SDL3/SDL.h>

class Ball : public Item
{
public:
	int move(const Item& collider, float deltaTime, const SDLState& state, const Item& collider2);
	Ball();
	void resetPosition() override;
};

