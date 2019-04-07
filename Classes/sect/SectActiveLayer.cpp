#include"SectActiveLayer.h"
#include"tool/Commen.h"
#include"tool/GameData.h"
#include"tool/UIHelper.h"
#include"tool/ConfigUtils.h"
#include"common/CommonProcessBar.h"
#include"common/CommonButton.h"
#include"player/CameraPlayer.h"
#include"tool/LogUtil.h"
#include"base/Medication.h"
#include"tool/Path.h"
#include"backpack/BackPackManager.h"
#include"SectManager.h"

bool SectActiveLayer::init()
{
	if (CommonTouchLayer::init())
	{
		auto size = SCREEN;
		m_imageBg = cocos2d::ui::ImageView::create();
		this->addChild(m_imageBg);
		m_imageBg->setPosition(cocos2d::Vec2(size.width*0.5, size.height*0.5));
		setExcludeRect(m_imageBg->getPosition(), cocos2d::Rect(0, 0, size.width, size.height));

		m_xiulian = cocos2d::ui::Button::create(getCommonPath("Effect"));
		m_xiulian->setTitleFontSize(32);
		m_xiulian->setTitleFontName(getFontPath("font2"));
		m_xiulian->setTitleText(StringValue("XiulianText"));
		m_xiulian->addClickEventListener(CC_CALLBACK_1(SectActiveLayer::onXiulianClickCallback, this));
		this->addChild(m_xiulian);

		m_gongfa = cocos2d::ui::Button::create(getCommonPath("Effect"));
		m_gongfa->setTitleFontSize(32);
		m_gongfa->setTitleFontName(getFontPath("font2"));
		m_gongfa->setTitleText(StringValue("GongfaText"));
		m_gongfa->addClickEventListener(CC_CALLBACK_1(SectActiveLayer::onGongfaClickCallback, this));
		this->addChild(m_gongfa);

		m_nodeDec = cocos2d::Node::create();
		this->addChild(m_nodeDec);
		m_nodeDec->setPosition(20, size.height - 30);

		m_title = UIHelper::getInstance()->createTTFConfigLabel("", 45);
		m_title->setPosition(size.width*0.5, size.height - 40);
		this->addChild(m_title);

		auto backBtn = ui::Button::create(getButtonPath("back_btn"));
		this->addChild(backBtn);
		backBtn->setPosition(Vec2(backBtn->getContentSize().width*0.5 + 5, size.height - 34));
		backBtn->addClickEventListener(CC_CALLBACK_1(SectActiveLayer::onBackClickCallback, this));

		initXiulian();
		initGongfa();
		return true;
	}
	return false;
}

void SectActiveLayer::updateUI(const std::string & name)
{
	m_name = name;
	m_imageBg->loadTexture(getSectBgPath(name));
	updateDec();
	updateAttrs();
}

void SectActiveLayer::onBackClickCallback(cocos2d::CCObject * sender)
{
	removeFromParent();
}

void SectActiveLayer::onXiulianClickCallback(cocos2d::CCObject * sender)
{
	if (!m_nodeGongfa->isVisible())
	{
		m_nodeXiulian->setVisible(true);
		updateXiulianView();
	}
}

void SectActiveLayer::onGongfaClickCallback(cocos2d::CCObject * sender)
{
	if (!m_nodeXiulian->isVisible())
		m_nodeGongfa->setVisible(true);
}

void SectActiveLayer::onOnceXiulianClickCallback(cocos2d::CCObject * sender)
{
	int nums = BackPackManager::getInstance()->ThingNums("Thing/ColorfulSpar");
	if (nums > 0)
	{
		auto attrs = ConfigUtils::getInstance()->getConfigAttr(getThingPurePath("ColorfulSpar"));
		if (SectManager::getInstance()->addXiulianExp(std::stof(attrs["addblood"])*nums))
		{
			BackPackManager::getInstance()->removeBackPackThing("Thing/ColorfulSpar", nums);
		}
		updateXiulianView();
	}
	else
	{
		UIHelper::getInstance()->showTip(StringValue("XiulianLack"));
	}
}

void SectActiveLayer::onOneXiulianClickCallback(cocos2d::CCObject * sender)
{
	int nums = BackPackManager::getInstance()->ThingNums("Thing/ColorfulSpar");
	if (nums > 0)
	{
		auto attrs = ConfigUtils::getInstance()->getConfigAttr(getThingPurePath("ColorfulSpar"));
		if (SectManager::getInstance()->addXiulianExp(std::stof(attrs["addblood"])))
		{
			BackPackManager::getInstance()->removeBackPackThing("Thing/ColorfulSpar", 1);
		}
		updateXiulianView();
	}
	else
	{
		UIHelper::getInstance()->showTip(StringValue("XiulianLack"));
	}
}

