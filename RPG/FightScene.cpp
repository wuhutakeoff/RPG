#include "FightScene.h"
#include "Define.h"
#include "DataMgr.h"
#include "GameMgr.h"
#include "GameMap.h"
#include <ctime>
#include <random>
CFightScene::CFightScene()
{
	m_pPlayer = nullptr;
	m_pMonster = nullptr;
	m_pCurMapDt = CDataMgr::getInstance()->getMgr<CMapDtMgr>("MapDtMgr")->getDataByID<CMapDt>(1004); 
	m_bPlayerRound = true;
	m_strState = "idle";
	m_nCurIndex = 0;
	m_nCurSkillIndex = 0;
	m_bInSkill = false;
	m_bShowConsumble = false;
	m_bInComsuble = false;
	m_bUseSkill = false;
	m_nCount = 0;
	m_vecItems = CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getBag()->getItemByType("consumables");
	//CItem* item = new CItem("��", 0, 0, 0, 0, 0);
	//m_vecItems.insert(m_vecItems.begin(), item);
}

CFightScene::~CFightScene()
{
}

void CFightScene::onUpdate()
{
	if (m_pPlayer->getCurPet())
	{
		//CPet* pCurPet=m_pPlayer->getCurPet();
		m_pPlayer->getCurPet()->setReverse(false);

	}
	for (int i = 1; i < m_vecItems.size(); i++)
	{
		if (m_vecItems[i]->getCount() == 0)
		{
			m_vecItems.erase(m_vecItems.begin() + i);
		}
	}

	if (m_bPlayerRound)
	{
		if (KEY_DOWN(VK_UP))
		{
			if (m_bInSkill)
			{
				m_nCurSkillIndex--;
				if (m_nCurSkillIndex < 0)
				{
					m_nCurSkillIndex = m_vecSkills.size() ;
				}
			}
			else if (m_bInComsuble)
			{
				m_nCurConsumbleIndex--;
				if (m_nCurConsumbleIndex < 0)
				{
					m_nCurConsumbleIndex = m_vecItems.size() - 1;
				}
			}
			else
			{
				m_nCurIndex--;
				if (m_nCurIndex < 0)
				{
					m_nCurIndex = 4;
				}
			}
			g_bClear = true;
		}
		else if (KEY_DOWN(VK_DOWN))
		{
			if (m_bInSkill)
			{
				m_nCurSkillIndex++;
				if (m_nCurSkillIndex > m_vecSkills.size())
				{
					m_nCurSkillIndex = 0;
				}
			}
			else if (m_bInComsuble)
			{
				m_nCurConsumbleIndex++;
				if (m_nCurConsumbleIndex > m_vecItems.size())
				{
					m_nCurConsumbleIndex = 0;
				}
			}
			else
			{
				m_nCurIndex++;
				if (m_nCurIndex >= 5)
				{
					m_nCurIndex = 0;
				}
			}
			g_bClear = true;
		}
		else if (KEY_DOWN(VK_RETURN))
		{
			m_nCount++;
			if (m_nCurIndex == 0)
			{
				if (m_strState !="back")
				{
					m_strState = "attack";
				}
			}
			else if (m_nCurIndex == 1)
			{
				m_bDefense = true;
				m_bPlayerRound = false;
				m_strState = "attack";
			}
			else if (m_nCurIndex == 2)
			{
				m_bShowSkill = true;
				m_bInSkill = true;
			}
			else if (m_nCurIndex == 3)
			{
				m_bShowConsumble = true;
				m_bInComsuble = true;
			}
			else if (m_nCurIndex==4)
			{
				m_strState = "flee";
			}

			if (m_nCurSkillIndex == m_vecSkills.size())
			{
				m_bInSkill = false;
				m_bShowSkill = false;
				g_bClear = true;
				m_nCurSkillIndex = 0;
				m_nCount = 0;
			}

			//�ͷż���
			if (m_bInSkill&&m_nCurIndex==2&&m_nCount>=2)
			{
				m_bUseSkill = true;
				m_bPlayerRound = false;
				m_bInSkill = false;
				
			}

			if (m_vecItems.size()!=0&&m_nCurConsumbleIndex== m_vecItems.size())
			{
				m_bShowConsumble = false;
				m_bInComsuble = false;
				g_bClear = true;
				m_nCurConsumbleIndex = 0;
			}
			else if (m_vecItems.size()==0&&m_nCurConsumbleIndex==0&&m_nCount>=2)
			{
				m_bShowConsumble = false;
				m_bInComsuble = false;
				g_bClear = true;
				m_nCurConsumbleIndex = 0;
				m_nCount = 0;
			}
			if (m_vecItems.size() != 0 && m_bInComsuble&& m_nCurIndex == 3)
			{
				if ( m_vecItems[m_nCurConsumbleIndex]->getID() == 3010)
				{
					m_vecItems[m_nCurConsumbleIndex]->setFightPos(10,8);
					m_bUseBall = true;
					m_bInComsuble = false;
					/*m_pMonster->setCatch(true);
					CPet* pPet = new CPet(m_pMonster);
					CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getPetBag()->addPet(pPet);
					system("cls");
					cout << "��ϲ���ó��" << pPet->getName();
					Sleep(1500);
					CGameMgr::getInstance()->restoreWnd();
					g_bClear = true;*/
				}
				else {
					useConsumble(m_vecItems[m_nCurConsumbleIndex]);
				}
			}
		}
	}

	if ( m_bUseBall && m_vecItems[m_nCurConsumbleIndex]->getFightPos().y<22)
	{
		m_vecItems[m_nCurConsumbleIndex]->onFightMove(1);
	}
	else if (m_bUseBall && m_vecItems[m_nCurConsumbleIndex]->getFightPos().y >=22)
	{

		m_bUseBall = false;
		m_bInComsuble = false;
		m_pMonster->setCatch(true);
		CPet* pPet = new CPet(m_pMonster);
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getPetBag()->addPet(pPet);
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->useConsumble(m_vecItems[m_nCurConsumbleIndex]);
		system("cls");
		cout << "��ϲ���ó��" << pPet->getName();
		Sleep(1500);
		CGameMgr::getInstance()->restoreWnd();
		g_bClear = true;
	}

	if (m_bPlayerRound)
	{
		if (KEY_DOWN(VK_SPACE)&&"back"!=m_strState)
		{
			m_strState = "attack";	
		}
	}

	if ("attack" == m_strState)
	{
		//����״̬����һغϻ��ǹ���غ�
		if (m_bPlayerRound)
		{
			m_pPlayer->changeState(E_FIGHT_ATTACK);
			m_pPlayer->onFightMove(2);
			//���ͼƬ������ͼƬ�غϡ�
			if (22 <= m_pPlayer->getCenterPos().y)
			{
				//�����������ص�ԭ�㡣  �����Ѫ��
				//״̬�ĳ�back
				m_pPlayer->changeState(E_FIGHT_BACK);///���ĺ���ͼƬ��
				m_strState = "back";
				
				//�����˺�ֵ
				int nDamage = m_pPlayer->getAck() - m_pMonster->getDef();
				nDamage = nDamage <= 0 ? 1 : nDamage;
				if (m_pMonster->onDamage(nDamage))
				{
					system("cls");
					//�Ӿ���
					m_pPlayer->addExp(m_pMonster->getExp());
					if (m_pPlayer->getCurPet() && m_pPlayer->getCurPet()->getIsFight())
					{
						m_pPlayer->getCurPet()->addExp(m_pMonster->getExp());
					}
					//����
					CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getTaskMgr()->addFinishCount(m_pMonster);
					
					CItemDt* pItemDt=CDataMgr::getInstance()->getMgr<CItemDtMgr>("ItemDtMgr")->getDataByID<CItemDt>(m_pMonster->getItemID());
					m_pPlayer->getBag()->addItem(pItemDt);
					cout << "��ϲ������Ʒ��" << pItemDt->strName << "һ��";
					Sleep(1500);
					//�л���ȥ��ͼ��
					CGameMgr::getInstance()->restoreWnd();
					g_bClear = true;
				}

			}
			return;
		}

		
		else if (m_pPlayer->getCurPet()&& m_pPlayer->getCurPet() ->getIsFight() && m_bPetRound)
		{
			m_pPlayer->getCurPet()->changeState(E_FIGHT_ATTACK);
			m_pPlayer->getCurPet()->onFightMove(2);
			int n=m_pPlayer->getCurPet()->getCenterPos().y;
			if (22 <= m_pPlayer->getCurPet()->getCenterPos().y)
			{
				m_pPlayer->getCurPet()->changeState(E_FIGHT_BACK);///���ĺ���ͼƬ��
				m_strState = "back";
				int nDamage = m_pPlayer->getCurPet()->getAck() - m_pMonster->getDef();
				nDamage = nDamage <= 0 ? 1 : nDamage;
				if (m_pMonster->onDamage(nDamage))
				{
					system("cls");
					//�Ӿ���
					m_pPlayer->addExp(m_pMonster->getExp());
					if (m_pPlayer->getCurPet()&&m_pPlayer->getCurPet()->getIsFight())
					{
						m_pPlayer->getCurPet()->addExp(m_pMonster->getExp());
					}
					CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getTaskMgr()->addFinishCount(m_pMonster);
					//���ս��Ʒ
					CItemDt* pItemDt = CDataMgr::getInstance()->getMgr<CItemDtMgr>("ItemDtMgr")->getDataByID<CItemDt>(m_pMonster->getItemID());
					cout << "��ϲ������Ʒ��" << pItemDt->strName << "һ��";
					m_pPlayer->getBag()->addItem(pItemDt);
					Sleep(1500);
					//�л���ȥ��ͼ��
					CGameMgr::getInstance()->restoreWnd();
					g_bClear = true;
				}
			}
			return;
		}
		///����״̬����غϴ���
		m_pMonster->changeState(E_FIGHT_ATTACK);
		m_pMonster->onFightMove(-1);
		if (7 == m_pMonster->getCenterPos().y)
		{
			//�������ҡ�
			//��ҿ�Ѫ������״̬���ģ�����״̬�ĳɺ��ˡ�
			m_pMonster->changeState(E_FIGHT_BACK);
			m_strState = "back";

			//�����˺�ֵ
			int nDamage = m_pMonster->getAck() - m_pPlayer->getDef();
			nDamage = nDamage <= 0 ? 1 : nDamage;
			if (m_bDefense)
			{
				nDamage = 0;
			}
			if (m_pPlayer->onDamage(nDamage))
			{
				//�л���ȥ��ͼ��
				m_pPlayer->setHp(1);
				CGameMgr::getInstance()->restoreWnd();
				g_bClear = true;
				CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->changeMap(1001);
			}
			m_bDefense = false;
			if (m_bShowSkill)
			{
				m_bInSkill = true;
			}
		}
	}
	else if ("back" == m_strState)
	{
		//����״̬����һغ�
		if (m_bPlayerRound)
		{
			m_pPlayer->onFightMove(-1);
			//����һص�ԭ��  5
			if (5 == m_pPlayer->getCenterPos().y)
			{
				//��һص�ԭ�㣬״̬�ɿ��С�
				m_pPlayer->changeState(E_FIGHT_IDLE);

				//��һغϽ���
				m_bPlayerRound = false;
				//����غ�

				m_strState = "attack";
				//����ͼƬ�ĳɹ���
				//m_pMonster->changeState(E_FIGHT_ATTACK);
				if (m_pPlayer->getCurPet()&&m_pPlayer->getCurPet()->getIsFight())
				{
					m_pPlayer->getCurPet()->changeState(E_FIGHT_ATTACK);
					m_bPetRound = true;
				}
				else
				{
					m_pMonster->changeState(E_FIGHT_ATTACK);
				}
			}
			return;
		}

		else if (m_bPetRound)
		{
			m_pPlayer->getCurPet()->onFightMove(-1);
			if (5 == m_pPlayer->getCurPet()->getCenterPos().y)
			{
				m_pPlayer->getCurPet()->changeState(E_FIGHT_IDLE);
				m_bPlayerRound = false;
				m_bPetRound = false;
				m_strState = "attack";
				m_pMonster->changeState(E_FIGHT_ATTACK);
			}
			return;
		}
		//����غϵĺ���
		m_pMonster->onFightMove(1);
		//����ص��Լ�ԭ����λ�ã���������������غϽ���
		if (25 == m_pMonster->getCenterPos().y)
		{
			m_pMonster->changeState(E_FIGHT_IDLE);
			//����غϽ���  ��һغϿ�ʼ
			m_bPlayerRound = true;
			m_strState = "idle";
		}
	}
	else if ("flee" == m_strState) 
	{
		m_pPlayer->changeState(E_FIGHT_BACK);
		m_pPlayer->onFightMove(-1);
		if (m_pPlayer->getCurPet())
		{
			m_pPlayer->getCurPet()->changeState(E_FIGHT_BACK);
			m_pPlayer->getCurPet()->onFightMove(-1);
		}
		if (-1>= m_pPlayer->getCenterPos().y)
		{
			m_pPlayer->changeState(E_FIGHT_IDLE);
			CGameMgr::getInstance()->restoreWnd();
		}
		g_bClear = true;
	}

	m_nSkillIndex = m_nCurSkillIndex >= m_vecSkills.size() ? m_vecSkills.size() - 1 : m_nCurSkillIndex;
	
	if(m_nSkillIndex>=0)
	{
		if (m_vecSkills[m_nSkillIndex]->getPosition().y >= m_pMonster->getCenterPos().y)
		{
			m_bUseSkill = false;
			m_vecSkills[m_nSkillIndex]->setPosition(m_pPlayer->getCenterPos());
			m_bPlayerRound = false;
			m_strState = "attack";
		}
		else if (m_bUseSkill)
		{
			m_vecSkills[m_nSkillIndex]->onUpdate();
		}
	}


}

