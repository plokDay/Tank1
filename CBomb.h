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
	//bool m_baby = true;//子弹是否是新生的

	//int m_interval;//时间间隔
	//int m_lastClock;//上一次的时钟
	int isMe;//用于遍历所有子弹时排除自己
	const char *m_shape[4] = { "●","●","◆","■" };
};