#include <iostream>
#include <time.h>
#include "CTank.h"
#include "CDraw.h"
#include "Data.h"
#include "CBomb.h"
#include "CGame.h"
using std::cout;

void CTank::DrawObj(CMap& map)
{

	int x = pos.X;
	int y = pos.Y;
	for (int y = pos.Y - 1,i=0; y < pos.Y + 2; ++y,++i)
	{
		for (int x = pos.X - 1,j=0; x < pos.X + 2; ++x,++j)
		{
			//不是草地就画
			if (map.m_ArrMap[1][x][y]!=GRASS)
			{
				CDraw::WriteChar(x, y, m_color, 0);
				cout << m_tankShape[tag][i][nDir][j];
			}
			//写入地图数组
			if (tag == 0 || tag == 1)map.setMap(0, x, y, MTANK);
			else map.setMap(0, x, y, ETANK);
		}
		
	}
	
}

void CTank::ClsObj(CMap& map)
{
	for (int y = pos.Y - 1; y < pos.Y + 2; ++y)
	{
		for (int x = pos.X - 1; x < pos.X + 2; ++x)
		{
			map.m_ArrMap[0][x][y] = 0;
			if (map.m_ArrMap[1][x][y] == 0)
			{
				CDraw::WriteChar(x, y); cout << "  ";
			}
			else if (map.m_ArrMap[1][x][y] == RIVER)
			{
				CDraw::WriteChar(x, y); cout << "≈";
			}
		}
	}
}

void CTank::IniMyTank(int mtag,int color,int revive,int score)
{
	pos.X = WEIGHT/2-5 + mtag * 10;
	pos.Y = HEIGHT-3;
	nDir = UP;
	m_score = 0;
	m_bulletCD = 10;
	tag = mtag;
	m_blood = 3;
	m_revive = revive;
	//isMe = false;
	m_color = color;
}
void CTank::IniEne(CMap& map, int mtag)
{
	do {
		pos.X = 3 + rand() % WEIGHT - 4;
		pos.Y = 2 + rand() % 13;
	} while (IsValid(map)==0);
	nDir = rand() % 4;
	m_bulletCD = 10;
	tag == 2 ? m_interval = 300 : m_interval = 0;//Ene1的速度快
	m_lastClock = clock();
	tag = mtag;
	m_color = 15;
	m_blood = 3;
	m_revive = 1;
	//isMe = false;
}

void CTank::MoveObj(CMap& map)
{
	++m_bulletCD;
	if (tag == 0)//我方
	{
		GetMovOp("WASDX", map);
	}
	else if (tag == 1)//友方
	{
		GetMovOp("IJKLM", map);
	}
	else if(clock()-m_lastClock>m_interval) //敌方
	{
		m_lastClock = clock();
		if (tag==2?(CheckObj(map) == 0):	//tag=2不能过河
			( CheckObj(map) == 0|| CheckObj(map) == RIVER))
		{
			ClsObj(map);
			switch (nDir)
			{
			case UP:pos.Y--; break;
			case DOWN:pos.Y++; break;
			case LEFT:pos.X--; break;
			case RIGHT:pos.X++; break;
			default:
				break;
			}
			DrawObj(map);
		}
		else
			nDir = rand() % 4;
		if (m_bulletCD>=10&&rand()%6==0)//如果CD时间到了有三分之一可能性发射炮弹
		{
			m_bulletCD = 0;
			Fire(map);
		}
	}
	
}
//可穿透返回0
int CTank::CheckObj(CMap& map)
{
	int nRes = 0;
	// 预定义4个方向的增量值
	int next_points_x[4][3] = { { -1,0,1 }, {-1,0,1},{-2,-2,-2},{2,2,2} };
	int next_points_y[4][3] = { { -2,-2,-2 },{2,2,2},{-1,0,1},{-1,0,1} };
	//int sideX[12] = {-1,0,+1,+2,+2,+2,+1,0,-1,-2,-2,-2};
	//int sideY[12] = {-2,-2,-2,-1,0,+1,+2,+2,+2,+1,0,-1};
	int nextx, nexty;
	for (int i = 0; i < 3; ++i)
	{
		nextx = pos.X + next_points_x[nDir][i];
		nexty = pos.Y + next_points_y[nDir][i];
		switch (map.m_ArrMap[1][nextx][nexty])
		{
		case BORDER:nRes = BORDER; break;
		case WALL_REFLECT:nRes = WALL_REFLECT; break;
		case WALL_BREAK:nRes= WALL_BREAK; break;
		case RIVER:nRes = RIVER; break;
		default:
			break;
		}
		switch (map.m_ArrMap[0][nextx][nexty])
		{
		case MTANK:nRes = MTANK; break;
		case ETANK:nRes = ETANK; break;
		
		default:
			break;
		}
		if (tag==2)//Ene1需要躲我方子弹
		{
			for (int i=0;i<CGame::m_vecBomb.size();++i)
			{
				if (CGame::m_vecBomb[i].GetTag()<=1)//找我方子弹
				{
					int x = 0, y = 0;
					CGame::m_vecBomb[i].GetPos(x, y);
					if (CGame::m_vecBomb[i].GetDir() > 1 && nexty == y && nDir <= 1) //   |
					{															     //   T
						nRes = MBOMB; break;									     //B--
					}
					else if (CGame::m_vecBomb[i].GetDir() <= 1 && nextx == x && nDir > 1) //   |
					{																	  //   B
						nRes = MBOMB; break;											  //T--
					}
					else if (CGame::m_vecBomb[i].GetDir() <= 1 && nextx == x && nDir <= 1)	 //   |
					{																		 //   T
						nRes = MBOMB; break;												 //   B						 
					}																		 //   |
					else if (CGame::m_vecBomb[i].GetDir() > 1 && nexty == y && nDir > 1)     
					{																		 //--T B--
						nRes = MBOMB; break;
					}
				}
			}
		}
		if (nRes != 0)break;
	}
	return nRes;
}

