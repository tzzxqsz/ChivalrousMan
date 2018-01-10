#include"Thing.h"
#include"Commen.h"
#include"GameScene.h"
#include"DetailLayer.h"
#include"GameDynamicData.h"
#include<fstream>

Thing::Thing(const std::string& name)
{
	initDetails(name);
}

Thing::~Thing()
{

}

void  Thing::showDetail(cocos2d::Node* node)
{
	node->removeChildByName("DetailLayer");
	auto detailLayer = DetailLayer::createWithThing(this);
	detailLayer->setName("DetailLayer");
	node->addChild(detailLayer);
}

std::string Thing::getName(const std::string& name)
{
	std::string targetname;
	std::string tmp = "";
	for (size_t i = 0; i < name.length(); i++)
	{
		tmp = name[i];
		if (tmp == ".")
		{
			break;
		}
		else
		{
			targetname += name[i];
		}
	}
	return targetname;
}

void  Thing::initDetails(const std::string& name)
{
	std::string realname = name;
	realname += ".dec";
	std::ifstream fin;
	fin.open(realname, std::ios::in);
	if (fin.fail())
	{
		return;
	}
	std::string tmp;
	do
	{
		fin >> tmp;
		m_details.push_back(tmp);
	} while (!fin.eof());
	fin.close();
}

std::vector<std::string>& Thing::getDetails()
{
	return m_details;
}