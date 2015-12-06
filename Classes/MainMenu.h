#pragma once

class MainMenu : public cocos2d::Scene
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    
    // a selector callback
    void menuPlayCallback(cocos2d::Ref* sender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
    
    virtual void update(float delta) override;

CC_CONSTRUCTOR_ACCESS:
    MainMenu();
    virtual ~MainMenu();
    
private:
	DISALLOW_COPY_AND_ASSIGN(MainMenu);
	
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    bool handleTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void handleTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void handleTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void onConnectController(cocos2d::Controller* controller, cocos2d::Event* event);
    void onDisconnectedController(cocos2d::Controller* controller, cocos2d::Event* event);
    
    void onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    void onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    void onKeyRepeat(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    
    void onAxisEvent(cocos2d::Controller* controller, int axis, cocos2d::Event* event);
    
    cocos2d::EventListenerKeyboard* _keybListener = nullptr;
    cocos2d::EventListener* _touchListener = nullptr;
    cocos2d::EventListenerController* _controllerListener = nullptr;
};
