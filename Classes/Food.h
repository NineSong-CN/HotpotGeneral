#pragma once
#include "cocos2d.h"

using namespace cocos2d;
class Food :public cocos2d::Sprite
{
public:
	enum FoodType
	{
		CHILI,
		CRAB,
		FISHCHIP,
		PRAWN,
		VEGE001
	};
public:
	Food();
	virtual bool init()override;
	static Food* create(FoodType _type, Vec2 _dir, FLOAT speed, UINT depth = 0);
	void SwitchDir();
	void delayOnce(float dt);
private:
	FoodType type;
	Vec2 dir;
	FLOAT speed;
	UINT depth;
	bool isSwitch;
};

