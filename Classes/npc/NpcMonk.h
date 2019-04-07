#pragma once
#ifndef __NPC_MONK_H__
#define __NPC_MONK_H__
#include"base/Npc.h"

/**
*NpcMonk
*¿œ∫Õ…–
*/
class NpcMonk Inherit(Npc)
{
	DEC_REFLECT_FUNC(NpcMonk)
public:
	NpcMonk();
	~NpcMonk();

	virtual void collisionEvent() override;
private:

};

#endif // !__NPC_MKNK_H__

