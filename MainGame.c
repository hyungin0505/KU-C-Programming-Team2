#include "Maingame_header.h"
#include "GameController.h"
#include "GameUI.h"
#include "MiniGame.h"



//�⺻���� ��ȣ��� ����, ���� �븻 �ϵ庰�� ���������ϱ� �� ���� �ٲ��ָ� ��Ұ� �ٲ�.
#define Easy_flags_amount 1//�Ϲ� ��� ����
#define Easy_falseflag_amount 2//���� �̴ϰ����� ������ ���. 
//��ǥ ��� : ��ü ���(falgs amount) - ��¥ ���(falseflase)
#define Easy_Map_Max_x 20//x�� ��ǥ
#define Easy_Map_Max_y 10//y�� ��ǥ
#define Easy_Player_Hp 5//�÷��̾� ü��
#define Easy_Player_move_amount 100//�÷��̾ ������ �� �ִ� Ƚ��
#define Easy_Obstacle_amount 40
#define Easy_Limit_Break 10

//
#define Normal_flags_amount 5
#define Normal_falseflag_amount 15
#define Normal_Map_Max_x 40
#define Normal_Map_Max_y 20
#define Normal_Player_Hp 3
#define Normal_Player_move_amount 80
#define Normal_Obstacle_amount 80
#define Normal_Limit_Break 8
//
#define Hard_flags_amount 50
#define Hard_falseflag_amount 15
#define Hard_Map_Max_x 60
#define Hard_Map_Max_y 29
#define Hard_Player_Hp 1
#define Hard_Player_move_amount 69
#define Hard_Obstacle_amount 200
#define Hard_Limit_Break 8
//
// �� ���� ����

#define Easy_cleartime_rate_S 10
#define Easy_cleartime_rate_A 20
#define Easy_cleartime_rate_B 30
#define Easy_cleartime_rate_C 40

#define Easy_remain_walk_rate_S 100
#define Easy_remain_walk_rate_A 90
#define Easy_remain_walk_rate_B 80
#define Easy_remain_walk_rate_C 70

#define Easy_Minigame_clear_rate_S 100
#define Easy_Minigame_clear_rate_A 90
#define Easy_Minigame_clear_rate_B 80
#define Easy_Minigame_clear_rate_C 70

#define Normal_cleartime_rate_S 20
#define Normal_cleartime_rate_A 30
#define Normal_cleartime_rate_B 40
#define Normal_cleartime_rate_C 50

#define Normal_remain_walk_rate_S 100
#define Normal_remain_walk_rate_A 80
#define Normal_remain_walk_rate_B 60
#define Normal_remain_walk_rate_C 40

#define Normal_Minigame_clear_rate_S 100
#define Normal_Minigame_clear_rate_A 80
#define Normal_Minigame_clear_rate_B 60
#define Normal_Minigame_clear_rate_C 40

#define Hard_cleartime_rate_S 30
#define Hard_cleartime_rate_A 40
#define Hard_cleartime_rate_B 50
#define Hard_cleartime_rate_C 60

#define Hard_remain_walk_rate_S 100
#define Hard_remain_walk_rate_A 70
#define Hard_remain_walk_rate_B 50
#define Hard_remain_walk_rate_C 30

#define Hard_Minigame_clear_rate_S 100
#define Hard_Minigame_clear_rate_A 70
#define Hard_Minigame_clear_rate_B 50
#define Hard_Minigame_clear_rate_C 30

//������ ����
typedef enum difficultyy {
	Easy,///���� 0, 1, 2,4 �� �����մϴ�
	Normal,
	Hard,
	End
}Gamedifficulty;

//��ü �������� ����. 

int isMinigameClear = 0;

void Maingame_Base_init(int); // �ܼ�â �� ���� ���� �⺻ ��� ����. ���⼭���� ���ʴ�� �ʱ�ȭ�Ǵ� ��� // �� ���� ���(��, ���, ��ֹ�) ���� ����
void Game_start(); //���� �����ϴ� �Լ�
//init -> printing -> element_init ������ �۵���!
void on_flag_f(); // �÷��̾ ��߿� ��ġ�� ��
int check_flag_t(); // �÷��̾ ���� �Ϲ� ������ Ȯ��

//�� ���� ���� �������� ����
Obje_Coord* Mapsize;//�ʻ�����
Obje_Coord* TrueflagCoord;//��¥ ��� ��ǥ
Obje_Coord* FalseflagCoord;//���� ��ǥ ��ǥ
Obje_Coord* ObstacleCoord;//��ֹ� ��ǥ. 
Player_Coord PlayerCoord;
int obstacle_amount;//��ֹ� ����
int maingame_difficult;//���̵�
int flag_amount;//��ƾ� �ϴ� ��� ����
int Falseflags_amount;//��¥ ��� ���� 