void CTank::CollisionObj(CMap& map)
{
	/*switch (map[1][][])
	{
	default:
		break;
	}*/
}

void CTank::Fire(CMap& map)
{
	int x = pos.X, y = pos.Y;
	const char *patter[4] = { "●","●","■","■" };
	switch (nDir)//可缩写
		{
		case UP:
			if (map.m_ArrMap[1][x][y + 1] != GRASS) { CDraw::WriteChar(x, y + 1); cout << patter[tag]; }
			if (map.m_ArrMap[1][x][y] != GRASS) { CDraw::WriteChar(x, y); cout << "┃"; }
			if (map.m_ArrMap[1][x][y - 1] != GRASS) { CDraw::WriteChar(x, y - 1); cout << "  "; }
			break;
		case DOWN:
			if (map.m_ArrMap[1][x][y - 1] != GRASS) {CDraw::WriteChar(x, y - 1);cout<< patter[tag];	}
			if (map.m_ArrMap[1][x][y] != GRASS) {CDraw::WriteChar(x, y);cout<< "┃";			   }
			if (map.m_ArrMap[1][x][y + 1] != GRASS) {CDraw::WriteChar(x, y + 1);cout<< "  ";		}
			break;
		case LEFT:
			if (map.m_ArrMap[1][x + 1][y] != GRASS) {CDraw::WriteChar(x + 1, y);cout<< patter[tag];}
			if (map.m_ArrMap[1][x][y] != GRASS) {CDraw::WriteChar(x, y);cout<< "━";			  }
			if (map.m_ArrMap[1][x - 1][y] != GRASS) {CDraw::WriteChar(x - 1, y);cout<< "  ";	   }
			break;
		case RIGHT:
			if (map.m_ArrMap[1][x + 1][y] != GRASS) {CDraw::WriteChar(x + 1, y);cout<< "  ";		 }
			if (map.m_ArrMap[1][x][y] != GRASS) {CDraw::WriteChar(x, y);cout<< "━";				}
			if (map.m_ArrMap[1][x + 1][y] != GRASS) {CDraw::WriteChar(x - 1, y);cout<< patter[tag];	 }
			break;
		}
	if (tag>=2)
	{
		CBomb::GreateB(*this, map);//创建子弹
		if (rand() % 2 == 0) tag==2? m_lastClock += clock() / 10: m_lastClock += clock() / 8;//坦克暂停的间隔时间加长
		else if (nDir % 2 != 0) nDir -= 1; else nDir += 1;//坦克转向
	}
	else//我方坦克需要等CD时间过了
	{
		if (m_bulletCD>=10)
		{
			m_bulletCD = 0;
			CBomb::GreateB(*this, map);//创建子弹
			
		}
	}
}

int CTank::GetRevive()const
{
	return m_revive;
}

void CTank::GetPos(short& x, short& y) const
{
	x = pos.X; y = pos.Y;
}

int CTank::GetTag() const
{
	return tag;
}

int CTank::GetDir() const
{
	return nDir;
}

int CTank::GetBlood() const
{
	return m_blood;
}

int CTank::GetScore() const
{
	return m_score;
}

void CTank::GetMovOp(const char cOp[5], CMap& map)
{
	if (GetAsyncKeyState(cOp[0]) & 1)
	{
		if (nDir != UP)
		{
			nDir = UP; DrawObj(map);
		}
		else if (CheckObj(map) == 0)
		{
			//坐标变化
			ClsObj(map); --pos.Y; DrawObj(map);
		}
	}
	else if (GetAsyncKeyState(cOp[1]) & 1)
	{
		if (nDir != LEFT)
		{
			nDir = LEFT; DrawObj(map);
		}
		else if (CheckObj(map) == 0)
		{
			//坐标变化
			ClsObj(map); --pos.X; DrawObj(map);
		}
	}
	else if (GetAsyncKeyState(cOp[2]) & 1)
	{
		if (nDir != DOWN)
		{
			nDir = DOWN; DrawObj(map);
		}
		else if (CheckObj(map) == 0)
		{
			//坐标变化
			ClsObj(map); ++pos.Y; DrawObj(map);
		}
	}
	else if (GetAsyncKeyState(cOp[3]) & 1)
	{
		if (nDir != RIGHT)
		{
			nDir = RIGHT; DrawObj(map);
		}
		else if (CheckObj(map) == 0)
		{
			//坐标变化
			ClsObj(map); ++pos.X; DrawObj(map);
		}
	}
	else if (GetAsyncKeyState(cOp[4]) & 1)
	{
		Fire(map);
	}
}
//随机生成的位置合法返回true
bool CTank::IsValid(CMap& map)
{
	for (int y = pos.Y - 1; y < pos.Y + 2; ++y)
	{
		for (int x = pos.X - 1; x < pos.X + 2; ++x)
		{
			if (map.m_ArrMap[1][x][y]==BORDER|| map.m_ArrMap[1][x][y] == WALL_BREAK
				|| map.m_ArrMap[1][x][y] == WALL_REFLECT|| map.m_ArrMap[1][x][y] == RIVER)
			{
				return false;
			}
			if (map.m_ArrMap[0][x][y] == MTANK || map.m_ArrMap[0][x][y] == ETANK
				|| map.m_ArrMap[0][x][y] == MBOMB)
			{
				return false;
			}
		}
	}
	return true;
}

