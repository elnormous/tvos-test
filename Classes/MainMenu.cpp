#include "MainMenu.h"
#include "CCCirculate.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

MainMenu::MainMenu()
{
	
}

MainMenu::~MainMenu()
{
    _eventDispatcher->removeEventListener(_touchListener);
    _eventDispatcher->removeEventListener(_controllerListener);
}

bool MainMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Sprite* obstacle = Sprite::create("obstacle.png");
    obstacle->setPosition(Point(300, 300));
    obstacle->setColor(Color3B(255, 0, 0));
    addChild(obstacle);
    
    Sprite* obstacle2 = Sprite::create("obstacle.png");
    obstacle2->setPosition(Point(400, 300));
    obstacle2->runAction(Circulate::create(5, Point(400, 400), false));
    addChild(obstacle2);
    
    //Controller* c = nullptr;
    Controller::startDiscoveryController();
    
    
    /*Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "HelloWorld.png",
                                           "HelloWorld.png",
                                           CC_CALLBACK_1(MainMenu::menuPlayCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width/2 ,
                                origin.y + visibleSize.height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/
    
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
    
    scheduleUpdate();
    
    return true;
}

void MainMenu::update(float delta)
{

}

void MainMenu::menuPlayCallback(Ref* pSender)
{
    
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
    _controller = controller;
    log("Controller connected %s", controller->getDeviceName().c_str());
}

void MainMenu::onDisconnectedController(cocos2d::Controller* controller, cocos2d::Event* event)
{
    if (controller == _controller)
    {
        _controller = nullptr;
    }
}

void MainMenu::onKeyDown(cocos2d::Controller* controller, int key, cocos2d::Event* event)
{
    log("key down: %d, float value: %f", key, controller->getKeyStatus(key).value);
    
    if (key == cocos2d::Controller::BUTTON_DPAD_UP)
    {
        log("up");
    }
    else if (key == cocos2d::Controller::BUTTON_DPAD_DOWN)
    {
        log("down");
    }
    else if (key == cocos2d::Controller::BUTTON_DPAD_LEFT)
    {
        log("left");
    }
    else if (key == cocos2d::Controller::BUTTON_DPAD_RIGHT)
    {
        log("right");
    }
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
}