//���ھ��ǿ��� ���ؾ� �ϴ� ����
int cleartime;//Ŭ�����ϴµ� �ɸ� �ð�. 
int minigame_acess_amount;//�̴ϰ��� �۵���Ų Ƚ��
int minigame_clear_amount;//�̴ϰ��� Ŭ������ Ƚ��.
//	
void Maingame_Base_init(int difficulty) //(���������� ���� �Ϸ�) �ܼ�â �� ���� �� ������Ʈ �� ��ֹ� �� �����.. �⺻ ��� ����
{
	srand((unsigned)time(NULL));
	system("mode con: cols=200 lines=100"); // �ܼ�â�� ũ�� ����, cols = ��, lines = ��
	CursorClosing();
	SetTextcolor(11, 0); // ��µ� �ؽ�Ʈ�� ����
	Mapsize = (Obje_Coord*)malloc(sizeof(Obje_Coord));//�ʻ�����
	switch (difficulty)
	{
		case Easy:
			Mapsize->x = Easy_Map_Max_x;
			Mapsize->y = Easy_Map_Max_y;
			TrueflagCoord = (Obje_Coord*)calloc((Easy_flags_amount), sizeof(Obje_Coord));//�����Ҵ�.
			FalseflagCoord = (Obje_Coord*)calloc(Easy_falseflag_amount, sizeof(Obje_Coord));//�����Ҵ�.
			maingame_difficult = Easy;
			flag_amount = Easy_flags_amount;
			Falseflags_amount = Easy_falseflag_amount;
			ObstacleCoord = (Obje_Coord*)calloc((Easy_Obstacle_amount), sizeof(Obje_Coord));
			obstacle_amount = Easy_Obstacle_amount;
			break;
		case Normal:
			Mapsize->x = Normal_Map_Max_x;
			Mapsize->y = Normal_Map_Max_y;
			TrueflagCoord = (Obje_Coord*)calloc((Normal_flags_amount), sizeof(Obje_Coord));//�����Ҵ�.
			FalseflagCoord = (Obje_Coord*)calloc(Normal_falseflag_amount, sizeof(Obje_Coord));//�����Ҵ�.
			maingame_difficult = Normal;
			flag_amount = Normal_flags_amount;
			Falseflags_amount = Normal_falseflag_amount;
			ObstacleCoord = (Obje_Coord*)calloc((Normal_Obstacle_amount), sizeof(Obje_Coord));
			obstacle_amount = Normal_Obstacle_amount;
			break;
		case Hard:
			Mapsize->x = Hard_Map_Max_x;
			Mapsize->y = Hard_Map_Max_y;
			TrueflagCoord = (Obje_Coord*)calloc((Hard_flags_amount), sizeof(Obje_Coord));//�����Ҵ�.
			FalseflagCoord = (Obje_Coord*)calloc(Hard_falseflag_amount, sizeof(Obje_Coord));//�����Ҵ�.
			ObstacleCoord = (Obje_Coord*)calloc((Hard_Obstacle_amount), sizeof(Obje_Coord));
			maingame_difficult = Hard;
			flag_amount = Hard_flags_amount;
			Falseflags_amount = Hard_falseflag_amount;
			obstacle_amount = Hard_Obstacle_amount;
			break;
			//���� ���� �Լ�
	}
	cleartime = time(NULL);//���� �ð� ������.
	minigame_clear_amount = minigame_acess_amount = 0;
	Maingame_map_printing();
	Maingame_map_element_init();
	Game_start();
}



