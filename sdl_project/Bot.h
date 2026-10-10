#pragma once
#include "Player.h"
#include "Ball.h"
class Bot : public Player
{
private:
	uint16_t timer;
	uint16_t reactionDelay;
	float target;
public:
	void move(float deltaTime, SDLState state, Ball ball);
	Bot();
	void resetPosition() override;
};