void SectActiveLayer::onClicked()
{

}

void SectActiveLayer::updateDec()
{
	auto desc = ConfigUtils::getInstance()->getConfigDec(getSectPath(m_name));
	m_title->setString(desc[CONFIG_NAME]);
}

void SectActiveLayer::updateAttrs()
{
	auto attrs = ConfigUtils::getInstance()->getConfigAttr(getSectPath(m_name));
	cocos2d::Vec2 pos;
	pos.x = std::stof(attrs["xiulianX"]);
	pos.y = std::stof(attrs["xiulianY"]);
	m_xiulian->setPosition(pos);
	pos.x = std::stof(attrs["gongfaX"]);
	pos.y = std::stof(attrs["gongfaY"]);
	m_gongfa->setPosition(pos);
}

void SectActiveLayer::initXiulian()
{
	m_nodeXiulian = cocos2d::Node::create();
	m_nodeXiulian->setPosition(SCREEN.width*0.5, SCREEN.height*0.5);
	this->addChild(m_nodeXiulian);
	m_nodeXiulian->setVisible(false);

	auto image = cocos2d::ui::ImageView::create(getBackgroundPath("StyleBg8"));
	m_nodeXiulian->addChild(image);
	auto size = image->getContentSize();
	auto delbtn = CommonButton::createCommonButton(getButtonPath("DelBtn"));
	delbtn->setPosition(Vec2(size.width*0.5, size.height*0.5));
	m_nodeXiulian->addChild(delbtn);
	delbtn->addClickCallback([this](cocos2d::Ref*) {
		this->m_nodeXiulian->setVisible(false);
	});

	m_avatar = cocos2d::ui::ImageView::create(getPlayerWaitPath(GetPlayerData().getroleType(), "1"));
	m_nodeXiulian->addChild(m_avatar);
	m_avatar->setScale(1.5);
	auto label1 = UIHelper::getInstance()->createTTFConfigLabel(StringValue("GongfaText") + ":", 30);
	m_nodeXiulian->addChild(label1);
	label1->setAnchorPoint(Vec2(0, 0.5));
	label1->setPosition(-90, size.height*0.5 - 30);
	auto gongfaName = SectManager::getInstance()->getGongfaName();
	m_gongfaName = UIHelper::getInstance()->createTTFConfigLabel(gongfaName == "" ? StringValue("NoLearnGongfa") : gongfaName, 30);
	m_nodeXiulian->addChild(m_gongfaName);
	m_gongfaName->setAnchorPoint(Vec2(0, 0.5));
	m_gongfaName->setPosition(-10, size.height*0.5 - 30);

	auto label2 = UIHelper::getInstance()->createTTFConfigLabel(StringValue("JingJieText") + ":", 30);
	m_nodeXiulian->addChild(label2);
	label2->setAnchorPoint(Vec2(0, 0.5));
	label2->setPosition(-90, size.height*0.5 - 70);
	m_jingjie = UIHelper::getInstance()->createTTFConfigLabel(SectManager::getInstance()->getJingjieName(), 30);
	m_nodeXiulian->addChild(m_jingjie);
	m_jingjie->setAnchorPoint(Vec2(0, 0.5));
	m_jingjie->setPosition(-10, size.height*0.5 - 70);

	auto stone = Medication::createWithImage(getThingPath("ColorfulSpar"));
	stone->addClickCallback([this,stone](cocos2d::Ref*) {
		stone->showDetail(this);
	});
	int nums = BackPackManager::getInstance()->ThingNums("Thing/ColorfulSpar");
	m_stoneNums = LabelTTF::create(NTS(nums), "¿¬Ìå", 20);
	m_stoneNums->setPosition(-18, -14);
	m_stoneNums->setColor(ccc3(255, 242, 0));
	stone->addChild(m_stoneNums);
	m_nodeXiulian->addChild(stone);
	stone->setPosition(-size.width*0.5 + 60, -size.height*0.5 + 80);
	m_curProcess = CommonProcessBar::create(getCommonPath("BarBG"), getCommonPath("bar"));
	m_nodeXiulian->addChild(m_curProcess);
	m_curProcess->setValue(30);
	m_curProcess->visibleValue(true);
	m_curProcess->setPosition(30, -size.height*0.5 + 80);
	m_btnOnce = CommonButton::createCommonButton(getButtonPath("CommonBtn"));
	m_btnOnce->setFontSize(26);
	m_btnOnce->setString(StringValue("XiulianText"));
	m_btnOnce->addClickCallback(CC_CALLBACK_1(SectActiveLayer::onOneXiulianClickCallback, this));
	m_nodeXiulian->addChild(m_btnOnce);
	m_btnOnce->setPosition(-70, -size.height*0.5 + 40);
	m_btnOneKey= CommonButton::createCommonButton(getButtonPath("CommonBtn"));
	m_btnOneKey->setFontSize(26);
	m_btnOneKey->addClickCallback(CC_CALLBACK_1(SectActiveLayer::onOnceXiulianClickCallback, this));
	m_nodeXiulian->addChild(m_btnOneKey);
	m_btnOneKey->setString(StringValue("OnceXiulianText"));
	m_btnOneKey->setPosition(70, -size.height*0.5 + 40);
}

