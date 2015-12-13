#include "MainMenu.h"
#include "Game.h"

USING_NS_CC;

MainMenu::MainMenu()
{
	
}

MainMenu::~MainMenu()
{
    if (_keybListener) _eventDispatcher->removeEventListener(_keybListener);
    if (_touchListener) _eventDispatcher->removeEventListener(_touchListener);
    if (_controllerListener) _eventDispatcher->removeEventListener(_controllerListener);
    if (_mouseListener) _eventDispatcher->removeEventListener(_mouseListener);
}

bool MainMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    _tag = 1;
    
    auto menu = Menu::create();
    this->addChild(menu);
    
    for (int i = 0; i < 9; ++i)
    {
        Sprite* normalSprite = Sprite::create("obstacle.png");
        normalSprite->setColor(Color3B(0, 0, 255));
        Sprite* selectedSprite = Sprite::create("obstacle.png");
        selectedSprite->setColor(Color3B(0, 0, 128));
        
        auto item = MenuItemSprite::create(normalSprite,
                                               selectedSprite,
                                               CC_CALLBACK_1(MainMenu::menuPlayCallback, this));
        
        menu->addChild(item);
    }
    
    menu->alignItemsInColumns(3, 3, 3, nullptr);
    
    _keybListener = EventListenerKeyboard::create();
    _keybListener->onKeyPressed = CC_CALLBACK_2(MainMenu::onKeyPressed, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keybListener, this);
    
#if defined(CC_TARGET_OS_IPHONE) || defined(CC_TARGET_OS_APPLETV)
    Controller::startDiscoveryController();
#endif
    
    _controllerListener = EventListenerController::create();
    
    _controllerListener->onConnected = CC_CALLBACK_2(MainMenu::onConnectController,this);
    _controllerListener->onDisconnected = CC_CALLBACK_2(MainMenu::onDisconnectedController,this);
    _controllerListener->onKeyDown = CC_CALLBACK_3(MainMenu::onKeyDown, this);
    _controllerListener->onKeyUp = CC_CALLBACK_3(MainMenu::onKeyUp, this);
    _controllerListener->onAxisEvent = CC_CALLBACK_3(MainMenu::onAxisEvent, this);
    _controllerListener->onKeyRepeat = CC_CALLBACK_3(MainMenu::onKeyRepeat, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_controllerListener, this);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(MainMenu::handleTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MainMenu::handleTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainMenu::handleTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    _touchListener = listener;
    
    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = CC_CALLBACK_1(MainMenu::onMouseDown, this);
    _mouseListener->onMouseUp = CC_CALLBACK_1(MainMenu::onMouseUp, this);
    _mouseListener->onMouseMove = CC_CALLBACK_1(MainMenu::onMouseMove, this);
    _mouseListener->onMouseScroll = CC_CALLBACK_1(MainMenu::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    
    scheduleUpdate();
    
    return true;
}

void MainMenu::update(float delta)
{

}

void MainMenu::menuPlayCallback(Ref* sender)
{
    Director::getInstance()->replaceScene(Game::create());
}

void MainMenu::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    log("key pressed: %d", keyCode);
}

bool MainMenu::handleTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = convertToNodeSpace(touch->getLocation());
    
    log("touch begin: %f, %f", location.x, location.y);
    
    return true;
}

void MainMenu::handleTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = convertToNodeSpace(touch->getLocation());
    
    //log("touch moved: %f, %f", location.x, location.y);
}

void MainMenu::handleTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 location = convertToNodeSpace(touch->getLocation());
    
    log("touch ended: %f, %f", location.x, location.y);
}

void MainMenu::onConnectController(cocos2d::Controller* controller, cocos2d::Event* event)
{
    log("Controller connected %s", controller->getDeviceName().c_str());
    
    controller->setAbsoluteDpadValues(true);
}

void MainMenu::onDisconnectedController(cocos2d::Controller* controller, cocos2d::Event* event)
{
}

void MainMenu::onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
#if defined(CC_TARGET_OS_IPHONE) || defined(CC_TARGET_OS_APPLETV)
    log("key down: %d, float value: %f", key, controller->getKeyStatus(key).value);
    
    if (key == Controller::BUTTON_X)
    {
        Director::getInstance()->replaceScene(Game::create());
    }
    
#endif
}

void MainMenu::onKeyUp(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    log("key up: %d", key);
}

void MainMenu::onAxisEvent(cocos2d::Controller* controller, int axis, cocos2d::Event* event)
{
    log("axis event: %d", axis);
}

void MainMenu::onKeyRepeat(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    log("key repeat: %d", key);
    
    if (key == cocos2d::Controller::BUTTON_DPAD_LEFT)
    {
        log("Left value: %f", controller->getKeyStatus(key).value);
    }
    else if (key == cocos2d::Controller::BUTTON_DPAD_RIGHT)
    {
        log("Right value: %f", controller->getKeyStatus(key).value);
    }
    else if (key == cocos2d::Controller::BUTTON_DPAD_UP)
    {
        log("Up value: %f", controller->getKeyStatus(key).value);
    }
    else if (key == cocos2d::Controller::BUTTON_DPAD_DOWN)
    {
        log("Down value: %f", controller->getKeyStatus(key).value);
    }
}

void MainMenu::onMouseDown(cocos2d::EventMouse* event)
{
    log("Mouse down: %d", event->getMouseButton());
}

void MainMenu::onMouseUp(cocos2d::EventMouse* event)
{
    log("Mouse up: %d", event->getMouseButton());
}

void MainMenu::onMouseMove(cocos2d::EventMouse* event)
{
    log("Mouse move: %d", event->getMouseButton());
}

void MainMenu::onMouseScroll(cocos2d::EventMouse* event)
{
    log("Mouse scroll: %f, %f", event->getDelta().x, event->getDelta().y);
}
