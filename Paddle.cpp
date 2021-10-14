#include "Paddle.h"

Paddle::Paddle(Ogre::Entity* paddleEntity, Ogre::SceneManager* scnMgr)
{
    // Creates paddle for our game
    paddleShape = scnMgr->getRootSceneNode()->createChildSceneNode();
    paddleShape->setPosition(0, 0, 0); // position set to 0,0,0 but later set to near bottom of the screen based off aspect ratio
    paddleShape->setScale(0.4f, 0.05f, 1.0f);
    paddleShape->attachObject(paddleEntity);
}

Paddle::Paddle()
{

}

Paddle::~Paddle()
{

}

// gets our paddles position
Ogre::Vector2 Paddle::getPosition() const
{
    return position;
}

// gets our paddles shape
Ogre::SceneNode* Paddle::getShape() const
{
    return paddleShape;
}

// gets our paddles velocity
Ogre::Vector2 Paddle::getVelocity() const
{
    return Ogre::Vector2();
}

// sets our players position
// can be based on mouse movement or left/right arrows
void Paddle::setPosition(Ogre::Vector3 position)
{
    paddleShape->setPosition(position);
    this->position = Ogre::Vector2(position.x, position.y);
}

// sets our players velocity
void Paddle::setVelocity(Ogre::Vector2 vel)
{
    this->velocity = vel;
}

void Paddle::update(float dt)
{

}