void Maingame_map_printing()//(��������������!)�� ����ϴ� �Լ�, Mapsize�� �� ũ����
{
	for (int i = 0; i <= Mapsize->y; i++) // �⺻ �� ��� ���. �̹��� �ƽ� x, �ƽ� y�� �������� ����.
	{
		for (int j = 0; j <= Mapsize->x; j++)
		{
			if ((i == 0) && (j == 0))
				printf("#");//����ϴ� ���ڴ� ������ ��.(�ٸ� ���ڸ� ���� ��������)

			else if (i == 0 && (j == (Mapsize->x)))
				printf("#");

			else if (i == (Mapsize->y) && (j == 0))
				printf("#");

			else if (i == (Mapsize->y) && (j == (Mapsize->x)))
				printf("#");

			else if (i == 0 || (i == Mapsize->y))
				printf("#");

			else if (j == 0 || (j == Mapsize->x))
				printf("#");

			else
				printf(" ");
		}
		printf("\n");
	}
}
void Maingame_map_element_init() // �� ���� ���(��, ���, ��ֹ�) ���� ����
{
	int FLAGS_T, FLAGS_F;//���� ����� ����� Ȯ��.
	FLAGS_F = Falseflags_amount;
	FLAGS_T = flag_amount;//����ü �迭�� ����ü ũ��� ������ ������ ���� ũ�⸦ �˾Ƴ��� �۾�.
	int i, j;//�ݺ��� ����� ����//��ֹ� ����.
	int current_obstacle_amount = 0;
	for (i = 2; i < Mapsize->y - 2; i++) // ��ֹ��� ������ ��ġ ����(�� ù �ٰ� �� �Ʒ� �� ����)
	{
		for (j = 1; j < (1 + (rand() % (Mapsize->x - 6))); j++) // x�࿡�� ������ ��ֹ� ���� ���� ����
		{
			int obstacle_x = 2 + rand() % (Mapsize->x - 6); // ��ֹ��� x ��ǥ
			current_obstacle_amount++;
			if (current_obstacle_amount>= obstacle_amount)
				break;
			gotoxy(obstacle_x, i); // ��ֹ� ��ġ
			printf("#");

			ObstacleCoord[current_obstacle_amount].x = obstacle_x;
			ObstacleCoord[current_obstacle_amount].y = i;
		}
	}
	for (i = 0; i < (FLAGS_T); i++) // ��¥ ����� ������ ��ġ ���� �� ��ǥ ����
	{
		int x_locate = 1 + rand() % (Mapsize->x - 5); // ����� ������ ���� �մ� ���� �߻�
		int y_locate = 1 + rand() % (Mapsize->y - 2);

		if (x_locate == 1 && y_locate == (Mapsize->y - 2) || Maingame_not_spawn_flag_on_obstacle(x_locate, y_locate)) // ���� ��ġ�� �������� �ʰԲ�
		{
			i--;
			continue;
		}
		for (j = 0; j < FLAGS_T; j++) {
			if (x_locate == TrueflagCoord[j].x && y_locate == TrueflagCoord[j].y)//�ߺ� ���� �˰���
			{
				i--;
				continue;
			}
		}
		gotoxy(x_locate, y_locate);//�� ��� ������ ����ϸ�
		printf("@"); // ��� ������ �ĺ��� �̡ڡ�ǢȢ���
		TrueflagCoord[i].x = x_locate;
		TrueflagCoord[i].y = y_locate;
	}
	for (i = 0; i < (FLAGS_F); i++) // ��¥����� ������ ��ġ ���� �� ��ǥ ����
	{
		int x_locate = 1 + rand() % (Mapsize->x - 5); // ����� ������ ���� �մ� ���� �߻�
		int y_locate = 1 + rand() % (Mapsize->y - 2);

		if (x_locate == 1 && y_locate == (Mapsize->y - 2) || Maingame_not_spawn_flag_on_obstacle(x_locate, y_locate)) // ���� ��ġ�� �������� �ʰԲ�
		{
			i--;
			continue;
		}
		for (j = 0; j < FLAGS_T; j++) {
			if (x_locate == TrueflagCoord[j].x && y_locate == TrueflagCoord[j].y)//�ߺ� ���� �˰���
			{
				i--;
				continue;
			}
		}
		for (j = 0; j < FLAGS_F; j++) {
			if (x_locate == FalseflagCoord[j].x && y_locate == FalseflagCoord[j].y)//�ߺ� ���� �˰���
			{
				i--;
				continue;
			}
		}
		gotoxy(x_locate, y_locate);//�� ��� ������ ����ϸ�
		printf("@"); // ��� ������ �ĺ��� �̡ڡ�ǢȢ���
		FalseflagCoord[i].x = x_locate;
		FalseflagCoord[i].y = y_locate;
	}
	gotoxy(Mapsize->x + 10, Mapsize->y + 5); //" ���� ��ȣ�� ���� ����
	printf("@: ���  #: ��ֹ�  *: �÷��̾�");

	gotoxy(Mapsize->x + 10, Mapsize->y + 4);
	printf("!: �̺�Ʈ ���(�̺�Ʈ �������� ��� Ȯ�� ����)");
}
void Maingame_map_reprinting()//�ٽ� �������� ���ư��� ����Ǵ� �Լ�.
{
	system("cls");
	Maingame_map_printing();
	int i;//�ݺ����� ���� ����
	for (i = 0; i < obstacle_amount; i++) // ��ֹ� ����.
	{
		if (ObstacleCoord[i].x == -1)//��ǥ�� -1�̸� ����� ����̶�°���. 
			continue;
		gotoxy(ObstacleCoord[i].x, ObstacleCoord[i].y); // ��ֹ� ��ġ
		printf("#");
	}
	for (i = 0; i < (flag_amount); i++) // ��¥ ����� ������ ��ġ ���� �� ��ǥ ����
	{
		if (TrueflagCoord[i].x == -1)//�̹� ����� ��߿� �����ϴ� ���
			continue;
		gotoxy(TrueflagCoord[i].x, TrueflagCoord[i].y);//�� ��� ������ ����ϸ�
		printf("@"); // ��� ������ �ĺ��� �̡ڡ�ǢȢ���
	}
	for (i = 0; i < (Falseflags_amount); i++) // ��¥ ����� ������ ��ġ ���� �� ��ǥ ����
	{
		if (FalseflagCoord[i].x == -1)//�̹� ����� ��߿� �����ϴ� ���
			continue;
		gotoxy(FalseflagCoord[i].x, FalseflagCoord[i].y);//�� ��� ������ ����ϸ�
		printf("@"); // ��� ������ �ĺ��� �̡ڡ�ǢȢ���
	}
	gotoxy(PlayerCoord.x, PlayerCoord.y);
	printf("*\b");

}
void Game_start()
{
	PlayerCoord.x = 2;//�÷��̾� ������ �ʱ�ȭ�Ǵ� ����
	PlayerCoord.y = (Mapsize->y - 1);//�÷��̾� ���� ��ǥ ����
	PlayerCoord.flagcount = 0;//�÷��̾ ���� ��� ����
	switch (maingame_difficult)
	{
		case Easy:
		PlayerCoord.hp = Easy_Player_Hp;//���� hp
		PlayerCoord.remain_move_amount = Easy_Player_move_amount;//���� �̵� Ƚ��
		PlayerCoord.limit_break = Easy_Limit_Break;//���� ��ֹ� ���� Ƚ��
		break;
		case Normal:
		PlayerCoord.hp = Normal_Player_Hp;
		PlayerCoord.remain_move_amount = Normal_Player_move_amount;
		PlayerCoord.limit_break = Normal_Limit_Break;
		break;
		case Hard:
		PlayerCoord.hp = Hard_Player_Hp;
		PlayerCoord.remain_move_amount = Hard_Player_move_amount;
		PlayerCoord.limit_break = Hard_Limit_Break;
		break;
	}
	int ch;
	while (1)
	{
		gotoxy(PlayerCoord.x, PlayerCoord.y);
		printf("*\b");
		on_flag_f(); // �÷��̾ ���Ƽ ����� ������� Ȯ��

		if (check_flag_t()) // �÷��̾ �Ϲ� ����� �������, �� ��Ҵ��� Ȯ��
		{
			Maingame_gamecomplete();
			Sleep(1000); // �� ���� ��� ���� ȭ�� ���, 1�� �� ���α׷� ����.
			break;
		}
		if (PlayerCoord.remain_move_amount == 0 || PlayerCoord.hp == 0) 
			//" �̵�Ƚ���� hp�� 0�� �Ǿ����� Ȯ��
		{
			Maingame_gameover(); //" �ش��ϸ� Game Over ȭ�� ���
			Sleep(1000);
			break;
		}
		gotoxy(Mapsize->x + 10, Mapsize->y - 2);//���� ��� �� ������ִ� printf
		printf("                      ");
		gotoxy(Mapsize->x + 10, Mapsize->y - 2);
		printf("���� ����� ��: %d", (flag_amount) - PlayerCoord.flagcount); //���� ��� �� Ȯ��
		gotoxy(Mapsize->x + 10, Mapsize->y - 5);
		printf("                         ");
		gotoxy(Mapsize->x + 10, Mapsize->y - 5);
		printf("���� �̵�Ƚ��: %3d", PlayerCoord.remain_move_amount); //" ���� �̵�Ƚ�� Ȯ��
		gotoxy(Mapsize->x + 10, Mapsize->y - 4);
		printf("                                      ");//�������� �����ִ� �۾�
		gotoxy(Mapsize->x + 10, Mapsize->y - 4);
		printf("���� ��ֹ� �ı� Ƚ��: %d", PlayerCoord.limit_break);
		gotoxy(Mapsize->x + 10, Mapsize->y - 6);
		printf("                                      ");//�������� �����ִ� �۾�
		gotoxy(Mapsize->x + 10, Mapsize->y - 6);
		printf("���� ü��: %d", PlayerCoord.hp);//" ���� ��ֹ� �ı� ���� Ƚ�� Ȯ��
		gotoxy(PlayerCoord.x, PlayerCoord.y);
		ch = _getch();

		if (ch == 224) // ����Ű ó��, �� �հ� ������ ���� ������ ���� �κ� �� �������ָ� ��
		{
			ch = _getch();

			switch (ch) {

			case 72:
				if (PlayerCoord.y == 1 || Maingame_check_locate_obstacle(PlayerCoord.x, PlayerCoord.y - 1))
					break;
				gotoxy(PlayerCoord.x, PlayerCoord.y);
				printf(" ");
				PlayerCoord.y--;
				PlayerCoord.remain_move_amount--;
				break;
			case 80:
				if (PlayerCoord.y == (Mapsize->y - 1) || Maingame_check_locate_obstacle(PlayerCoord.x, PlayerCoord.y + 1))
					break;
				gotoxy(PlayerCoord.x, PlayerCoord.y);
				printf(" ");
				PlayerCoord.y++;
				PlayerCoord.remain_move_amount--;
				break;
			case 75:
				if (PlayerCoord.x == 1 || Maingame_check_locate_obstacle(PlayerCoord.x - 1, PlayerCoord.y))
					break;
				gotoxy(PlayerCoord.x, PlayerCoord.y);
				printf(" ");
				PlayerCoord.x--;
				PlayerCoord.remain_move_amount--;
				break;
			case 77:
				if (PlayerCoord.x == (Mapsize->x - 1) || Maingame_check_locate_obstacle(PlayerCoord.x + 1, PlayerCoord.y))
					break;
				gotoxy(PlayerCoord.x, PlayerCoord.y);
				printf(" ");
				PlayerCoord.x++;
				PlayerCoord.remain_move_amount--;
				break;
			}
		}
		else if (ch == 101) // Ű���� �󿡼� EŰ�� ������ �ֺ� 4������ ��ֹ��� �����
		{
			if (PlayerCoord.limit_break != 0)
			{
				Maingame_break_obstacle(PlayerCoord.x, PlayerCoord.y);
				PlayerCoord.limit_break--;
			}
		}
		//������ �Լ���.
		else if (ch == 'a')
		{
			Maingame_gamecomplete();
			break;
		}
		else if (ch == 'b')
		{
			GetData_game_init(maingame_difficult);
			Maingame_map_reprinting();
		}
		else if (ch == 'c')
		{
			PW_game_init(maingame_difficult);
			Maingame_map_reprinting();

		}
		else if (ch == 'd')
		{
		   quiz_game_init(maingame_difficult);
		   Maingame_map_reprinting();

		}
		else if (ch == 'g')
		{
			Maingame_get_reward();
			Sleep(2000);
			Maingame_map_reprinting();
		}
		else if (ch == 'f')
		{
			Maingame_get_penalty();
			Sleep(2000);
			Maingame_map_reprinting();
		}
	}
	//�������� �� �Լ� �� �ڸ�
	//�������� �� �Լ� �� �ڸ�.
}


