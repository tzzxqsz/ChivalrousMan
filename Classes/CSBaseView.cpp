#include"CSBaseView.h"
#include"cocostudio/ActionTimeline/CSLoader.h"
#include"Commen.h"

CSBaseView::CSBaseView()
{
}

CSBaseView::~CSBaseView()
{
}

bool CSBaseView::init(const Json::Value& csb)
{
	if (Node::init())
	{
		m_resourceNode = cocos2d::CSLoader::createNode(csb["model"].asString() + "/" + csb["name"].asString() + ".csb");
		this->addChild(m_resourceNode);
		filterChildNode(m_resourceNode);
		return true;
	}
	return false;
}

void CSBaseView::filterChildNode(cocos2d::Node * parent)
{
	auto childs = parent->getChildren();
	for (auto node : childs)
	{
		std::string name = node->getName();
		if (name[0] =='_')
		{
			_self[name] = node;
		}
		filterChildNode(node);
	}
}
