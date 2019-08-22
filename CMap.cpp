#include <iostream>
#include "CMap.h"

#include "Data.h"
#include "CGame.h"
using std::cout;

//CMap& CMap::GetMap() const
//{
//	//return m_ArrMap;
//}
int CMap::m_ArrMap[2][WEIGHT][HEIGHT] = {0};
void CMap::setMap(int nZ, int nX, int nY,int val)
{
	m_ArrMap[nZ ][nX][nY] = val;
}

void CMap::DrawMap()
{
	CGame::WriteChar(WEIGHT / 2 - 1, HEIGHT - 4); cout << "������";
	CGame::WriteChar(WEIGHT / 2 - 1, HEIGHT - 3); cout << "������";
	CGame::WriteChar(WEIGHT / 2 - 1, HEIGHT - 2); cout << "������";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_ArrMap[1][WEIGHT / 2 - 1 + i][HEIGHT - 4 + j] = BASE;
		}
	}
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WEIGHT; ++x)
		{
			/*if (m_ArrMap[0][x][y] == MBOMB|| m_ArrMap[0][x][y] == EBOMB)
			{
				CDraw::WriteChar(x, y); cout << "��";
			}*/
			switch ((m_ArrMap[1][x][y]))
			{
			case BORDER:CGame::WriteChar(x, y); cout << "�~"; break;
			case WALL_BREAK:CGame::WriteChar(x, y); cout << "��"; break;
			case WALL_REFLECT:CGame::WriteChar(x, y); cout << "��"; break;
			case GRASS:CGame::WriteChar(x, y); cout << "��"; break;
			case RIVER:CGame::WriteChar(x, y); cout << "��"; break;
			default:
				break;
			}
		}
	}

}

void CMap::SaveMap(const char* name)
{
	FILE *pFile = nullptr;
	//1.��
	if (fopen_s(&pFile, name, "wb+"))
		printf("ʧ��\n");
	//д��
	fwrite(m_ArrMap, sizeof(m_ArrMap),1, pFile);
	//3.�ر�
	fclose(pFile);
}

void CMap::ReadMap(const char* name)
{
	memset(m_ArrMap, 0, sizeof(m_ArrMap));//ע��Ҫ����
	FILE *pFile = nullptr;

	//1.��
	if (fopen_s(&pFile, name, "rb+"))
		printf("ʧ��\n");
	//д��

	fread(m_ArrMap, sizeof(m_ArrMap),1, pFile);
	//3.�ر�
	fclose(pFile);
}

bool CMap::EditMap(int& lev,CGame* game)
{
	system("cls");
	CGame::set();
	char name[10] = { 0 };
	strcpy_s(name, 10, game->GetMapName(lev - 1));

	ReadMap(name);
	DrawMap();
	CGame::WriteChar(5, HEIGHT+1);  cout << "Press 'B': ��ǽ";
	CGame::WriteChar(15, HEIGHT+1); cout << "Press 'S': ��ǽ";
	CGame::WriteChar(25, HEIGHT+1); cout << "Press 'F': ����ǽ";
	CGame::WriteChar(38, HEIGHT+1); cout << "Press 'R': ����";
	CGame::WriteChar(47, HEIGHT+1); cout << "Press 'G': �ݵ�";
	CGame::WriteChar(5, HEIGHT + 2); cout << "Right Click: ���հ�";
	CGame::WriteChar(25, HEIGHT+2); cout << "Press 'BACK': ȡ�����˳�";
	CGame::WriteChar(40, HEIGHT+2); cout << "Press 'RCTRL': ���沢Ӧ��";
	CGame::WriteChar(WEIGHT/2-3, HEIGHT+3); cout << name;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ir = {};
	DWORD dw = 0;

	while (1)
	{
		ReadConsoleInput(hInput, &ir, 1, &dw);
		if (ir.EventType == MOUSE_EVENT)
		{
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;

				if (GetAsyncKeyState('B'))
				{
					CGame::WriteChar(pos.X / 2, pos.Y); cout << "��";
					m_ArrMap[1][pos.X / 2][pos.Y] = WALL_BREAK;
				}
				if (GetAsyncKeyState('S'))
				{
					CGame::WriteChar(pos.X / 2, pos.Y); cout << "�~";
					m_ArrMap[1][pos.X / 2][pos.Y] = BORDER;
				}
				if (GetAsyncKeyState('F'))
				{
					CGame::WriteChar(pos.X / 2, pos.Y); cout << "��";
					m_ArrMap[1][pos.X / 2][pos.Y] = WALL_REFLECT;
				}
				if (GetAsyncKeyState('R'))
				{
					CGame::WriteChar(pos.X / 2, pos.Y); cout << "��";
					m_ArrMap[1][pos.X / 2][pos.Y] = RIVER;
				}
				if (GetAsyncKeyState('G'))
				{
					CGame::WriteChar(pos.X / 2, pos.Y); cout << "��";
					m_ArrMap[1][pos.X / 2][pos.Y] = GRASS;
				}
			}
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				CGame::WriteChar(pos.X / 2, pos.Y); cout << "  ";
				m_ArrMap[1][pos.X / 2][pos.Y] = 0;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT) & 1)
		{
			if (lev == 3)lev = 0;
			++lev; break;
		}

		if (GetAsyncKeyState(VK_LEFT) & 1)
		{
			if (lev == 1)lev = 4;
			--lev; break;
		}

		//Backȡ�����˳�
		if (GetAsyncKeyState(VK_BACK) & 1)
		{
			return false;
		}

		//�ұߵ�CTRL���沢Ӧ��
		if (GetAsyncKeyState(VK_RCONTROL) & 1)
		{
			//�������
			SaveMap(name);
			CGame::WriteChar(WEIGHT/2+10, HEIGHT+3); cout << "Ӧ�óɹ�";
			return false;
		}
	}
	return true;


}

int* CMap::GetMap() const
{
	return (int*)m_ArrMap;
}
