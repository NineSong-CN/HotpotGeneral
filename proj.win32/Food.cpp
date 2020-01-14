#include "Food.h"

Food::Food() :
	type(NONE),
	dir(cocos2d::ccp(0.0f, 0.0f)),
	speed(0.0f),
	depth(0)
{
}

bool Food::init()
{
	type = NONE;
	dir = cocos2d::ccp(0.0f, 0.0f);
	speed = 0.0f;
	depth = 0;
	return false;
}

Food * Food::create(FoodType _type, FLOAT _speed, UINT _depth = 0)
{
	Food* food = (Food*)Sprite::create();

	food->type = _type;
	food->dir.x = rand() % 2 - 0.5f > 0 ? 1 : -1;
	food->speed = _speed;
	food->depth = _depth;
	food->scheduleUpdate();

	return food;
}

void Food::update(float dt)
{
	if (true)
	{

	}
}
