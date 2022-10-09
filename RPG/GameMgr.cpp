#include "GameMgr.h"
#include "Define.h"

CGameMgr* CGameMgr::m_spInstance = nullptr;
CGameMgr::CGameMgr()
{
	m_pCurWnd = nullptr;
}

void CGameMgr::onUpdate()
{
	m_pCurWnd->onUpdate();
}

void CGameMgr::onRender()
{
	if (g_bClear)
	{
		system("cls");
		g_bClear = false;
	}

	m_pCurWnd->onRender();

}

void CGameMgr::runWithWnd(CWndBase* pWnd)
{
	m_pCurWnd = pWnd;
}

void CGameMgr::changeWnd(CWndBase* pWnd)
{
	//�л�ǰ��m_pCurWndǰ��Ĵ��ڡ�
	/*if (m_pCurWnd)
	{*/
	m_vecPreWnds.push_back(m_pCurWnd);
	//}
	//�л����ڡ�
	m_pCurWnd = pWnd;
}

void CGameMgr::restoreWnd()
{
	if (m_vecPreWnds.size() <= 0)
	{
		return;
	}
	//Ҫ�ͷŵ���ǰ�ڴ档
	if (m_pCurWnd->getDelete())
	{
		SAFE_DEL(m_pCurWnd);//���̵��˻ص���ͼ�� �̵�Ҫ�ͷŵ���  m_pCurWnd�̵ꡣ
	}
	//�õ����������һ��Ԫ�ظ�ֵ����ǰ����ָ�롣
	m_pCurWnd = m_vecPreWnds.back();
	//���һ��Ԫ��Ҫ��ǰ�ô�������ȥ��
	m_vecPreWnds.pop_back();
}

CGameMgr* CGameMgr::getInstance()
{
	if (!m_spInstance)
	{
		m_spInstance = new CGameMgr();
	}
	return m_spInstance;
}

void CGameMgr::mainLoop()
{
	//HANDLE HOUT = GetStdHandle(STD_OUTPUT_HANDLE);    //��ÿ���̨���
	//COORD NewSize = GetLargestConsoleWindowSize(HOUT);//��ÿ���̨������꣬�������ַ���Ϊ��λ
	//NewSize.X -= 1;
	//NewSize.Y -= 1;    //���Բ��ӣ�����ʱ��ʾ������
	//SetConsoleScreenBufferSize(HOUT, NewSize); //���ÿ���̨��������С

	//SMALL_RECT DisplayArea = { 0,0,0,0 };
	//DisplayArea.Right = NewSize.X;
	//DisplayArea.Bottom = NewSize.Y;
	//SetConsoleWindowInfo(HOUT, TRUE, &DisplayArea);
	/*HWND Hwnd = GetForegroundWindow();
	ShowWindow(Hwnd, SW_MAXIMIZE);*/

	SetConsoleTitleA("RPG");
	Sleep(100);
	CONSOLE_CURSOR_INFO cursor; //����ṹ�� ����̨�����Ϣ
	cursor.bVisible = 0; //���ò���ʾ
	cursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor); //���ù����Ϣ
	COORD coord = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	this->onUpdate();
	this->onRender();
}
