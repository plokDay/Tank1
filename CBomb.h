#pragma once
#include "CBaseObj.h"
#include "CMap.h"
#include "CTank.h"
class CMap;
class CTank;
class CBomb:public CBaseObj
{
public:
	void DrawObj(CMap& map);
	void ClsObj(CMap& map);
	int CheckObj(CMap& map);
	void CollisionObj(CMap& map,int check);
	void MoveObj(CMap& map);
	static void GreateB(CTank& tank, CMap& map);
	bool GetExist()const;
	void GetPos(int& x, int& y)const;
	int GetTag()const;
	int GetDir()const;
	bool operator== (CTank& tank);
private:
	bool m_exist;
	//bool m_baby = true;//�ӵ��Ƿ���������

	//int m_interval;//ʱ����
	//int m_lastClock;//��һ�ε�ʱ��
	int isMe;//���ڱ��������ӵ�ʱ�ų��Լ�
	const char *m_shape[4] = { "��","��","��","��" };
};