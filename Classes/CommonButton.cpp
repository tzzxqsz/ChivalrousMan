#include "CommonButton.h"
#include"Path.h"
using namespace cocos2d;
using namespace ui;

bool CommonButton::init(std::string res)
{
	if (Node::init())
	{
		m_btn = Button::create(res);
		m_btn->setName("btn");
		this->addChild(m_btn);
		m_btn->addClickEventListener(CC_CALLBACK_1(CommonButton::onClickCallback, this));
		auto size = m_btn->getContentSize();
		this->setContentSize(size);
		m_spot = Sprite::create(getMainPath("MsgTip"));
		this->addChild(m_spot);
		m_spot->setPosition(size.width*0.5, size.height*0.5);

		return true;
	}
	return false;
}

void CommonButton::addClickCallback(cocos2d::ui::Widget::ccWidgetClickCallback callback)
{
	m_callback = callback;
}

void CommonButton::onEnter()
{
	Node::onEnter();
	m_spot->setVisible(false);
}

void CommonButton::showRedPoint(const bool & visible)
{
	m_spot->setVisible(visible);
}

void CommonButton::setContentSize(const cocos2d::Size & size)
{
	Node::setContentSize(size);
	m_btn->setContentSize(size);
}

void CommonButton::onClickCallback(cocos2d::CCObject * sender)
{
	if (m_callback)
	{
		m_callback(this);
	}
}
