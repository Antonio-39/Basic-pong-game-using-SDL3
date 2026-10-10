#include "Player.h"

void Player :: move(const bool* keys, float deltaTime, SDLState state)
{
	//move the player when keys are pressed
	float moveAmount = 0;
	if (keys[SDL_SCANCODE_A])
		moveAmount += -150.0f;
	if (keys[SDL_SCANCODE_D])
		moveAmount += 150.0f;
	xVelocity = moveAmount;
	moveAmount *= deltaTime;
	pos.x += moveAmount;
	
	//keep the player inside the game
	if ((pos.x < 0) || (pos.x + pWidth > state.logW))
		pos.x -= moveAmount;
	return;
	
}
Player::Player() 
{
	yVelocity = 0.0f;
	pWidth = 100.0f;
	pHeight = 16.0f;
	pos.x = LOGICAL_WIDTH / 2 * (1.0) - pWidth / 2;
	pos.y = LOGICAL_HEIGHT * (1.0) - pHeight; 
}
void Player::resetPosition()
{
	pos.x = LOGICAL_WIDTH / 2 * (1.0) - pWidth / 2; 
}
