#pragma once
#include <windows.h>
#include "CMap.h"
#include "CBaseObj.h"
class CMap;
class CTank:public CBaseObj
{
public:
	void DrawObj();
	void ClsObj();
	void IniMyTank(int mtag,int color,int revive,int score);
	void IniEne(int mtag,int revive);
	void MoveObj();
	int CheckObj();
	void Fire();
	
	int GetRevive()const;
	void GetPos(short& x, short& y)const;
	int GetTag()const;
	int GetDir()const;
	int GetBlood()const;
	int GetScore()const;
	int GetCD()const;
private:
	int m_bulletCD;//射击冷却时间
	int m_color;
	int m_blood;
	int m_score;
	int m_revive;//有几条命
	int m_interval;//时间间隔
	int m_lastClock;//上一次的时钟
	

	const char* m_tankShape[4][3][4][3] =
	{
{			  
	{{"◢","┃","◣"},{"◢","︻","◣"},{"◢","┳","◣"},{"◢","┳","◣"}},
	{{"┣","●","┫"},{"┣","●","┫"},{"━","●","】"},{"【","●","━"}},
	{{"◥","︼","◤"},{"◥","┃","◤"},{"◥","┻","◤"},{"◥","┻","◤"}}},{
	{{"┏","┃","┓"},{"◢","━","◣"},{"┏","┳","◣"},{"◢","┳","┓"}},
	{{"┣","●","┫"},{"┣","●","┫"},{"━","●","┃"},{"┃","●","━"}},
	{{"◥","━","◤"},{"┗","┃","┛"},{"┗","┻","◤"},{"◥","┻","┛"}}},{
	{{"╔","┃","╗"},{"╔","╦","╗"},{"╔","╦","╗"},{"╔","╦","╗"}},
	{{"╠","◆","╣"},{"╠","◆","╣"},{"━","◆","╣"},{"╠","◆","━"}},
	{{"╚","╩","╝"},{"╚","┃","╝"},{"╚","╩","╝"},{"╚","╩","╝"}}},{
	{{"┏","┃","┓"},{"┏","┳","┓"},{"┏","┳","┓"},{"┏","┳","┓"}},
	{{"┣","■","┫"},{"┣","■","┫"},{"━","■","┫"},{"┣","■","━"}},
	{{"┗","┻","┛"},{"┗","┃","┛"},{"┗","┻","┛"},{"┗","┻","┛"}}
}
	};
private:
	void GetMovOp(const char cOp[5]);
	bool IsValid();

	friend class CBomb;
};