void CFightScene::onRender()
{
	this->showTarget();

	cout << m_pCurMapDt->strName << endl;
	for (int i = 0; i < m_pCurMapDt->nRowSize; i++)
	{
		for (int j = 0; j < m_pCurMapDt->nColSize; j++)
		{

			if (1 == m_pCurMapDt->pArrMap[i][j])
			{
				cout << "��";
			}
			else if (m_pPlayer->isContain(i, j))
			{
				m_pPlayer->onRender();
			}
			else if (m_pPlayer->getCurPet()&&m_pPlayer->getCurPet()->isContain(i,j)&& m_pPlayer->getCurPet()->getIsFight())
			{
				m_pPlayer->getCurPet()->onRender();
			}
			else if (m_pMonster->isContain(i, j))
			{
				m_pMonster->onRender();
			}
			else if ( m_bUseSkill&&m_vecSkills[m_nSkillIndex]->isEquals(i, j))
			{
				m_vecSkills[m_nSkillIndex]->onRender();
			}
			else if (m_bUseBall&& m_vecItems[m_nCurConsumbleIndex]->isEquals(i,j))
			{
				m_vecItems[m_nCurConsumbleIndex]->onRender();
			}
			else if (m_bDefense && j == 7 && (i > 6 && i < 14))
			{
				cout << "| ";
			}
			else
			{
				cout << "  ";
			}
			
		}
		cout << endl;
	}
	
	
	showSelectMenu();

	if (!m_bShowSkill&&!m_bShowConsumble)
	{
		cout << "								";
		cout << "								";
		cout << "								";
		cout << "								"; 
		cout << "								";
	}
	else if (m_bShowSkill)
	{
		showSkill();
	}
	else if (m_bShowConsumble)
	{
		showConsumble();
	}

	
}

