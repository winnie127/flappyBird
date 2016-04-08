#include "HelloWorldScene.h"
#include "Pipe.h"

USING_NS_CC;

HelloWorld::HelloWorld()
:rollSpeed(0.5)
, gravity(0.25)
, dropSpeed(0)
, gameStart(false)
, canTouch(false)
, rotate(1)
, score(0)
{

}

HelloWorld::~HelloWorld()
{

}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	initUI();
	scheduleUpdate();

	//addlistener
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HelloWorld::initUI()
{
	//size
	Size s = Director::getInstance()->getVisibleSize();

	//BG
	bg1 = Sprite::create("bg.png");
	bg1->setPosition(s.width / 2, s.height / 2);
	this->addChild(bg1,1);

	//land
	land1 = Sprite::create("land.png");
	land1->setAnchorPoint(Vec2(0.5, 0));
	land1->setPosition(s.width / 2, 0);
	this->addChild(land1,2);
	backGroundRoll();

	//startBtn
	auto startBtn = Button::create("button_play.png");
	startBtn->setPosition(Vec2(s.width / 2, s.height * 2 / 5));
	startBtn->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			rollSpeed = 1.5;
			gameStart = true;
			scoreLabel->setVisible(true);
			addPipe();
			btnLayer->removeFromParentAndCleanup(true);
			break;
		default:
			break;
		}
	});
	btnLayer = Layer::create();
	this->addChild(btnLayer,2);
	btnLayer->addChild(startBtn);

	//scoreLabel
	char str[10];
	sprintf(str, "%d", score);
	scoreLabel = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 25);
	scoreLabel->setPosition(Vec2(s.width / 2, s.height * 4 / 5));
	this->addChild(scoreLabel, 3);
	scoreLabel->setVisible(false);

	//BirdFrame
	auto animation = Animation::create();
	for (int i = 0; i < 3;i++)
	{
		char str[20];
		sprintf(str, "bird1_%d.png", i);
		animation->addSpriteFrameWithFile(str);
	}
	animation->setDelayPerUnit(1.f / 6);
	animation->setLoops(-1);

	auto action = Animate::create(animation);
	bird = Sprite::create("bird1_0.png");
	bird->runAction(action);
	bird->setPosition(s.width / 2, s.height * 3 / 5);
	this->addChild(bird,3);
	
}

void HelloWorld::addPipe()
{
	//size
	Size s = Director::getInstance()->getWinSize();

	//pipe
	for (int i = 0; i < 3; i++)
	{
		Pipe* pipeUp = Pipe::createPipe(up);
		pipeUp->setAnchorPoint(Vec2(0.5, 1));
		pipeUp->setPosition(s.width + pipeUp->boundingBox().size.width / 2 + i*s.width / 2, s.height / 2 - 50);
		this->addChild(pipeUp, 1);
		pipeUpVector.pushBack(pipeUp);
	}
	for (int i = 0; i < 3; i++)
	{
		Pipe* pipeDown = Pipe::createPipe(down);
		pipeDown->setAnchorPoint(Vec2(0.5, 0));
		pipeDown->setPosition(s.width + pipeDown->boundingBox().size.width / 2 + i*s.width / 2, s.height / 2 + 50);
		this->addChild(pipeDown, 1);
		pipeDownVector.pushBack(pipeDown);
	}
}

void HelloWorld::backGroundRoll()
{
	//Size
	Size s = Director::getInstance()->getVisibleSize();

	//bg
	bg2 = Sprite::create("bg.png");
	bg2->setPosition(s.width + s.width / 2, s.height / 2);
	this->addChild(bg2,1);

	//land
	land2 = Sprite::create("land.png");
	land2->setAnchorPoint(Vec2(0.5, 0));
	land2->setPosition(s.width + s.width / 2, 0);
	this->addChild(land2,2);
}

