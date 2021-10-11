#include "Ball.h"

Ball::Ball(Ogre::Entity* ballEntity, Ogre::SceneManager* scnMgr)
{
	// Create ball
	// Set position, size
	ballShape = scnMgr->getRootSceneNode()->createChildSceneNode();
	ballShape->setPosition(0, 20, 0);
	ballShape->setScale(0.2f, 0.2f, 0.2f);
	ballShape->attachObject(ballEntity);

	// Set starting velocity/speed and position to zero
	velocity = Ogre::Vector2::ZERO;
	position = Ogre::Vector2::ZERO;

	//this->ballShape = ballEntity;
}

Ball::Ball()
{
}

Ball::~Ball()
{
}

Ogre::Vector2 Ball::getPosition() const
{
	return position;
}

Ogre::SceneNode* Ball::getShape() const
{
	return ballShape;
}

Ogre::Vector2 Ball::getVelocity() const
{
	return velocity;
}

void Ball::setPosition(Ogre::Vector3 position)
{
	ballShape->setPosition(position);
	this->position = Ogre::Vector2(position.x, position.y);
}

void Ball::setVelocity(Ogre::Vector2 vel)
{
	this->velocity = vel;
}

void Ball::update(float dt)
{
	position += velocity * dt;
	this->setPosition(Ogre::Vector3(position.x, position.y, 0.f));
}

void Ball::checkBounds(float x, float y)
{
	// Checks ball position to see if its in bounds
	
	// if balls x position is greater than x bound, reverse the movement
	if (position.x > x * 0.5f)
	{
		velocity.x *= -1.0f;
	}
	if (position.x < -x * 0.5f)
	{
		velocity.x *= -1.0f;
	}
	if (position.y > y * 0.5f)
	{
		velocity.y *= -1.0f;
	}

}

void Ball::reset()
{
	// chooses between random event for ball movement
	int ran = rand() % 4;
	float randomDirection = 0.0f;

	// if ball gets reset, go through random cases so game gets less stale or predictable
	switch (ran)
	{
	case 0: 
		randomDirection = 45.0f; 
		break;
	case 1: 
		randomDirection = 135.0f; 
		break;
	case 2: 
		randomDirection = 225.0f; 
		break;
	case 3: 
		randomDirection = 315.0f; 
		break;
	}

	float desiredX = 160.0f * cos(randomDirection * 3.14159f / 180.0f);
	float desiredY = 160.0f * sin(randomDirection * 3.14159f / 180.0f);

	this->setPosition(Ogre::Vector3::ZERO);
	this->setVelocity(Ogre::Vector2(desiredX, desiredY));
}