void CFightScene::setTarget(CPlayer* pPlayer, CMonster* pMonster)
{
	m_pPlayer = pPlayer;
	m_pMonster = pMonster;
	//����λ�ã� 
	
	if (m_pPlayer->getCurPet()&&m_pPlayer->getCurPet()->getIsFight())
	{
		m_pPlayer->setFightPosition(7, 5);
		m_pPlayer->getCurPet()->setFightPosition(12, 5);
	}
	else {
		m_pPlayer->setFightPosition(10, 5);
	}
	m_pMonster->setFightPosition(10, 25);
	/*CVec2 pos = CVec2(10, 5);
	CVec2 pos1 = CVec2(10, 25);
	m_pPlayer->setPosition(pos);
	m_pMonster->setPosition(pos1);*/
	m_pMonster->setReverse(true);
	m_bPlayerRound = true;
	m_strState = "idle";
	m_vecSkills = m_pPlayer->getSkills();
	for (int i = 0; i < m_vecSkills.size(); i++)
	{
		m_vecSkills[i]->setPosition(m_pPlayer->getCenterPos());
	}	
}

void CFightScene::showTarget()
{
	cout << "���\t\t\t\t����" << endl;
	cout << "ְ  ҵ:" << m_pPlayer->getName() << "\t\t\t" << "����:" << m_pMonster->getName() << endl;
	cout << "Ѫ  ��:" << m_pPlayer->getHp() <<"/"<<m_pPlayer->getMaxHp()<<"  " << "\t\t\t" << "Ѫ  ��:" << m_pMonster->getHp() << "/" << m_pMonster->getMaxHp()<<"  " << endl;
	cout << "��  ��:" << m_pPlayer->getMp() << "\t\t\t" << "��  ��:" << m_pMonster->getMp() << endl;
	cout << "������:" << m_pPlayer->getAck() << "\t\t\t" << "������:" << m_pMonster->getAck() << endl;
	cout << "������:" << m_pPlayer->getDef() << "\t\t\t" << "������:" << m_pMonster->getDef() << endl;
}

