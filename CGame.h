#pragma once
#include <vector>
#include "CMap.h"
#include "CTank.h"
#include "CBomb.h"

using std::vector;
class CTank;
class CBomb;
class CMap;
class CGame
{
public:
	int Menu();
	void IniAll();
	void StartGame();
	void SetDouble(int n);
	void SetOld();
	CMap& GetMap();
	int GetLevel()const;
	void SaveGame()const;
	void ReadGame();
	const char* GetMapName(int index);
	void PrintUI()const;
	static vector<CTank>  m_vecTank;
	static vector<CBomb>  m_vecBomb;
	static void CheckGame();
	static void WriteChar(int x, int y, int foreColor = 15, int backcolor = 0);
	static void set();
public:
	static int m_stop;//1������Ϸ-1��ͣ-2����2��һ��
private:
	
	CMap m_map;
	
	int m_isDouble = 0;//0����ģʽ��2˫��ģʽ
	bool m_isOld = false;
	int m_level=1;
	char m_mapNamelev[3][10] = { "maplevel1", "maplevel2", "maplevel3" };
	
};