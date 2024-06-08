#define _CRT_SECURE_NO_WARNINGS
#include "All_In_one_header.h"

///<PWminigame�� ���ǵ�> 

#define Password_Easy_Max_Len 2//���ڿ� ���̴� �׻� �ϳ� �� ���� ¥�ֱ�
#define Password_Easy_Max_end_time 10.0f
#define Password_Easy_Max_Hint 3

#define Password_Normal_Max_Len 5
#define Password_Normal_Max_end_time 10.0f
#define Password_Normal_Max_Hint 3

#define Password_Hard_Max_Len 20
#define Password_Hard_Max_end_time 10.0f
#define Password_Hard_Max_Hint 5

///<GetData�� ���ǵ�>

#define GetData_Max_X 70//GatData���ӿ��� x������ ������ ����


#define GetData_Easy_MAX_target 3
#define GetData_Easy_MAX_Obstacle 5

#define GetData_Normal_MAX_target 4
#define GetData_Normal_MAX_Obstacle 7

#define GetData_Hard_MAX_target 5
#define GetData_Hard_MAX_Obstacle 12//������ Ÿ�� ����, ���⼭ ���ݸ� �ٲ��ָ� ��.

#define GetData_Easy_hp 4
#define GetData_Easy_end_time 15.0f

#define GetData_Normal_hp 3
#define GetData_Normal_end_time 12.0f

#define GetData_Hard_hp 2
#define GetData_Hard_end_time 10.0f//������ �ð� ���.. 

#define GetData_Distance 5//���� �������ִ� ����
///
/// 
/// 
///����� ���ǵ�
/// 
#define NUM_QUESTIONS 20 // ���ݱ��� �߰��� ���� ��. ���� ���� �߰��� ���Ѵٸ� ��, ��, ��޿� �ѹ����� �� �߰��ؾ߸� ��.+ indicies �ϳ� �÷��ֱ�. 
#define Quiz_Easy_Hp 7
#define Quiz_Easy_end_time 15.0f
#define Quiz_Normal_Hp 7
#define Quiz_Normal_end_time 15.0f
#define Quiz_Hard_Hp 7
#define Quiz_Hard_end_time 15.0f
//


//�̴ϰ����� ��ü������ ����ϴ� ����ü�� ��������
typedef enum difficulty {//���̵� ���� ����. ���⼭ l �ϳ� ������.
	Easy,
	Normal,
	Hard
}difficulty;//���� 0, 1, 2�� ����, Easy, Normal, Hard ���� ������ �����ϰ� 0, 1, 2 ����ϸ� ��. 
//
//�������� ����
extern int isMinigameClear;//�̰� 1�� �ٲ�� �̴ϰ����� Ŭ����ȰŰ�, 0�̸� Ŭ���� �ȵȰ���. 

