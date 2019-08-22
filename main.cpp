#include <stdlib.h>
#include <time.h>
#include "CGame.h"


//bug2 要保证第一炮随时打响
//bug3 单人模式闪退
//第三关有出生点
//Ene1攻击力为2 Ene1每次-2 能躲子弹 速度快 发射完之后停止或转向
//Ene2攻击力1 Ene2每次-1 能过河 速度慢 发射完之后停止或转向
int main(void)
{
	SetConsoleTitle("坦克大战");
	system("mode con cols=150 lines=45");
	
	srand((unsigned)time(NULL));
	CGame mGame;
	while (1)
	{
		switch (mGame.Menu())
		{
		case 1://单人
			mGame.SetDouble(0);
			mGame.IniAll();
			mGame.StartGame();
		break;
		case 2://双人
			mGame.SetDouble(2);
			mGame.IniAll();
			mGame.StartGame();
			break;
		case 3://编辑地图
		{
			int nlev = 1;//临时变量，用来记录地图关卡
			while (1)
			{
				if (mGame.GetMap().EditMap(nlev,&mGame) == false)
					break;
			}
		}
			break;
		case 4:
			mGame.ReadGame();
			
			mGame.StartGame();
			break;
		case 5:
			exit(0);
		}
	}
	mGame.Menu();//游戏结束之后进入菜单
	return 0;
}