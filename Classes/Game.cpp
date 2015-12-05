//
//  Game.cpp
//  cocos2d-x-test
//
//  Created by Elviss Strazdins on 05/12/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#include "Game.h"

USING_NS_CC;

Game* Game::create()
{
	Game* ret = new Game();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		delete ret;
		return nullptr;
	}
}

Game::Game()
{
}

Game::~Game()
{
    _eventDispatcher->removeEventListener(_controllerListener);
}

bool Game::init()
{
	if (!Scene::init())
	{
		return false;
	}
    
    _controllerListener = EventListenerController::create();
    _controllerListener->onKeyDown = CC_CALLBACK_3(Game::onKeyDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_controllerListener, this);

	return true;
}

void Game::update(float delta)
{
}

void Game::onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
#if defined(CC_TARGET_OS_IPHONE) || defined(CC_TARGET_OS_APPLETV)
    log("key down: %d, float value: %f", key, controller->getKeyStatus(key).value);
#endif
    
    if (key == cocos2d::Controller::BUTTON_X)
    {
        Director::getInstance()->replaceScene(Game::create());
    }
}
