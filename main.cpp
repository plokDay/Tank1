#include <stdlib.h>
#include <time.h>
#include "CGame.h"


//bug2 Ҫ��֤��һ����ʱ����
//bug3 ����ģʽ����
//�������г�����
//Ene1������Ϊ2 Ene1ÿ��-2 �ܶ��ӵ� �ٶȿ� ������֮��ֹͣ��ת��
//Ene2������1 Ene2ÿ��-1 �ܹ��� �ٶ��� ������֮��ֹͣ��ת��
int main(void)
{
	SetConsoleTitle("̹�˴�ս");
	system("mode con cols=150 lines=45");
	
	srand((unsigned)time(NULL));
	CGame mGame;
	while (1)
	{
		switch (mGame.Menu())
		{
		case 1://����
			mGame.SetDouble(0);
			mGame.IniAll();
			mGame.StartGame();
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
	mGame.Menu();//��Ϸ����֮�����˵�
	return 0;
}