void HelloWorld::update(float dt)
{
	//Size
	Size s = Director::getInstance()->getVisibleSize();
		
	if (gameStart)
	{
		dropSpeed -= gravity;
		//setPosition
		bird->setPositionY(bird->getPositionY() + dropSpeed);
		if (bird->getPositionY() >= s.height)
		{
			bird->setPositionY(s.height);
		}

		//setRotation
		bird->setRotation(bird->getRotation() + rotate);
		if (bird->getRotation()>=75)
		{
			bird->setRotation(75);
		}
		
	}
	
	//backGroundRoll_judge
	bg1->setPositionX(bg1->getPositionX() - rollSpeed);
	bg2->setPositionX(bg2->getPositionX() - rollSpeed);
	if (bg1->getPositionX() <= -s.width / 2)
	{
		bg1->setPositionX(s.width + s.width / 2-2);
	}
	if (bg2->getPositionX() <= -s.width / 2)
	{
		bg2->setPositionX(s.width + s.width / 2-2);
	}

	//landRoll_judge
	land1->setPositionX(land1->getPositionX() - rollSpeed);
	land2->setPositionX(land2->getPositionX() - rollSpeed);
	if (land1->getPositionX() <= -s.width / 2)
	{
		land1->setPositionX(s.width + s.width / 2 - 2);
	}
	if (land2->getPositionX() <= -s.width / 2)
	{
		land2->setPositionX(s.width + s.width / 2 - 2);
	}
	
	//pipeMove
	Rect body = CCRectMake(bird->getPositionX() - bird->boundingBox().size.width / 2 + 10, bird->getPositionY() - bird->boundingBox().size.height / 2 + 10, 30, 30);
	int temp = CCRANDOM_0_1() * 200 + 150;
	for (int i = 0; i < pipeDownVector.size();i++)
	{
		Pipe* pi = (Pipe*)pipeDownVector.at(i);
		pi->setPositionX(pi->getPositionX() - rollSpeed);
		if (pi->getPositionX() < -pi->boundingBox().size.width / 2)
		{
			pi->setPosition(s.width * 3 / 2, temp + 100);
		}

		//gameOver
		if (pi->boundingBox().intersectsRect(body) || bird->getPositionY() <= land1->boundingBox().size.height + bird->boundingBox().size.height / 2)
		{
			this->unscheduleUpdate();
			gameOver();
			return;
		}
	}
	for (int i = 0; i < pipeUpVector.size(); i++)
	{
		Pipe* pi = (Pipe*)pipeUpVector.at(i);
		pi->setPositionX(pi->getPositionX() - rollSpeed);
		if (pi->getPositionX() < -pi->boundingBox().size.width / 2)
		{
			pi->setPosition(s.width * 3 / 2, temp);
		}

		//gameOver
		if (pi->boundingBox().intersectsRect(body) || bird->getPositionY() <= land1->boundingBox().size.height + bird->boundingBox().size.height / 2)
		{
			this->unscheduleUpdate();
			gameOver();
			return;
		}

		//scoreLabel
		if (pi->getPositionX() >= s.width / 2 - pi->boundingBox().size.width / 2 - 0.7 && pi->getPositionX() <= s.width / 2 - pi->boundingBox().size.width / 2 + 0.7)
		{
			score++;
			char str[10];
			sprintf(str, "%d", score);
			scoreLabel->setString(str);
		}
	}
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (gameStart)
	{
		canTouch = true;
		dropSpeed = 5;
		bird->setRotation(-30);
		return true;
	}
	else
	{
		return false;
	}
}

void HelloWorld::gameOver()
{
	//size
	Size s = Director::getInstance()->getWinSize();

	gameStart = false;
	bird->stopAllActions();

	auto gameSign = Sprite::create("text_game_over.png");
	gameSign->setScale(0);
	gameSign->setPosition(s.width / 2, s.height * 3 / 4);
	this->addChild(gameSign, 1);
	gameSign->runAction(Sequence::create(ScaleTo::create(0.5, 1), DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(HelloWorld::callBack, this)), nullptr));
}

void HelloWorld::callBack()
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
