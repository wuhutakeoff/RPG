#include "Dialogue.h"
#include "GameMgr.h"
#include "GameMap.h"
#include "DataMgr.h"

CDialogue::CDialogue()
{
	m_nCurIndex = 0;
	m_bShowDialogue = false;
	m_bShowTask = false;
	m_nTaskIndex = 0;
}

void CDialogue::onUpdate()
{
	m_vecTaskDt = CDataMgr::getInstance()->getMgr<CTaskDtMgr>("TaskDtMgr")->getDatasByNpcID(m_pNpc->getID());

	if (KEY_DOWN(VK_UP))
	{
		if (m_bShowTask&&m_bInSelect)
		{
			m_nTaskIndex--;
			m_nTaskIndex = m_nTaskIndex < 0 ? m_vecTaskDt.size() - 1 : m_nTaskIndex;
		}
		else
		{
			m_nCurIndex--;

			if (m_nCurIndex < E_MENU_START)
			{
				m_nCurIndex = E_MENU_EXIT;
			}
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		if (m_bShowTask && m_bInSelect)
		{
			m_nTaskIndex++;
			m_nTaskIndex = m_nTaskIndex >= m_vecTaskDt.size() ? 0 : m_nTaskIndex;
		}
		else
		{
			m_nCurIndex++;

			if (m_nCurIndex > E_MENU_EXIT)
			{
				m_nCurIndex = 0;
			}
		}
	}
	else if (KEY_DOWN(VK_RETURN))
	{
		if (m_bShowTask)
		{
			m_nNum++;
		}
		if (m_nCount == 0 && m_bShowDialogue)
		{
			m_bSubmit = true;
		}

		if (m_nCurIndex == 0)
		{
			m_bShowDialogue = true;
		}
		else if (m_nCurIndex==1)
		{
			m_bShowTask = true;
			m_bInSelect = true;
		}
		else if (m_nCurIndex==2)
		{
			CGameMgr::getInstance()->restoreWnd();
			g_bClear = true;
		}

		if (m_bShowTask && m_nNum >=1)
		{
			m_bShowSelect = true;
			m_bInSelect = false;
		}
		if (m_nState==1)
		{
			m_bShowSelect = false;
			m_bInSelect = true;
			//�h���΄�
			CTask* pTask = new CTask();
			pTask->initData(m_vecTaskDt[m_nTaskIndex]);
			CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getTaskMgr()->deletTask(pTask);
			m_nNum = 1;
			m_nState = 0;
		}
		else if (m_nState==0&&m_nNum>=2)
		{
			//��������
			CTask* pTask = new CTask();
			pTask->initData(m_vecTaskDt[m_nTaskIndex]);
			CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getTaskMgr()->addTask(pTask);
			m_bShowSelect = false;
			m_bInSelect = true;
			m_nNum = 0;
			m_nState = 0;
		}

		g_bClear = true;

	}
	else if (KEY_DOWN(VK_LEFT))
	{
		if (m_bShowSelect)
		{
			m_nState--;
			m_nState = m_nState <0 ? 1 : m_nState;
		}
	}
	else if (KEY_DOWN(VK_RIGHT))
	{
		if (m_bShowSelect)
		{
			m_nState++;
			m_nState = m_nState >= 2 ? 0 : m_nState;
		}
	}
	else if (KEY_DOWN(VK_SPACE))
	{
		if (m_bShowDialogue)
		{
			m_nCount++;
		}
	}
	else if (KEY_DOWN(VK_ESCAPE))
	{
		m_bShowDialogue = false;
		m_nCount = 0;
		if (m_bShowTask)
		{
			m_bShowTask = false;
			m_bShowSelect = false;
			m_nNum = 0;
		}
	}


}

void CDialogue::onRender()
{

	if (m_bShowDialogue)
	{
		showDialogue();
	}
	else if (m_bShowTask)
	{
		g_bClear = true;
		showTask();
	}
	else
	{
		g_bClear = true;
		showMenu();
	}
}

void CDialogue::showMenu()
{
	if (m_nCurIndex==0)
	{
		cout << "---------------------------------" << endl;
		cout << "->�Ի�						 " << endl;
		cout << "  ����						 " << endl;
		cout << "  �˳�						 " << endl;
		cout << "---------------------------------" << endl;
	}
	else if (m_nCurIndex==1)
	{
		cout << "---------------------------------" << endl;
		cout << "  �Ի�						 " << endl;
		cout << "->����						 " << endl;
		cout << "  �˳�						 " << endl;
		cout << "---------------------------------" << endl;
	}
	else if (m_nCurIndex==2)
	{
		cout << "---------------------------------" << endl;
		cout << "  �Ի�						 " << endl;
		cout << "  ����						 " << endl;
		cout << "->�˳�						 " << endl;
		cout << "---------------------------------" << endl;
	}
}

void CDialogue::showDialogue()
{
	string strNpcName = m_pNpc->getName();
	CTask* pCurTask = CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getTaskMgr()->getFinishTask();

	if (pCurTask)
	{
		cout << "��ã���Ҫ�ύ������"<<endl;
		if (m_nCount==0)
		{
			cout << "  ->��    ��";
			//ɾ������
			if (m_bSubmit)
			{
				CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->taskAwad(pCurTask->getAwadMoney(), pCurTask->getAwadExp());
				CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getTaskMgr()->deletTask(pCurTask);
				m_bShowDialogue = false;
			}
		}
		else
		{
			cout << "    ��  ->��";
		}
	}
	else
	{
		if (m_nCount == 0)
		{
			cout << strNpcName << "�����,��ʲô����" << endl;
		}
		else if (m_nCount == 1)
		{
			cout << strNpcName << "�����,��ʲô����" << endl;
			cout << "�㣺û��" << endl;
		}
		else if (m_nCount >= 2)
		{
			cout << strNpcName << "�����,��ʲô����" << endl;
			cout << "�㣺û��" << endl;
			cout << strNpcName << ":û�¾ͳ�����÷" << endl;
		}
	}

}

void CDialogue::showTask()
{
	cout << "��������"<<endl;
	cout << "  ��������" << "\t\t\t" << "����Ŀ��" << endl;
	for (int i = 0; i < m_vecTaskDt.size(); i++)
	{
		if (i == m_nTaskIndex)
		{
			cout << "->";
		}
		else
		{
			cout << "  ";
		}
		cout << i + 1 << "." << m_vecTaskDt[i]->strName<<"\t\t";
		cout << m_vecTaskDt[i]->strDescription;

		if (m_bShowSelect&&i == m_nTaskIndex)
		{
			if (m_nState==0)
			{
				cout << "  ->" << "����"  << "    �ܾ�";
			}
			else
			{
				cout << "    ����" <<"  ->" << "�ܾ�";
			}
		}
		cout << endl;
	}
}



