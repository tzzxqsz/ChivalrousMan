#include"UIHelper.h"
#include"Path.h"

DEFINE_SINGLE_ATTRIBUTES(UIHelper);

cocos2d::Label * UIHelper::createTTFConfigLabel(const std::string & text, const int & fontSize, cocos2d::Color3B color, const std::string & font)
{
	cocos2d::TTFConfig ttfConfig;
	ttfConfig.fontFilePath = getFontPath(font); //±ØÐëÅäÖÃ
	ttfConfig.fontSize = fontSize;
	auto label = cocos2d::Label::createWithTTF(ttfConfig, text);
	label->setColor(color);
	return label;
}
