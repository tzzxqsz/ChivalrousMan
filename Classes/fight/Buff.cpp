#include"Buff.h"
#include"tool/Path.h"
#include"tool/ConfigUtils.h"

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
	this->m_times = times;
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
	if (this->m_times <= 0)
	{
		this->removeFromParent();
		return;
	}
	--this->m_times;
}

void Buff::decodeAttr(const std::string & name)
{
	auto attrs = ConfigUtils::getInstance()->getConfigAttr(getBuffPurePath(name), false);
	for (auto& var : attrs)
	{
		m_buffAttr[var.first] = std::stoi(var.second);
	}
}