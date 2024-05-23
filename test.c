#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "GameUtility.h"//GameUtility ����Ǿ� ����.


///<GetData�� ���ǵ�>
#define GetData_Max_X 70//GatData���ӿ��� x������ ������ ����


#define GetData_Easy_MAX_target 3
#define GetData_Easy_MAX_Obstacle 5

#define GetData_Normal_MAX_target 5
#define GetData_Normal_MAX_Obstacle 7

#define GetData_Hard_MAX_target 7
#define GetData_Hard_MAX_Obstacle 9//������ Ÿ�� ����, ���⼭ ���ݸ� �ٲ��ָ� ��.

#define GetData_Easy_hp 4
#define GetData_Easy_end_time 15.0f

#define GetData_Normal_hp 3
#define GetData_Normal_end_time 12.0f

#define GetData_Hard_hp 2
#define GetData_Hard_end_time 10.0f//������ �ð� ���.. 
///</�������>


//���α׷��� ��ü������ ����ϴ� ����ü�� ��������

typedef enum difficullty {//���̵� ���� ����.
	Easy,
	Normal,
	Hard
}difficulty;//���� 0, 1, 2�� ����, Easy, Normal, Hard ���� ������ �����ϰ� 0, 1, 2 ����ϸ� ��. 

typedef struct level_memory {//���� �ð��� hp. 
	float end_time;
	int hp
}level_memory;
//


//GetData�� ����������
typedef struct ObjectCoord//������Ʈ ��ǥ�� �����ص� ��Ʈ����
{
	int x;//x��
	int y;//y��
	int speed;//�ӵ�
}ObjectCoord;

typedef struct target {//�Ծ�� �ϴ� ��ǥ�� ������ ��� ��Ʈ����.. 
	char* name;
	size_t n;
}target;

 

//�Լ� ����� 

void PWMiniGameLevel1(int);//��й�ȣ ����. 

//�ٵ����Ϳ� �Լ���
void GetData_game_init(int);//�ٵ����� ���� �ʱ�ȭ
void Getdata_Minigame(target*, int*, level_memory*, int, int, int);//�������� �����͸� ���������� �ݴ� ����
void ControlObjMove(ObjectCoord*, int, ObjectCoord, int*);//�ٵ����Ϳ�, ������Ʈ���� ���� ��ġ ��Ʈ��
void ControlGoldMove(ObjectCoord*, int, char*, ObjectCoord, char*);//���������Ʈ���� ��ġ ��Ʈ��
void PlayerMoveControl(ObjectCoord*);//�÷��̾� ��ġ ��Ʈ��
//


int main()
{
	srand((unsigned)time(NULL));
	GetData_game_init(Easy);
	printf("��");
	Sleep(2000);
	return 0;
}

void GetData_game_init(int difficult) {//���̵��� ���� �� ���ڵ�� hp, ������ �ð�. Easy�� 0��, Normal�� 1��, Hard�� 2����. 
	target* Target;////���� �Ҵ���. ���� �� �޸� ���� ��ٸ� �̰� �ʱ�ȭ�ߴ��� �ٽ� Ȯ���غ���
	int* FindDupli;//���� �Ҵ���. ���� �� �޸� ���� ��ٸ� �̰� �ʱ�ȭ�ߴ��� �ٽ� Ȯ���غ���
	level_memory* Level;////���� �Ҵ���. ���� �� �޸� ���� ��ٸ� �̰� �ʱ�ȭ�ߴ��� �ٽ� Ȯ���غ���
	int IsProperDiff = 0;//���̵��� �ùٸ��� Ȯ����.
	int Targetamount, Obstacleamount;
	switch(difficult)//Ease, Normal, Hard�� ���� 0,1,2�� �ش��ϰ� �����Ǳ� ������ ��������. ���̵��� ���� �ٸ� ���� ����.
	{
		case Easy:
			Target->name = " YEE";
			Target->n = 4;
			FindDupli = (int*)malloc((GetData_Easy_MAX_target + GetData_Easy_MAX_Obstacle) * sizeof(int));
			Level->hp = GetData_Easy_hp;
			Level->end_time = GetData_Easy_end_time;
			IsProperDiff = 1;
			Targetamount = GetData_Easy_MAX_target;
			Obstacleamount = GetData_Easy_MAX_Obstacle;
			break;
		case Normal: 
			Target->name = " Kimch!";
			Target->n = 7;
			FindDupli = (int*)malloc((GetData_Normal_MAX_target + GetData_Normal_MAX_Obstacle) * sizeof(int));
			Level->hp = GetData_Normal_hp;
			Level->end_time = GetData_Normal_end_time;
			IsProperDiff = 1;
			Targetamount = GetData_Normal_MAX_target;
			Obstacleamount = GetData_Normal_MAX_Obstacle;
			break;
		case Hard:
			Target->name = " HelloPlayer!";
			Target->n = 13;
			FindDupli = (int*)malloc((GetData_Hard_MAX_target + GetData_Hard_MAX_Obstacle) * sizeof(int));
			Level->hp = GetData_Hard_hp;
			Level->end_time = GetData_Hard_end_time;
			IsProperDiff = 1;
			Targetamount = GetData_Hard_MAX_target;
			Obstacleamount = GetData_Hard_MAX_Obstacle;
			break;
		default:
			printf("�ùٸ� ���̵��� �������ּ���");
			return;
			break;
	}
	if (IsProperDiff)
	{
		if (FindDupli == NULL)//�����Ҵ� ���� üũ
		{
			printf("\n\n���� : �޸𸮰� �����մϴ�"); 
			return;
		}
		else
		{
			Getdata_Minigame(Target, FindDupli, Level, difficult, Targetamount, Obstacleamount);
			return;
		}
	}

}

