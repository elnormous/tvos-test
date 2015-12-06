//
//  Game.cpp
//  cocos2d-x-test
//
//  Created by Elviss Strazdins on 05/12/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#include "Game.h"
#include "CCCirculate.h"

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
    _eventDispatcher->removeEventListener(_touchListener);
    _eventDispatcher->removeEventListener(_controllerListener);
}

bool Game::init()
{
	if (!Scene::init())
	{
		return false;
	}
    
    _tag = 2;
    
    Sprite* obstacle = Sprite::create("obstacle.png");
    obstacle->setPosition(Point(300, 300));
    obstacle->setColor(Color3B(255, 0, 0));
    addChild(obstacle);
    
    Sprite* obstacle2 = Sprite::create("obstacle.png");
    obstacle2->setPosition(Point(400, 300));
    obstacle2->setColor(Color3B(0, 255, 0));
    obstacle2->runAction(Circulate::create(5, Point(400, 400), false));
    addChild(obstacle2);
    
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    
#if defined(CC_TARGET_OS_IPHONE) || defined(CC_TARGET_OS_APPLETV)
    Controller::startDiscoveryController();
#endif
    
    _controllerListener = EventListenerController::create();
    _controllerListener->onKeyDown = CC_CALLBACK_3(Game::onKeyDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_controllerListener, this);

	return true;
}

void Game::update(float delta)
{
}

bool Game::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = convertToNodeSpace(touch->getLocation());
    
    log("touch begin: %f, %f", location.x, location.y);
    
    return false;
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
