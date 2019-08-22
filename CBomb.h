#pragma once
#include "CBaseObj.h"
#include "CMap.h"
#include "CTank.h"
class CMap;
class CTank;
class CBomb:public CBaseObj
{
public:
	void DrawObj();
	void ClsObj();
	int CheckObj();
	void CollisionObj(int check);
	void MoveObj();
	static void GreateB(CTank& tank);
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