void CFightScene::showSelectMenu()
{
	
	if (m_nCurIndex == 0)
	{
		cout << "---------------------------------" << endl;
		cout << "->	����					 " << endl;
		cout << "	����					 " << endl;
		cout << "	����					 " << endl;
		cout << "	����Ʒ 					 " << endl;
		cout << "	����					 " << endl;
		cout << "---------------------------------" << endl;
	}
	else if (m_nCurIndex == 1)
	{
		cout << "---------------------------------" << endl;
		cout << "	����					 " << endl;
		cout << "->	����					 " << endl;
		cout << "	����					 " << endl;
		cout << "	����Ʒ 					 " << endl;
		cout << "	����					 " << endl;
		cout << "---------------------------------" << endl;
	}
	else if (m_nCurIndex == 2)
	{
		cout << "---------------------------------" << endl;
		cout << "	����					 " << endl;
		cout << "	����					 " << endl;
		cout << "->	����					 " << endl;
		cout << "	����Ʒ 					 " << endl;
		cout << "	����					 " << endl;
		cout << "---------------------------------" << endl;
	}
	else if (m_nCurIndex == 3)
	{
		cout << "---------------------------------" << endl;
		cout << "	����					 " << endl;
		cout << "	����					 " << endl;
		cout << "	����					 " << endl;
		cout << "->	����Ʒ					 " << endl;
		cout << "	����					 " << endl;
		cout << "---------------------------------" << endl;
	}
	else if (m_nCurIndex==4)
	{
		cout << "---------------------------------" << endl;
		cout << "	����					 " << endl;
		cout << "	����					 " << endl;
		cout << "	����					 " << endl;
		cout << "	����Ʒ					 " << endl;
		cout << "->	����					 " << endl;
		cout << "---------------------------------" << endl;
	}
}

