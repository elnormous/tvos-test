#pragma once

class MainMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    
    // a selector callback
    void menuPlayCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
    
    virtual void update(float delta) override;

    bool handleTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void handleTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void handleTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void onConnectController(cocos2d::Controller* controller, cocos2d::Event* event);
    void onDisconnectedController(cocos2d::Controller* controller, cocos2d::Event* event);
    
    void onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    void onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    void onKeyRepeat(cocos2d::Controller* controller, int key, cocos2d::Event* event);
    
    void onAxisEvent(cocos2d::Controller* controller, int axis, cocos2d::Event* event);
    
private:
	DISALLOW_COPY_AND_ASSIGN(MainMenu);
	MainMenu();
    virtual ~MainMenu();
    
    cocos2d::EventListener* _touchListener = nullptr;
    cocos2d::EventListenerController* _controllerListener = nullptr;
    
    cocos2d::Controller* _controller = nullptr;
};
