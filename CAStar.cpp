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


//返回false表示需要躲避炮弹
bool CAStar::EludeBomb(int nextx, int nexty,int nDir)
{
	for (int i = 0; i < CGame::m_vecBomb.size(); ++i)
	{
		if (CGame::m_vecBomb[i].GetTag() <= 1)//找我方子弹
		{
			int x = 0, y = 0;
			CGame::m_vecBomb[i].GetPos(x, y);
			if (CGame::m_vecBomb[i].GetDir() > 1 && nexty == y && nDir <= 1) //   |
			{															     //   T
				return false;									     //B--
			}
			else if (CGame::m_vecBomb[i].GetDir() <= 1 && nextx == x && nDir > 1) //   |
			{																	  //   B
				return false;											  //T--
			}
			else if (CGame::m_vecBomb[i].GetDir() <= 1 && nextx == x && nDir <= 1)	 //   |
			{																		 //   T
				return false;														 //   B						 
			}																		 //   |
			else if (CGame::m_vecBomb[i].GetDir() > 1 && nexty == y && nDir > 1)
			{																		 //--T B--
				return false;
			}
		}
	}
	return true;
}

void CAStar::InitMapInfo(/*int* pMap,*/ int nHigh, int nWidth, int nBlock)
{
	//m_pMap = pMap;
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

bool CAStar::FindPath(bool *stop)
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
		if ((m_Start.X==m_End.X-2 && m_Start.Y == m_End.Y )|| (m_Start.X == m_End.X - 1 && m_Start.Y == m_End.Y)
			|| (m_Start.X == m_End.X + 1 &&m_Start.Y == m_End.Y)|| (m_Start.X == m_End.X + 2 && m_Start.Y == m_End.Y))//到达寻路终点
		{
			*stop = true; return false;
		}
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
		int x1 = m_Open[nIndex].codSelf.X;
		int y1 = m_Open[nIndex].codSelf.Y;
		m_pVir[y1 * m_MapWidth + x1].isClose = true;
		m_pVir[y1 * m_MapWidth + x1].isOpen = false;

		//把扩散过的点保存到Close表，并从Open表中删除
		m_Close.push_back(m_Open[nIndex]);
		m_Open.erase(m_Open.begin() + nIndex);

		//检测扩散出来的点是否合格，是否是终点
		for (int k = 0; k < 4; k++)
		{
			int x = nodeNew[k].codSelf.X;
			int y = nodeNew[k].codSelf.Y;
			//CGame::WriteChar(x, y); cout << "*";
			//是不是终点
			if (nodeNew[k].codSelf == m_End)
			{
				m_Close.push_back(nodeNew[k]);
				return true;
			}
			//是否越界
			if (x <1 || y <1 ||
				x >(m_MapWidth) ||
				y >(m_MapHigh))
			{
				continue;
			}
			//判断是否是障碍物
			bool mapp = false;
			for (int i = x - 1; i <= x + 1; i++) {
				if (mapp) {
					break;
				}
				for (int j = y - 1; j <= y + 1; j++) {
					if (CMap::m_ArrMap[1][i][j] == BORDER || CMap::m_ArrMap[1][i][j] == WALL_REFLECT
						|| CMap::m_ArrMap[1][i][j] == WALL_BREAK|| CMap::m_ArrMap[0][i][j] == MTANK||
						CMap::m_ArrMap[0][i][j] == ETANK|| CMap::m_ArrMap[0][i][j] == MBOMB)//|| EludeBomb(i, j,k)==false)
					{
						mapp = true;
						break;
					}
				}
			}
			if (mapp) {
				mapp = false;
				continue;
			}


			//判断是否在Open表和Close表中
			if (m_pVir[y * m_MapWidth + x].isClose ||
				m_pVir[y * m_MapWidth + x].isOpen)
			{
				continue;
			}
			//将合格的点保存到Open表中
			m_Open.push_back(nodeNew[k]);

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


