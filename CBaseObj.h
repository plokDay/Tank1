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
	int tag;//0我方1友方2敌方3敌方
	
};