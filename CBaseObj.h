#pragma once
#include <windows.h>
#include "Data.h"
class CBaseObj
{
public:
	
	virtual void DrawObj() {}
	virtual void ClsObj() {}
	virtual void MoveObj() {}
	virtual int CheckObj() { return 0; }
	virtual void CollisionObj() {}
protected:
	COORD pos;
	int nDir;
	int tag;//0�ҷ�1�ѷ�2�з�3�з�
	
};