int Maingame_not_spawn_flag_on_obstacle(int x_locate, int y_locate) // ����� ��ֹ��� ������ ��ġ�� ���� ������ �������� �ʵ��� üũ!
{
	for (int i = 0; i < obstacle_amount; i++)
	{
		if (ObstacleCoord[i].x == x_locate && ObstacleCoord[i].y == y_locate)
			return 1;
	}

	return 0;
}
int Maingame_check_locate_obstacle(int x, int y) // ��ֹ��� �浹 �������� Ȯ����. 
{
	for (int i = 0; i < obstacle_amount; i++)
	{
		if (ObstacleCoord[i].x == x && ObstacleCoord[i].y == y)
			return 1;
	}
	return 0;
}
void on_flag_f() // �÷��̾ ���Ƽ ��߿� ��ġ�� ��
{
	int size = Falseflags_amount;//�г�Ƽ ��� ��ü ũ�� Ȯ��
	for (int i = 0; i < size; i++) // �÷��̾ ���Ƽ ��߿� ��ġ�ϴ��� Ȯ��, ��ġ�ϸ� �̺�Ʈ �߻�
	{
		if (FalseflagCoord[i].x == PlayerCoord.x && FalseflagCoord[i].y == PlayerCoord.y)
		{
			FalseflagCoord[i].x = FalseflagCoord[i].y = -1;//-1�� �ٲ㼭 ����� ������� ���
			minigame_acess_amount += 1;//�̴ϰ��� ���� Ƚ�� +1.
			Maingame_start_minigame(maingame_difficult);//���ΰ��� ���̵� �޾Ƽ� �̴ϰ��� ����
			SetTextcolor(11, 0);//���� �ٽ� �������
			Maingame_map_reprinting();//�� �ٽ� ������
		}
	}
}
int check_flag_t() // �÷��̾ �Ϲ� ��߿� ��ġ�� ��
{
	int size = flag_amount;//���� ��� ��ü ũ�� Ȯ��
	for (int i = 0; i < size; i++) // �÷��̾ ���Ƽ ��߿� ��ġ�ϴ��� Ȯ��, ��ġ�ϸ� �̺�Ʈ �߻�
	{
		if (TrueflagCoord[i].x == PlayerCoord.x && TrueflagCoord[i].y == PlayerCoord.y)
		{
			PlayerCoord.flagcount += 1;
			gotoxy(TrueflagCoord[i].x, TrueflagCoord[i].y);
			printf(" ");
			TrueflagCoord[i].x = TrueflagCoord[i].y = -1;//-1�� �ٲ㼭 ����� ������� ���.
		}
	}

	if (PlayerCoord.flagcount == size) // ��� �Ϲ� ����� �� ���� ���
	{
		system("cls");
		gotoxy(17, 7);
		printf("��� �Ϲ� ����� �� ��ҽ��ϴ�!");
		return 1;
	}

	return 0;
}
void Maingame_break_obstacle(int x, int y) //" EŰ�� ������ �� �� ������ ��ֹ��� ��! ��! 
{
	for (int i = 0; i < obstacle_amount; i++)
	{
		if (ObstacleCoord[i].x == (x - 1) && ObstacleCoord[i].y == y) // if - else if�� �θ� 1���⸸ �������� �׷��� X
		{
			gotoxy(x - 1, y);
			printf(" ");
			ObstacleCoord[i].x = ObstacleCoord[i].y = 0;
		}

		if (ObstacleCoord[i].x == (x + 1) && ObstacleCoord[i].y == y)
		{
			gotoxy(x + 1, y);
			printf(" ");
			ObstacleCoord[i].x = ObstacleCoord[i].y = 0;
		}

		if (ObstacleCoord[i].x == x && ObstacleCoord[i].y == (y - 1))
		{
			gotoxy(x, y - 1);
			printf(" ");
			ObstacleCoord[i].x = ObstacleCoord[i].y = 0;
		}

		if (ObstacleCoord[i].x == x && ObstacleCoord[i].y == (y + 1))
		{
			gotoxy(x, y + 1);
			printf(" ");
			ObstacleCoord[i].x = ObstacleCoord[i].y = 0;
		}
	}
}

