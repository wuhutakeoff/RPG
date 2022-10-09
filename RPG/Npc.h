#pragma once
#include "Vec2.h"
#include "DataStruct.h"
#include"Define.h"
class CNpc
{
public:
	CNpc();
	//��Ϊ���Զ���˽�У�������ⲿ����Щ����һ����setû���⣬���Ǵ����ر�࣬����д���ӿڣ�ͨ�����ݶ����Գ�ʼ�����ڱ������ֱ��ʹ��˽������
	void initWithData(CNpcDt* pNpcDt);
	bool isEquals(int nRow, int nCol, int nMapID);
	void onRender();
	SYN_THE_SIZE(int, m_nID, ID);//�����˱������壬����get��set�ӿڡ�
	SYN_THE_SIZE(string, m_strName, Name);
	SYN_THE_SIZE(CVec2, m_vPos, Pos);
	SYN_THE_SIZE(int, m_nMapID, MapID);
	SYN_THE_SIZE(int, m_nType, Type);
	SYN_THE_SIZE(string, m_strPic, Pic);

	/*CVec2 getPos()
	{
		return m_vPos;
	}
	int getMapID()
	{
		return m_nMapID;
	}
	string getPic()
	{
		return m_strPic;
	}

	int getType()
	{
		return m_nType;
	}


	
public:
	string getName()
	{
		return m_strName;
	}
	void setName(string strName)
	{
		m_strName = strName;
	}
private:
	string m_strName;

private:
	
	
	CVec2 m_vPos;
	int m_nMapID;
	string m_strPic;
	int m_nType;*/
};

