#pragma once
#include "Monster.h"
class CMonsterMgr
{
public:
	CMonsterMgr();
	~CMonsterMgr();
	void createMonster();
	//ͨ�����к͵�ͼID��ȡĳ������
	CMonster* getMonster(int nRow, int nCol, int nMapID);
	vector<CMonster*> getMonsters()
	{
		return m_vecMonster;
	}
	void addDeathMonster(CMonster* pMonster);
	//ˢ�¹��
	void refreshMonster();
	void onUpdate();
	vector<CVec2> getMonsterPosByMapId(int nMapId);

	vector<CMonster*> m_vecDeathMonster;
	int m_nTime;
	//SYN_THE_SIZE(int, m_nDeathMonsterNum, DeathMonsterNum);
private:
	vector<CMonster*> m_vecMonster;
	//������ֻ�������һ��map�� û��Ҫ����ɹ���ĳ�Ա����������ֻ�֣����ٸ��� ֻҪ��һ���͹��� �����嵽��������ߡ�
	map<int, CVec2> m_mapDir;

};

