#pragma once
#include "Define.h"
class CWndBase
{
public:
	CWndBase();
	~CWndBase();
	//�麯����
	//�ṩ�ӿڣ�����������д��ʵ�ֶ�̬��
	virtual void onUpdate() = 0;
	virtual void onRender() = 0;
	SYN_THE_SIZE(string, m_strName, Name);
	SYN_THE_SIZE(bool, m_bDelete, Delete);
};

