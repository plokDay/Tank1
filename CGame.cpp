#include <stdlib.h>
#include <iostream>
#include "CGame.h"
#include "Data.h"

using std::cout;
vector<CBomb> CGame::m_vecBomb;//静态数据成员类内声明类外定义
vector<CTank> CGame::m_vecTank;
int CGame::m_stop = 1;

void CGame::CheckGame()
{
	bool isWin = true;
	for (int i = 1; i < CGame::m_vecTank.size(); ++i)//遍历判断有没有赢
	{
		if (CGame::m_vecTank[i].GetTag() > 1)
		{
			if (CGame::m_vecTank[i].GetRevive() > 0)
			{
				isWin=false;
			}
		}
		 
	}
	if (isWin)CGame::m_stop = 2;//表示赢了
	
}


int CGame::Menu()
{
	CDraw::cls();
	//system("cls");
	int i = 0;//临时变量，用来移动坦克
	int nOp = 1;//记录选项
	CDraw::WriteChar(WEIGHT / 2, 31); cout << "单人模式";
	CDraw::WriteChar(WEIGHT / 2, 32); cout << "双人模式";
	CDraw::WriteChar(WEIGHT / 2, 33); cout << "编辑地图";
	CDraw::WriteChar(WEIGHT / 2, 34);	cout << "读取存档";
	CDraw::WriteChar(WEIGHT / 2, 35);	cout << "退出游戏";
	while (1)
	{
		if (i == WEIGHT - 1)
		{
			i = 0;
		}
		
		CDraw::WriteChar(i++, 3, 7, 0);cout<<("                           @@@                                                                 ");
		CDraw::WriteChar(i, 4, 7, 0);  cout<<("                        @#####@                                                               ");
		CDraw::WriteChar(i, 5, 7, 0);  cout << ("                   @#############@##@                                                  ");
		CDraw::WriteChar(i, 6, 7, 0);  cout << ("                 @###############@@######@                                               ");
		CDraw::WriteChar(i, 7, 7, 0);  cout << ("                @################@@@########@                                             ");
		CDraw::WriteChar(i, 8, 7, 0);  cout << ("                       @#########@@##################################################@    ");
		CDraw::WriteChar(i, 9, 7, 0);  cout << ("                       @@@@@@######@#######@                                             ");
		CDraw::WriteChar(i, 10, 7, 0); cout << ("      @@@@@@@@@@@@@@@@@#####################@@@@@@@                                        ");
		CDraw::WriteChar(i, 11, 7, 0); cout << ("    @##############################################@@@@@                                 ");
		CDraw::WriteChar(i, 12, 7, 0); cout << ("    @###################################################@@@@@@@@@@                                 ");
		CDraw::WriteChar(i, 13, 7, 0); cout << ("    @##############################################################@                                 ");
		CDraw::WriteChar(i, 14, 7, 0); cout << ("      @##############################################################@                    ");
		CDraw::WriteChar(i, 15, 7, 0); cout << ("      @###############################################################@                    ");
		CDraw::WriteChar(i, 16, 7, 0); cout << ("      @########     @##@    @##@      @##@     @###@    @##@    ######@              ");
		CDraw::WriteChar(i, 17, 7, 0); cout << ("       @######    @#####@ @######@  @######@  @#####@ @#######@   ###@                     ");
		CDraw::WriteChar(i, 18, 7, 0); cout << ("          @####     @##@    @##@      @##@     @###@    @##@    ####@                       ");
		CDraw::WriteChar(i, 19, 7, 0); cout << ("              @###############################################%@                          ");
	
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			if (nOp==5)nOp = 0;
			++nOp;
		}
		if (GetAsyncKeyState(VK_UP) & 1) 
		{ 
			if (nOp==1)nOp = 6;
			--nOp;
		}
		
		switch (nOp)
		{
		case 1:
			CDraw::WriteChar(WEIGHT / 2, 35); cout << "退出游戏";
			CDraw::WriteChar(WEIGHT / 2, 31, 0, 7); cout << "单人模式";
			CDraw::WriteChar(WEIGHT / 2, 32); cout << "双人模式"; break;
		case 2:
			CDraw::WriteChar(WEIGHT / 2, 31); cout << "单人模式";
			CDraw::WriteChar(WEIGHT / 2, 32, 0, 7); cout << "双人模式";
			CDraw::WriteChar(WEIGHT / 2, 33); cout << "编辑地图"; break;
		case 3:
			CDraw::WriteChar(WEIGHT / 2, 32); cout << "双人模式";
			CDraw::WriteChar(WEIGHT / 2, 33,0,7);cout << "编辑地图";
			CDraw::WriteChar(WEIGHT / 2, 34); cout << "读取存档"; break;
		case 4:
			CDraw::WriteChar(WEIGHT / 2, 33); cout << "编辑地图";
			CDraw::WriteChar(WEIGHT / 2, 34,0,7);cout << "读取存档";
			CDraw::WriteChar(WEIGHT / 2, 35); cout << "退出游戏"; break;
		case 5:
			CDraw::WriteChar(WEIGHT / 2, 34); cout << "读取存档";
			CDraw::WriteChar(WEIGHT / 2, 35, 0, 7); cout << "退出游戏";
			CDraw::WriteChar(WEIGHT / 2, 31); cout << "单人模式"; break;
		}
		CDraw::WriteChar(2, 2);//恢复颜色
		if (GetAsyncKeyState(VK_RETURN) & 1)
		{
			if (nOp>=1&&nOp<=5)
			{
				break;
			}
		}

		Sleep(90);
	}
	return nOp;
}
void CGame::IniAll()
{
	
	m_map.ReadMap(m_mapNamelev[m_level-1]);
	
	CTank tempTank;
	tempTank.IniMyTank(0, 15, 2,0);
	m_vecTank.push_back(tempTank);
	tempTank.IniMyTank(1, 15, m_isDouble,0);
	m_vecTank.push_back(tempTank);
	tempTank.IniEne(m_map, 2);
	m_vecTank.push_back(tempTank);
	tempTank.IniEne(m_map, 3);
	m_vecTank.push_back(tempTank);
}