//�н����� �̴ϰ���
void PW_game_init(difficulty difficult)
{
	Password_inform* Password = (Password_inform*)calloc(1, sizeof(Password_inform));//�н����� ������ ������ ����
	level_memory* Level = (level_memory*)calloc(1, sizeof(level_memory));//���� ���� �Ҵ��̶� ������ �ʱ�ȭ �������.
	switch (difficult) {
		case Easy://���̵� �Ҵ� �۾�
			Password->size = Password_Easy_Max_Len;
			(*Password).pw = (char*)calloc(Password_Easy_Max_Len, sizeof(char));
			Level->end_time = Password_Easy_Max_end_time;
			Level->hp = Password_Easy_Max_Hint;//���⼱ hp�� ��Ʈ
			break;
		case Normal:
			Password->size = Password_Normal_Max_Len;
			(*Password).pw = (char*)calloc(Password_Normal_Max_Len, sizeof(char));
			Level->end_time = Password_Normal_Max_end_time;
			Level->hp = Password_Normal_Max_Hint;//���⼱ hp�� ��Ʈ
			break;
		case Hard:
			Password->size = Password_Hard_Max_Len;
			(*Password).pw = (char*)calloc(Password_Hard_Max_Len, sizeof(char));
			Level->end_time = Password_Hard_Max_end_time;
			Level->hp = Password_Hard_Max_Hint;//���⼱ hp�� ��Ʈ
			break;
		default: 
			printf("�ùٸ� ���̵��� �������ּ���");
			return;
			break;

	}
	PW_game(Password, Level);//�޸� ���� Ȯ���ϴ� ���� �־��ֱ�
}
void PW_game(Password_inform* Password, level_memory* Level)
{
	int i, j = 0;
	int Hint_amount = Level->hp;//��Ʈ ����
	int end_time = (int)Level->end_time; //���� end time ��� �����ϴٸ� ����� ��.. ���⼱ ��� ��� ���� �𸣰ڴ�.
	int s_time;
	char* Password_pw = (*Password).pw;
	char* initialize = (char*)calloc(Password->size, sizeof(char));//�ʱ�ȭ�� ����
	char* input = (char*)calloc(Password->size, sizeof(char));//����� �Է� �޴� ����. �� �� �����Ҵ��̶� free �������
	//��й�ȣ ���� ����
	for (i = 0; i < (Password->size)-1; i++)//�н����� �Ҵ� �۾�
	{
		if (rand() % 2)
			Password_pw[i] = 'a' + rand() % 26;

		else
			Password_pw[i] = 'A' + rand() % 26;

	}
	Password_pw[i] = '\0';
	//
	PW_game_show_PW_screen(Password);//���� ���� ȭ�� ���
	PW_game_show_input_screen(Hint_amount, end_time);//��ǲ ȭ�� ���
	s_time = time(0);
	// 
	while (1) {//�Է¹��� ����ֱ�
		if (_kbhit())
		{
			if ((input[j] = _getch()) == 8)
			{
				if (j == 0)
					continue;
				j--;
				printf("\b \b");
				input[j] = '\0';
			}

			else
			{
				printf("%c", input[j]);
				j++;
			}
		}
		if (j >= Password->size - 1) {//�� �Է����� ���
			input[Password->size - 1] = '\0';
			printf("\n�˻���..."); 
			Sleep(2000);
			if (!strcmp(Password->pw, input)){
				PW_game_wIn();
				break;
			}
			else {
				if (Hint_amount > 0) {
					system("cls");
					Hint_amount--;
					printf("\n Ʋ�Ƚ��ϴ�, ���� ��Ʈ�� %d���Դϴ�.", Hint_amount);
					Sleep(2000);
					j = 0;
					strcpy(input, initialize);
					PW_game_show_PW_screen(Password);
					PW_game_show_input_screen(Hint_amount, end_time);
				}
				else {
					PW_game_defeat();
					break;
				}
			}
		}
	}
	free(Password); //�����Ҵ� ����
	free(Level);
	free(initialize);
	free(input);
}
void PW_game_show_PW_screen(Password_inform* Password)//�н����� �̴ϰ��ӿ��� ��й�ȣ �Է� ȭ�� ����ϴ� ��
{
	system("cls");
	printf("----------------------------------------------------------\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|           ��й�ȣ: %s                           |\n", (*Password).pw);
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	Sleep(2000);
}
void PW_game_show_input_screen(int hp, int end_time)//����� �Է� �޴� ��ũ��
{
	system("cls");
	printf("----------------------------------------------------------\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|    ��й�ȣ�� �Է��ϼ���                                |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	printf("���� ��ȸ : %d\n", hp); 
	return;
}
void PW_game_wIn()
{
	PW_game_show_winsreen();
	isMinigameClear = 1;
	//���� ���⿡ ���� ��
}
//�¸��� ����Ǵ� �Լ�
void PW_game_defeat()
{
	PW_game_show_defeatscreen();
	//���� ���⿡ ����� ��
}
//�й�� ����Ǵ� �Լ�
//�������

///getdata �̴ϰ���
//GetData�� ��������
int* FindDupli;//������Ʈ ���� �ߺ� �ִ��� Ȯ��
//
void GetData_game_init(difficulty difficult) {//���̵��� ���� �� ���ڵ�� hp, ������ �ð�. Easy�� 0��, Normal�� 1��, Hard�� 2����. 
	target* Target = (target*)calloc(1, sizeof(target));////���� �Ҵ���. ���� �� �޸� ���� ��ٸ� �̰� �ʱ�ȭ�ߴ��� �ٽ� Ȯ���غ���
	level_memory* Level = (level_memory*)calloc(1, sizeof(level_memory));////���� �Ҵ���. ���� �� �޸� ���� ��ٸ� �̰� �ʱ�ȭ�ߴ��� �ٽ� Ȯ���غ���
	int IsProperDiff = 0;//���̵��� �ùٸ��� Ȯ����.
	int Targetamount, Obstacleamount;
	switch(difficult)//Ease, Normal, Hard�� ���� 0,1,2�� �ش��ϰ� �����Ǳ� ������ ��������. ���̵��� ���� �ٸ� ���� ����.
	{
		case Easy:
			Target->name = " Kimch!";
			Target->n = 6;
			FindDupli = (int*)malloc((GetData_Easy_MAX_target + GetData_Easy_MAX_Obstacle) * sizeof(int));
			Level->hp = GetData_Easy_hp;
			Level->end_time = GetData_Easy_end_time;
			IsProperDiff = 1;
			Targetamount = GetData_Easy_MAX_target;
			Obstacleamount = GetData_Easy_MAX_Obstacle;
			break;
		case Normal: 
			Target->name = " Kimch!";
			Target->n = 6;
			FindDupli = (int*)malloc((GetData_Normal_MAX_target + GetData_Normal_MAX_Obstacle) * sizeof(int));
			Level->hp = GetData_Normal_hp;
			Level->end_time = GetData_Normal_end_time;
			IsProperDiff = 1;
			Targetamount = GetData_Normal_MAX_target;
			Obstacleamount = GetData_Normal_MAX_Obstacle;
			break;
		case Hard:
			Target->name = " HelloPlayer!";
			Target->n = 12;
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
			Getdata_Minigame(Target, Level, difficult, Targetamount, Obstacleamount);
			return;
		}
	}
}
void Getdata_Minigame(target* Target, level_memory* Stats, int difficult, int targetamount, int obstacleamount)//���� ����� [����], ����� �迭�� �ݴ� ����. 
{
	int GameHp = Stats->hp;//���� ü��
	float GameOverCount = Stats->end_time;//���� ������ �ð�
	int string_size = (int)Target->n;
	char *GetData = (char*)calloc((((int)Target->n)+1), sizeof(char));
	GetData[(Target->n)+1] = '\0';//������ ���ڿ� ����Ǵ� �迭. �����Ҵ���(free�� ����)
	ObjectCoord* D = (ObjectCoord*)malloc(targetamount * sizeof(ObjectCoord));//Ÿ�� ���� ����Ǵ� �迭
	ObjectCoord* B = (ObjectCoord*)malloc(obstacleamount * sizeof(ObjectCoord));//��ֹ� ���� ����Ǵ� �迭
	ObjectCoord P1 = { 0, 29, 3 };//�÷��̾� ����
	int IsFullCollect = 0;//���� ��Ҵ��� Ȯ���ϴ� ����. 
	int i;//�ݺ����� ����
	int arr_size = (obstacleamount+targetamount)/sizeof(int);//�迭 ������ 
	for (i = 0; i < obstacleamount; i++)//��ǥ�� �ο����ִ� ����.
	{
		get_position(arr_size, i, string_size/targetamount);
		B[i].x = FindDupli[i];
		B[i].speed = rand() % 10 + 1;
		B[i].y = 0;
	}
	for (i = obstacleamount; i < obstacleamount+targetamount; i++)//���� ��ġ�� �ߺ� ���Բ� ������ִ� �Լ�
	{
		get_position(arr_size, i, string_size);
		D[i-obstacleamount].x = FindDupli[obstacleamount];//D�� B�� ���� �迭�� �޶��. 
		D[i-obstacleamount].y = 0;
		D[i-obstacleamount].speed = rand() % 10 + 1;
	}
	while (1)
	{
		system("cls");//ȭ�� �����

		if (_kbhit())//�ú��ҷ� �ڵ带 ������. ù��°�δ� �÷��̾� �������� ��Ʈ����.
		{
			Control_Player_Move(&P1);
		}
		for (i = 0; i < obstacleamount; i++) {//������Ʈ �������ִ� ����
			Control_Obst_Move(&B[i], i, P1, &GameHp, arr_size, string_size);
		}
		for (i = 0; i < targetamount; i++)
		{
			if (D[i].speed != -1)
			{
				Control_Target_Move(&D[i], Target, 2 * i, Target->name, arr_size, P1, GetData, arr_size, string_size);//�̸��� ����.
			}
		}
		if (GameHp <= 0 || GameOverCount <= 0)//���� ���� �ڵ�. �������� �� �������� �ѹ� üũ����. 
		{
			break;
		}
		if (_kbhit())
		{
			Control_Player_Move(&P1);
		}
//ȭ�� ����� �ڵ�
		GetData_game_show_menu_screen(GameHp, GameOverCount, GetData, string_size, GetData_Max_X);
		if (strlen(GetData) >= string_size-1)//���߿� ���⼭ ���� �� ����, üũ
		{
			break;
		}
		gotoxy(P1.x, P1.y);
		for (i = 0; i < 4; i++)
		{
			while(_kbhit())
			{
				Control_Player_Move(&P1);
			}
			Sleep(50);
		}
		if (_kbhit())//�÷��̾� ��ġ�� ��� üũ���ָ鼭 ������ �ؼ�
		{
			Control_Player_Move(&P1);
		}
		GameOverCount -= 0.2f;

	}//���� �ڵ�
	system("cls");
	IsFullCollect = 0;
	for (i = 0; i < string_size; i++)
	{
		if (GetData[i] == Target->name[i + 1])//�ν�Ʈ
		{
			IsFullCollect += 1;
		}
	}
	GetData_Gameover(IsFullCollect, string_size);
	//���� �׼�(�޸� �Ҵ� ����)
	free(Target);
	free(Stats);
	free(FindDupli);
	free(D); 
	free(B); 
}
void Control_Obst_Move(ObjectCoord* Obje1, int i, ObjectCoord Player, int* Hp, int Allamount, int string_size)//������Ʈ �������� ���
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
		get_position(Allamount, i, string_size);
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
void Control_Target_Move(
	ObjectCoord* Obje1, target* Target, 
	int i, char* TargetText, int arr_size,
	ObjectCoord Player, char* GetText, int Targetamount, int string_size)
{
	int t = 0;//�ؿ�.. ���� �������� ����ϴ¤���
	int j = 0;//���⼭�� ���Ǵ� ��������
	if (Obje1->y >= 30)//������ �� �� ����
	{
		if (abs(Player.x - Obje1->x) < Target->n/Targetamount)//��Ҵ��� Ȯ���ϴ� ����
		{
			t = i;
			for (j = 1 + i; j <= 2 + i; j++)
			{
				GetText[t] = TargetText[j];
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
		get_position(arr_size, i, ((int)Target->n / Targetamount + 3));
		Obje1->x = FindDupli[i];
		Obje1->y = 0;
		Obje1->speed = rand() % 10 + 1;
		return;
	}
	//������Ʈ ���ǵ尡 1�� �Ǵ� ���� ���� ���� �������� �� 
	gotoxy(Obje1->x, Obje1->y);
	for (j = 1 + i; j <= 2 + i; j++)
	{
		printf("%c", *(TargetText + j));
	}
	Obje1->y += Obje1->speed;
	return;
}//���� ���ڿ��� �������� ����
void Control_Player_Move(ObjectCoord* Obje1)
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
		if (Obje1->x <= GetData_Max_X)
			Obje1->x += Obje1->speed;
		break;
	}
	}
	gotoxy(Obje1->x, Obje1->y);
	printf("��");
	return;
}
void get_position(size_t size, int idx, int distance) {//��ġ ����ִ� ����, ��ֹ��� �����, ������Ʈ ��ȣ, ���� ���� �޾Ƽ� ��ġ ����.
	int i;
	int pos = rand() % GetData_Max_X;

	for (i = 0; i < size; i++) //���� ��ġ�� �ߺ� ���Բ� ������ִ� �Լ�
	{
		if (abs(pos - FindDupli[i]) < distance+3)//���� 3ĭ �̳��� ��ֹ��̳� �ٸ� ������ �ִٸ�
		{
			pos = rand() % GetData_Max_X;//�ٽ� ������
			i = 0;
		}
	}
	FindDupli[idx] = pos;
}
void GetData_Gameover(int isFullCorrect, int string_size)
{
	GetData_game_show_Gameover_screen(isFullCorrect, string_size);
	if (((double)isFullCorrect/string_size)*100 >= 60.0)
	{
		isMinigameClear = 1;//�̴ϰ��� Ŭ��� 1��
	}
	//isfullcorrect�� ���� �迭 ��, string_size�� ��ü �迭 ��. �Ϸ��� �������� �ٸ� ����� �ֵ��� �� ��
	//����� �� �Լ�.
}
//�������

