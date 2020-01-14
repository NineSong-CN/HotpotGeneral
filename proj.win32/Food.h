#pragma once
#include "cocos2d.h"
class Food :public cocos2d::Sprite
{
public:
	enum FoodType
	{
		NONE,
		MEAT,
		VEGE
	};
public:
	Food();
	virtual bool init()override;
	static Food* create(FoodType _type,FLOAT speed, UINT depth);
	void update(float dt)override;
private:
	FoodType type;
	cocos2d::Vec2 dir;
	FLOAT speed;
	UINT depth;
};

