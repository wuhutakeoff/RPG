#pragma once
#include "DataStruct.h"
#include "Player.h"
#include "NpcMgr.h"
#include "MonsterMgr.h"
#include "Define.h"
#include "WndBase.h"
#include "TaskMgr.h"
#include "PetBag.h"
class CGameMap:public CWndBase
{
public:
	CGameMap();
	void onUpdate();
	void onRender();
	void onCollision();
	void changeMap(int nID);
	void recharge();
	void setNull();

	SYN_THE_SIZE_READONLY(CPlayer*, m_pPlayer, Player);
	SYN_THE_SIZE_READONLY(CMonsterMgr*, m_pMonsterMgr, MonsterMgr);
	SYN_THE_SIZE_READONLY(CMapDt*, m_pCurMapDt, CurMapDt);
	SYN_THE_SIZE_READONLY(CNpcMgr*, m_pNpcMgr, NpcMgr);
	SYN_THE_SIZE_READONLY(CTaskMgr*, m_pTaskMgr, TaskMgr);
private:
	//ר�����ڴ����ͼ�߼�����Ⱦ�ĵ�ͼ���ݡ�
	//CNpcMgr* m_pNpcMgr;
	vector < CTask*> m_vecTask;
	int x;
	int y;
};

