#include "GameMenu.h"
#include "Define.h"
#include "GameMgr.h"
#include "GameMap.h"
#include "RoleSelect.h"
CGameMenu::CGameMenu()
{
	m_nMenuState = E_MENU_START;
}

void CGameMenu::onUpdate()
{
	if (KEY_DOWN(VK_UP))
	{
		m_nMenuState--;
		if (m_nMenuState < E_MENU_START)
		{
			m_nMenuState = E_MENU_EXIT;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nMenuState++;
		if (m_nMenuState > E_MENU_EXIT)
		{
			m_nMenuState = 0;
		}
	}
	if (KEY_DOWN(VK_RETURN))
	{
		if (E_MENU_START == m_nMenuState)
		{
			//g_pGameMgr->m_nGameState = E_GAME_MAP;
			CRoleSelect* pRoleSelect = new CRoleSelect();
			pRoleSelect->setName("RoleSelect");
			CGameMgr::getInstance()->changeWnd(pRoleSelect);
			//����
			g_bClear = true;
		}
	}
}

void CGameMenu::onRender()
{
	if (E_MENU_START == m_nMenuState)
	{
		cout << "->��Ϸ��ʼ" << endl;
		cout << "  ��Ϸ����" << endl;
		cout << "  ��Ϸ����" << endl;
	}
	else if (E_MENU_SET == m_nMenuState)
	{
		cout << "  ��Ϸ��ʼ" << endl;
		cout << "->��Ϸ����" << endl;
		cout << "  ��Ϸ����" << endl;
	}
	else if (E_MENU_EXIT == m_nMenuState)
	{
		cout << "  ��Ϸ��ʼ" << endl;
		cout << "  ��Ϸ����" << endl;
		cout << "->��Ϸ����" << endl;
	}
}
