#pragma once

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"

// Ball class
// Ball behaviour goes below VVV
class Ball
{
private:
	// Ball, similar to the paddle, uses a prefab for its shape (sphere)
	Ogre::SceneNode* ballShape;

	// Balls velocity, or speed
	Ogre::Vector2 ballVelocity;

	// Ball position
	Ogre::Vector2 ballPosition;

public:
	// Constructor for the ball class.
	Ball(Ogre::Entity* ballEntity, Ogre::SceneManager* scnMgr);

	// Ball class constructor
	Ball();

	// Ball destructor
	~Ball();

	// Gets ball shape (sphere)
	// Returns the shape as a Ogre::SceneNode reference
	Ogre::SceneNode* getShape() const;

	// Gets Ball position
	// Returns the position as an Ogre::Vector2
	Ogre::Vector2 getPosition() const;

	// Gets ball velocity/speed
	// Returns the velocity of the ball as an Ogre::Vector2
	Ogre::Vector2 getVelocity() const;

	// Set ball position
	void setPosition(Ogre::Vector3 ballPosition);

	// Sets ball velocity/speed
	void setVelocity(Ogre::Vector2 ballVelocity);

	// Called once per tick in game class
	// (float dt) is time elapsed since previous frame
	void update(float dt);

	// Checks ball position compared to screen bounds
	// performs an AABB collision test and deflects ball velocity accordingly 
	void checkBounds(float x, float y);

	// reset function is called when the ball misses paddle or hits a wall
	// or the ball leaves the boundary. The balls velocity is set to be a random diagonal direction on each call
	void reset();
};
