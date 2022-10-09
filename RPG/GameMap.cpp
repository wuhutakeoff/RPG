#include "GameMap.h"
#include "Define.h"
#include "GameMgr.h"
#include "DataMgr.h"
#include "FightScene.h"
#include "Shop.h"
#include "Dialogue.h"
#include "AStar.h"
#include <graphics.h>
#include <conio.h>

POINT p;
HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
HWND h = GetForegroundWindow();
CONSOLE_FONT_INFO consoleCurrentFont;

CGameMap::CGameMap()
{
	//m_pCurMapDt = CDataMgr::getInstance()->getMapDtMgr()->getDataByID(1001);
	this->changeMap(1001);
	//new�����
	m_pPlayer = new CPlayer();
	//��ҳ�ʼλ�����á� ����������������ӿڡ�
	m_pPlayer->setPosition(m_pCurMapDt->nInitRow, m_pCurMapDt->nInitCol);
	m_pNpcMgr = new CNpcMgr();
	m_pMonsterMgr = new CMonsterMgr();
	m_pTaskMgr = new CTaskMgr();
	x = 0;
	y = 0;
}

void CGameMap::onUpdate()
{
	m_vecTask = m_pTaskMgr->getTasks();

	//������¼�
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);


	if (KEY_DOWN(VK_LBUTTON)) {  			//����������
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(h, &p);               //��ȡ����ڴ����ϵ�λ��
		GetCurrentConsoleFont(hOutput, FALSE, &consoleCurrentFont); //��ȡ������Ϣ
		x = p.x /= consoleCurrentFont.dwFontSize.X;
		y = p.y /= consoleCurrentFont.dwFontSize.Y;

		//A*�㷨�������·��
		Astar astar;
		int** arr = getCurMapDt()->pArrMap;
		int nRow = getCurMapDt()->nRowSize;
		int nCol = getCurMapDt()->nColSize;
		vector<CVec2> vec1=m_pNpcMgr->getNpcPos(getCurMapDt()->nID);
		vector<CVec2> vec2 = m_pMonsterMgr->getMonsterPosByMapId(getCurMapDt()->nID);
		vector<CVec2> vec3;
		vec3.insert(vec3.end(), vec1.begin(), vec1.end());
		vec3.insert(vec3.end(), vec2.begin(), vec2.end());
		astar.InitAstar(arr,nRow,nCol,vec3 );
		Point cur(m_pPlayer->getPosition().x, m_pPlayer->getPosition().y);
		Point dis(y - 8, (x - 56) / 2);
		list<Point*> path = astar.GetPath(cur, dis, false);
		m_pPlayer->setPath(path);
		m_pPlayer->setIt();
		cout << x << " " << y;
	}

	if (x>=122&&x<=125&&y==7)
	{
		recharge();
	}

	if ((x > 56 && y > 8)&&(x < 126 && y < 34))
	{
		int nRow = y - 8;
		int nCol = (x - 56) / 2;
		CVec2 point = CVec2(nRow,nCol);
		m_pPlayer->autoMove(point);
	}

	if (m_pPlayer->getCurPet() && m_pPlayer->getCurPet()->getIsFollow())
	{
		m_pPlayer->getCurPet()->setPosition(m_pPlayer->getPosition().xBk, m_pPlayer->getPosition().yBk);
		if (m_pPlayer->getCurPet()->isEquals(m_pPlayer->getPosition()))
		{
			m_pPlayer->getCurPet()->onRestore();
		}
	}

	string str;
	if (KEY_DOWN(VK_RETURN))
	{
		str = "";
		while (true) {
			if (_kbhit()) {//����а������£���_kbhit()����������
				char ch;
				ch = _getch();//ʹ��_getch()��ȡ���µļ�ֵ
				if ((ch >= 65 && ch <= 90)||(ch>=97&&ch<=122))
				{
					str += ch;
				}
				if (ch == 27||ch== 13) 
				{ 
					break;
				}//������ESCʱ�˳�ѭ����ESC���ļ�ֵ��27.
			}
		}
		if (str.substr(0, 8) == "addmoney")
		{
			m_pPlayer->addMoney(1000);
		}
		else if (str.substr(0,8)=="artifact")
		{
			CItemDt* pItemDt=CDataMgr::getInstance()->getMgr<CItemDtMgr>("ItemDtMgr")->getDataByID<CItemDt>(3000);
			m_pPlayer->getBag()->addItem(pItemDt);
		}
	}
	else if (KEY_DOWN(VK_B))
	{	
		CGameMgr::getInstance()->changeWnd(m_pPlayer->getBag());
		g_bClear = true;
	}
	else if (KEY_DOWN(VK_P))
	{
		CGameMgr::getInstance()->changeWnd(m_pPlayer->getPetBag());
		g_bClear = true;
	}
	else if (KEY_DOWN(VK_ESCAPE))
	{
		closegraph();
		x = 0;
		y = 0;
	}
	m_pPlayer->onUpdate();
	//�ж�����Ƿ�ײǽ��
	//��ȡ�������
	CVec2 vPos = m_pPlayer->getPosition();
	if (1 == m_pCurMapDt->pArrMap[vPos.x][vPos.y])
	{
		m_pPlayer->onRestore();
	}
	
	//vector<CMonster*> vecMonsters = m_pMonsterMgr->getMonsters();
	//for (CMonster* pMonster:vecMonsters)
	//{
	//	if (pMonster->isEquals(vPos))
	//	{
	//		m_pPlayer->onRestore();
	//	}
	//}

	//����ƶ���ʱ���ڵ�ͼ��������õ�ֵ�ã������ŵ�ֵ�Ǵ���1000���Ҵ����ŵ�ֵ�պ�����һ�ŵ�ID
	int nNextMapID = m_pCurMapDt->pArrMap[vPos.x][vPos.y];
	if (nNextMapID > 1000)
	{
		x = 0;
		y = 0;
		//����ڴ������ϡ�
		//���͵���һ��ͼ���޸ĵ�ͼ����
		m_pCurMapDt = CDataMgr::getInstance()->getMgr<CMapDtMgr>("MapDtMgr")->getDataByID<CMapDt>(nNextMapID);
		//ÿһ��ͼ��Ҷ��и�������
		m_pPlayer->setPosition(m_pCurMapDt->nInitRow, m_pCurMapDt->nInitCol);
		//����
		g_bClear = true;
	}

	//�����Npc��ͨ��������к͵�ͼID��Npc��������Npc����õ���ζ���������Npc
	CNpc* pNpc = m_pNpcMgr->getNpc(vPos.x, vPos.y, m_pCurMapDt->nID);
	if (pNpc)
	{
		m_pPlayer->onRestore();
		if (0 == pNpc->getType())
		{
			//�����̵ꡣ
			CShop* pShop = new CShop();
			pShop->setName("Shop");

			//�л����̵�
			CGameMgr::getInstance()->changeWnd(pShop);
			//ˢ����Ʒ��
			pShop->refreshItem(pNpc->getID());
			g_bClear = true;
			return;
		}
		else if(1==pNpc->getType())
		{
			CDialogue* pDialogue = new CDialogue();
			pDialogue->setName("Dialogue");
			pDialogue->setNpc(pNpc);
			CGameMgr::getInstance()->changeWnd(pDialogue);			
		}

		//������껹ԭ


	}
	
	m_pMonsterMgr->onUpdate();
	onCollision();
}