void SectActiveLayer::initGongfa()
{
	m_nodeGongfa = cocos2d::Node::create();
	m_nodeGongfa->setPosition(SCREEN.width*0.5, SCREEN.height*0.5);
	this->addChild(m_nodeGongfa);
	m_nodeGongfa->setVisible(false);

	auto image = cocos2d::ui::ImageView::create(getBackgroundPath("StyleBg5"));
	m_nodeGongfa->addChild(image);
	auto size = image->getContentSize();
	auto delbtn = CommonButton::createCommonButton(getButtonPath("DelBtn"));
	delbtn->setPosition(Vec2(size.width*0.5 - 10, size.height*0.5 - 10));
	m_nodeGongfa->addChild(delbtn);
	delbtn->addClickCallback([this](cocos2d::Ref*) {
		this->m_nodeGongfa->setVisible(false);
	});

	auto title = UIHelper::getInstance()->createTTFConfigLabel(StringValue("GongfaText"), 28);
	m_nodeGongfa->addChild(title);
	title->setPosition(0, size.height*0.5 - 20);

	m_listview = cocos2d::ui::ListView::create();
	m_nodeGongfa->addChild(m_listview);
	m_listview->setContentSize(Size(size.width - 20, size.height - 50));
	auto realSize = m_listview->getContentSize();
	m_listview->setPosition(Vec2(-realSize.width*0.5, -realSize.height*0.5 - 10));

	for (int i = 1; i <= 4; ++i)
	{
		auto layout = cocos2d::ui::Layout::create();
		layout->setContentSize(Size(size.width - 70, 100));
		auto bg = cocos2d::ui::ImageView::create(getCommonPath("CellBg"));
		bg->setScale9Enabled(true);
		bg->setAnchorPoint(Vec2(0, 0));
		bg->setContentSize(Size(size.width - 80, 90));
		bg->setPosition(Vec2(25, 5));
		layout->addChild(bg);
		auto icon = cocos2d::ui::ImageView::create(getSectSkillPath(GetPlayerData().getSect(), "skill" + NTS(i)));
		layout->addChild(icon);
		icon->setPosition(Vec2(70, 50));

		auto dec = ConfigUtils::getInstance()->getConfigAttr(getSectSkillAttrPath(GetPlayerData().getSect(), "skill" + NTS(i)));
		auto name = UIHelper::getInstance()->createTTFConfigLabel(StringValue("GName")+dec["textname"], 24);
		layout->addChild(name);
		name->setPosition(110, 70);
		name->setAnchorPoint(Vec2(0, 0.5));
		auto gold = UIHelper::getInstance()->createTTFConfigLabel(StringValue("GGold") + dec["gold"], 24);
		layout->addChild(gold);
		gold->setPosition(110, 35);
		gold->setAnchorPoint(Vec2(0, 0.5));

		auto btn = CommonButton::createCommonButton(getButtonPath("CommonBtn"));
		btn->setString(StringValue("LearnText"));
		btn->setFontSize(30);
		btn->addClickCallback([i](cocos2d::Ref*) {
			SectManager::getInstance()->learnGongfa("skill" + NTS(i));
		});
		layout->addChild(btn);
		btn->setPosition(Vec2(360, 50));
		m_listview->pushBackCustomItem(layout);
	}
}

void SectActiveLayer::updateXiulianView()
{
	auto gongfaName = SectManager::getInstance()->getGongfaName();
	m_gongfaName->setString(gongfaName == "" ? StringValue("NoLearnGongfa") : gongfaName);
	int nums = BackPackManager::getInstance()->ThingNums("Thing/ColorfulSpar");
	m_stoneNums->setString(NTS(nums));
	auto data = SectManager::getInstance()->getJingjie();
	m_curProcess->setMax(data.exp);
	m_curProcess->setValue(data.curexp);
	m_jingjie->setString(SectManager::getInstance()->getJingjieName());
}
