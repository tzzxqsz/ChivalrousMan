#include"TalismanAvatar.h"
#include"tool/Commen.h"
#include"tool/Path.h"

TalismanAvatar * TalismanAvatar::create()
{
	TalismanAvatar* pRet = new TalismanAvatar();
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool TalismanAvatar::init()
{
	if (Node::init())
	{
		m_avatar = ui::ImageView::create("");
		m_avatar->ignoreContentAdaptWithSize(true);
		this->addChild(m_avatar);
		
		return true;
	}
	return false;
}

void TalismanAvatar::onEnter()
{
	Node::onEnter();
	auto move1 = MoveBy::create(1.3, Vec3(0, 40, 0));
	auto move2 = MoveBy::create(1.3, Vec3(0, -40, 0));
	auto sequece = Sequence::createWithTwoActions(move1, move2);
	m_avatar->runAction(CCRepeatForever::create(sequece));
}

void TalismanAvatar::updateAvatar(const std::string & name)
{
	m_avatar->loadTexture(getTalismanPath(name));
	m_avatar->setScale(1.3);
}

TalismanAvatar::TalismanAvatar()
{

}

TalismanAvatar::~TalismanAvatar()
{

}