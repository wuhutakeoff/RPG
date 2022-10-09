#include "NpcMgr.h"
#include "Define.h"
#include"DataMgr.h"
CNpcMgr::CNpcMgr()
{
	//��Ϸ����������Ҫ����Npc�����Կ��������ﴴ����Npc
	int nCount = CDataMgr::getInstance()->getMgr<CNpcDtMgr>("NpcDtMgr")->getSize();
	for (int i = 0; i < nCount; i++)
	{
		CNpc* pNpc = new CNpc();
		//��Ҫ�õ�npc���ݣ���ÿ��npc�������Դ���
		int nID = 2001 + i;
		CNpcDt* pNpcDt = CDataMgr::getInstance()->getMgr<CNpcDtMgr>("NpcDtMgr")->getDataByID<CNpcDt>(nID);
		//ͨ�����Npc���ݶ�npc���Խ��д���
		//pNpc->nType = pNpcDt->nType;
		//pNpc->nID = pNpcDt->nID;
		pNpc->initWithData(pNpcDt);
		//��Ҫ���Ǵ洢
		m_vecNpc.push_back(pNpc);
	}
}

CNpc* CNpcMgr::getNpc(int nRow, int nCol, int nMapID)
{
	//��������Npc���ȶ�
	for (CNpc* pNpc : m_vecNpc)
	{
		//if (nRow == pNpc->getPos().x && nCol == pNpc->getPos().y && nMapID == pNpc->getMapID())//�ѱȽ�д��Npc����
		//{
		//	return pNpc;
		//}
		if (pNpc->isEquals(nRow, nCol, nMapID))
		{
			return pNpc;
		}
	}
	return nullptr;
}

vector<CVec2> CNpcMgr::getNpcPos(int nMapId)
{
	vector<CVec2> vecPos;
	for (int i = 0; i < m_vecNpc.size(); i++)
	{
		if (nMapId==m_vecNpc[i]->getMapID())
		{
			vecPos.push_back(m_vecNpc[i]->getPos());
		}
	}
	return vecPos;
}
