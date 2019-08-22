#include <iostream>
#include <time.h>
#include "CBomb.h"
#include "CGame.h"
using std::cout;
void CBomb::DrawObj()
{
	//���ǲݵؾͻ�
	if (CMap::m_ArrMap[1][pos.X][pos.Y] != GRASS)
	{
		CGame::WriteChar(pos.X, pos.Y);
		cout <<m_shape[tag];
	}
	//д���ͼ����
	if (tag == 0 || tag == 1)
		CMap::m_ArrMap[0][pos.X][pos.Y] = MBOMB;
	else CMap::m_ArrMap[0][pos.X][pos.Y] = EBOMB;
}

void CBomb::ClsObj()
{
	int x = pos.X, y = pos.Y;
	CMap::m_ArrMap[0][x][y] = 0;
	if (CMap::m_ArrMap[1][x][y] == 0)
	{
		CGame::WriteChar(x, y); cout << "  ";
	}
	else if (CMap::m_ArrMap[1][x][y] == RIVER)
	{
		CGame::WriteChar(x, y); cout << "��";
	}
}
//�ɴ�͸����0���ı�m_exist
int CBomb::CheckObj()
{
	int nRes = 0;
	int nX = pos.X, nY = pos.Y;
	switch (CMap::m_ArrMap[1][nX][nY])
	{
	case WALL_BREAK:m_exist = false; 
		nRes = WALL_BREAK;
		CGame::WriteChar(nX, nY); cout << "  ";
		CMap::m_ArrMap[1][nX][nY] = 0;
		break;
	case BORDER:m_exist = false; nRes = BORDER;break;
	case WALL_REFLECT:m_exist = true; nRes = WALL_REFLECT;
		//����ı�
		if (nDir % 2 != 0) nDir -= 1;else nDir += 1;
		switch (nDir)	//�ӵ�����仯
		{
		case UP:--pos.Y; break;
		case DOWN:++pos.Y; break;
		case LEFT:--pos.X; break;
		case RIGHT:++pos.X; break;
		}break;
	case BASE:
		CGame::m_stop = -2;
		
		break;
	}
	switch (CMap::m_ArrMap[0][nX][nY])
	{
	case MTANK:nRes = MTANK; break;
	case ETANK:nRes = ETANK; break;
	case MBOMB:nRes = MBOMB; break;
	case EBOMB:nRes = EBOMB; break;
	default:break;
	}
	return nRes;
	
}

void CBomb::CollisionObj(int check)
{
	isMe = true;
	if (check == MTANK && tag >= 2)//�з������ҷ�̹��
	{
		ClsObj();
		m_exist = false;
		for (int i = 0; i < 2; ++i)
		{
			if (CGame::m_vecTank[i].tag<2)
			{
				if (*this == CGame::m_vecTank[i])
				{
					tag == 2 ? CGame::m_vecTank[i].m_blood-=2 : CGame::m_vecTank[i].m_blood--;//Ene1������Ϊ2 Ene2������1
					if (CGame::m_vecTank[i].m_blood <= 0)
					{//����
						CGame::m_vecTank[i].ClsObj();
						CGame::m_vecTank[i].m_revive--;
						CGame::m_vecTank[i].IniMyTank(i, 7, CGame::m_vecTank[i].m_revive, CGame::m_vecTank[i].m_score);
					}
				}
			}
		}
		if (CGame::m_vecTank[0].m_revive <=0&& CGame::m_vecTank[1].m_revive <= 0)
		{
			CGame::m_stop = -2;//��Ϸ����
		}
	}
	else if (check == ETANK && tag <=1)//�ҷ����ез�̹��
	{
		//�ӵ���ʧ
		ClsObj();
		m_exist = false;
	
		for (int i=1;i< CGame::m_vecTank.size();++i)
		{
			if (*this == CGame::m_vecTank[i])//�����ҵ���ײ��̹��
			{
				CGame::m_vecTank[i].tag == 2 ? CGame::m_vecTank[i].m_blood -= 2 : CGame::m_vecTank[i].m_blood -= 1;//Ene1�ı�����ÿ��-2 Ene2ÿ��-1
				
				if (CGame::m_vecTank[i].m_blood <= 0)
				{//�з�̹�˲�����
					//̹�˼ӷ�
					tag == 0 ? CGame::m_vecTank[0].m_score++ : CGame::m_vecTank[1].m_score++;
					CGame::m_vecTank[i].ClsObj();
					CGame::m_vecTank[i].m_revive--;
					//CGame::m_vecTank[i].IniMyTank(0, 15, CGame::m_vecTank[i].m_revive);
					break;
				}
			}
		}
		CGame::CheckGame();
		
	}
	else if ((check == MBOMB )|| (check == EBOMB ))//�ӵ���ײ����ʧ
	{
		for (int j = 0; j < CGame::m_vecBomb.size(); j++)
		{
			if (CGame::m_vecBomb[j].isMe == false && CGame::m_vecBomb[j].m_exist)
			{
				int nx = 0, ny = 0; CGame::m_vecBomb[j].GetPos(nx, ny);
				if (pos.X == nx&& pos.Y == ny)
				{
					m_exist = false;
					CGame::m_vecBomb[j].m_exist = false;
				}
			}
		}
	}
	isMe = false;
}

void CBomb::MoveObj()
{
	
	if (m_exist)//&& clock() - lastClock > interval)
	{
		//lastClock = clock();//���¿�ʼ��ʱ
		ClsObj();//���ԭ����

		switch (nDir)	//�ӵ�����仯
		{
		case UP:--pos.Y; break;
		case DOWN:++pos.Y; break;
		case LEFT:--pos.X; break;
		case RIGHT:++pos.X; break;
		}
		CollisionObj( CheckObj()) ;//�������仯���λ���Ƿ�Ϸ�
		if (m_exist)
			DrawObj();//�����ǰ�����ǲݵؾͻ��ݵ�
	}
}

void CBomb::GreateB(CTank& tank)
{
	CBomb tempB;
	//tempB.lastClock = clock();//�ӵ��ٶ�
	
	tank.GetPos(tempB.pos.X, tempB.pos.Y);
	tempB.nDir = tank.GetDir(); tempB.tag = tank.GetTag();
	//tempB.tag == 3 ? tempB.interval = 0 : tempB.interval = 100;
	switch (tempB.nDir)
	{
	case UP:tempB.pos.Y-=2; break;
	case DOWN:tempB.pos.Y+=2; break;
	case LEFT:tempB.pos.X-=2; break;
	case RIGHT:tempB.pos.X+=2; break;
	default:
		break;
	}
	tempB.CheckObj();
	if (tempB.m_exist)//��ⷢ��λ���Ƿ�Ϸ�,�Ϸ��ʹ���
	{
		CGame::m_vecBomb.push_back(tempB);
	}
}

bool CBomb::GetExist()const
{
	return m_exist;
}

void CBomb::GetPos(int& x, int& y) const
{
	x = pos.X; y = pos.Y;
}

int CBomb::GetTag() const
{
	return tag;
}

int CBomb::GetDir() const
{
	return nDir;
}

bool CBomb::operator==(CTank& tank)
{
	short nx = 0, ny = 0;
	tank.GetPos(nx, ny);
	if (tank.GetRevive())
	{
		for (int y=ny-1;y<ny+2;++y)
		{
			for (int x=nx-1;x<nx+2;++x)
			{
				if (pos.X==x&&pos.Y==y)
				{
					return true;
				}
			}
		}
		
	}
	return false;
}
