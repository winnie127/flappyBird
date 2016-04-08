#include "Pipe.h"

Pipe* Pipe::createPipe(int dir)
{
	auto pipe = new Pipe();
	if (pipe)
	{
		pipe->autorelease();
		pipe->initPipe(dir);
		return pipe;
	}
	CC_SAFE_RELEASE(pipe);
	pipe = NULL;
	return pipe;
}

void Pipe::initPipe(int dir)
{
	if (dir)
	{
		this->initWithFile("pipe_down.png");
		this->setDir(up);
	}
	else
	{
		this->initWithFile("pipe_up.png");
		this->setDir(down);
	}
}