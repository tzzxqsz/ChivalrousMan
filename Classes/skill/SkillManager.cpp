#include"SkillManager.h"
#include"tool/Commen.h"
#include"tool/GameData.h"
#include"tool/GameDynamicData.h"
#include"dbconnect/Model.h"
#include"dbconnect/DBDao.h"

DEFINE_SINGLE_ATTRIBUTES(SkillManager);

SkillManager::SkillManager()
{

}

 SkillManager::~SkillManager()
{

}

 void SkillManager::release()
 {
	 RELEASE_NULL(m_instance);
 }

int SkillManager::addSkill(const std::string& name,const int& grade)
 {
	auto it = m_skillMap.find(name);
	if (it != m_skillMap.end())
	{
		return -1;
	}
	m_skillMap[name] = grade;
	insertSkillInfo(name, grade);
	 return 0;
 }

 void SkillManager::removeSkill(const std::string& name)
 {
	 deleteSkillInfo(name);
	 m_skillMap.erase(name);
 }

 bool SkillManager::haveSkill(const std::string& name)
 {
	 auto it = m_skillMap.find(name);
	 return it != m_skillMap.end();
 }

 const std::map<std::string, int>& SkillManager::getSkillMap()
 {
	 return m_skillMap;
 }

 int SkillManager::skillNumbers()
 {
	 return m_skillMap.size();
 }

 int SkillManager::upSkill(const std::string& name)
 {
	 if (m_skillMap.find(name) != m_skillMap.end())
	 {
		 m_skillMap[name] += 1;
		 SkillInfo info;
		 DBDao<SkillInfo> dao;
		 info.setskillgrade(NTS(m_skillMap[name]));
		 std::map<std::string, std::string> keyvls;
		 keyvls["playername"] = GetStringData("playername");
		 keyvls["rolename"] = GetStringData("rolename");
		 keyvls["skillname"] = name;
		 dao.setModel(info);
		 dao.updateModel(keyvls);
		 return 0;
	 }
	 return -1;
 }

 void SkillManager::readSkillInfo()
 {
	 m_skillMap.clear();
	 SkillInfo info;
	 DBDao<SkillInfo> dao;
	 info.setplayername(GetStringData("playername"));
	 info.setrolename(GetStringData("rolename"));
	 dao.setModel(info);
	 auto list = dao.queryModel();
	 for (auto var : list)
	 {
		 m_skillMap[var.getskillname()] = std::stoi(var.getskillgrade());
	 }
 }

 void SkillManager::insertSkillInfo(const std::string& name, const int& grade)
 {
	 SkillInfo info;
	 DBDao<SkillInfo> dao;
	 info.setplayername(GetStringData("playername"));
	 info.setrolename(GetStringData("rolename"));
	 info.setskillname(name);
	 info.setskillgrade(NTS(grade));
	 dao.setModel(info);
	 dao.insertModel();
 }

 void SkillManager::deleteSkillInfo(const std::string& name)
 {
	 SkillInfo info;
	 DBDao<SkillInfo> dao;
	 info.setplayername(GetStringData("playername"));
	 info.setrolename(GetStringData("rolename"));
	 info.setskillname(name);
	 dao.setModel(info);
	 dao.deleteModel();
 }