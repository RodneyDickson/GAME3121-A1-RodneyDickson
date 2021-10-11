#pragma once
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"

// Behaviour of our paddle
class Paddle
{
private:

	// Shape of paddle based off of plane prefab
	Ogre::SceneNode* paddleShape;

	// Velocity, or speed, of our paddle
	Ogre::Vector2 velocity;

	// Position of our paddle
	Ogre::Vector2 position;

public:

	// Creates ball and scene manager
	Paddle(Ogre::Entity* ballEntity, Ogre::SceneManager* scnMgr);

	// Create paddle constructor
	Paddle();

	// Create paddle destructor
	~Paddle();


	// Position of our paddle
	// Returns the position as an Ogre::Vector2
	Ogre::Vector2 getPosition() const;

	// Paddle shape reference
	// Returns the shape as a Ogre::SceneNode reference
	Ogre::SceneNode* getShape() const;

	// Our paddles velocity/speed
	// Returns the velocity of the ball as an Ogre::Vector2
	Ogre::Vector2 getVelocity() const;

	// Sets paddle position
	void setPosition(Ogre::Vector3 position);

	// Sets paddle velocity, or speed.
	void setVelocity(Ogre::Vector2 vel);

	// update called once per frame  
	// (dt) stands for time elapsed since previous frame (must use a frame listener for delta time)
	void update(float dt);
};