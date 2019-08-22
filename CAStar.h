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
		int d; //����̹�˵��ƶ�����
	}MY_MYCOORD, *PMY_MYCOORD;


	//�ڵ�Ľṹ
	typedef struct _NODE_INFO
	{
		int g; //�ƶ����
		int h; //���յ���̾���
		int f; //g+h
		MY_MYCOORD codSelf;  //��������
		MY_MYCOORD codParent;//���ڵ����꣨��˭��ɢ�ģ�
						   //NODE_INFO privor;
		void SetH_F(MYCOORD cod1, MYCOORD cod2)
		{
			h = abs(cod1.X - cod2.X) + abs(cod1.Y - cod2.Y);
			f = g + h;
		}

	}NODE_INFO, *PNODE_INFO;
	MYCOORD m_Start; //�������
	MYCOORD m_End;   //�յ�����

	vector<NODE_INFO> m_Open;  //����ɢ�ĵ�
	vector<NODE_INFO> m_Close; //��ɢ���ĵ�
	vector<MY_MYCOORD>  m_Path;  //���·��

	int* m_pMap;      //��ͼ���׵�ַ
	int  m_MapHigh;   //��ͼ�ĳ�
	int  m_MapWidth;  //��ͼ�Ŀ�

	int m_Block = 10;      //�ϰ���
					  /*
					  1 2 3
					  4 5 6
					  7 8 9
					  */
	bool m_bInitMapInfo;    //�Ƿ��ʼ����ͼ��Ϣ
	bool m_bInitCoordInfo;  //�Ƿ��ʼ����ʼ������Ϣ


	void InitMapInfo(int* pMap, int nHigh, int nWidth, int nBlock);
	void InitCoord(MYCOORD codStar, MYCOORD codEnd);

	bool FindPath(CMap& map); //���Ұ������·���ĵ㣨�õ�Close��
	void GetPath();  //��ȡ���·��
	typedef struct _VIR_INFO
	{
		char isOpen : 1; //���Ƿ���Open����
		char isClose : 1; //��ʾ�Ƿ���CLose����
		char rcieve : 6; //����
	}VIR_INFO, *PVIR_INFO;

	static PVIR_INFO m_pVir; //ָ�������ͼ���׵�ַ
	void PrintPath();
};