#include<iostream>
#include "CAStar.h"
#include "CMap.h"
#include "CGame.h"
using std::cout;
CAStar::PVIR_INFO CAStar::m_pVir;

void CAStar::PrintPath()
{
	for (int i = m_Path.size() - 1; i >= 0; i--)
	{
		CGame::WriteChar(m_Path[i].X, m_Path[i].Y); cout << "@";
	}
}



void CAStar::InitMapInfo(int* pMap, int nHigh, int nWidth, int nBlock)
{
	m_pMap = pMap;
	m_MapHigh = nHigh;
	m_MapWidth = nWidth;
	m_Block = nBlock;
	

	m_pVir = new VIR_INFO[m_MapHigh*m_MapWidth]{};


	m_bInitMapInfo = true;
}

void CAStar::InitCoord(MYCOORD codStar, MYCOORD codEnd)
{
	m_Start = codStar;
	m_End = codEnd;
	m_bInitCoordInfo = true;
}

bool CAStar::FindPath(CMap& map)
{
	//是否初始化完毕
	if (!m_bInitCoordInfo || !m_bInitMapInfo)
	{
		return false;
	}
	/*
	1.  把起点坐标保存到Open表中
	2.1 判断Open表是否为空，空了说明此路不同
	2.2 找出Open表中F值最小的点
	2.3 进行扩散
	2.4 把扩散的点保存到Close表中，从Open表中删除
	2.5 判断新扩散出来的点是否合格
	2.5.1 是否是终点，是就直接返回
	是不是障碍物
	是不是越界
	是否在Open表中
	是否在Close表中
	2.6 把合格的点存进Open表中
	2.7 重复2.1 -- 2.6
	*/

	//清空Open和Close表
	m_Open.clear();
	m_Close.clear();

	ZeroMemory(m_pVir, m_MapWidth*m_MapHigh);



	NODE_INFO nodeStar;
	nodeStar.codSelf = m_Start;
	nodeStar.g = 0;
	nodeStar.SetH_F(m_Start, m_End);

	m_Open.push_back(nodeStar);

	//开始循环查找

	while (true)
	{
		//Open表是否为空
		if (m_Open.empty())
		{
			return false;
		}
		//找Open表中F值最小的点
		int nIndex = 0;
		for (int i = 1; i < m_Open.size(); i++)
		{
			//如果当前的nIndex大于 i的 交换
			if (m_Open[nIndex].f > m_Open[i].f)
			{
				nIndex = i;
			}
		}

		//这里是以最小的点扩散
		//扩散
		NODE_INFO nodeNew[4]{};

		//上
		nodeNew[0].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[0].codSelf.Y = m_Open[nIndex].codSelf.Y - 1;
		//下
		nodeNew[1].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[1].codSelf.Y = m_Open[nIndex].codSelf.Y + 1;
		//左
		nodeNew[2].codSelf.X = m_Open[nIndex].codSelf.X - 1;
		nodeNew[2].codSelf.Y = m_Open[nIndex].codSelf.Y;
		//右
		nodeNew[3].codSelf.X = m_Open[nIndex].codSelf.X + 1;
		nodeNew[3].codSelf.Y = m_Open[nIndex].codSelf.Y;

		for (int i = 0; i < 4; i++)
		{
			nodeNew[i].codParent = m_Open[nIndex].codSelf;
			nodeNew[i].g = m_Open[nIndex].g + 1;
			nodeNew[i].SetH_F(nodeNew[i].codSelf, m_End);
			//方向
			nodeNew[i].codSelf.d = i;
		}
		//=====优化处理==================================================================================



		int x1 = m_Open[nIndex].codSelf.X;
		int y1 = m_Open[nIndex].codSelf.Y;
		m_pVir[y1 * m_MapWidth + x1].isClose = true;
		m_pVir[y1 * m_MapWidth + x1].isOpen = false;

		//把扩散过的点保存到Close表，并从Open表中删除
		m_Close.push_back(m_Open[nIndex]);
		m_Open.erase(m_Open.begin() + nIndex);

		//检测扩散出来的点是否合格，是否是终点
		for (int i = 0; i < 4; i++)
		{
			int x = nodeNew[i].codSelf.X;
			int y = nodeNew[i].codSelf.Y;

			//是不是终点
			if (nodeNew[i].codSelf == m_End)
			{
				m_Close.push_back(nodeNew[i]);
				return true;
			}
			//是否越界
			if (x <1 || y <1 ||
				x >(m_MapWidth) ||
				y >(m_MapHigh))
			{
				continue;
			}
			
			bool mapp = false;
			for (int i = x - 1; i <= x + 1; i++) {
				if (mapp) {
					break;
				}
				for (int j = y - 1; j <= y + 1; j++) {
					if (map.m_ArrMap[1][i][j] == BORDER || map.m_ArrMap[1][i][j] == WALL_REFLECT
						|| map.m_ArrMap[1][i][j] == WALL_BREAK) {
						mapp = true;
						break;
					}
				}
			}
			if (mapp) {
				mapp = false;
				continue;
			}


			//=====优化处理==================================================================================




			//判断是否在Open表和Close表中
			if (m_pVir[y * m_MapWidth + x].isClose ||
				m_pVir[y * m_MapWidth + x].isOpen)
			{
				continue;
			}

			

			//将合格的点保存到Open表中
			m_Open.push_back(nodeNew[i]);

			m_pVir[y * m_MapWidth + x].isOpen = true;

		}

	}
}

void CAStar::GetPath()
{
	//回溯父节点
	m_Path.clear();//清空原来的路径
	int nSize = m_Close.size();
	int nIndex = nSize - 1;

	while (true)
	{
		for (int i = 0; i < nSize; i++)
		{
			if (m_Close[nIndex].codParent == m_Start)
			{
				return;
			}
			if (m_Close[nIndex].codParent == m_Close[i].codSelf)
			{
				m_Path.push_back(m_Close[i].codSelf);
				nIndex = i;
				break;
			}
		}
	}
}


