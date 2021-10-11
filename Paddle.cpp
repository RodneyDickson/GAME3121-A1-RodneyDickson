#include "Paddle.h"

Paddle::Paddle(Ogre::Entity* paddleEntity, Ogre::SceneManager* scnMgr)
{
    // Creates paddle for our game
    paddleShape = scnMgr->getRootSceneNode()->createChildSceneNode();
    paddleShape->setPosition(0, 0, 0);
    paddleShape->setScale(0.4f, 0.05f, 1.0f);
    paddleShape->attachObject(paddleEntity);
}

Paddle::Paddle()
{

}

Paddle::~Paddle()
{

}

Ogre::Vector2 Paddle::getPosition() const
{
    return position;
}

Ogre::SceneNode* Paddle::getShape() const
{
    return paddleShape;
}

Ogre::Vector2 Paddle::getVelocity() const
{
    return Ogre::Vector2();
}

void Paddle::setPosition(Ogre::Vector3 position)
{
    paddleShape->setPosition(position);
    this->position = Ogre::Vector2(position.x, position.y);
}

void Paddle::setVelocity(Ogre::Vector2 vel)
{
    this->velocity = vel;
}

void Paddle::update(float dt)
{

}