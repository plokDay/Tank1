#include <iostream>
#include <time.h>
#include "CTank.h"
#include "CMap.h"
#include "Data.h"
#include "CBomb.h"
#include "CGame.h"
#include "CAStar.h"
using std::cout;

void CTank::DrawObj()
{

	int x = pos.X;
	int y = pos.Y;
	for (int y = pos.Y - 1, i = 0; y < pos.Y + 2; ++y, ++i)
	{
		for (int x = pos.X - 1, j = 0; x < pos.X + 2; ++x, ++j)
		{
			//不是草地就画
			if (CMap::m_ArrMap[1][x][y] != GRASS)
			{
				CGame::WriteChar(x, y, m_color, 0);
				cout << m_tankShape[tag][i][nDir][j];
			}
			//写入地图数组
			if (tag == 0 || tag == 1)CMap::m_ArrMap[0][x][y] = MTANK;
			else CMap::m_ArrMap[0][x][y] = ETANK;
		}

	}

}

void CTank::ClsObj()
{
	for (int y = pos.Y - 1; y < pos.Y + 2; ++y)
	{
		for (int x = pos.X - 1; x < pos.X + 2; ++x)
		{
			CMap::m_ArrMap[0][x][y] = 0;
			if (CMap::m_ArrMap[1][x][y] == 0)
			{
				CGame::WriteChar(x, y); cout << "  ";
			}
			else if (CMap::m_ArrMap[1][x][y] == RIVER)
			{
				CGame::WriteChar(x, y); cout << "≈";
			}
		}
	}
}

void CTank::IniMyTank(int mtag, int color, int revive, int score)
{
	pos.X = WEIGHT / 2 - 5 + mtag * 10;
	pos.Y = HEIGHT - 3;
	nDir = UP;
	m_score = 0;
	m_bulletCD = 10;
	tag = mtag;
	m_blood = 3;
	m_revive = revive;
	m_color = color;
}
void CTank::IniEne( int mtag,int revive)
{
	do {
		pos.X = 3 + rand() % WEIGHT - 4;
		pos.Y = 2 + rand() % 13;
	} while (IsValid() == 0);
	nDir = rand() % 4;
	m_bulletCD = 10;
	tag == 2 ? m_interval = 300 : m_interval = 150;//Ene1的速度快
	m_lastClock = clock();
	tag = mtag;
	
	m_color = 15;
	m_blood = 3;
	m_revive = revive;
	
}

void CTank::MoveObj()
{
	if(m_bulletCD < 10 ) m_bulletCD+=1;
	if (tag == 0)//我方
	{
		GetMovOp("WASDE");
	}
	else if (tag == 1)//友方
	{
		GetMovOp("IJKLU");
	}
	else if (clock() - m_lastClock > m_interval) //敌方
	{
		m_lastClock = clock();
		if (tag == 2) //Ene1的移动
		{
			if (CheckObj() == 0)	//tag=2不能过河
			{
				ClsObj();
				switch (nDir)
				{
				case UP:pos.Y--; break;
				case DOWN:pos.Y++; break;
				case LEFT:pos.X--; break;
				case RIGHT:pos.X++; break;
				default:
					break;
				}
				DrawObj();
			}
			else nDir = rand() % 4;
		}
		if (tag==3)//Ene2的移动
		{
			bool isStop = false;
			int nEnd = 0; pos.X > WEIGHT / 2 ? nEnd = WEIGHT / 2 + 7 : nEnd = WEIGHT / 2 - 7;
			//if (CheckObj() == 0|| CheckObj() == RIVER)//Ene2能过河
			{
				ClsObj();
				CAStar as;
				as.InitMapInfo(/*(int*)*CMap::m_ArrMap,*/ HEIGHT, WEIGHT*2, 0);
				as.InitCoord({ pos.X,pos.Y}, { nEnd, HEIGHT-5 });
				bool res=as.FindPath(&isStop);
				if (isStop==false&&res)
				{
					as.GetPath();
						//as.PrintPath();
						for (int i = as.m_Path.size() - 1; i > 0; i--)
						{
							nDir = as.m_Path[i].d;
							break;
						}
					
					switch (nDir)
					{
					case UP:pos.Y--; break;
					case DOWN:pos.Y++; break;
					case LEFT:pos.X--; break;
					case RIGHT:pos.X++; break;
					default:
						break;
					}
				}
				else//到达终点
				{
					nEnd > WEIGHT / 2 ? nDir = LEFT : nDir = RIGHT;
				}
				
				DrawObj();
			}
		}
		if (m_bulletCD >= 10 && rand() % 10 == 0)//如果CD时间到了有三分之一可能性发射炮弹
		{
			
			m_bulletCD = 0;
			Fire();
		}
	}

}
//可穿透返回0
int CTank::CheckObj()
{
	int nRes = 0;
	// 预定义4个方向的增量值
	int next_points_x[4][3] = { { -1,0,1 }, {-1,0,1},{-2,-2,-2},{2,2,2} };
	int next_points_y[4][3] = { { -2,-2,-2 },{2,2,2},{-1,0,1},{-1,0,1} };
	
	int nextx, nexty;
	for (int i = 0; i < 3; ++i)
	{
		nextx = pos.X + next_points_x[nDir][i];
		nexty = pos.Y + next_points_y[nDir][i];
		switch (CMap::m_ArrMap[1][nextx][nexty])
		{
		case BORDER:nRes = BORDER; break;
		case WALL_REFLECT:nRes = WALL_REFLECT; break;
		case WALL_BREAK:nRes = WALL_BREAK; break;
		case RIVER:nRes = RIVER; break;
		default:
			break;
		}
		switch (CMap::m_ArrMap[0][nextx][nexty])
		{
		case MTANK:nRes = MTANK; break;
		case ETANK:nRes = ETANK; break;

		default:
			break;
		}
		if (tag >= 2)//Ene需要躲我方子弹
		{
			CAStar as;
			if (as.EludeBomb( nextx, nexty,nDir)==false)
			{
				nRes = MBOMB; break;
			}
		
		}
		if (nRes != 0)break;
	}
	return nRes;
}


