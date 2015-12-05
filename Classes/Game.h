//
//  Game.h
//  cocos2d-x-test
//
//  Created by Elviss Strazdins on 05/12/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#pragma once

class Game: public cocos2d::Scene
{
public:
	static Game* create();

	virtual void update(float delta) override;

CC_CONSTRUCTOR_ACCESS:
	Game();
	virtual ~Game();

	virtual bool init() override;

private:
	CC_DISALLOW_COPY_AND_ASSIGN(Game);
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    
    cocos2d::EventListenerTouchOneByOne* _touchListener = nullptr;
    cocos2d::EventListenerController* _controllerListener = nullptr;
};
