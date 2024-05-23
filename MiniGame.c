#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "GameUtility.h"//GameUtility ����Ǿ� ����.
//�Ű����� ����, ���߿� ���̵� ������ ����� ����
#define Easy 3
#define Normal 6
#define Hard 9
#define Max_X 70//GatData���ӿ��� x������ ������ ����
//
//�������� ���� ����
// 
//GetData�� ����������
typedef struct ObjectCoord//������Ʈ ��ǥ�� �����ص� ��Ʈ����
{
	int x;//x��
	int y;//y��
	int speed;//�ӵ�
}ObjectCoord;
int FindDupli[8];//��ǥ�� �Ҵ� �������� �ߺ� ������ üũ���ִ� �迭
//

void PWMiniGameLevel1(int);//���� ������ 1�ܰ��� �� �̴ϰ���. DIfficult�� ���̵�, �õ� Ƚ���� ������. 
void GetDataLevel1(int);//�������� �����͸� ���������� �ݴ� ����
void ControlObjMove(ObjectCoord*, int, ObjectCoord, int*);//������Ʈ���� ���� ��ġ ��Ʈ��
void ControlGoldMove(ObjectCoord*, int, char*, ObjectCoord, char*);//���������Ʈ���� ��ġ ��Ʈ��
void PlayerMoveControl(ObjectCoord*);//�÷��̾� ��ġ ��Ʈ��
void MemoryReturnMiniGameLevel1(int);//���� ������ �ܾ� ������ ������, �̸� �����ϵ��� ����� ��. �迭�� �ڼ����ٴ� ����. 
void Quiz(int);//��� ������ ���� ���Ϸ� ������ ���̹Ƿ�, �Ű������� �� �����س��� ��. 
void ClickMiniGameLevel1(int);//�ܼ��� ������ Ŭ���ϴ� �̴ϰ���. 

