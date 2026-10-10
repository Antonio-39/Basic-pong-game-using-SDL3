#pragma once
#include "Item.h"

class Player : public Item
{
public:
	void move(const bool *keys, float deltaTime, SDLState state);
	Player();
	void resetPosition() override;
};