void CFightScene::showSkill()
{
	cout << " ---------------------------------" << endl;
	for (int i = 0; i < m_vecSkills.size(); i++)
	{
		cout << "|";
		if (m_nCurSkillIndex==i)
		{
			cout << "->";
		}
		else
		{
			cout << "  ";
		}
		cout<< m_vecSkills[i]->getName() << "\t";
		cout << m_vecSkills[i]->getDamage() << "\t";
		cout << m_vecSkills[i]->getDefense() << "\t";
		cout << m_vecSkills[i]->getMp() << "\t" << "|";
		cout << endl;
		
	}
	cout << "|";
	if (m_nCurSkillIndex== m_vecSkills.size())
	{
		cout << "->";
	}
	else
	{
		cout << "  ";
	}

	cout << "�˳�" << "				" << "|" << endl;
	cout << " ---------------------------------" << endl;
}

void CFightScene::showConsumble()
{
	cout << " --------------------------------------------------------" << endl;
	cout << "|  ����		HP	MP	ACK	DEF	COUNT	|" << endl;

	if (m_vecItems.size()<=0)
	{
		cout << "|  ��"<<endl;
	}
	else
	{
		for (int i = 0; i < m_vecItems.size(); i++)
		{
			cout << "|";
			if (m_nCurConsumbleIndex == i)
			{
				cout << "->";
			}
			else
			{
				cout << "  ";
			}
			cout << m_vecItems[i]->getName() << "\t";
			cout << m_vecItems[i]->getHp() << "\t";
			cout << m_vecItems[i]->getMp() << "\t";
			cout << m_vecItems[i]->getAck() << "\t";
			cout << m_vecItems[i]->getDef() << "\t";
			cout << m_vecItems[i]->getCount() << "\t" << "|";
			cout << endl;

		}
	}
	
	cout << "|";
	if (m_nCurConsumbleIndex == m_vecItems.size())
	{
		cout << "->";
	}
	else
	{
		cout << "  ";
	}

	cout << "�˳�" << "							"<<"|"<<endl;
	cout << " --------------------------------------------------------" << endl;
}

void CFightScene::setAllFalse()
{
	m_bShowSkill = false;
	m_bInSkill = false;
	m_bShowConsumble = false;
	m_bInComsuble = false;
	m_nCurIndex = 0;
	m_nCurConsumbleIndex = 0;
	m_nCurSkillIndex = 0;
}

void CFightScene::useConsumble(CItem* pItem)
{
	if (!pItem)
	{
		return;
	}
	for (CItem* item : m_vecItems)
	{
		if (item->getName() == pItem->getName() && item->getCount() > 0)
		{
			CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->useConsumble(pItem);

		}
	}
}







