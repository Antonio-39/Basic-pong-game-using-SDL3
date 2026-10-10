#include "Ball.h"
#include <iostream>
#include <algorithm> // Required for std::clamp

Ball::Ball()
{
    pWidth = 16.0f;
    pHeight = 16.0f;
    pos.x = LOGICAL_WIDTH / 2 * (1.0f) - pWidth / 2;
	pos.y = LOGICAL_WIDTH  * (1.0f) - pHeight * 3;
	
	xVelocity = 125.0f;
	yVelocity = 125.0f;
}



int Ball::move(const Item& collider1, float deltaTime, const SDLState& state, const Item& collider2)
{
    
    const float MOMENTUM_TRANSFER_RATE = 0.15f;
    const float MAX_X_VELOCITY = 400.0f; 

    //  X-AXIS MOVEMENT 
    pos.x += (xVelocity * deltaTime);

    // Check screen boundaries (Left and Right walls)
    if (pos.x < 0)
    {
        pos.x = 0; 
        xVelocity *= -1;
    }
    else if (pos.x + pWidth > state.logW)
    {
        pos.x = state.logW - pWidth;
        xVelocity *= -1;
    }
    // Check collider collision (Side of the paddle)
    else if (checkCollision(*this, collider1) || checkCollision(*this, collider2))
    {
        // Step back out of the paddle to resolve the overlap
        pos.x -= (xVelocity * deltaTime);
        xVelocity *= -1;
    }

    // Y-AXIS MOVEMENT 
    pos.y -= (yVelocity * deltaTime);

    
    // Check collider collision (Top or bottom of the paddle)
    if (checkCollision(*this, collider1) )
    {
        // Step back out of the paddle
        pos.y += (yVelocity * deltaTime);
        yVelocity *= -1;

        // Transfer velocity from collider
        float colliderVel = collider1.getXVelocity();
        xVelocity += colliderVel * MOMENTUM_TRANSFER_RATE;

        // Clamp max velocity to prevent the ball from accelerating infinitely
        xVelocity = std::clamp(xVelocity, -MAX_X_VELOCITY, MAX_X_VELOCITY);
    }
    else if (checkCollision(*this, collider2))
    {
        // Step back out of the paddle
        pos.y += (yVelocity * deltaTime);
        yVelocity *= -1;

        // Transfer velocity from collider
        float colliderVel = collider2.getXVelocity();
        xVelocity += colliderVel * MOMENTUM_TRANSFER_RATE;

        // Clamp max velocity to prevent the ball from accelerating infinitely
        xVelocity = std::clamp(xVelocity, -MAX_X_VELOCITY, MAX_X_VELOCITY);
    }

    // Check bottom screen boundary
    if (pos.y + pHeight > state.logH)
        return 1;


    // check top screen boundry
    if (pos.y < 0)
        return -1;

    return 0;
}

void Ball::resetPosition()
{
    pos.x = LOGICAL_WIDTH / 2 * (1.0f) - pWidth / 2;
    pos.y = LOGICAL_HEIGHT / 2.0f - pHeight / 2.0f;


    xVelocity = 125.0f;
    yVelocity = 125.0f;

}