void CTank::Fire()
{
	int x = pos.X, y = pos.Y;
	const char *patter[4] = { "●","●","◆","■" };
	switch (nDir)//可缩写
	{
	case UP:
		if (CMap::m_ArrMap[1][x][y + 1] != GRASS) { CGame::WriteChar(x, y + 1); cout << patter[tag]; }
		if (CMap::m_ArrMap[1][x][y] != GRASS) { CGame::WriteChar(x, y); cout << "┃"; }
		if (CMap::m_ArrMap[1][x][y - 1] != GRASS) { CGame::WriteChar(x, y - 1); cout << "  "; }
		break;
	case DOWN:
		if (CMap::m_ArrMap[1][x][y - 1] != GRASS) { CGame::WriteChar(x, y - 1); cout << patter[tag]; }
		if (CMap::m_ArrMap[1][x][y] != GRASS) { CGame::WriteChar(x, y); cout << "┃"; }
		if (CMap::m_ArrMap[1][x][y + 1] != GRASS) { CGame::WriteChar(x, y + 1); cout << "  "; }
		break;
	case LEFT:
		if (CMap::m_ArrMap[1][x + 1][y] != GRASS) { CGame::WriteChar(x + 1, y); cout << patter[tag]; }
		if (CMap::m_ArrMap[1][x][y] != GRASS) { CGame::WriteChar(x, y); cout << "━"; }
		if (CMap::m_ArrMap[1][x - 1][y] != GRASS) { CGame::WriteChar(x - 1, y); cout << "  "; }
		break;
	case RIGHT:
		if (CMap::m_ArrMap[1][x + 1][y] != GRASS) { CGame::WriteChar(x + 1, y); cout << "  "; }
		if (CMap::m_ArrMap[1][x][y] != GRASS) { CGame::WriteChar(x, y); cout << "━"; }
		if (CMap::m_ArrMap[1][x + 1][y] != GRASS) { CGame::WriteChar(x - 1, y); cout << patter[tag]; }
		break;
	}
	if (tag >= 2)
	{
		mciSendString("play shoot2.wav", NULL, 0, NULL);
		CBomb::GreateB(*this);//创建子弹
		//nDir = rand() % 4;
		//if (rand() % 2 == 0) tag == 2 ? m_lastClock += clock() / 10 : m_lastClock += clock() / 8;//坦克暂停的间隔时间加长
		//else if (nDir % 2 != 0) nDir -= 1; else nDir += 1;//坦克转向
	}
	else//我方坦克需要等CD时间过了
	{
		if (m_bulletCD >= 10)
		{
			mciSendString("play shoot0.wav", NULL, 0, NULL);
			m_bulletCD = 0;

			CBomb::GreateB(*this);//创建子弹

		}else mciSendString("play prepare.wav", NULL, 0, NULL);
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

int CTank::GetCD() const
{
	return m_bulletCD;
}

void CTank::GetMovOp(const char cOp[5])
{
	if (GetAsyncKeyState(cOp[0]) & 1)
	{
		if (nDir != UP)
		{
			nDir = UP; DrawObj();
		}
		else if (CheckObj() == 0)
		{
			//坐标变化
			ClsObj(); --pos.Y; DrawObj();
		}
	}
	else if (GetAsyncKeyState(cOp[1]) & 1)
	{
		if (nDir != LEFT)
		{
			nDir = LEFT; DrawObj();
		}
		else if (CheckObj() == 0)
		{
			//坐标变化
			ClsObj(); --pos.X; DrawObj();
		}
	}
	else if (GetAsyncKeyState(cOp[2]) & 1)
	{
		if (nDir != DOWN)
		{
			nDir = DOWN; DrawObj();
		}
		else if (CheckObj() == 0)
		{
			//坐标变化
			ClsObj(); ++pos.Y; DrawObj();
		}
	}
	else if (GetAsyncKeyState(cOp[3]) & 1)
	{
		if (nDir != RIGHT)
		{
			nDir = RIGHT; DrawObj();
		}
		else if (CheckObj() == 0)
		{
			//坐标变化
			ClsObj(); ++pos.X; DrawObj();
		}
	}
	else if (GetAsyncKeyState(cOp[4]) & 1)
	{
		Fire(); 
	}
}
//随机生成的位置合法返回true
bool CTank::IsValid()
{
	for (int y = pos.Y - 1; y < pos.Y + 2; ++y)
	{
		for (int x = pos.X - 1; x < pos.X + 2; ++x)
		{
			if (CMap::m_ArrMap[1][x][y] == BORDER || CMap::m_ArrMap[1][x][y] == WALL_BREAK
				|| CMap::m_ArrMap[1][x][y] == WALL_REFLECT || CMap::m_ArrMap[1][x][y] == RIVER)
			{
				return false;
			}
			if (CMap::m_ArrMap[0][x][y] == MTANK || CMap::m_ArrMap[0][x][y] == ETANK
				|| CMap::m_ArrMap[0][x][y] == MBOMB)
			{
				return false;
			}
		}
	}
	return true;
}

