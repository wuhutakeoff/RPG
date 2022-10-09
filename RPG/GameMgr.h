#pragma once
#include "WndBase.h"
#include <vector>
using namespace std;
class CGameMgr
{
public:
	static CGameMgr* getInstance();
	void mainLoop();
	void onUpdate();
	void onRender();
	void runWithWnd(CWndBase* pWnd);
	//�ṩһ���ӿ����ڸı䵱ǰ����ָ��ָ�� ָ��˵��ڴ棬�˵����� ָ���ͼ����ͼ����
	void changeWnd(CWndBase* pWnd);
	//�ص���һ������
	void restoreWnd();


	template <class T>
	T* getWndByName(string strName)
	{
		if (strName.empty())
		{
			return nullptr;
		}
		if (m_pCurWnd && m_pCurWnd->getName() == strName)
		{
			return static_cast<T*>(m_pCurWnd);
		}
		for (CWndBase* pWnd : m_vecPreWnds)
		{
			if (strName == pWnd->getName())
			{
				return static_cast<T*>(pWnd);
			}
		}
		return nullptr;
	}
private:
	CGameMgr();
	static CGameMgr* m_spInstance;

	//��������ָ�룬ֻ����һ��ָ�롣 ���ڻ���ָ�롣
	CWndBase* m_pCurWnd;

	//���������ڴ洢�л����Ĵ��ڡ� ��ʱ�洢���л���ʱ��洢������changWnd�л���
	vector<CWndBase*> m_vecPreWnds;
};