extern int quiz_work_count;
//�̴ϰ��� ���� �Լ�
void Maingame_start_minigame(int difficulty)//�̴ϰ��� ��½�Ű�� �Լ�. ���⼭ ��������/����� ���� ������.
{
	int game_num = 1;//3���� ����� ���� ����.
	Maingame_show_minigame_inrush_screen();//�̴ϰ��� ���� �� UI ����ϴ� �Լ�. 
	switch (game_num) {
		case 0: GetData_show_start_screen();  GetData_game_init(difficulty); break;
		case 1: PW_show_start_screen();  PW_game_init(difficulty); break;
		case 2: 
			if(quiz_work_count <= 19)//����� ��� �� �������� ���.
			{
				quiz_show_start_screen();
				quiz_game_init(difficulty); 
				break;
			}
			else
			{
				PW_show_start_screen();  
				PW_game_init(difficulty); 
				break;
			}
	}
	if (isMinigameClear)
	{
		Maingame_get_reward();//�����Լ� ����
		Sleep(2000);
		isMinigameClear = 0;
		minigame_clear_amount += 1;//Ŭ�������� 1�� ���������ää�
	}
	else
	{
		Maingame_get_penalty();
		Sleep(2000);
	}
}
//

//�̴ϰ��� Ŭ���� �� ����Ǵ� �Լ�
void Maingame_get_reward(void) //" ������ ���� �� ��� ������ �����ϰ� ����
{
	int reward = rand() % 4; // ���� ������ ���� ��� ����
	system("cls");
	switch (reward) // ���������� ������ ���� ���߾� �Լ� ����
	{
	case 0:
		gotoxy(Mapsize->x, Mapsize->y + 6);
		printf("���̷����� ������ ������ ��ĵ���ٰ�! ������ �ﰢ�� ����� �ɰž�!");
		Maingame_reward_show_event_flag();
		break;
	case 1:
		gotoxy(Mapsize->x, Mapsize->y + 6); 
		printf("���̷����� ������ �����͸� ȸ���Ұ�!!");
		Maingame_reward_get_flag();
		break;
	case 2:
		gotoxy(Mapsize->x, Mapsize->y + 6);
		printf("�̵� ���� Ƚ���� �÷��ٰ�!\n");
		gotoxy(Mapsize->x, Mapsize->y + 7);
		printf("%d -> %d", PlayerCoord.remain_move_amount, PlayerCoord.remain_move_amount + 100);
		PlayerCoord.remain_move_amount += 100;
		break;
	case 3:
		gotoxy(Mapsize->x, Mapsize->y + 6);
		printf("��ֹ� �ı� ���� Ƚ���� �÷��ٰ�!\n");
		gotoxy(Mapsize->x, Mapsize->y + 7);
		printf("%d -> %d", PlayerCoord.limit_break, PlayerCoord.limit_break + 1);
		PlayerCoord.limit_break += 1;//��� �ı� Ƚ�� �÷��ֱ�.
		break;
	}
}

