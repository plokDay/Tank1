#include <stdlib.h>
#include <iostream>
#include "CGame.h"
#include "Data.h"

using std::cout;
vector<CBomb> CGame::m_vecBomb;//��̬���ݳ�Ա�����������ⶨ��
vector<CTank> CGame::m_vecTank;
int CGame::m_stop = 1;

void CGame::CheckGame()
{
	bool isWin = true;
	for (int i = 1; i < CGame::m_vecTank.size(); ++i)//�����ж���û��Ӯ
	{
		if (CGame::m_vecTank[i].GetTag() > 1)
		{
			if (CGame::m_vecTank[i].GetRevive() > 0)
			{
				isWin=false;
			}
		}
		 
	}
	if (isWin)CGame::m_stop = 2;//��ʾӮ��
	
}


int CGame::Menu()
{
	CDraw::cls();
	//system("cls");
	int i = 0;//��ʱ�����������ƶ�̹��
	int nOp = 1;//��¼ѡ��
	CDraw::WriteChar(WEIGHT / 2, 31); cout << "����ģʽ";
	CDraw::WriteChar(WEIGHT / 2, 32); cout << "˫��ģʽ";
	CDraw::WriteChar(WEIGHT / 2, 33); cout << "�༭��ͼ";
	CDraw::WriteChar(WEIGHT / 2, 34);	cout << "��ȡ�浵";
	CDraw::WriteChar(WEIGHT / 2, 35);	cout << "�˳���Ϸ";
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
			CDraw::WriteChar(WEIGHT / 2, 35); cout << "�˳���Ϸ";
			CDraw::WriteChar(WEIGHT / 2, 31, 0, 7); cout << "����ģʽ";
			CDraw::WriteChar(WEIGHT / 2, 32); cout << "˫��ģʽ"; break;
		case 2:
			CDraw::WriteChar(WEIGHT / 2, 31); cout << "����ģʽ";
			CDraw::WriteChar(WEIGHT / 2, 32, 0, 7); cout << "˫��ģʽ";
			CDraw::WriteChar(WEIGHT / 2, 33); cout << "�༭��ͼ"; break;
		case 3:
			CDraw::WriteChar(WEIGHT / 2, 32); cout << "˫��ģʽ";
			CDraw::WriteChar(WEIGHT / 2, 33,0,7);cout << "�༭��ͼ";
			CDraw::WriteChar(WEIGHT / 2, 34); cout << "��ȡ�浵"; break;
		case 4:
			CDraw::WriteChar(WEIGHT / 2, 33); cout << "�༭��ͼ";
			CDraw::WriteChar(WEIGHT / 2, 34,0,7);cout << "��ȡ�浵";
			CDraw::WriteChar(WEIGHT / 2, 35); cout << "�˳���Ϸ"; break;
		case 5:
			CDraw::WriteChar(WEIGHT / 2, 34); cout << "��ȡ�浵";
			CDraw::WriteChar(WEIGHT / 2, 35, 0, 7); cout << "�˳���Ϸ";
			CDraw::WriteChar(WEIGHT / 2, 31); cout << "����ģʽ"; break;
		}
		CDraw::WriteChar(2, 2);//�ָ���ɫ
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
		
		if (m_stop == 2)//��Ϸ������һ��
		{
			vector<CBomb>().swap(m_vecBomb);//��ղ��ͷ��ڴ�
			vector<CTank>().swap(m_vecTank);//��ղ��ͷ��ڴ�
			m_level++;
			if (m_level > 3) break;//���ͨ�����һ�ؾ�����
			m_stop = 1;
			IniAll();
		}
		if (m_stop==1)
		{
			
			for (int i = 0; i < m_vecTank.size(); ++i)
			{
				if (m_vecTank[i].GetRevive()<=0)
				{
					m_vecTank.erase(m_vecTank.begin()+i);//ɾ����i��Ԫ��
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
					m_vecBomb.erase(m_vecBomb.begin() + i);//ɾ����i��Ԫ��
					continue;
				}
				m_vecBomb[i].DrawObj(m_map);
				m_vecBomb[i].MoveObj(m_map);
			}
			
		}
		PrintUI();
		if (m_stop==-2)
		{
			vector<CBomb>().swap(m_vecBomb);//��ղ��ͷ��ڴ�
			vector<CTank>().swap(m_vecTank);//��ղ��ͷ��ڴ�
			break;//��Ϸ����
		}
		
		if (GetAsyncKeyState(VK_RCONTROL) & 1)	//�ұߵ�CTRL�浵
		{
			m_stop = -1;
			SaveGame();
			CDraw::WriteChar(WEIGHT / 2+30, HEIGHT+2);
			cout << "����ɹ�";
			Sleep(50);
			CDraw::WriteChar(WEIGHT / 2 + 30, HEIGHT + 2);
			cout << "        ";
			
		}
		if (GetAsyncKeyState(VK_SPACE) & 1)	//�ո���ͣ
		{
			m_stop = -m_stop;
		}
		if (GetAsyncKeyState(VK_BACK) & 1)	//BACK�˳�
		{
			vector<CBomb>().swap(m_vecBomb);//��ղ��ͷ��ڴ�
			vector<CTank>().swap(m_vecTank);//��ղ��ͷ��ڴ�
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
		printf("ʧ��\n");

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
	memset(m_map.GetMap(), 0, 4 * 2 * HEIGHT*WEIGHT);//ע��Ҫ����
	FILE *pFile = nullptr;
	if (fopen_s(&pFile, "save", "rb+"))
		printf("ʧ��\n");
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
	cout << "SPACE��ͣ BACK�˳�  RCTRL�浵 ";
	CDraw::WriteChar(WEIGHT / 2-1, HEIGHT);
	cout << "Level"<<GetLevel();
	CDraw::WriteChar(WEIGHT / 2 - 25, HEIGHT+1);
	cout << "Blood:" << m_vecTank[0].GetBlood() << "   Revive:" << m_vecTank[0].GetRevive()<<
		"   Score:"<< m_vecTank[0].GetScore();
}