void CGameMap::onRender()
{
	//m_pPlayer->getEquip()->showEquip();
	for (int i = 0; i < 7; i++)
	{
		cout << endl;
	}

	cout << "							";
	cout << m_pCurMapDt->strName << "								  ";
	cout<<"��ֵ" << endl;


	//m_pPlayer->getEquip()->showEquip();
	for (int i = 0; i < m_pCurMapDt->nRowSize; i++)
	{
		cout << "							";
		for (int j = 0; j < m_pCurMapDt->nColSize; j++)
		{
			//������Ұ��Χ
			/*if (1 == m_pCurMapDt->nType&&m_pPlayer->isOutOfView(i, j)) {
				cout << "  ";
				continue;
			}*/
			//ͨ�����к͵�ͼID����Npc�����߻�ȡNpc��
			CNpc* pNpc = m_pNpcMgr->getNpc(i, j, m_pCurMapDt->nID);
			CMonster* pMonster = m_pMonsterMgr->getMonster(i, j, m_pCurMapDt->nID);
			if (1 == m_pCurMapDt->pArrMap[i][j])
			{
				cout << "��";
			}
			else if (m_pPlayer->isEuqals(i,j))
			{
				cout << m_pPlayer->getPic();
			}
			else if (pNpc)
			{
				//cout << pNpc->getPic();
				pNpc->onRender();
			}
			else if (m_pPlayer->getCurPet()&&m_pPlayer->getCurPet()->isEquals(i,j)&&m_pPlayer->getCurPet()->getIsFollow())
			{
				m_pPlayer->getCurPet()->onRender();
			}
			else if (pMonster)
			{
				pMonster->onRender();
			}
			else if (1000 < m_pCurMapDt->pArrMap[i][j])
			{
				cout << "��";
			}
			else
			{
				cout << "  ";
			}
		}
		if (0 == i)
		{
			cout << "��  ɫ:" << m_pPlayer->getName() << "                 ";;
		}
		else if (1 == i)
		{
			cout << "��  ��:" << m_pPlayer->getLevel() << "                 ";
		}
		else if (2 == i)
		{
			cout << "Ѫ  ��:" << m_pPlayer->getHp() << "/" << m_pPlayer->getMaxHp() << "                 ";;
		}
		else if (3 == i)
		{
			cout << "��  ��:" << m_pPlayer->getMp() << "/"<<m_pPlayer->getMaxMp() << "                 ";;
		}
		else if (4 == i)
		{
			cout << "������:" << m_pPlayer->getAck() << "                 ";;
		}
		else if (5 == i)
		{
			cout << "������:" << m_pPlayer->getDef() << "                 ";;
		}
		else if (6 == i)
		{
			cout << "��  ��:" << m_pPlayer->getExp() << "/" << m_pPlayer->getLevelUpExp() << "              ";
		}


		if (m_vecTask.size() != 0)
		{
			for (int k = 0; k < m_vecTask.size(); k++)
			{
				if (m_vecTask[k])
				{
					if (i == 10 + k * 5)
					{
						cout << "��ǰ����";
					}
					else if (i == 11 + k * 5)
					{
						cout << "�������ƣ�" << m_vecTask[k]->getName() << "     ";
					}
					else if (i == 12 + k * 5)
					{
						cout << "����������" << m_vecTask[k]->getDescription();
					}
					else if (i == 13 + k * 5)
					{
						cout << "������ȣ�" << m_vecTask[k]->getFinishCount() << "/" << m_vecTask[k]->getCount();
					}
				}
			}
		}
		else
		{
			if (i == 10)
			{
				cout << "��ǰ����";
			}
			else if (i==11)
			{
				cout << "������,��ȥNpc����������";
			}
		}

		cout << endl;
	}
}