void CGame::StartGame()
{
	CDraw::cls();
	//system("cls");
	m_map.DrawMap();
	
	while (1)
	{
		
		if (m_stop == 2)//游戏进入下一关
		{
			vector<CBomb>().swap(m_vecBomb);//清空并释放内存
			vector<CTank>().swap(m_vecTank);//清空并释放内存
			m_level++;
			if (m_level > 3) break;//如果通过最后一关就跳出
			m_stop = 1;
			IniAll();
		}
		if (m_stop==1)
		{
			
			for (int i = 0; i < m_vecTank.size(); ++i)
			{
				if (m_vecTank[i].GetRevive()<=0)
				{
					m_vecTank.erase(m_vecTank.begin()+i);//删除第i个元素
					continue;
				}
				m_vecTank[i].DrawObj(m_map);
				m_vecTank[i].MoveObj(m_map);
			}
			for (int i = 0; i < m_vecBomb.size(); ++i)
			{
				if (m_vecBomb[i].GetExist() == 0)
				{
					m_vecBomb[i].ClsObj(m_map);
					m_vecBomb.erase(m_vecBomb.begin() + i);//删除第i个元素
					continue;
				}
				m_vecBomb[i].DrawObj(m_map);
				m_vecBomb[i].MoveObj(m_map);
			}
			
		}
		PrintUI();
		if (m_stop==-2)
		{
			vector<CBomb>().swap(m_vecBomb);//清空并释放内存
			vector<CTank>().swap(m_vecTank);//清空并释放内存
			break;//游戏结束
		}
		
		if (GetAsyncKeyState(VK_RCONTROL) & 1)	//右边的CTRL存档
		{
			m_stop = -1;
			SaveGame();
			CDraw::WriteChar(WEIGHT / 2+30, HEIGHT+2);
			cout << "保存成功";
			Sleep(50);
			CDraw::WriteChar(WEIGHT / 2 + 30, HEIGHT + 2);
			cout << "        ";
			
		}
		if (GetAsyncKeyState(VK_SPACE) & 1)	//空格暂停
		{
			m_stop = -m_stop;
		}
		if (GetAsyncKeyState(VK_BACK) & 1)	//BACK退出
		{
			vector<CBomb>().swap(m_vecBomb);//清空并释放内存
			vector<CTank>().swap(m_vecTank);//清空并释放内存
			m_level = 1;
			break;
		}
		Sleep(30);
	}
}

