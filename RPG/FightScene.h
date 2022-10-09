#pragma once
#include "DataStruct.h"
#include "Player.h"
#include "Monster.h"
#include "Define.h"
#include <string>
#include "WndBase.h"
class CFightScene:public CWndBase
{
public:
	CFightScene();
	~CFightScene();
	void onUpdate();
	void onRender();
	//����Ŀ��
	void setTarget(CPlayer* pPlayer, CMonster* pMonster);
	void showTarget();
	void showSelectMenu();
	void showSkill();
	void showConsumble();
	void setAllFalse();
	void useConsumble(CItem* pItem);

	SYN_THE_SIZE(int, m_nCurIndex, CurIndex);
private:
	CMapDt* m_pCurMapDt;
	//���ڴ���ս������������߼�����ʱ����������������Һ͹������ý���
	CPlayer* m_pPlayer;
	CMonster* m_pMonster;

	//����ֵ��ʾ��һغϣ�Ĭ���������
	bool m_bPlayerRound;
	bool m_bPetRound;

	bool m_bDefense;

	bool m_bShowSkill;
	bool m_bInSkill;

	//��ʾ
	bool m_bShowConsumble;
	bool m_bInComsuble;

	bool m_bIsFlee;
	bool m_bUseSkill;
	bool m_bUseBall;
	//��ǰ��һ��߹����״̬��
	string m_strState;

	int m_nCurSkillIndex;
	int m_nCurConsumbleIndex;
	int m_nSkillIndex;
	int m_nCount;

	vector<CItem*> m_vecItems;
	vector<CSkill*> m_vecSkills;
};


