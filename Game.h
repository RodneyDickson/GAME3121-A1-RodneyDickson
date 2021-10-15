#pragma once
#include <iostream>
#include "Ball.h"
#include "Paddle.h"
#include <memory>
#include <cassert>

using namespace Ogre;
using namespace OgreBites;


// Game Class
// Main base class, inherits from Application Listener and Input Listener. Any type of keyboard/mouse event based entities should be done from here

class Game
    : public ApplicationContext
    , public InputListener
{
public:
    // Constructor
    // called in main.cpp
    Game();

    // Virtual Destructor
    // called after application quits
    virtual ~Game() {}

    void setup();

    // called when a key is pressed
    // boolean = always true
    // evt references to a keyboard event
    bool keyPressed(const KeyboardEvent& evt);

    // called once per tick
    // returns boolean = always true
    // evt references to a frame event
    bool frameRenderingQueued(const FrameEvent& evt);

    // refreshes all labels
    void refreshUserInterface();


    // called when the mouse is moved
    // boolean = always true
    // evt is a reference to a mouse motion event
    bool mouseMoved(const MouseMotionEvent& evt) override;


    // Tray listener is used for our GUI system
    OgreBites::TrayListener myTrayListener;

    // Gui showing our score
    OgreBites::Label* m_scoreLabel;
    
    // Gui showing our lives
    OgreBites::Label* m_livesLabel;
    
    // Gui showing our frames per second
    OgreBites::Label* m_fpsLabel;
    
    // Gui showing our miliseconds per frame (0.1667)
    OgreBites::Label* m_mspfLabel; 

    // create a default label
    OgreBites::Label* m_myLabel;

    // create our game over label for later
    OgreBites::Label* m_gameOverLabel;

    // tray manager
    OgreBites::TrayManager* mTrayMgr;
    
    // Displays game over / quit button
    OgreBites::Button* m_quitBtn = nullptr;
    OgreBites::Button* m_resetBtn = nullptr;

    // Reference to our ball entity
    std::shared_ptr<Ball> m_ball;

    // reference to our paddle entity
    std::shared_ptr<Paddle> m_playerPaddle;

private:
    
    // players aspect ratio for x (<-->) 325
    float aspectX = 325.0f;
    
    // players aspect ratio for y (^   V) 243
    float aspectY = 243.0f;
    
    // sets up our game score to start at 0
    int score = 0;
    
    // sets our lives to a max of 3
    int lives = 3;
    
    // int for number of frames to keep track of frames per second
    int numOfFrames = 0;
    
    // displays time since last frame to help give fps
    float timeSinceLastFrame = 0.0f;
    
    // also helps display fps
    float latestFramerate = 0.0f;
    
    // tells us how often to refresh our stats
    float refreshTime = 0.9f;
    
    // set up a buffer for all of our gui items
    char buffer[50];
    
    // our collision detection for our paddle and ball
    bool collisionDetect = false;
    
    // game over condition when we run out of lives
    bool gameOver = false;
};