void CGame::SetDouble(int n)
{
	m_isDouble = n;
}

void CGame::SetOld()
{
	m_isOld = true;
}


CMap& CGame::GetMap() 
{
	return m_map;
}

int CGame::GetLevel() const
{
	return m_level;
}

void CGame::SaveGame() const
{
	FILE *pFile = nullptr;
	if (fopen_s(&pFile, "save", "wb+"))
		printf("失败\n");

	fwrite(m_map.GetMap(), 4 * 2 * HEIGHT*WEIGHT, 1, pFile);
	fprintf_s(pFile, "%d\n", m_stop);
	fprintf_s(pFile, "%d\n", m_level);
	fprintf_s(pFile, "%d\n", m_isDouble);
	fprintf_s(pFile, "%d\n", m_vecTank.size());
	fprintf_s(pFile, "%d\n", m_vecBomb.size());
	for (auto& val : m_vecTank)
	{
		fwrite(&val, sizeof(CTank), 1, pFile);
	}
	for (auto& val : m_vecBomb)
	{
		fwrite(&val, sizeof(CBomb), 1, pFile);
	}
	fclose(pFile);
}

void CGame::ReadGame()
{
	int tankCount = 0, bombCount = 0;
	CTank tempTank;
	CBomb tempBomb;
	memset(m_map.GetMap(), 0, 4 * 2 * HEIGHT*WEIGHT);//注意要清零
	FILE *pFile = nullptr;
	if (fopen_s(&pFile, "save", "rb+"))
		printf("失败\n");
	fread(m_map.GetMap(), 4 * 2 * HEIGHT*WEIGHT, 1, pFile);
	fscanf_s(pFile, "%d\n", &m_stop);
	fscanf_s(pFile, "%d\n",&m_level);
	fscanf_s(pFile, "%d\n", &m_isDouble);
	fscanf_s(pFile, "%d\n", &tankCount);
	fscanf_s(pFile, "%d\n", &bombCount);
	for (int i=0;i< tankCount;++i)
	{
		fread(&tempTank, sizeof(CTank), 1, pFile);
		m_vecTank.push_back(tempTank);
	}
	for (int i = 0; i < bombCount; ++i)
	{
		fread(&tempBomb, sizeof(CBomb), 1, pFile);
		m_vecBomb.push_back(tempBomb);
	}
	
	fclose(pFile);
}

const char* CGame::GetMapName(int index) 
{
	return m_mapNamelev[index];
}

void CGame::PrintUI() const
{
	CDraw::WriteChar(5, HEIGHT );
	cout << "--------\n             W   \n          A  X  D\n             S   \n          --------";
	if (m_isDouble==2)
	{
		CDraw::WriteChar(WEIGHT - 9, HEIGHT);cout << "--------"; 
		CDraw::WriteChar(WEIGHT - 9, HEIGHT+1);   cout << "   I   ";
		CDraw::WriteChar(WEIGHT - 9, HEIGHT + 2); cout << "J  M  L";
		CDraw::WriteChar(WEIGHT - 9, HEIGHT + 3); cout << "   K   ";
		CDraw::WriteChar(WEIGHT - 9, HEIGHT+4); cout << "--------";
		CDraw::WriteChar(WEIGHT / 2 + 10, HEIGHT + 1);
		cout << "Blood:" << m_vecTank[1].GetBlood() << "   Revive:" << m_vecTank[1].GetRevive() <<
			"   Score:" << m_vecTank[1].GetScore();
	}
	CDraw::WriteChar(WEIGHT/2-7, HEIGHT + 2);
	cout << "SPACE暂停 BACK退出  RCTRL存档 ";
	CDraw::WriteChar(WEIGHT / 2-1, HEIGHT);
	cout << "Level"<<GetLevel();
	CDraw::WriteChar(WEIGHT / 2 - 25, HEIGHT+1);
	cout << "Blood:" << m_vecTank[0].GetBlood() << "   Revive:" << m_vecTank[0].GetRevive()<<
		"   Score:"<< m_vecTank[0].GetScore();
}

