#include"Thing.h"
#include"Commen.h"
#include"GameScene.h"
#include"DetailLayer.h"
#include"GameDynamicData.h"
#include"Path.h"
#include<fstream>

Thing::Thing(const std::string& name):
	m_name(name)
{
	initDetails(name);
}

Thing::~Thing()
{

}

void  Thing::showDetail(cocos2d::Node* node)
{
	node->removeChildByName("DetailLayer");
	auto detailLayer = DetailLayer::createWithThing(this->getDetails(), getbuyglod());
	detailLayer->setName("DetailLayer");
	node->addChild(detailLayer);
}

std::string Thing::getfileName(const std::string& name)
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
	fin >> m_firsttext;
	m_details.push_back(m_firsttext);
	do
	{
		fin >> tmp;
		if (tmp != "")
			m_details.push_back(tmp);
	} while (!fin.eof());
	fin.close();
}

std::vector<std::string>& Thing::getDetails()
{
	return m_details;
}

float Thing::beUse(cocos2d::CCObject* obj,cocos2d::CCObject* who,cocos2d::CCObject* towho)
{
	return -1.0f;
}

bool Thing::init()
{
	if (Node::init())
	{
		auto bg = ui::Button::create(getCommonPath("img_com_frame"), getCommonPath("img_com_frame"));
		this->addChild(bg);
		bg->addClickEventListener(CC_CALLBACK_1(Thing::onClick, this));
		return true;
	}
	return false;
}

void Thing::addClickCallback(cocos2d::ui::Widget::ccWidgetClickCallback callback)
{
	m_callback = callback;
}

void Thing::onClick(cocos2d::CCObject * sender)
{
	if (m_callback)
		m_callback(this);
}