//���� �Լ���
void Maingame_reward_get_flag(void) //" �̺�Ʈ ��� 1���� ���Ƿ� ������
{
	int check_special_circumstance = 1; // ��� �̺�Ʈ ����� �� �����ų� ���ŵ� ���� �� ���� ����ΰ�?

	for (int i = 0; i < Falseflags_amount; i++)
	{
		if (FalseflagCoord[i].x != -1) // ȸ���� ����� �ϳ��� ���� �ֳ��� ���ܰ� �ƴ�.
			check_special_circumstance = 0;
	}

	int selected_flag = rand() % Falseflags_amount; // ������ ��� ����

	if (!(check_special_circumstance)) // ���� ��찡 �ƴ� ��� ��� ����
	{
		while (FalseflagCoord[selected_flag].x == -1 && FalseflagCoord[selected_flag].y == -1) // ����ų� ���ŵ� ����� ���õ��� ����
			selected_flag = rand() % Falseflags_amount;

		gotoxy(FalseflagCoord[selected_flag].x, FalseflagCoord[selected_flag].y);
		printf("@");
		Sleep(50); 
		printf(" ");
		FalseflagCoord[selected_flag].x = FalseflagCoord[selected_flag].y = -1;
	}
}
void Maingame_reward_show_event_flag(void) //" �̺�Ʈ ����� ��ġ�� ������
{
	//��ġ �����ִ� ���� : ������� �ﰢ�� ��ߵ��� ���ʴ�� ��Ÿ���� ���.
	for (int i = 0; i < Falseflags_amount; i++)
	{
		if (FalseflagCoord[i].x == -1 && FalseflagCoord[i].y == -1) // �̹� ���� �̺�Ʈ ����� ��ġ�� ����
			continue;

		gotoxy(FalseflagCoord[i].x, FalseflagCoord[i].y);
		printf("��");
		Sleep(500); 
		printf("  ");
	}
}

