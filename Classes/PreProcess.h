#pragma once
#ifndef __PRE_PROCESS_H__
#define __PRE_PROCESS_H__
#include"cocos2d.h"

#define CLASS_ESSENTAIL(__TYPE__)  \
    private:  \
           __TYPE__(){} \
    public:          \
           virtual ~__TYPE__(){}

#define Inherit(__TYPE__) :public __TYPE__

#endif // !__PRE_PRECESS_H__
