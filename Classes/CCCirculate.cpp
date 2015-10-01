#include "CCCirculate.h"

USING_NS_CC;

Circulate* Circulate::create(float duration, const cocos2d::Point& center, bool clockwise)
{
    Circulate* action = new Circulate();
    action->initWithDuration(duration, center, clockwise);
    action->autorelease();
	
    return action;
}

bool Circulate::initWithDuration(float duration, const cocos2d::Point& center, bool clockwise)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _center = center;
        _clockwise = clockwise;
		
        return true;
    }
	
    return false;
}

void Circulate::startWithTarget(cocos2d::Node* target)
{
	ActionInterval::startWithTarget(target);
    _startPos = target->getPosition();
    _radius = _startPos.distance(_center);
    
    Point offset = _center - _startPos;
    
    _startAngle = atan2f(-offset.y, offset.x);
}

void Circulate::update(float time)
{
	if (_target)
    {
        float angle = _clockwise ? (_startAngle + M_PI * 2.0f * time) : (_startAngle - M_PI * 2.0f * time);
        
        
        
        if (angle >= M_PI * 2.0f)
        {
            angle -= M_PI * 2.0f;
        }
        else if (angle < 0.0f)
        {
            angle += M_PI * 2.0f;
        }
        
        _target->setPosition(
                             Point(_center.x - _radius * cosf(angle),
                                   _center.y + _radius * sinf(angle)));
    }
}
