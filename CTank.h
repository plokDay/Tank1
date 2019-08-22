#pragma once
#include <windows.h>
#include "CMap.h"
#include "CBaseObj.h"
class CMap;
class CTank:public CBaseObj
{
public:
	void DrawObj(CMap& map);
	void ClsObj(CMap& map);
	void IniMyTank(int mtag,int color,int revive,int score);
	void IniEne(CMap& map,int mtag);
	void MoveObj(CMap& map);
	int CheckObj(CMap& map);
	void CollisionObj(CMap& map);
	void Fire(CMap& map);
	int GetRevive()const;
	void GetPos(short& x, short& y)const;
	int GetTag()const;
	int GetDir()const;
	int GetBlood()const;
	int GetScore()const;
private:
	int m_bulletCD;//�����ȴʱ��
	int m_color;
	int m_blood;
	int m_score;
	int m_revive;//�м�����
	int m_interval;//ʱ����
	int m_lastClock;//��һ�ε�ʱ��


	const char* m_tankShape[4][3][4][3] =
	{
{			  
	{{"��","��","��"},{"��","��","��"},{"��","��","��"},{"��","��","��"}},
	{{"��","��","��"},{"��","��","��"},{"��","��","��"},{"��","��","��"}},
	{{"��","��","��"},{"��","��","��"},{"��","��","��"},{"��","��","��"}}},{
	{{"��","��","��"},{"��","��","��"},{"��","��","��"},{"��","��","��"}},
	{{"��","��","��"},{"��","��","��"},{"��","��","��"},{"��","��","��"}},
	{{"��","��","��"},{"��","��","��"},{"��","��","��"},{"��","��","��"}}},{
	{{"�X","��","�["},{"�X","�j","�["},{"�X","�j","�["},{"�X","�j","�["}},
	{{"�d","��","�g"},{"�d","��","�g"},{"��","��","�g"},{"�d","��","��"}},
	{{"�^","�m","�a"},{"�^","��","�a"},{"�^","�m","�a"},{"�^","�m","�a"}}},{
	{{"��","��","��"},{"��","��","��"},{"��","��","��"},{"��","��","��"}},
	{{"��","��","��"},{"��","��","��"},{"��","��","��"},{"��","��","��"}},
	{{"��","��","��"},{"��","��","��"},{"��","��","��"},{"��","��","��"}}
}
	};
private:
	void GetMovOp(const char cOp[5], CMap& map);
	bool IsValid(CMap& map);

	friend class CBomb;
};