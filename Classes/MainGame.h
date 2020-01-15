#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Food.h"

using namespace cocos2d;

class MainGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void update(float dt)override;

    // implement the "static create()" method manually
    CREATE_FUNC(MainGame);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
private:
	Rect upRect;
	Rect downRect;
	//Sprite* down;
	bool stretching;
	bool recovering;
	bool get;
	Vec2 lastPos;
	Vec2 desPos;
	Vector<Food*> foodPools;
	int count;
};

#endif // __HELLOWORLD_SCENE_H__
