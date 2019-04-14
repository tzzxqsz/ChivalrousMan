#include"Buff.h"

Buff::~Buff()
{
}

void Buff::attachTo(cocos2d::Node * node)
{
	node->addChild(this);
	this->play();
}

void Buff::setTimes(const int & times)
{
	this->times = times;
}

void Buff::play()
{
}

bool Buff::init()
{
	if (Node::init())
	{
		return true;
	}
	return false;
}

void Buff::decTimes()
{
	if (this->times <= 0)
	{
		this->removeFromParent();
		return;
	}
	--this->times;
}

void Buff::decodeAttr(const std::string & name)
{
}