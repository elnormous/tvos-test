#pragma once

#include <CCActionInterval.h>

class Circulate: public cocos2d::ActionInterval
{
public:

    static Circulate* create(float duration, const cocos2d::Point& center, bool clockwise = true);
	
	bool initWithDuration(float duration, const cocos2d::Point& center, bool clockwise);
	
	virtual void startWithTarget(cocos2d::Node* target);
	virtual void update(float time);
	
private:
    float _radius;
    cocos2d::Point _center;
    bool _clockwise;
	cocos2d::Point _startPos;
    float _startAngle;
};
