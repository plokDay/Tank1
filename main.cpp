#pragma comment(lib, "winmm")
#include <stdlib.h>
#include <time.h>
#include "CGame.h"

int main(void)
{
	SetConsoleTitle("̹�˴�ս");
	system("mode con cols=150 lines=45");
	
	srand((unsigned)time(NULL));
	CGame mGame;
	while (1)
	{
		switch (mGame.Menu(mGame.m_backSound,mGame.m_text))
		{
		case 1://����
			
			mGame.SetDouble(0);
			mGame.IniAll();
			mGame.StartGame();
			break;
		break;
		case 2://˫��
			
			mGame.SetDouble(2);
			mGame.IniAll();
			mGame.StartGame();
			break;
		case 3://�༭��ͼ
		{
			int nlev = 1;//��ʱ������������¼��ͼ�ؿ�
			while (1)
			{
				PlaySound("paint.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
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

	return 0;
}