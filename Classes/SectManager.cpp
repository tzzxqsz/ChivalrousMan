#include"SectManager.h"
#include"DBDao.h"
#include"Model.h"
#include"CameraPlayer.h"

DEFINE_SINGLE_ATTRIBUTES(SectManager);

bool SectManager::joinSect(const std::string & name)
{
	DBDao<PlayerInfo> db;
	PlayerInfo pi;
	pi.setsect(name);
	db.setModel(pi); 
	std::map<std::string, std::string> kvls;
	kvls["playername"] = GetPlayerData().getplayername();
	kvls["rolename"] = GetPlayerData().getrolename();
	return db.updateModel(kvls);
 }
