#include "MonsterMgr.h"
#include "DataMgr.h"
#include "GameMgr.h"
#include "GameMap.h"
CMonsterMgr::CMonsterMgr()
{
	this->createMonster();
	m_mapDir[E_DIR_NONE] = CVec2(0, 0);
	m_mapDir[E_DIR_UP] = CVec2(-1, 0);
	m_mapDir[E_DIR_DOWN] = CVec2(1, 0);
	m_mapDir[E_DIR_LEFT] = CVec2(0, -1);
	m_mapDir[E_DIR_RIGHT] = CVec2(0, 1);
}

CMonsterMgr::~CMonsterMgr()
{
}

void CMonsterMgr::createMonster()
{
	//��������
	int nSize = CDataMgr::getInstance()->getMgr<CMonsterDtMgr>("MonsterDtMgr")->getSize();
	//ѭ����������
	for (int i = 0; i < nSize; i++)
	{
		//�õ�Ҫ������������������
		CMonsterDt* pMonsterDt = CDataMgr::getInstance()->getMgr<CMonsterDtMgr>("MonsterDtMgr")->getDataByID<CMonsterDt>(4001 + i);
		for (int j = 0; j < pMonsterDt->nCount; j++)
		{
			CMonster* pMonster = new CMonster();//�������
			//���ֹ������ڵĵ�ͼ�ĵ�ͼID
			CMapDt* pMapDt = CDataMgr::getInstance()->getMgr<CMapDtMgr>("MapDtMgr")->getDataByID<CMapDt>(pMonsterDt->nMapID);
			//�������
			// 1~nRowSize-2   1+ 0~nRowsize-3  rand()%(nRowSize-2)
			int nRandomRow = 1 + rand() % (pMapDt->nRowSize - 2);
			int nRandomCol = 1 + rand() % (pMapDt->nColSize - 2);
			pMonster->setPosition(CVec2(nRandomRow, nRandomCol));
			//ʹ�ù������ݶ���ֻ����������ݴ����ʼ��
			pMonster->initWithData(pMonsterDt);
			m_vecMonster.push_back(pMonster);
		}
	}
}

CMonster* CMonsterMgr::getMonster(int nRow, int nCol, int nMapID)
{
	for (CMonster* pMonster : m_vecMonster)
	{
		if (pMonster->isEquals(nRow, nCol, nMapID))
		{
			return pMonster;
		}
	}
	return nullptr;
}


void CMonsterMgr::addDeathMonster(CMonster* pMonster)
{
	pMonster->onRecovery();
	m_vecDeathMonster.push_back(pMonster);
}

void CMonsterMgr::refreshMonster()
{
	m_vecMonster.insert(m_vecMonster.end(), m_vecDeathMonster.begin(), m_vecDeathMonster.end());
	m_vecDeathMonster.clear();
}

void CMonsterMgr::onUpdate()
{
	for (CMonster* pMonster : m_vecMonster)
	{
		pMonster->onMove(m_mapDir);
	}

	//���������ǽ��
	//��ȡ��ǰ��ͼ����
	CMapDt* pCurMapDt = CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getCurMapDt();
	for (CMonster* pMonster : m_vecMonster)
	{
		int nRow = pMonster->getPosition().x;
		int nCol = pMonster->getPosition().y;
		if (1 == pCurMapDt->pArrMap[nRow][nCol])
		{
			pMonster->onRestore();
			pMonster->changeDir();
		}
	}

	for (int i = 0; i < m_vecMonster.size(); i++)
	{

		if (m_vecMonster[i]->getHp() <= 0|| m_vecMonster[i]->getCatch())
		{
			//�ѵ�iֻ����洢����������	
			this->addDeathMonster(m_vecMonster[i]);
			
			//if (CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getTaskMgr()->getTaskByMonsterId(m_vecMonster[i]->getID()))
			//{
			//	m_nDeathMonsterNum++;
			//}

			if (m_vecMonster[i]->getCatch())
			{
				m_vecMonster[i]->setCatch(false);
			}
			/*else
			{
				CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->addExp(m_vecMonster[i]->getExp());
			}*/
			m_vecMonster.erase(m_vecMonster.begin() + i);
			m_nTime = 0;
			return;
		}
	}

	m_nTime++;
	//ˢ��ʱ�䵽���������������й��
	if (m_vecDeathMonster.size() > 0 && m_nTime >= 30)
	{
		m_nTime = 0;
		this->refreshMonster();
	}
}

vector<CVec2> CMonsterMgr::getMonsterPosByMapId(int nMapId)
{
	vector<CVec2> vecPos;
	for (int i=0;i<m_vecMonster.size();i++)
	{
		if (m_vecMonster[i]->getMapID()==nMapId)
		{
			vecPos.push_back(m_vecMonster[i]->getPosition());
		}
	}
	return vecPos;
}