void get_position(int* arr, size_t size, int idx,int distance) {//��ġ ����ִ� ����, ��ֹ��� �����, ������Ʈ ��ȣ, ���� ���� 
	int i;
	int pos = rand() % GetData_Max_X;
	
	for (i = 0; i < size; i++) //���� ��ġ�� �ߺ� ���Բ� ������ִ� �Լ�
	{
		if (abs(pos - arr[i]) < distance)//���� 3ĭ �̳��� ��ֹ��̳� �ٸ� ������ �ִٸ�
		{
			pos = rand() % GetData_Max_X;//�ٽ� ������
			i = 0;
		}
	}
	arr[idx] = pos;
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
			if (TryLimit - 1)//�õ� Ƚ�� �����ִ��� Ȯ��
			{
				printf("Ʋ�Ƚ��ϴ�. ��ȸ�� %d���Դϴ�", TryLimit - 1);//Ʋ���� �ٽ� �ݺ�
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
void Getdata_Minigame(target* Target, int* FInddupli, level_memory* Stats, int difficult, int obstacleamount, int targetamount)//���� ����� [����], ����� �迭�� �ݴ� ����. 
{
	char
	int GameHp = Stats->hp;//���� ü��
	float GameOverCount = Stats->end_time;//���� ������ �ð�
	int string_size = Target->n;
	char *GetData = (char*)malloc((Target->n+1)*sizeof(char));//������ ���ڿ� ����Ǵ� �迭. �����Ҵ���(free�� ����)
	int* FindDupli = FInddupli;
	ObjectCoord* D = (ObjectCoord*)malloc(targetamount * sizeof(ObjectCoord));//Ÿ�� ���� ����Ǵ� �迭
	ObjectCoord* B = (ObjectCoord*)malloc(obstacleamount * sizeof(ObjectCoord));//��ֹ� ���� ����Ǵ� �迭
	ObjectCoord P1 = { 0, 29, 3 };//�÷��̾� ����
	int IsFullCollect = 0;//���� ��Ҵ��� Ȯ���ϴ� ����. 
	int i, j;//�ݺ����� ����
	int arr_size = sizeof(FindDupli) / sizeof(FindDupli[0]);//�迭 ������ 
	for (i = 0; i < obstacleamount; i++)//��ǥ�� �ο����ִ� ����.
	{
		get_position(FindDupli, arr_size, i, string_size);
		B[i].x = FindDupli[i];
		B[i].speed = rand() % 10 + 1;
		B[i].y = 0;
	}
	for (i = obstacleamount; i < obstacleamount+targetamount; i++)//���� ��ġ�� �ߺ� ���Բ� ������ִ� �Լ�
	{
		get_position(FindDupli, arr_size, i, string_size);
		D[i-obstacleamount].x = FindDupli[obstacleamount];//D�� B�� ���� �迭�� �޶��. 
		D[i-obstacleamount].y = 0;
		D[i-obstacleamount].speed = rand() % 10 + 1;
	}
	while (1)
	{
		system("cls");//ȭ�� �����

		if (_kbhit())
		{
			PlayerMoveControl(&P1);
		}
		for (i = 0; i < obstacleamount; i++) {//������Ʈ �������ִ� ����
			ControlObjMove(&B[i], i, P1, &GameHp);
		}
		for (i = 0; i < targetamount; i++)
		{
			if (D[i].speed != -1)
			{
				ControlGoldMove(&D[i], 2 * i, , P1, GetData);
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
		for (i = 0; i < string_size; i++)
		{
			printf("%c", GetData[i]);
			if (GetData[i] == Target[string_random].name[i + 1])
			{
				IsFullCollect += 1;
			}
		}
		if (IsFullCollect >= string_size-1)
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
		if (GetData[i] == Target[string_random].name[i + 1])//�ν�Ʈ
		{
			IsFullCollect += 1;
		}
	}
	printf("----------------------------------------------------------\n");//ȭ�� ���
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                       GameOver                          |\n");
	printf("|                      �Ϸ��� = %.lf%%                        |\n", (IsFullCollect / 6.0) * 100);
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
		gotoxy(Obje1->x, Obje1->y - 1);//���� ����
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
			for (j = 1 + i; j <= 2 + i; j++)
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
		if (Obje1->x > 0)
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
