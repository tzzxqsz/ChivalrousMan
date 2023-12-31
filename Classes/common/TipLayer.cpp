#include"TipLayer.h"
#include"tool/GameData.h"
#include"tool/Commen.h"
#include"ui/UIText.h"

bool TipLayer::init(const std::string& tiptext)
{
	if (Layer::init())
	{
		auto size = SCREEN;
		auto back = Sprite::create("tipbg.png");
		back->setPosition(size.width*0.5, size.height - back->getContentSize().height*0.5 - 10);
		this->addChild(back);

		auto tipLabel = LabelTTF::create(tiptext, "����", 25);
		tipLabel->setColor(ccc3(217, 17, 27));
		tipLabel->setPosition(size.width*0.5, back->getPositionY());
		this->addChild(tipLabel);
		
		setZOrder(100);
		scheduleOnce(schedule_selector(TipLayer::killSelf), 1.5);
		return true;
	}
	return false;
}

void TipLayer::killSelf(float dt)
{
	this->removeFromParent();
}
