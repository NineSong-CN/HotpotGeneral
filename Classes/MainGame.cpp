#include "MainGame.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

enum
{
	kTagChopSticks = 1,
};

Scene* MainGame::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainGame::init()
{
	/**  you can create scene with following comment code instead of using csb file.
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
										   "CloseNormal.png",
										   "CloseSelected.png",
										   CC_CALLBACK_1(MainGame::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
								origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
							origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "MainGame" splash screen"
	auto sprite = Sprite::create("MainGame.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	**/

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(MainGame::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	srand(GetTickCount64());

	scheduleUpdate();

	auto rootNode = CSLoader::createNode("MainScene.csb");

	addChild(rootNode);

	auto chopSticks = Sprite::create("kuaizi.png");

	addChild(chopSticks, 0, kTagChopSticks);
	chopSticks->setPosition(150, 500);

	auto glView = Director::getInstance()->getOpenGLView();
	auto frameSize = glView->getFrameSize();

	upRect = CCRectMake(100.0f, frameSize.height - 200.0f, frameSize.width - 200.0f, 100.0f);
	downRect = CCRectMake(100.0f, 100.0f, frameSize.width - 200.0f, 300.0f);
	stretching = recovering = false;

	CCDrawNode *draw1 = CCDrawNode::create();
	addChild(draw1, 1000);
	ccColor4F yellow = { 1, 1, 0, 1 };
	CCPoint rect1[4] = { ccp(100,frameSize.height - 100.0f),
		ccp(100, frameSize.height - 200.0f),
		ccp(frameSize.width - 100.0f, frameSize.height - 200.0f),
		ccp(frameSize.width - 100.0f, frameSize.height - 100.0f) };
	draw1->drawPolygon(rect1, 4, ccc4f(0, 0, 0, 0), 1, yellow);

	CCDrawNode *draw2 = CCDrawNode::create();
	addChild(draw2, 2000);
	ccColor4F red = { 1, 0, 0, 1 };
	CCPoint rect2[4] = { ccp(100.0f,100.0f),
		ccp(100.0f, 400.0f),
		ccp(frameSize.width - 100.0f, 400.0f),
		ccp(frameSize.width - 100.0f, 100.0f) };
	draw2->drawPolygon(rect2, 4, ccc4f(0, 0, 0, 0), 1, red);

	return true;
}

void MainGame::update(float dt)
{
	auto s = getChildByTag(kTagChopSticks);
	if (stretching && s->getPosition().distance(desPos) <= 1.0f)
	{
		CCLOG("执行:%d", 3);
		stretching = false;
		recovering = true;
		s->stopAllActions();
		s->runAction(MoveTo::create(1.5, lastPos));
	}

	if (recovering && s->getPosition().distance(lastPos) <= 1.0f)
	{
		CCLOG("执行:%d", 4);
		s->stopAllActions();
		recovering = false;
	}
}

bool MainGame::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	return true;
}

void MainGame::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	auto location = touch->getLocation();
	if (!stretching && !recovering)
	{
		auto s = getChildByTag(kTagChopSticks);
		Vec2 sp;
		s->convertToWorldSpace(sp);
		if (upRect.containsPoint(location))
		{
			CCLOG("执行:%d", 1);
			s->stopAllActions();
			s->runAction(MoveTo::create(0.5, Vec2(location.x, location.y)));
		}

		if (downRect.containsPoint(location))
		{
			CCLOG("执行:%d", 2);
			stretching = true;
			s->stopAllActions();
			lastPos = s->getPosition();
			desPos = location;
			s->runAction(MoveTo::create(1, Vec2(location.x, location.y)));
		}
	}
}