void CGameMap::onCollision() {
	CMonster* pMonster=m_pMonsterMgr->getMonster(m_pPlayer->getPosition().x, m_pPlayer->getPosition().y, m_pCurMapDt->nID);
	if (pMonster)
	{
		//��תս������
		m_pPlayer->onRestore();
		g_bClear = true;
		CFightScene* pFight = new CFightScene();
		pFight->setTarget(m_pPlayer, pMonster);
		CGameMgr::getInstance()->changeWnd(pFight);
		return;
	}

}

void CGameMap::changeMap(int nID)
{
	m_pCurMapDt = CDataMgr::getInstance()->getMgr<CMapDtMgr>("MapDtMgr")->getDataByID<CMapDt>(nID);
}


void CGameMap::recharge()
{
	initgraph(650, 650, EW_SHOWCONSOLE | EW_NOCLOSE);
	IMAGE pic1;
	loadimage(&pic1, _T("source/1.png"), 650, 650);
	putimage(0, 0, &pic1);
	system("pause");
}

void CGameMap::setNull()
{
	x = 0;
	y = 0;
}




//��Npc ���� ���ߣ�ҩˮ���ӻ���  ���� 
//������������̵꣬  ��ͬ�̵���ʾ��ͬ��Ʒ����ҿ��Թ���  �洢������
//��ҿ��Դ򿪱�����ʹ����Ʒ������Ʒ��  ������װ���� װ������ �滻װ��
//����
//��������������ս���������غ��ơ�

