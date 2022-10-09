#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//���ݻ���
class CDataBase
{
public:
	int nID;
};


//���ݲ�������
class CDataBaseMgr
{
public:
	CDataBaseMgr();
	~CDataBaseMgr();
	virtual void loadFile(string strPath);
	virtual void parse(fstream& fromFile) = 0;
	template <class T>
	T* getDataByID(int nID)
	{
		for (CDataBase* pData : m_vecDatas)
		{
			if (nID == pData->nID)
			{
				return static_cast<T*>(pData);
			}
		}
		return nullptr;
	}
	//��ȡ����
	int getSize()
	{
		return m_vecDatas.size();
	}
	//��ȡ���е�����
	template <class T>
	vector<T*> getDatas()
	{
		vector<T*> vecDatas;
		for (CDataBase* pData : m_vecDatas)
		{
			vecDatas.push_back(static_cast<T*>(pData));
		}
		return vecDatas;
	}
protected:
	vector<CDataBase*> m_vecDatas;
};

