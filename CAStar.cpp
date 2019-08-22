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
	//�Ƿ��ʼ�����
	if (!m_bInitCoordInfo || !m_bInitMapInfo)
	{
		return false;
	}
	/*
	1.  ��������걣�浽Open����
	2.1 �ж�Open���Ƿ�Ϊ�գ�����˵����·��ͬ
	2.2 �ҳ�Open����Fֵ��С�ĵ�
	2.3 ������ɢ
	2.4 ����ɢ�ĵ㱣�浽Close���У���Open����ɾ��
	2.5 �ж�����ɢ�����ĵ��Ƿ�ϸ�
	2.5.1 �Ƿ����յ㣬�Ǿ�ֱ�ӷ���
	�ǲ����ϰ���
	�ǲ���Խ��
	�Ƿ���Open����
	�Ƿ���Close����
	2.6 �Ѻϸ�ĵ���Open����
	2.7 �ظ�2.1 -- 2.6
	*/

	//���Open��Close��
	m_Open.clear();
	m_Close.clear();

	ZeroMemory(m_pVir, m_MapWidth*m_MapHigh);



	NODE_INFO nodeStar;
	nodeStar.codSelf = m_Start;
	nodeStar.g = 0;
	nodeStar.SetH_F(m_Start, m_End);

	m_Open.push_back(nodeStar);

	//��ʼѭ������

	while (true)
	{
		//Open���Ƿ�Ϊ��
		if (m_Open.empty())
		{
			return false;
		}
		//��Open����Fֵ��С�ĵ�
		int nIndex = 0;
		for (int i = 1; i < m_Open.size(); i++)
		{
			//�����ǰ��nIndex���� i�� ����
			if (m_Open[nIndex].f > m_Open[i].f)
			{
				nIndex = i;
			}
		}

		//����������С�ĵ���ɢ
		//��ɢ
		NODE_INFO nodeNew[4]{};

		//��
		nodeNew[0].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[0].codSelf.Y = m_Open[nIndex].codSelf.Y - 1;
		//��
		nodeNew[1].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[1].codSelf.Y = m_Open[nIndex].codSelf.Y + 1;
		//��
		nodeNew[2].codSelf.X = m_Open[nIndex].codSelf.X - 1;
		nodeNew[2].codSelf.Y = m_Open[nIndex].codSelf.Y;
		//��
		nodeNew[3].codSelf.X = m_Open[nIndex].codSelf.X + 1;
		nodeNew[3].codSelf.Y = m_Open[nIndex].codSelf.Y;

		for (int i = 0; i < 4; i++)
		{
			nodeNew[i].codParent = m_Open[nIndex].codSelf;
			nodeNew[i].g = m_Open[nIndex].g + 1;
			nodeNew[i].SetH_F(nodeNew[i].codSelf, m_End);
			//����
			nodeNew[i].codSelf.d = i;
		}
		//=====�Ż�����==================================================================================



		int x1 = m_Open[nIndex].codSelf.X;
		int y1 = m_Open[nIndex].codSelf.Y;
		m_pVir[y1 * m_MapWidth + x1].isClose = true;
		m_pVir[y1 * m_MapWidth + x1].isOpen = false;

		//����ɢ���ĵ㱣�浽Close��������Open����ɾ��
		m_Close.push_back(m_Open[nIndex]);
		m_Open.erase(m_Open.begin() + nIndex);

		//�����ɢ�����ĵ��Ƿ�ϸ��Ƿ����յ�
		for (int i = 0; i < 4; i++)
		{
			int x = nodeNew[i].codSelf.X;
			int y = nodeNew[i].codSelf.Y;

			//�ǲ����յ�
			if (nodeNew[i].codSelf == m_End)
			{
				m_Close.push_back(nodeNew[i]);
				return true;
			}
			//�Ƿ�Խ��
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


			//=====�Ż�����==================================================================================




			//�ж��Ƿ���Open����Close����
			if (m_pVir[y * m_MapWidth + x].isClose ||
				m_pVir[y * m_MapWidth + x].isOpen)
			{
				continue;
			}

			

			//���ϸ�ĵ㱣�浽Open����
			m_Open.push_back(nodeNew[i]);

			m_pVir[y * m_MapWidth + x].isOpen = true;

		}

	}
}

void CAStar::GetPath()
{
	//���ݸ��ڵ�
	m_Path.clear();//���ԭ����·��
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