//���� �̴ϰ���
//���� �̴ϰ��ӿ� ��������, 

//���� ����������. ���� �� �ø� ������ �� �װ��� �� �÷���� ��.
Question easy_questions[NUM_QUESTIONS] = {
		{"C ����� ǥ�� ���̺귯�� �� �ϳ��� `stdio.h`�� ���Ե� �Լ��� �����ΰ���?", {"printf", "malloc", "strcpy", "sqrt"}, 0},
		{"C ���� ���� ������ �ùٸ� ���ô� �����ΰ���?", {"int 4number;", "int number4;", "int number 4;", "int number-4;"}, 1},
		{"C ���α׷��� �������� �Ǵ� �Լ��� �����ΰ���?", {"start()", "main()", "printf()", "init()"}, 1},
		{"C���� ���ڸ� ��Ÿ���� ���� ����ϴ� �ڷ����� �����ΰ���?", {"char", "int", "float", "double"}, 0},
		{"���� �� �ּ��� �ùٸ��� ����ϴ� ����� �����ΰ���?", {"\\ This is a comment", "/* This is a comment */", "// This is a comment */", "/* This is a comment"}, 1},
		{"C ���� �迭�� �ε����� ����� �����ϳ���?", {"1", "0", "2", "-1"}, 1},
		{"���� �� C���� ����ϴ� �ڷ����� �ƴ� ����?", {"int", "float", "real", "double"}, 2},
		{"C���� ����� �����ϴ� Ű����� �����ΰ���?", {"const", "var", "let", "constant"}, 0},
		{"���� �� C ����� �� �����ڰ� �ƴ� ����?", {"&&", "||", "!", "&"}, 3},
		{"���� �� C���� ���ڿ��� �����ϱ� ���� �ڷ����� �����ΰ���?", {"char", "int", "float", "string"}, 0},
		{"C ����� ǥ�� ���̺귯�� �� �ϳ��� `stdio.h`�� ���Ե� �Լ��� �����ΰ���?", {"printf", "malloc", "strcpy", "sqrt"}, 0},
		{"C ���� ���� ������ �ùٸ� ���ô� �����ΰ���?", {"int 4number;", "int number4;", "int number 4;", "int number-4;"}, 1},
		{"C ���α׷��� �������� �Ǵ� �Լ��� �����ΰ���?", {"start()", "main()", "printf()", "init()"}, 1},
		{"C���� ���ڸ� ��Ÿ���� ���� ����ϴ� �ڷ����� �����ΰ���?", {"char", "int", "float", "double"}, 0},
		{"���� �� �ּ��� �ùٸ��� ����ϴ� ����� �����ΰ���?", {"// This is a comment", "/* This is a comment */", "// This is a comment */", "/* This is a comment"}, 1},
		{"C ���� �迭�� �ε����� ����� �����ϳ���?", {"1", "0", "2", "-1"}, 1},
		{"���� �� C���� ����ϴ� �ڷ����� �ƴ� ����?", {"int", "float", "real", "double"}, 2},
		{"C���� ����� �����ϴ� Ű����� �����ΰ���?", {"const", "var", "let", "constant"}, 0},
		{"���� �� C ����� �� �����ڰ� �ƴ� ����?", {"&&", "||", "!", "&"}, 3},
		{"���� �� C���� ���ڿ��� �����ϱ� ���� �ڷ����� �����ΰ���?", {"char", "int", "float", "string"}, 0}
};
Question medium_questions[NUM_QUESTIONS] = {
	{"���� �ڵ��� ��� ����� �����ΰ���? \nint a = 5;\nint b = 10;\nint c = a + b;\nprintf(\"%d\", c);", {"5", "10", "15", "20"}, 2},
	{"C ���� �Լ��� �����ϴ� �ùٸ� ����� �����ΰ���?", {"function int add(int a, int b)", "int add(int a, int b);", "int add(a, b)", "func int add(int a, int b)"}, 1},
	{"���� �� ������ ������ �ùٸ� ���� �����ΰ���?", {"int p;", "int *p;", "int p*;", "int * p;"}, 1},
	{"���� �ڵ��� ��� ����� �����ΰ���?\nint a = 10;\nint *p = &a;\nprintf(\"%d\", *p);", {"0", "10", "������ ��", "������ ����"}, 1},
	{"���� �� �迭�� �����ϴ� �ùٸ� ����� �����ΰ���?", {"int arr[5];", "int arr;", "int arr[];", "arr[5];"}, 0},
	{"���� �ڵ��� ��� ����� �����ΰ���?\nint arr[] = {1, 2, 3, 4, 5};\nprintf(\"%d\", arr[2]);", {"1", "2", "3", "4"}, 2},
	{"���� �� ������ ���� 1 ������Ű�� �ùٸ� ����� �����ΰ���?", {"x += 1;", "x =+ 1;", "x = 1;", "x == 1;"}, 0},
	{"���� �ڵ��� ��� ����� �����ΰ���?\nprintf(\"%d\", sizeof(int));", {"2", "4", "8", "16"}, 1},
	{"���� �ڵ��� ��� ����� �����ΰ���?\nchar str[] = \"Hello\";\nprintf(\"%s\", str);", {"Hello", "H", "str", "������ ����"}, 0},
	{"���� �� �Լ� �����͸� ����ϴ� �ùٸ� ����� �����ΰ���?", {"int (*funcPtr)(int, int) = &functionName;", "int *funcPtr(int, int) = &functionName;", "int funcPtr(int, int) = &functionName;", "int (*funcPtr)(int, int) = functionName;"}, 3},
	{"C���� ���Ǵ� Ű����� ������ �����ϴ� ���� �����ΰ���?", {"define", "int", "var", "let"}, 1},
	{"���� �� C���� ���Ǵ� �ݺ����� �ƴ� ���� �����ΰ���?", {"for", "while", "repeat", "do-while"}, 2},
	{"C���� ������ ������ ��, �ʱ�ȭ���� ������ �ش� ������ ���� ������ �ɱ��?", {"0", "1", "������ ��", "����"}, 2},
	{"C���� ���ڿ��� ���ϴ� �Լ��� �����ΰ���?", {"strcmp", "strcpy", "strcat", "strlen"}, 0},
	{"C���� ������ ������ �����ϴ� Ű����� �����ΰ���?", {"int", "float", "real", "double"}, 0},
	{"C���� ���Ǵ� �� �����ڰ� �ƴ� ���� �����ΰ���?", {"<", ">", "<=", "=="}, 3},
	{"C���� �Ǽ��� �����͸� ��Ÿ���� Ű����� �����ΰ���?", {"int", "float", "double", "real"}, 1},
	{"C���� ������ ���� ������Ű�� ������� ������ ���� �����ΰ���?", {"x++", "++x", "x += 1", "���"}, 3},
	{"C���� ���ǹ��� ���� ������ �ڵ� ����� �����ϴ� �� ���Ǵ� ��ȣ�� �����ΰ���?", {"()", "{}", "[]", "���"}, 1},
	{"C���� ���Ǵ� �Ҵ� �����ڰ� �ƴ� ���� �����ΰ���?", {"=", "+=", "-=", "=="}, 3}
};
Question hard_questions[NUM_QUESTIONS] = {
	{"���� �ڵ��� ��� ����� �����ΰ���? \nint arr[] = {1, 2, 3, 4, 5};\nint *p = arr;\nprintf(\"%d\", *(p + 3));", {"1", "2", "3", "4"}, 3},
	{"���� �ڵ��� ��� ����� �����ΰ���? \nint a = 5;\nint b = 10;\nint *p = &a;\nint *q = &b;\n*p = *q;\nprintf(\"%d\", a);", {"5", "10", "������ ��", "0"}, 1},
	{"���� �ڵ��� ��� ����� �����ΰ���? \nint a = 10;\nint *p = &a;\n*p += 5;\nprintf(\"%d\", *p);", {"10", "15", "������ ��", "������ ����"}, 1},
	{"���� �ڵ��� ��� ����� �����ΰ���? \nint x = 5;\nint *p = &x;\n*p = *p + 10;\nprintf(\"%d\", x);", {"5", "10", "15", "20"}, 2},
	{"���� �� ���� �޸� �Ҵ��� �����ϴ� �Լ��� �����ΰ���?", {"malloc", "calloc", "realloc", "free"}, 3},
	{"���� �ڵ��� ��� ����� �����ΰ���? \nint arr[5] = {1, 2, 3, 4, 5};\nint *p = arr;\nprintf(\"%d\", p[2]);", {"1", "2", "3", "4"}, 2},
	{"���� �� �Լ� �����͸� ����ϴ� �ùٸ� ����� �����ΰ���?", {"int (*funcPtr)(int, int) = &functionName;", "int *funcPtr(int, int) = &functionName;", "int funcPtr(int, int) = &functionName;", "int (*funcPtr)(int, int) = functionName;"}, 3},
	{"���� �ڵ��� ��� ����� �����ΰ���? \nstruct Point {int x; int y;};\nstruct Point p1 = {10, 20};\nstruct Point *p2 = &p1;\nprintf(\"%d\", p2->y);", {"10", "20", "������ ��", "������ ����"}, 1},
	{"���� �� �޸� �Ҵ翡 �������� �� ��ȯ�ϴ� ���� �����ΰ���?", {"NULL", "0", "-1", "EOF"}, 0},
	{"���� �� ���� �ڵ带 ���� ������ �� �ִ� ���� �����ΰ���? \nstruct Node {int data; struct Node *next;};\nstruct Node n1 = {10, NULL};\nstruct Node n2 = {20, &n1};\nprintf(\"%d\", n2.next->data);", {"10", "20", "������ ��", "������ ����"}, 0},
	{"���� �ڵ��� ��� ����� �����ΰ���? \nint arr[] = {1, 2, 3, 4, 5};\nint *p = &arr[2];\nprintf(\"%d\", *p);", {"1", "2", "3", "4"}, 2},
	{"C���� ������ ���� ���ҽ�Ű�� ������� �ùٸ� ���� �����ΰ���?", {"x -= 1", "x =- 1", "x = 1", "x != 1"}, 0},
	{"C���� ������ �ʴ� ������ �����ΰ���?", {"int", "real", "double", "char"}, 1},
	{"C���� �����͸� ����� �� �߻��ϴ� ���� �� �ϳ��� �����ΰ���?", {"�����", "Ż�⹮��", "��۸� ������", "����"}, 2},
	{"C���� �� ������ ���� ��ȯ�ϱ� ���� ���� ������ ����� �����ΰ���?", {"temp ���� ���", "�Լ� ȣ��", "������ ���", "����"}, 0},
	{"C���� ���Ǵ� �� ������ ���� ���� ���ϱ� ���� �����ڴ� �����ΰ���?", {"==", "=", "!=", "<>"}, 0},
	{"C���� �� �����ڷ� �� ���� ������ ��� ���� �� ����� ���� �Ǵ� �����ڴ� �����ΰ���?", {"&&", "||", "!", "&"}, 0},
	{"C���� ���ڿ��� �����ϴ� �Լ��� �����ΰ���?", {"strcat", "strcmp", "strlen", "strcpy"}, 0},
	{"C���� �����͸� ����� �� �߻��� �� �ִ� ���� �� �ϳ��� �����ΰ���?", {"�޸� ����", "�޸� ����", "�޸� ���� ����", "�޸� ���� ����"}, 2},
	{"C���� �޸� ���� �Ҵ翡 �������� �� ��ȯ�Ǵ� ���� �����ΰ���?", {"NULL", "0", "-1", "EOF"}, 0}
};
//
level_memory quiz_level;//���� Ʋ���� Ƚ���� ����Ÿ�� �����س��� ����ü. 
int question_indices[NUM_QUESTIONS] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };//�������� ����
int quiz_work_count = 0;//��� ��� �۵��ߴ��� üũ. 
int quiz_difficult;//���̵� å��

