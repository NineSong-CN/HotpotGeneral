#include "Food.h"

Food::Food() :
	type(),
	dir(cocos2d::ccp(0.0f, 0.0f)),
	speed(0.0f),
	depth(0),
	isSwitch(true)
{
}

bool Food::init()
{
	dir = cocos2d::ccp(0.0f, 0.0f);
	speed = 0.0f;
	depth = 0;
	return false;
}

std::string foodPath[] = { "food_chili.png","food_crab.png","food_fishchip.png","food_prawn.png","food_vege01.png","food_meatroll.png" };

Food * Food::create(FoodType _type, Vec2 _dir, FLOAT _speed, UINT _depth)
{
	Food* food = new (std::nothrow) Food();
	if (food && food->initWithFile(foodPath[_type]))
	{
		food->type = _type;
		food->dir = _dir;
		food->speed = _speed;
		food->depth = _depth;
		food->isSwitch = true;
		food->autorelease();
		return food;
	}
	CC_SAFE_DELETE(food);
	return nullptr;
	return food;
}

void Food::SwitchDir()
{
	if (isSwitch)
	{
		isSwitch = false;
		dir = -dir;
		Vec2 des = getPosition() + dir * 1000;
		stopAllActions();
		runAction(MoveTo::create(speed, des));
		scheduleOnce(schedule_selector(Food::delayOnce),1.0f);
	}
}

void Food::delayOnce(float dt)
{
	isSwitch = true;
}
