#pragma once
/*
//A*�㷨������
*/
#include <vector>
#include <list>
#include "Vec2.h"
using namespace std;

const int kCost1 = 10; //ֱ��һ������
const int kCost2 = 14; //б��һ������

struct Point
{
	int x, y; //�����꣬����Ϊ�˷��㰴��C++�����������㣬x������ţ�y��������
	int F, G, H; //F=G+H
	Point* parent; //parent�����꣬����û����ָ�룬�Ӷ��򻯴���
	Point(int _x, int _y) :x(_x), y(_y), F(0), G(0), H(0), parent(NULL)  //������ʼ��
	{
	}
};

class Astar
{
public:
	void InitAstar(int** _maze, int nRow, int nCol,vector<CVec2> vecPos);
	list<Point*> GetPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner);

private:
	Point* findPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner);
	vector<Point*> getSurroundPoints(const Point* point, bool isIgnoreCorner) const;
	bool isCanreach(const Point* point, const Point* target, bool isIgnoreCorner) const; //�ж�ĳ���Ƿ����������һ���ж�
	Point* isInList(const list<Point*>& list, const Point* point) const; //�жϿ���/�ر��б����Ƿ����ĳ��
	Point* getLeastFpoint(); //�ӿ����б��з���Fֵ��С�Ľڵ�
	//����FGHֵ
	int calcG(Point* temp_start, Point* point);
	int calcH(Point* point, Point* end);
	int calcF(Point* point);
private:
	int** maze;
	list<Point*> openList;  //�����б�
	list<Point*> closeList; //�ر��б�
	int Row;
	int Col;
	vector<CVec2> vecPos;
};