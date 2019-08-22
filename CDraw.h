#pragma once

class CDraw
{
public:

	//************************************
	// Function:  光标移动到指定位置打印
	// Parameter: int x X坐标
	// Parameter: int y Y坐标
	// Parameter: int foreColor 前景色
	// Parameter: int backcolor 背景色
	// Returns:   void
	//************************************
	static void WriteChar(int x, int y, int foreColor=15, int backcolor=0);
	static void set();
	static bool cls(); //编程方式实现清除屏幕
	

};