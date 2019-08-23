#pragma once
#include "Data.h"
//#include"CTank.h"
//#include "CBomb.h"
//#include "CGame.h"
class CGame;
class CMap
{
public:
	
	
	void DrawMap();
	void SaveMap(const char*);
	void ReadMap(const char*);
	bool EditMap(int& lev,CGame* game);
	int* GetMap()const;
	static int m_ArrMap[2][WEIGHT][HEIGHT];

};