#pragma once
#include "Npc.h"
class CNpcMgr
{
public:
	CNpcMgr();
	//ͨ�����к͵�ͼID��ȡNpc
	CNpc* getNpc(int nRow, int nCol, int nMapID);
	vector<CVec2> getNpcPos(int nMapID);

private:
	vector<CNpc*> m_vecNpc;
};

