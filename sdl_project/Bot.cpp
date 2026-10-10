#include "Bot.h"
#include <iostream>

void Bot::move(float deltaTime, SDLState state, Ball ball)
{
	// move the bot every reactionDelay frames
	timer++;
	if (timer >= reactionDelay)
	{
		target = ball.getPos().x + (ball.getPWidth() / 2);
		timer = 0;
	}

	// move the bot towords the target with a dead zone of 10px
	float moveAmount = 0;
	float center = pos.x + (pWidth / 2);
	if (target > center + 10.0f)
		moveAmount += 150.0f;
	else if (target + 10.0f < center)
		moveAmount += -150.0f;
	xVelocity = moveAmount;
	moveAmount *= deltaTime;
	pos.x += moveAmount;

	// keep the bot inside the game
	if ((pos.x < 0) || (pos.x + pWidth > state.logW))
		pos.x -= moveAmount;
	return;
}
Bot::Bot()
{
	yVelocity = 0.0f;
	pWidth = 100.0f;
	pHeight = 16.0f;
	pos.x = LOGICAL_WIDTH / 2 * (1.0) - pWidth / 2;  
	pos.y = 0; 
	timer = 0;
	reactionDelay = 10;
	target = 0.0f;
}
void Bot::resetPosition()
{
	pos.x = LOGICAL_WIDTH / 2 * (1.0) - pWidth / 2; 
}