//�г�Ƽ
void Maingame_get_penalty()
{
	system("cls");
	int penalty = rand() % 3;
	PlayerCoord.hp--;
	switch (penalty) {
	case 0:
		printf("����� ��ġ�� �ڼ��Դϴ�!");
		Maingame_penalty_change_locate();
		break;

	case 1: //" �����ϴ� ��ҵ��� �뷱�� �����ؾ��� ���� ����
		if (PlayerCoord.remain_move_amount < 100) //" ���� �̵�Ƚ���� 100���� ������ ���� ���� ���ݸ�ŭ ����
		{
			gotoxy(Mapsize->x, Mapsize->y + 6);
			printf("�̵� ���� Ƚ���� �پ��ϴ�!!\n");
			gotoxy(Mapsize->x, Mapsize->y + 7);
			printf("%d -> %d", PlayerCoord.remain_move_amount, 
				PlayerCoord.remain_move_amount - (PlayerCoord.remain_move_amount / 2));
			PlayerCoord.remain_move_amount -= (PlayerCoord.remain_move_amount / 2);
			break;
		}
		gotoxy(Mapsize->x, Mapsize->y + 6);
		printf("�̵� ���� Ƚ���� �پ��ϴ�!!\n");
		gotoxy(Mapsize->x, Mapsize->y + 7);
		printf("%d -> %d", PlayerCoord.remain_move_amount, PlayerCoord.remain_move_amount - 100);
		PlayerCoord.remain_move_amount -= 100;
		break;

	case 2://" ���� ��ֹ� �ı� ���� Ƚ���� 0�̸� �������� X
		gotoxy(Mapsize->x, Mapsize->y + 6);
		printf("��ֹ� �ı� ���� Ƚ���� �پ��ϴ�!!\n");
		gotoxy(Mapsize->x, Mapsize->y + 7);
		printf("%d -> %d", PlayerCoord.limit_break, PlayerCoord.limit_break - 1);
		if (PlayerCoord.limit_break <= 0)
			break;

		PlayerCoord.limit_break--;
		break;
	}
}
void Maingame_penalty_change_locate(void) //" �Ϲ� ����� ��ġ ����, ��κ� ���� �ڵ� ��Ȱ��
{
	int i, j;//�ݺ����� ���� ����.
	for (i = 0; i < (flag_amount); i++) // ��¥ ����� ������ ��ġ ���� �� ��ǥ ����
	{
		int x_locate = 1 + rand() % (Mapsize->x - 5); // ����� ������ ���� �մ� ���� �߻�
		int y_locate = 1 + rand() % (Mapsize->y - 2);

		if (x_locate == 1 && y_locate == (Mapsize->y - 2) || Maingame_not_spawn_flag_on_obstacle(x_locate, y_locate)) // ���� ��ġ�� �������� �ʰԲ�
		{
			i--;
			continue;
		}
		if (TrueflagCoord[i].x == -1)//�̹� ���� ����̸�
		{
			continue;
		}
		for (j = 0; j < (flag_amount); j++) {
			if (x_locate == TrueflagCoord[j].x && y_locate == TrueflagCoord[j].y)//�ߺ� ���� �˰���
			{
				i--;
				continue;
			}
		}
		TrueflagCoord[i].x = x_locate;
		TrueflagCoord[i].y = y_locate;
	}
	for (i = 0; i < (Falseflags_amount); i++) // ��¥����� ������ ��ġ ���� �� ��ǥ ����
	{
		int x_locate = 1 + rand() % (Mapsize->x - 5); // ����� ������ ���� �մ� ���� �߻�
		int y_locate = 1 + rand() % (Mapsize->y - 2);

		if (x_locate == 1 && y_locate == (Mapsize->y - 2) || Maingame_not_spawn_flag_on_obstacle(x_locate, y_locate)) // ���� ��ġ�� �������� �ʰԲ�
		{
			i--;
			continue;
		}
		if (FalseflagCoord[i].x == -1)
		{
			continue;
		}
		for (j = 0; j < flag_amount; j++) {
			if (x_locate == TrueflagCoord[j].x && y_locate == TrueflagCoord[j].y)//�ߺ� ���� �˰���
			{
				i--;
				continue;
			}
		}
		for (j = 0; j < Falseflags_amount; j++) {
			if (x_locate == FalseflagCoord[j].x && y_locate == FalseflagCoord[j].y)//�ߺ� ���� �˰���
			{
				i--;
				continue;
			}
		}
		FalseflagCoord[i].x = x_locate;
		FalseflagCoord[i].y = y_locate;
	}
}


