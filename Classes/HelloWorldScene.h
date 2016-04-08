#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "Pipe.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();
	~HelloWorld();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	//initUI
	void initUI();

	//initPipe
	void addPipe();

	//bg-roll
	void backGroundRoll();

	//updata
	void update(float dt);

	//gameOver
	void gameOver();

	//gameOver _callback
	void callBack();
   
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	Vector<Pipe*>pipeUpVector,pipeDownVector;

	//map_roll
	Sprite* bg1, *bg2,*land1,*land2;

	Sprite* bird;

	//score_Label
	Label* scoreLabel;

	//·ÖÊý
	int score;

	//speed_control
	float rollSpeed, gravity, dropSpeed, rotate;

	//gameStart button layer
	Layer* btnLayer;

	//gameStart_control
	bool gameStart, canTouch;

	bool onTouchBegan(Touch *touch, Event *unused_event);
};

#endif // __HELLOWORLD_SCENE_H__
