#pragma once
#include "Vec2.h"
#include "Bag.h"
#include "Define.h"
#include "Equip.h"
#include "RoleBase.h"
#include "Skill.h"
#include "PetBag.h"
#include "Monster.h"
#include <list>
#include "AStar.h"
class CPlayer : public CRoleBase
{
public:
	CPlayer();
	void onUpdate();
	//����ӿڣ�����ֵΪ����ֵ�����Ǯ�����򣬷����棬�������ؼ١�
	int buyItem(CItemDt* pItemDt);
	void addMoney(int nMoney);
	//�ж�ĳ�������Ƿ�����ҵ���Ұ��Χ�ڡ� ������Ұ��Χ������
	bool isOutOfView(int nRow, int nCol);
	void initData(CRoleDt* pRoleDt);
	void useConsumble(CItem* pItem);
	void addExp(int nExp);
	void taskAwad(int nTaskMoney, int nTaskExp);
	void onLevelUp();
	void autoMove(CVec2 point);
	void addAttribute(CItem* pItem);
	void setIt()
	{
		this->it = path.begin();
	}
	void setPath(list<Point*> path)
	{
		this->path = path;
	}

	SYN_THE_SIZE_READONLY(CBag*, m_pBag, Bag);
	SYN_THE_SIZE_READONLY(CPetBag*, m_pPetBag, PetBag);
	SYN_THE_SIZE_READONLY(vector<CSkill*>, m_vecSkills, Skills);
	SYN_THE_SIZE_READONLY(CEquip*, m_pEquip, Equip);
	SYN_THE_SIZE(int, m_nRange, Range);
	SYN_THE_SIZE(string,m_strProfession , Profession);
	SYN_THE_SIZE(int, m_nExp, Exp);
	SYN_THE_SIZE(CPet*, m_pCurPet, CurPet);

private:
	list<Point*> path;
	list<Point*>::iterator it;
};

