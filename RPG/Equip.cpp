#include "Equip.h"
#include"DataMgr.h"
#include "GameMgr.h"
#include "GameMap.h"
CEquip::CEquip()
{
	this->init();
}

CEquip::~CEquip()
{
}

void CEquip::init()
{
	m_nCount = 0;
	bInBag = false;
	m_mapShowInfo = CDataMgr::getInstance()->getMgr<CItemDtMgr>("ItemDtMgr")->getEquipInfo();
	//���������������װ���ÿա�
	for (auto iter: m_mapShowInfo)
	{
		m_mapEquip[iter.first] = nullptr;
	}
}


//��װ���ӿڡ�
//���ػ�������װ����
CItem* CEquip::addEquip(string strName, CItem* pItem)
{
	int nCount = m_mapEquip.count(strName);
	if (nCount <= 0)
	{
		return nullptr;
	}
	//����������͵�װ������ȡ���ǿ�ָ�롣û��װ����
	if (!m_mapEquip[strName])
	{
		m_mapEquip[strName] = pItem;
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->addAttribute(pItem);
		//��װ����
		return nullptr;
	}
	
	//�Ѿ���һ���������͵�װ����
	CItem* pTempItem = m_mapEquip[strName];
	m_mapEquip[strName] = pItem;
	return pTempItem;

}

void CEquip::showEquip()
{
	for (auto iter : m_mapShowInfo)
	{
		if (!bInBag)
		{
			cout << "							";
		}
		cout << iter.second << ":";
		string strName = m_mapEquip[iter.first] ? m_mapEquip[iter.first]->getName() : "��";
		cout << strName << endl;
	}
	cout << endl;

}
