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

//��ʵ�����ģʽ��������
#define SINGLE_ATTRIBUTES(__TYPE__) \
private: \
	static __TYPE__* m_instance; \
	static std::atomic<__TYPE__*> m_load; \
	static std::mutex m_mutex

//���嵥ʵ�����ģʽ�Ļ�������
#define DEFINE_SINGLE_ATTRIBUTES(__TYPE__) \
std::atomic<__TYPE__*> __TYPE__::m_load; \
std::mutex __TYPE__::m_mutex; \
__TYPE__* __TYPE__::m_instance = nullptr

//��ȡ��ʵ�����ģʽ��ʵ������
#define GET_SINGLE_OBJECT(__TYPE__)  \
public: \
	static __TYPE__*  getInstance() \
	{ \
	m_instance = m_load.load(std::memory_order_relaxed); \
	std::atomic_thread_fence(std::memory_order_acquire); \
	if (m_instance == nullptr) \
	{ \
		std::lock_guard<std::mutex> lock(m_mutex); \
		m_instance = m_load.load(std::memory_order_relaxed); \
		if (m_instance == nullptr) \
		{ \
			m_instance = new  __TYPE__; \
			std::atomic_thread_fence(std::memory_order_release); \
			m_load.store(m_instance, std::memory_order_release); \
		} \
	} \
	return m_instance; \
	}

#define GettingAndSetting(varType,varName,funName) \
protected: varType varName; \
public: virtual varType get##funName(void){return varName;} \
public: virtual void set##funName(varType var) {varName=var;}

#define PROPERTY__REF(varType, varName, funName)     \
protected: varType varName;     \
public: virtual const varType& get##funName(void){return varName;}    \
public: virtual void set##funName(const varType& var){varName=var;} 


#define CreateWithParam(__OBJTYPE__,__TYPE__) \
static __OBJTYPE__* create##__OBJTYPE__(const __TYPE__& PARAM)  \
{    \
__OBJTYPE__*  pRet = new __OBJTYPE__;     \
if (pRet&&pRet->init(PARAM))      \
{      \
	pRet->autorelease();    \
	return pRet;     \
}     \
else    \
{       \
	delete pRet;     \
	pRet = nullptr;      \
	return nullptr;      \
}      \
}  

#define ADD_PROPERTY(NAME)  \
fin >> tmp; \
fin >> tmp; \
m_##NAME = std::stof(tmp)

#define DEC_REFLECT_FUNC(__TYPE__)    \
friend Npc* ReflectClass##__TYPE__();

#define DEF_REFLECT_FUNC(__TYPE__) \
Npc* ReflectClass##__TYPE__() \
{ \
	return (new __TYPE__); \
}

#define REG_REFLECT_CLASS(__TYPE__) \
ReflectNpc::getInstance()->registerReflectClass(#__TYPE__,&ReflectClass##__TYPE__)

#define GET_REFLECT_OBJECT ReflectNpc::getInstance()->getReflectObject

enum class Dir
{
	Dir_Left,
	Dir_Down,
	Dir_Right,
	Dir_Up,
};

enum class Player_Type
{
	Player1_Type,
	Player2_Type,
	Player3_Type,
};

//��ͼ����
#define LEVEL_ONE 1
#define LEVEL_TWO 2
#define LEVEL_THREE 3
#define LEVEL_FOUR 4
#define LEVEL_FIVE 5

//��Ʒ����
#define MEDICATION 1001
#define EQUIPMENT 1002
#define SKILL 1003 

//װ������
#define EM_HEAD 1005
#define EM_WEPON 1006
#define EM_JEWELRY 1007
#define EM_CLOTH 1008
#define EM_FOOT 1009

//��������
#define T_KILL 2001              //��ɱ����
#define T_COLLECT  2002     //�ռ���Ʒ
#define T_ACCESS 2003        //���ʱ���

//NPC״̬
#define NS_FREE 3001       //����״̬
#define NS_HTASK 3002    //��δ������
#define NS_WSTASK 3003   //�еȴ��ύ������
#define NS_STASK  3004    //�д��ύ����

//���״̬
#define P_STATUS_NORMAL 4001
#define P_STATUS_HEADER 4002
#define P_STATUS_MEMBER 4003

//���鰴ť��Ϊ
#define TB_DISSOLVE 5001
#define TB_QUIT 5002
#define TB_KICKOUT 5003
#define TB_NULL 5004

typedef cocos2d::Node* (*Sel_Create_Func)(void);
#define CREATE_FUNC_SELECTOR(_CREATE_FUNC) reinterpret_cast<Sel_Create_Func>(&_CREATE_FUNC)

#endif // !__PRE_PRECESS_H__