int main()
{
	srand((unsigned)time(NULL)); 
	GetDataLevel1(3);
	printf("��");
	Sleep(2000);
	return 0; 
}
void PWMiniGameLevel1(int Difficult)
{
	srand((unsigned)time(NULL));
	char word[10];
	char input[10];
	int TryLimit, i;//�ݺ��� ����� ����, TryLimit�� ��й�ȣ ����
	TryLimit = Difficult;
//��й�ȣ ����
	for (i = 0; i < 9; i++)
	{
		word[i] = 'a' + rand() % 25;
	}
	word[i] = '\0';
//��й�ȣ ����
//
	for (; TryLimit > 0; TryLimit--)//���̵��� ���� �־����� Ƚ����ŭ ����
	{
		printf("----------------------------------------------------------\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|           ��й�ȣ: %s                           |\n", word);
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("----------------------------------------------------------\n");
		Sleep(2000);
		system("cls");
		//
		//��й�ȣ �Է� �޴� ������
		printf("----------------------------------------------------------\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|    ��й�ȣ�� �Է��ϼ���                                |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("----------------------------------------------------------\n");
		printf(":");
		gets_s(input, 10);//���߿� ���� ����Ʈ�� �ٲٱ�. 
		///
		///����, ���� ���� �ǰ���
		if (!(strcmp(word, input)))
		{
			printf("�����Դϴ�.");
			//hp���� ����� Ư�� �� �ڸ�
			// //������ ����
		}
		else
		{
			if (TryLimit-1)//�õ� Ƚ�� �����ִ��� Ȯ��
			{
				printf("Ʋ�Ƚ��ϴ�. ��ȸ�� %d���Դϴ�", TryLimit-1);//Ʋ���� �ٽ� �ݺ�
				Sleep(2000);
				system("cls");
			}
			else
			{
				printf("��ȸ�� ��� �����ϼ̽��ϴ�. ������� �޽��ϴ�");
				//����� �ڵ�
			}
		}
	}
}
void GetDataLevel1(int Difficult)//���� ����� [����], ����� �迭�� �ݴ� ����. 
{
	int GameHp = 3;//�̴ϰ��� hp
	char LostData[8] = " [Gold]"; //������ ���ڿ�
	char GetData[7] = {0,};//������ ���ڿ� ����Ǵ� �迭
	float GameOverCount = 15;//���ӿ� �־����� �ð�
	int IsFullCollect = 0;//���� ��Ҵ��� Ȯ���ϴ� ����. 
	ObjectCoord D[3];//������Ʈ ��ǥ�� �����ϴ� ���丮��
	ObjectCoord B[5];
	ObjectCoord P1 = { 0, 29, 3};
	int i, j; //�ݺ��� ����� ����
	for (i = 0; i < 5; i++)//��ֹ� ��ġ�� �ߺ� ���Բ� ������ִ� �Լ�
	{
		FindDupli[i] = rand() % Max_X;
		for (j = 0; j < 5; j++)
		{
			if (FindDupli[i] == FindDupli[j])//���� �ߺ��� �ִٸ� �ٸ��� ��������
			{
				FindDupli[i] = rand() % Max_X;
				continue;
			}
		}
	}
	for (i = 5; i < 8; i++)//���� ��ġ�� �ߺ� ���Բ� ������ִ� �Լ�
	{
		FindDupli[i] = rand() % Max_X;
		for (j = 0; j < 8; j++)
		{
			if ( abs(FindDupli[i] - FindDupli[j]) < 3 )//���� 3ĭ �̳��� ��ֹ��̳� �ٸ� ������ �ִٸ�
			{
				FindDupli[i] = rand() % Max_X;//�ٽ� ������
				continue;
			}
		}
	}
//������ �Ҵ�
	for (i = 0; i < 5; i++) {
		B[i].x = FindDupli[i];
		B[i].speed = rand() % 10 + 1;
		B[i].y = 0;
	}
	for (i = 0; i < 3; i++)
	{
		D[i].x = FindDupli[5+i];
		D[i].y = 0;
		D[i].speed = rand() % 10 + 1;
	}
//��
	while (1)
	{
		system("cls");
		if (_kbhit())
		{
			PlayerMoveControl(&P1);
		}
		for (i = 0; i < 5; i++) {
			ControlObjMove(&B[i], i, P1, &GameHp);
		}
		for (i = 0; i < 3; i++)
		{
			if (D[i].speed != -1)
			{
				ControlGoldMove(&D[i], 2*i, LostData, P1, GetData);
			}
		}
		if (GameHp <= 0 || GameOverCount <= 0)//���� ���� �ڵ�
		{
			break;
		}
		if (_kbhit())
		{
			PlayerMoveControl(&P1);
		}
		for (i = 0; i < 30; i++)
		{
			gotoxy(Max_X + 10, i);
			printf("|");
		}
		gotoxy(Max_X + 13, 5);
		printf("�������� �����͸� �ֿ켼��!");
		gotoxy(Max_X + 13, 8);
		printf("���� ü�� : %d", GameHp);
		gotoxy(Max_X + 13, 12);
		printf("���ݱ��� �ֿ� �迭 : ");
		for (i = 0; i < 7; i++)
		{
			printf("%c", GetData[i]);
			if (GetData[i] == LostData[i + 1])
			{
				IsFullCollect += 1;
			}
		}
		if (IsFullCollect >= 6)
		{
			break;
		}
		IsFullCollect = 0;
		gotoxy(Max_X + 13, 15);
		printf("���� �ð� : %.f", GameOverCount);
		gotoxy(P1.x, P1.y);
		for (i = 0; i < 4; i++)
		{
			if (_kbhit())
			{
				PlayerMoveControl(&P1);
			}
			Sleep(50);
		}
		if (_kbhit())//�÷��̾� ��ġ�� ��� üũ���ָ鼭 ������ �ؼ�
		{
			PlayerMoveControl(&P1);
		}
		GameOverCount -= 0.2f;
		
	}//���� �ڵ�
	system("cls");
	IsFullCollect = 0;
	for (i = 0; i < 6; i++)
	{
		if (GetData[i] == LostData[i+1])//�ν�Ʈ
		{
			IsFullCollect += 1;
		}
	}
	printf("----------------------------------------------------------\n");//ȭ�� ���
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                       GameOver                          |\n");
	printf("|                      �Ϸ��� = %.lf%%                        |\n", (IsFullCollect/6.0)*100);
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	Sleep(2000);
}
//GetData �̴ϰ��ӿ��� ���̴� �Լ���
void ControlObjMove(ObjectCoord* Obje1, int i, ObjectCoord Player, int* Hp)//������Ʈ �������� ���
{
	int j = 0;//���⼭�� ���Ǵ� ��������
	if (Obje1->y >= 30)//������ �� �� ����
	{
		if (abs(Player.x - Obje1->x) < 5)//hp���� ����
		{
			(*Hp)--;
		}
		gotoxy(Obje1->x, Obje1->y-1);//���� ����
		printf(" ");
		FindDupli[i] = rand() % Max_X;
		for (j = 0; j < 5; j++)
		{
			if (FindDupli[i] == FindDupli[j])//���� �ߺ��� �ִٸ� �ٸ��� ��������
			{
				FindDupli[i] = rand() % Max_X;
				continue;
			}
		}
		Obje1->x = FindDupli[i];
		Obje1->y = 0;
		Obje1->speed = rand() % 10 + 1;
		return;
	}
	gotoxy(Obje1->x, Obje1->y);
	printf("*");
	Obje1->y += Obje1->speed;
	return;
}//�� ������ ����
void ControlGoldMove(ObjectCoord* Obje1, int i, char* GoldText, ObjectCoord Player, char* GetText)
{
	int t = 0;//�ؿ�.. ���� �������� ����ϴ¤���
	int j = 0;//���⼭�� ���Ǵ� ��������
	if (Obje1->y >= 30)//������ �� �� ����
	{
		if (abs(Player.x - Obje1->x) < 7)//��Ҵ��� Ȯ���ϴ� ����
		{
			t = i;
			for (j = 1+i; j <= 2+i; j++)
			{
				GetText[t] = GoldText[j];
				t++;
			}
			Obje1->speed = -1;
			gotoxy(Obje1->x, Obje1->y - 1);//���� ����
			printf("     ");
			Obje1->y = 0;
			return;
		}
			gotoxy(Obje1->x, Obje1->y - 1);//���� ����
			printf("     ");
			FindDupli[i] = rand() % Max_X;
			for (j = 0; j < 8; j++)
			{
				if (abs(FindDupli[i] - FindDupli[j]) < 3)//���� 5ĭ �̳��� ��ֹ��̳� �ٸ� ������ �ִٸ�
				{
					FindDupli[i] = rand() % Max_X;//�ٽ� ������
					continue;
				}
			}
			Obje1->x = FindDupli[i];
			Obje1->y = 0;
			Obje1->speed = rand() % 10 + 1;
			return;
	}
//������Ʈ ���ǵ尡 1�� �Ǵ� ���� ���� ���� �������� �� 
		gotoxy(Obje1->x, Obje1->y);
		for (j = 1 + i; j <= 2 + i; j++)
		{
			printf("%c", *(GoldText + j));
		}
		Obje1->y += Obje1->speed;
		return;
}//���� ���ڿ��� �������� ����
void PlayerMoveControl(ObjectCoord* Obje1)
{
	gotoxy(Obje1->x, Obje1->y);
	printf("   ");
	char ch = _getch();
	switch (ch)
	{
		case 75:
		{
			if(Obje1->x > 0)
				Obje1->x -= Obje1->speed;
			break;
		}
		case 77:
		{
			if (Obje1->x <= Max_X)
				Obje1->x += Obje1->speed;
			break;
		}
	}
	gotoxy(Obje1->x, Obje1->y);
	printf("��");
	return Obje1;
}
//�������
void Quiz()//����� ������ ������,������ Ǯ�� ��. �̶� ���ڴ� ������ �迭�� ���·� �־���. 
{

}
