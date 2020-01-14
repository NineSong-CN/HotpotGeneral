#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

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
	cocos2d::Rect upRect;
	cocos2d::Rect downRect;
	bool stretching;
	bool recovering;
	cocos2d::Vec2 lastPos;
	cocos2d::Vec2 desPos;
	cocos2d::Vector<cocos2d::Sprite*> spritePools;
};

#endif // __HELLOWORLD_SCENE_H__
