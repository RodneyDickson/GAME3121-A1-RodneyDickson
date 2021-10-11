#include "Game.h"

Game::Game()
    : ApplicationContext("GAME3121 - Assignment 1 - by Rodney Dickson")
{
}

bool Game::frameRenderingQueued(const FrameEvent& evt)
{
    if (latestFramerate < 30.f && !gameOver)
    {
        // if the window gets resized, we dont want the ball to move to the bottom of the screen and result in an instant life lost now
        // would we?
        m_ball->reset();
    }

    //std::cout << "viewports: " << getRenderWindow()->getViewport(0)->getActualWidth() << std::endl;
    // Pause game when the game is over
    if (gameOver)
    {
        if (m_quitBtn->getState() == OgreBites::ButtonState::BS_DOWN)
        {
            getRoot()->queueEndRendering();
        }
        return true;
    }

    if (timeSinceLastFrame < refreshTime)
    {
        timeSinceLastFrame += evt.timeSinceLastFrame;
        numOfFrames++;

    }
    else
    {
        latestFramerate = (float)numOfFrames / timeSinceLastFrame;
        numOfFrames = 0;
        timeSinceLastFrame = 0.0f;

        sprintf_s(buffer, "FPS: %.1f", latestFramerate);
        m_fpsLabel->setCaption(buffer);

    // M/s per frame (shows 3 decimals)
        sprintf_s(buffer, "m/s %.3f", evt.timeSinceLastFrame);
        m_mspfLabel->setCaption(buffer);
    }


    // Checks if ball is out of bounds first
    m_ball->checkBounds(aspectX, aspectY);

    // Ball movement
    m_ball->update(evt.timeSinceLastFrame);

    // Updates paddle
    m_playerPaddle->update(evt.timeSinceLastEvent);

    Vector2 ballPos = m_ball->getPosition();
    Vector2 batPos = m_playerPaddle->getPosition();

    if (ballPos.y < -aspectY * 0.5f)
    {
        lives--;
        this->refreshUserInterface();
        if (lives <= 0)
        {
            m_gameOverLabel = mTrayMgr->createLabel(TL_CENTER, "L_GAMEOVER", "GAME OVER!", 150);
            m_quitBtn = mTrayMgr->createButton(TL_CENTER, "L_GAMEOVERBUTTON", "Quit Game", 150);


            gameOver = true;
        }
        else
        {
            m_ball->reset();
        }
    }

    // collision with our paddle
    if (ballPos.y < batPos.y + 10.f && ballPos.y > batPos.y - 10.0f && ballPos.x > batPos.x - 50.f && ballPos.x < batPos.x + 50.f)
    {
        // Only the first time it collided.
        if (!collisionDetect)
        {
            collisionDetect = true;

            score += 1;
            if (score % 10 == 0)
            {
                lives += 1;
            }
            this->refreshUserInterface();

            Vector2 vel = m_ball->getVelocity();
            vel.y *= -1.0f;
            //std::cout << "DEFLECT!" << std::endl;
            m_ball->setVelocity(vel);

        }

    }
    else
    {
        collisionDetect = false;
    }


    // moves ball based off last frame
    Vector3 move = Vector3(evt.timeSinceLastFrame * 15.f, 0.f, 0.f);

    return true;
}

bool Game::mouseMoved(const MouseMotionEvent& evt)
{
    // Pause game when the game is over
    if (gameOver)
        return true;

    float mouseToWorld = (evt.x - (float)getRenderWindow()->getWidth() / 2.0f) * 0.5f;

    // sets position of paddle to where the mouse is, minus 100 on the y (going down)
    m_playerPaddle->setPosition(Vector3(mouseToWorld, -100.f, 0.f));
    return true;
}

void Game::refreshUserInterface()
{
    // This function refreshes the user interface for each score/lives update
    // Score UI
    {
        sprintf_s(buffer, "Score: %d", score);
        m_scoreLabel->setCaption(buffer);
    }
    // Lives ui
    {
        sprintf_s(buffer, "Lives: %d", lives);
        m_livesLabel->setCaption(buffer);
    }
}

void Game::setup()
{
    // set up game starts here
    ApplicationContext::setup();
    addInputListener(this);

    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();

    // sets shader for our game
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);
    scnMgr->setAmbientLight(ColourValue(0.9, 0.9, 0.9));


    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(0.0001f);
    cam->setAutoAspectRatio(true);
    cam->setProjectionType(Ogre::ProjectionType::PT_PERSPECTIVE);

    camNode->attachObject(cam);
    getRenderWindow()->addViewport(cam);

    // sets cam position to centre of screen
    camNode->setPosition(0, 0, aspectX); // 0, 0, aspectX
    mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());



    // adds tray to game screen
    scnMgr->addRenderQueueListener(mOverlaySystem);
    // adds tray to game screen
    addInputListener(mTrayMgr);

    // Displays the OGRE logo
    //mTrayMgr->showLogo(TL_TOPRIGHT);

    // Creates SCORE and LIVES labels. Sets size
    m_scoreLabel = mTrayMgr->createLabel(TL_TOPLEFT, "L_SCORE", "SCORE: XX", 150);
    m_livesLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "L_LIVES", "LIVES: XX", 150);

    // Creates FPS, miliseconds and game title
    m_fpsLabel = mTrayMgr->createLabel(TL_BOTTOMLEFT, "L_FPS", "FPS: 60", 150);
    m_mspfLabel = mTrayMgr->createLabel(TL_BOTTOMRIGHT, "L_MSPF", "m/s: 0.1667", 150);
    m_myLabel = mTrayMgr->createLabel(TL_BOTTOM, "L_LABEL", "Game Engine Development I - A1 - Rodney Dickson", 450);


    Ogre::Entity* ballEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_SPHERE);
    Ogre::Entity* paddleEntity = scnMgr->createEntity(SceneManager::PrefabType::PT_PLANE);

    m_ball = std::make_shared<Ball>(ballEntity, scnMgr);

    // random direction
    srand(unsigned(time(NULL)));

    m_ball->reset();

    // set ball position
    m_ball->setPosition(Vector3(0.f, 20.f, 0.f));

    // set paddle position
    m_playerPaddle = std::make_shared<Paddle>(paddleEntity, scnMgr);
    m_playerPaddle->setPosition(Vector3(0.f, -100.f, 0.f));
    this->refreshUserInterface();

    //243 / 2 - 50 = 171.5
    aspectX = (getRenderWindow()->getViewport(0)->getActualWidth() / 2.0f) - 50.0f;
    aspectY = (getRenderWindow()->getViewport(0)->getActualHeight() / 2.0f) - 50.0f;
}


bool Game::keyPressed(const KeyboardEvent& evt)
{
    // ESC exits game
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    // SPACE resets ball in the event the ball gets stuck
    if (evt.keysym.sym == SDLK_SPACE)
    {
        m_ball->reset();
    }
    // Added left and right for harder movements
    if (evt.keysym.sym == SDLK_LEFT)
    {
        m_playerPaddle->setPosition(Vector3(m_playerPaddle->getPosition().x - 10.0f, -100.0f, 0.f));
    }
    if (evt.keysym.sym == SDLK_RIGHT)
    {
        m_playerPaddle->setPosition(Vector3(m_playerPaddle->getPosition().x + 10.0f, -100.0f, 0.f));
    }
    

    return true;
}