void quiz_game_init(difficulty difficult)
{
	if (quiz_work_count == 0)//�ѹ��� �۵����� �ʾҴٸ�
	{
		shuffle(question_indices, NUM_QUESTIONS);//���� ������ ���� ����. 
	}
	switch (difficult)//���̵��� ���� �ٸ� ���� �Ҵ�. 
	{
		case Easy:
			quiz_level.hp = Quiz_Easy_Hp;
			quiz_level.end_time = Quiz_Easy_end_time;
			quiz_difficult = Easy;
			quiz_Minigame(easy_questions);
			break;
		case Normal:
			quiz_level.hp = Quiz_Normal_Hp; 
			quiz_level.end_time = Quiz_Normal_end_time;
			quiz_difficult = Normal;
			quiz_Minigame(medium_questions);
			break;
		case Hard:
			quiz_level.hp = Quiz_Hard_Hp;
			quiz_level.end_time = Quiz_Normal_end_time;
			quiz_difficult = Hard;
			quiz_Minigame(hard_questions);
			break;
	}
}
void quiz_Minigame(Question* question)
{
	quiz_show_screen(question[question_indices[quiz_work_count]].question);//ȭ�� ���. 
	quiz_Select_answer_Screen_draw(4, question[question_indices[quiz_work_count]].choices);
	if (quiz_Select_menu_control(4, quiz_Select_answer_Screen_draw, question[question_indices[quiz_work_count]].choices) == question[question_indices[quiz_work_count]].correct_answer)
	{
		//������ ��
		system("cls");
		quiz_win();//�������� �Լ� �۵�
	}
	else
	{
		//Ʋ���� ��
		system("cls");
		quiz_defeat();//Ʋ������ �Լ� �۵�
	}
}
void quiz_win()//�������� �Լ�
{
	quiz_work_count++;
	quiz_show_win_screen();
	isMinigameClear = 1;
}
void quiz_defeat()//Ʋ������ �Լ�
{
	quiz_work_count++;
	quiz_show_defeat_screen();
}
void shuffle(int* array, int n) {
	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}