//���ΰ����� ���� Ŭ���������� ����Ǵ� �Լ���. 
void Maingame_gamecomplete(void) //�� ���̵��� Ŭ�����ҽ� ��µǴ� ����.
{
	Maingame_show_gamecomplete_screen();
	Sleep(500);
	int ClearTimetoStart = time(NULL) - cleartime;//Ŭ���� �ð� ���ϱ�.
	float Minigame_clear_rate = (minigame_clear_amount / (double)minigame_acess_amount) * 100;
	printf("\n Ŭ���� �ð� : %d", ClearTimetoStart);
	printf("\n ���� �̵� ���� Ƚ�� : %d", PlayerCoord.remain_move_amount);
	printf("\n �̴ϰ��� Ŭ������ : %f\n", (minigame_acess_amount) ? Minigame_clear_rate: 0.0);
	if (minigame_acess_amount == 0)
	{
		Minigame_clear_rate = 0;
	}
	printf("�� ���� : ");
	switch (maingame_difficult) {
	case Easy:
		if (ClearTimetoStart <= Easy_cleartime_rate_S)
			printf("S");
		else if (ClearTimetoStart <= Easy_cleartime_rate_A)
			printf("A");
		else if (ClearTimetoStart <= Easy_cleartime_rate_B)
			printf("B");
		else if (ClearTimetoStart <= Easy_cleartime_rate_C)
			printf("C");
		else 
			printf("D");

		if (PlayerCoord.remain_move_amount >= Easy_remain_walk_rate_S)
			printf("S");
		else if (PlayerCoord.remain_move_amount >= Easy_remain_walk_rate_A)
			printf("A");
		else if (PlayerCoord.remain_move_amount >= Easy_remain_walk_rate_B)
			printf("B");
		else if (PlayerCoord.remain_move_amount >= Easy_remain_walk_rate_C)
			printf("C");
		else
			printf("D");

		if (Minigame_clear_rate >= Easy_Minigame_clear_rate_S)
			printf("S");
		else if (Minigame_clear_rate >= Easy_Minigame_clear_rate_A)
			printf("A");
		else if (Minigame_clear_rate >= Easy_Minigame_clear_rate_B)
			printf("B");
		else if (Minigame_clear_rate >= Easy_Minigame_clear_rate_C)
			printf("C");
		else if (minigame_acess_amount == 0)
			printf("�� ã���� ���!");
		else
			printf("D");
		break;

	case Normal:
		if (ClearTimetoStart <= Normal_cleartime_rate_S)
			printf("S");
		else if (ClearTimetoStart <= Normal_cleartime_rate_A)
			printf("A");
		else if (ClearTimetoStart <= Normal_cleartime_rate_B)
			printf("B");
		else if (ClearTimetoStart <= Normal_cleartime_rate_C)
			printf("C");
		else
			printf("D");

		if (PlayerCoord.remain_move_amount >= Normal_remain_walk_rate_S)
			printf("S");
		else if (PlayerCoord.remain_move_amount >= Normal_remain_walk_rate_A)
			printf("A");
		else if (PlayerCoord.remain_move_amount >= Normal_remain_walk_rate_B)
			printf("B");
		else if (PlayerCoord.remain_move_amount >= Normal_remain_walk_rate_C)
			printf("C");
		else
			printf("D");

		if (Minigame_clear_rate >= Normal_Minigame_clear_rate_S)
			printf("S");
		else if (Minigame_clear_rate >= Normal_Minigame_clear_rate_A)
			printf("A");
		else if (Minigame_clear_rate >= Normal_Minigame_clear_rate_B)
			printf("B");
		else if (Minigame_clear_rate >= Normal_Minigame_clear_rate_C)
			printf("C");
		else if (minigame_acess_amount == 0)
			printf("�� ã���� ���!");
		else
			printf("D");
		break;

	case Hard:
		if (ClearTimetoStart <= Hard_cleartime_rate_S)
			printf("S");
		else if (ClearTimetoStart <= Hard_cleartime_rate_A)
			printf("A");
		else if (ClearTimetoStart <= Hard_cleartime_rate_B)
			printf("B");
		else if (ClearTimetoStart <= Hard_cleartime_rate_C)
			printf("C");
		else
			printf("D");

		if (PlayerCoord.remain_move_amount >= Hard_remain_walk_rate_S)
			printf("S");
		else if (PlayerCoord.remain_move_amount >= Hard_remain_walk_rate_A)
			printf("A");
		else if (PlayerCoord.remain_move_amount >= Hard_remain_walk_rate_B)
			printf("B");
		else if (PlayerCoord.remain_move_amount >= Hard_remain_walk_rate_C)
			printf("C");
		else
			printf("D");

		if (Minigame_clear_rate >= Hard_Minigame_clear_rate_S)
			printf("S");
		else if (Minigame_clear_rate >= Hard_Minigame_clear_rate_A)
			printf("A");
		else if (Minigame_clear_rate >= Hard_Minigame_clear_rate_B)
			printf("B");
		else if (Minigame_clear_rate >= Hard_Minigame_clear_rate_C)
			printf("C");
		else if (minigame_acess_amount == 0)
			printf("�� ã���� ���!");
		else
			printf("D");
		break;

	default:
		break;
	}
	Sleep(2000);




	//�����޸� �Ҵ� ������
	free(FalseflagCoord); //" ���� �޸� ���� �������� ��� �ϴ� ���α׷� ���� �����̴� �߰�(���ع�)
	free(TrueflagCoord);
	free(Mapsize);
	free(ObstacleCoord);
}
void Maingame_gameover(void) //" ���� ������ ��µǴ� ȭ��
{
	Maingame_show_gameover_screen();
	exit(1);//�ٷ� ���������ع���. 
	free(FalseflagCoord); //" ���� �޸� ���� �������� ��� �ϴ� ���α׷� ���� �����̴� �߰�(���ع�)
	free(TrueflagCoord);
	free(Mapsize);
	free(ObstacleCoord);
}



/*
----------------------------


���̵��: ��Ģ�� �ִ� ���, ��¥ ���, ��� ���߸� ����, Ʋ���� ��Ģ�� �ִ� ���

	-> ���� ��� ����:
		1. C���α׷��� �Ϲ� ����
		2. ��ǻ�Ͱ��а��� �Ϲ� ����
		3.
		4.
		5.

	-> ��Ģ ��� ����:
		1. �ð� ����
		2. ü�� ����
		3. ������ ��ƼƼ �߰� - ex) ���� ����Ʈ���� or ���
		4. ���� ��� ��ġ ����(����?)
		5. ���̵� ������� ��� ��Ģ X, �ٷ� Game Over(�翬�� ��Ģ�� �ִ� ��ߵ� X)

	-> ���� ��� ����:
		1. ���Ƽ ��߰� �Ϲ� ����� �� ����(yes)
		2. ���Ƽ ��� ����(yes)
		3. ���� ����
		4. �ð� ����
		5. ü�� ����
		6. ��ֹ� ����
*/