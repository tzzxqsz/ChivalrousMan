#pragma once
#ifndef __CS_BASE_VIEW_H__
#define __CS_BASE_VIEW_H__
#include"tool/PreProcess.h"
#include<map>
#include<string>
#include"jsonCpp/value.h"

using Param = Json::Value;

class CSBaseView : public cocos2d::Node
{
public:
	CSBaseView();

	virtual ~CSBaseView();

	CreateWithParam(CSBaseView, Json::Value)

	bool init(const Json::Value& csb);
protected:
	void filterChildNode(cocos2d::Node* parent);

	cocos2d::Node* m_resourceNode;

	std::map<std::string, cocos2d::Node*> _self;
};

#endif // !__CS_BASE_VIEW_H__
