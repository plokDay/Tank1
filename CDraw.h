#pragma once

class CDraw
{
public:

	//************************************
	// Function:  ����ƶ���ָ��λ�ô�ӡ
	// Parameter: int x X����
	// Parameter: int y Y����
	// Parameter: int foreColor ǰ��ɫ
	// Parameter: int backcolor ����ɫ
	// Returns:   void
	//************************************
	static void WriteChar(int x, int y, int foreColor=15, int backcolor=0);
	static void set();
	static bool cls(); //��̷�ʽʵ�������Ļ
	

};