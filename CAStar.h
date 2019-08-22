#pragma once
#include <windows.h>
#include <vector>
#include "CMap.h"
using std::vector;

class CAStar
{
public:

	typedef struct _MYCOORD {
		int X;
		int Y;
	} MYCOORD, *PMYCOORD;
	typedef struct _MY_MYCOORD : public MYCOORD
	{
		bool operator==(MYCOORD cod)
		{
			return (X == cod.X) && (Y == cod.Y);
		}
		void operator=(MYCOORD cod)
		{
			X = cod.X;
			Y = cod.Y;
		}
		int d; //方向（坦克的移动方向）
	}MY_MYCOORD, *PMY_MYCOORD;


	//节点的结构
	typedef struct _NODE_INFO
	{
		int g; //移动损耗
		int h; //据终点最短距离
		int f; //g+h
		MY_MYCOORD codSelf;  //自身坐标
		MY_MYCOORD codParent;//父节点坐标（由谁扩散的）
						   //NODE_INFO privor;
		void SetH_F(MYCOORD cod1, MYCOORD cod2)
		{
			h = abs(cod1.X - cod2.X) + abs(cod1.Y - cod2.Y);
			f = g + h;
		}

	}NODE_INFO, *PNODE_INFO;
	MYCOORD m_Start; //起点坐标
	MYCOORD m_End;   //终点坐标

	vector<NODE_INFO> m_Open;  //待扩散的点
	vector<NODE_INFO> m_Close; //扩散过的点
	vector<MY_MYCOORD>  m_Path;  //最短路径

	int* m_pMap;      //地图的首地址
	int  m_MapHigh;   //地图的长
	int  m_MapWidth;  //地图的宽

	int m_Block = 10;      //障碍物
					  /*
					  1 2 3
					  4 5 6
					  7 8 9
					  */
	bool m_bInitMapInfo;    //是否初始化地图信息
	bool m_bInitCoordInfo;  //是否初始化起始坐标信息


	void InitMapInfo(int* pMap, int nHigh, int nWidth, int nBlock);
	void InitCoord(MYCOORD codStar, MYCOORD codEnd);

	bool FindPath(CMap& map); //查找包含最短路径的点（得到Close表）
	void GetPath();  //获取最短路径
	typedef struct _VIR_INFO
	{
		char isOpen : 1; //表是否在Open表中
		char isClose : 1; //表示是否在CLose表中
		char rcieve : 6; //保留
	}VIR_INFO, *PVIR_INFO;

	static PVIR_INFO m_pVir; //指向虚拟地图的首地址
	void PrintPath();
};