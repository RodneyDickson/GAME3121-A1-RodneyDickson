#include "Ball.h"

Ball::Ball(Ogre::Entity* ballEntity, Ogre::SceneManager* scnMgr)
{
	// Create ball
	// Set position, size
	ballShape = scnMgr->getRootSceneNode()->createChildSceneNode();
	ballShape->setPosition(0, 20, 0); // about mid screen
	ballShape->setScale(0.1f, 0.1f, 0.1f);
	ballShape->attachObject(ballEntity);

	// Set starting velocity/speed and position to zero
	ballVelocity = Ogre::Vector2(0.0f, 0.0f);
	ballPosition = Ogre::Vector2(0.0f, 0.0f);
}

Ball::Ball()
{

}

Ball::~Ball()
{

}

// returns balls position
Ogre::Vector2 Ball::getPosition() const
{
	return ballPosition;
}

// sets up our balls shape
Ogre::SceneNode* Ball::getShape() const
{
	return ballShape;
}

// gets our balls velocity
Ogre::Vector2 Ball::getVelocity() const
{
	return ballVelocity;
}

// sets up our balls position
void Ball::setPosition(Ogre::Vector3 ballPosition)
{
	ballShape->setPosition(ballPosition);
	this->ballPosition = Ogre::Vector2(ballPosition.x, ballPosition.y);
}

// sets up our balls velocity
void Ball::setVelocity(Ogre::Vector2 ballVelocity)
{
	this->ballVelocity = ballVelocity;
}

// remember float dt is used for calculating time since last frame
void Ball::update(float dt)
{
	ballPosition += ballVelocity * dt;
	this->setPosition(Ogre::Vector3(ballPosition.x, ballPosition.y, 0.f));
}

void Ball::checkBounds(float x, float y)
{
	// Checks ball position to see if its in bounds
	// if balls x position is greater than x bound, reverse the movement
	if (ballPosition.x > x * 0.5f)
	{
		ballVelocity.x *= -1.0f;
	}
	// if balls x position is lesser than x bound, reverse the movement
	if (ballPosition.x < -x * 0.5f)
	{
		ballVelocity.x *= -1.0f;
	}
	// if balls x position is greater than y bound, reverse the movement
	if (ballPosition.y > y * 0.5f)
	{
		ballVelocity.y *= -1.0f;
	}
	// no call for lesser than y since this condition results in a loss of life and/or game loss
}

void Ball::reset()
{
	// chooses between random event for ball movement
	int ran = rand() % 2;
	float randomDirection = 0.0f;

	// if ball gets reset, go through random cases so game gets less stale or predictable
	switch (ran)
	{
	case 0: 
		randomDirection = 45.0f;  // Goes towards top right
		break;
	case 1: 
		randomDirection = 135.0f; // Goes towards top left
		break;
	}
	// no bottom directions to avoid insta loses


	float desiredX = 160.0f * cos(randomDirection * 3.14159f / 180.0f);
	float desiredY = 160.0f * sin(randomDirection * 3.14159f / 180.0f);

	this->setPosition(Ogre::Vector3(0.0f, 0.0f, 0.0f));
	this->setVelocity(Ogre::Vector2(desiredX, desiredY));
}