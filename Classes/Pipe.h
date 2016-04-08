#ifndef __PIPE_H__
#define __PIPE_H__

#include "cocos2d.h"
enum Dir
{
	up = 0,
	down
};

class Pipe : public cocos2d::Sprite
{
public:
	static Pipe* createPipe(int dir);

	virtual void initPipe(int dir);

	CC_SYNTHESIZE(int, dir, Dir);

};


#endif // !__PIPE_H__
