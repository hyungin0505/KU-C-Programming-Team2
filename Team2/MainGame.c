#include "Maingame_header.h"
#include "GameUI.h"
#include "MiniGame.h"



#define Tutorial_flags_amount 3
#define Tutorial_falseflag_amount 0
#define Tutorial_Obstacle_amount 60
#define Tutorial_Map_Max_x 15
#define Tutorial_Map_Max_y 10
#define Tutorial_Player_Hp 10
#define Tutorial_Player_move_amount 500
#define Tutorial_Obstacle_amount_min 3
#define Tutorial_Obstacle_amount_max 6
#define Tutorial_Player_Limit_Break 10

//기본적인 기호상수 선언, 이지 노말 하드별로 나눠놨으니까 이 값만 바꿔주면 요소가 바뀜.
#define Easy_flags_amount 2//일반 깃발 개수
#define Easy_falseflag_amount 1//들어가면 미니게임이 나오는 깃발. 
//목표 깃발 : 전체 깃발(falgs amount) - 가짜 깃발(falseflase)
#define Easy_Map_Max_x 20//x축 좌표
#define Easy_Map_Max_y 10//y축 좌표
#define Easy_Player_Hp 5//플레이어 체력
#define Easy_Player_move_amount 150//플레이어가 움직일 수 있는 횟수
#define Easy_Obstacle_amount 100
#define Easy_Obstacle_amount_min 7
#define Easy_Obstacle_amount_max 10
#define Easy_Limit_Break 5

//
#define Normal_flags_amount 25
#define Normal_falseflag_amount 5
#define Normal_Map_Max_x 40
#define Normal_Map_Max_y 20
#define Normal_Player_Hp 3
#define Normal_Player_move_amount 400
#define Normal_Obstacle_amount 440
#define Normal_Obstacle_amount_min 15
#define Normal_Obstacle_amount_max 22
#define Normal_Limit_Break 6
//
#define Hard_flags_amount 35
#define Hard_falseflag_amount 15
#define Hard_Map_Max_x 60
#define Hard_Map_Max_y 29 // Windows 10 환경에서는 30으로 설정해도 상관 X
#define Hard_Player_Hp 1
#define Hard_Player_move_amount 700
#define Hard_Obstacle_amount 1200
#define Hard_Obstacle_amount_min 30
#define Hard_Obstacle_amount_max 40
#define Hard_Limit_Break 7
//
// 평가 기준 정의

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


//열거형 정의
typedef enum difficultyy {
	Easy,///각각 0, 1, 2,4 에 대응합니다
	Normal,
	Hard,
	End,
	Tutorial
}Gamedifficulty;

//전체 전역변수 선언. 

int isMinigameClear = 0;

void Maingame_Base_init(int); // 콘솔창 및 난수 등의 기본 요소 설정. 여기서부터 차례대로 초기화되는 방식 // 맵 구성 요소(벽, 깃발, 장애물) 관련 설정
void Game_start(); //게임 시작하는 함수
//init -> printing -> element_init 순서로 작동함!
void on_flag_f(); // 플레이어가 깃발에 위치할 때
int check_flag_t(); // 플레이어가 모은 일반 갯발을 확인

//맵 생성 위한 전역변수 선언
Obje_Coord* Mapsize;//맵사이즈
Obje_Coord* TrueflagCoord;//진짜 깃발 좌표
Obje_Coord* FalseflagCoord;//구라 좌표 좌표
Obje_Coord* ObstacleCoord;//장애물 좌표. 
Player_Coord PlayerCoord;
int obstacle_amount;//장애물 개수
int obstacle_amount_min;//최소 개수
int obstacle_amount_max;//최대 개수
int maingame_difficult;//난이도
int flag_amount;//모아야 하는 깃발 갯수
int Falseflags_amount;//가짜 깃발 개수 

//스코어판에서 비교해야 하는 값들
int cleartime;//클리어하는데 걸린 시간. 
int minigame_acess_amount;//미니게임 작동시킨 횟수
int minigame_clear_amount;//미니게임 클리어한 횟수.
//	
void Maingame_Base_init(int difficulty) //(전역변수로 수정 완료) 콘솔창 및 난수 및 오브젝트 및 장애물 및 등등의.. 기본 요소 설정
{
	srand((unsigned)time(NULL));
	system("mode con: cols=150 lines=40"); // 콘솔창의 크기 설정, cols = 행, lines = 열
	CursorClosing();
	SetTextcolor(11, 0); // 출력될 텍스트의 색상
	Mapsize = (Obje_Coord*)malloc(sizeof(Obje_Coord));//맵사이즈
	switch (difficulty)
	{
	case Tutorial:
		Mapsize->x = Tutorial_Map_Max_x;
		Mapsize->y = Tutorial_Map_Max_y;
		TrueflagCoord = (Obje_Coord*)calloc(Tutorial_flags_amount, sizeof(Obje_Coord));
		FalseflagCoord = (Obje_Coord*)calloc(Tutorial_falseflag_amount, sizeof(Obje_Coord));
		maingame_difficult = Tutorial;
		flag_amount = Tutorial_flags_amount;
		Falseflags_amount = Tutorial_falseflag_amount;
		ObstacleCoord = (Obje_Coord*)calloc(Tutorial_Obstacle_amount, sizeof(Obje_Coord));
		obstacle_amount = Tutorial_Obstacle_amount;
		obstacle_amount_min = Tutorial_Obstacle_amount_min;
		obstacle_amount_max = Tutorial_Obstacle_amount_max;
		Maingame_how_to_play();
		break;
	case Easy:
		Mapsize->x = Easy_Map_Max_x;
		Mapsize->y = Easy_Map_Max_y;
		TrueflagCoord = (Obje_Coord*)calloc((Easy_flags_amount), sizeof(Obje_Coord));//동적할당.
		FalseflagCoord = (Obje_Coord*)calloc(Easy_falseflag_amount, sizeof(Obje_Coord));//동적할당.
		maingame_difficult = Easy;
		flag_amount = Easy_flags_amount;
		Falseflags_amount = Easy_falseflag_amount;
		ObstacleCoord = (Obje_Coord*)calloc((Easy_Obstacle_amount), sizeof(Obje_Coord));
		obstacle_amount = Easy_Obstacle_amount;
		obstacle_amount_min = Easy_Obstacle_amount_min;
		obstacle_amount_max = Easy_Obstacle_amount_max;
		break;
	case Normal:
		Mapsize->x = Normal_Map_Max_x;
		Mapsize->y = Normal_Map_Max_y;
		TrueflagCoord = (Obje_Coord*)calloc((Normal_flags_amount), sizeof(Obje_Coord));//동적할당.
		FalseflagCoord = (Obje_Coord*)calloc(Normal_falseflag_amount, sizeof(Obje_Coord));//동적할당.
		maingame_difficult = Normal;
		flag_amount = Normal_flags_amount;
		Falseflags_amount = Normal_falseflag_amount;
		ObstacleCoord = (Obje_Coord*)calloc((Normal_Obstacle_amount), sizeof(Obje_Coord));
		obstacle_amount = Normal_Obstacle_amount;
		obstacle_amount_min = Normal_Obstacle_amount_min;
		obstacle_amount_max = Normal_Obstacle_amount_max;
		break;
	case Hard:
		Mapsize->x = Hard_Map_Max_x;
		Mapsize->y = Hard_Map_Max_y;
		TrueflagCoord = (Obje_Coord*)calloc((Hard_flags_amount), sizeof(Obje_Coord));//동적할당.
		FalseflagCoord = (Obje_Coord*)calloc(Hard_falseflag_amount, sizeof(Obje_Coord));//동적할당.
		ObstacleCoord = (Obje_Coord*)calloc((Hard_Obstacle_amount), sizeof(Obje_Coord));
		maingame_difficult = Hard;
		flag_amount = Hard_flags_amount;
		Falseflags_amount = Hard_falseflag_amount;
		obstacle_amount = Hard_Obstacle_amount;
		obstacle_amount_min = Hard_Obstacle_amount_min;
		obstacle_amount_max = Hard_Obstacle_amount_max;
		break;
		//게임 엔딩 함수
	}
	cleartime = time(NULL);//현재 시간 측정함.
	minigame_clear_amount = minigame_acess_amount = 0;
	Maingame_map_printing();
	Maingame_map_element_init();
	Game_start();
}



void Maingame_map_printing()//(전역변수수정완!)맵 출력하는 함수, Mapsize는 맵 크기임
{
	for (int i = 0; i <= Mapsize->y; i++) // 기본 맵 출력 방식. 이번엔 맥스 x, 맥스 y를 기준으로 했음.
	{
		for (int j = 0; j <= Mapsize->x; j++)
		{
			if ((i == 0) && (j == 0))
				printf("#");//출력하는 문자는 샵으로 함.(다른 문자를 쓰면 더러워짐)

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
void Maingame_map_element_init() // 맵 구성 요소(벽, 깃발, 장애물) 관련 설정
{
	int FLAGS_T, FLAGS_F;//각각 깃발이 몇개인지 확인.
	FLAGS_F = Falseflags_amount;
	FLAGS_T = flag_amount;//구조체 배열을 구조체 크기로 나눠서 각자의 원래 크기를 알아내는 작업.
	int i, j;//반복문 제어용 변수//장애물 개수.
	int current_obstacle_amount = 0;
	for (i = 2; i < Mapsize->y - 1; i++) // 장애물이 생성될 위치 결정(맨 첫 줄과 맨 아랫 줄 제외)
	{
		int obstacle_in_line = obstacle_amount_min + (rand() % (Mapsize->x - 6)); // 각 행마다 생성할 장애물 갯수 랜덤 지정

		if (obstacle_in_line > obstacle_amount_max) // 각 줄당 장애물 최댓값은 넘지 않게 설정
		{
			while (obstacle_in_line != obstacle_amount_max)
				obstacle_in_line--;
		}

		for (j = 1; j < obstacle_in_line; j++) // x축에서 생성할 장애물 갯수 랜덤 지정
		{
			int obstacle_x = 2 + rand() % (Mapsize->x - 4); // 장애물의 x 좌표
			current_obstacle_amount++;
			if (current_obstacle_amount >= obstacle_amount)
				break;
			gotoxy(obstacle_x, i); // 장애물 배치, 특수문자는 ▣
			printf("#");

			ObstacleCoord[current_obstacle_amount].x = obstacle_x;
			ObstacleCoord[current_obstacle_amount].y = i;
		}
	}
	for (i = 0; i < (FLAGS_T); i++) // 진짜 깃발이 생성될 위치 결정 및 좌표 저장
	{
		int x_locate = 1 + rand() % (Mapsize->x - 5); // 깃발이 오른쪽 벽을 뚫는 오류 발생
		int y_locate = 1 + rand() % (Mapsize->y - 2);

		if (x_locate == 1 && y_locate == (Mapsize->y - 2) || Maingame_not_spawn_flag_on_obstacle(x_locate, y_locate)) // 스폰 위치에 생성되지 않게끔
		{
			i--;
			continue;
		}
		for (j = 0; j < FLAGS_T; j++) {
			if (x_locate == TrueflagCoord[j].x && y_locate == TrueflagCoord[j].y)//중복 방지 알고리즘
			{
				i--;
				continue;
			}
		}
		gotoxy(x_locate, y_locate);//이 모든 검증을 통과하면
		printf("@"); // 깃발 디자인 후보군 ▩★■▤▥▷▶
		TrueflagCoord[i].x = x_locate;
		TrueflagCoord[i].y = y_locate;
	}
	for (i = 0; i < (FLAGS_F); i++) // 가짜깃발이 생성될 위치 결정 및 좌표 저장
	{
		int x_locate = 1 + rand() % (Mapsize->x - 5); // 깃발이 오른쪽 벽을 뚫는 오류 발생
		int y_locate = 1 + rand() % (Mapsize->y - 2);

		if (x_locate == 1 && y_locate == (Mapsize->y - 2) || Maingame_not_spawn_flag_on_obstacle(x_locate, y_locate)) // 스폰 위치에 생성되지 않게끔
		{
			i--;
			continue;
		}
		for (j = 0; j < FLAGS_T; j++) {
			if (x_locate == TrueflagCoord[j].x && y_locate == TrueflagCoord[j].y)//중복 방지 알고리즘
			{
				i--;
				continue;
			}
		}
		for (j = 0; j < FLAGS_F; j++) {
			if (x_locate == FalseflagCoord[j].x && y_locate == FalseflagCoord[j].y)//중복 방지 알고리즘
			{
				i--;
				continue;
			}
		}
		gotoxy(x_locate, y_locate);//이 모든 검증을 통과하면
		printf("@"); // 깃발 디자인 후보군 ▩★■▤▥▷▶
		FalseflagCoord[i].x = x_locate;
		FalseflagCoord[i].y = y_locate;
	}
	gotoxy(Mapsize->x + 10, 2); //" 사용된 기호에 대한 정의
	printf("\"E\": 방화벽 파괴(주변 4방향)");

	gotoxy(Mapsize->x + 10, Mapsize->y); //" 사용된 기호에 대한 정의
	printf("@: 데이터  #: 방화벽  *: 플레이어"); // 특수문자 적용시 ▷: 깃발  ▣: 장애물  *: 플레이어
}
void Maingame_map_reprinting()//다시 게임으로 돌아갈때 시행되는 함수.
{
	system("cls");
	Maingame_map_printing();
	int i;//반복문용 더미 변수
	for (i = 0; i < obstacle_amount; i++) // 장애물 생성.
	{
		if (ObstacleCoord[i].x == -1)//좌표가 -1이면 사라진 깃발이라는거임. 
			continue;
		gotoxy(ObstacleCoord[i].x, ObstacleCoord[i].y); // 장애물 배치
		printf("#"); //특수문자는 ▣
	}
	for (i = 0; i < (flag_amount); i++) // 진짜 깃발이 생성될 위치 결정 및 좌표 저장
	{
		if (TrueflagCoord[i].x == -1)//이미 사라진 깃발에 접근하는 경우
			continue;
		gotoxy(TrueflagCoord[i].x, TrueflagCoord[i].y);//이 모든 검증을 통과하면
		printf("@"); // 깃발 디자인 후보군 ▩★■▤▥▷▶, 특수문자는 ▷
	}
	for (i = 0; i < (Falseflags_amount); i++) // 진짜 깃발이 생성될 위치 결정 및 좌표 저장
	{
		if (FalseflagCoord[i].x == -1)//이미 사라진 깃발에 접근하는 경우
			continue;
		gotoxy(FalseflagCoord[i].x, FalseflagCoord[i].y);//이 모든 검증을 통과하면
		printf("@"); // 깃발 디자인 후보군 ▩★■▤▥▷▶, 특수문자는 ▷
	}

	gotoxy(Mapsize->x + 10, 2); //" 사용된 기호에 대한 정의
	printf("\"E\": 방화벽 파괴(주변 4방향)");

	gotoxy(Mapsize->x + 10, Mapsize->y); //" 사용된 기호에 대한 정의
	printf("@: 데이터  #: 방화벽  *: 플레이어"); // 특수문자 적용시 ▷: 깃발  ▣: 장애물  *: 플레이어

	gotoxy(PlayerCoord.x, PlayerCoord.y);
	printf("*\b");

}

void Game_start()
{
	PlayerCoord.x = 2;//플레이어 정보가 초기화되는 영역
	PlayerCoord.y = (Mapsize->y - 1);//플레이어 스폰 좌표 지정
	PlayerCoord.flagcount = 0;//플레이어가 모은 깃발 지정
	switch (maingame_difficult)
	{
	case Tutorial:
		PlayerCoord.hp = Tutorial_Player_Hp;
		PlayerCoord.remain_move_amount = Tutorial_Player_move_amount;
		PlayerCoord.limit_break = Tutorial_Player_Limit_Break;
		break;
	case Easy:
		PlayerCoord.hp = Easy_Player_Hp;//남은 hp
		PlayerCoord.remain_move_amount = Easy_Player_move_amount;//남은 이동 횟수
		PlayerCoord.limit_break = Easy_Limit_Break;//남은 장애물 제거 횟수
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
		on_flag_f(); // 플레이어가 페널티 깃발을 얻었는지 확인

		if (check_flag_t()) // 플레이어가 일반 깃발을 얻었는지, 다 모았는지 확인
		{
			Maingame_gamecomplete();
			Sleep(1000); // 다 모은 경우 성공 화면 출력, 1초 후 프로그램 종료.
			break;
		}
		if (PlayerCoord.remain_move_amount == 0 || PlayerCoord.hp == 0)
			//" 이동횟수나 hp가 0이 되었는지 확인
		{
			Maingame_gameover(); //" 해당하면 Game Over 화면 출력
			Sleep(1000);
			break;
		}
		gotoxy(Mapsize->x + 10, Mapsize->y - 3);//남은 깃발 수 출력해주는 printf
		printf("                      ");
		gotoxy(Mapsize->x + 10, Mapsize->y - 3);
		printf("남은 데이터의 수: %d", (flag_amount)-PlayerCoord.flagcount); //남은 깃발 수 확인
		gotoxy(Mapsize->x + 10, Mapsize->y - 5);
		printf("                         ");
		gotoxy(Mapsize->x + 10, Mapsize->y - 5);
		printf("남은 이동횟수: %3d", PlayerCoord.remain_move_amount); //" 남은 이동횟수 확인
		gotoxy(Mapsize->x + 10, Mapsize->y - 4);
		printf("                                      ");//공백으로 지워주는 작업
		gotoxy(Mapsize->x + 10, Mapsize->y - 4);
		printf("남은 방화벽 파괴 횟수: %d", PlayerCoord.limit_break);
		gotoxy(Mapsize->x + 10, Mapsize->y - 6);
		printf("                                      ");//공백으로 지워주는 작업
		gotoxy(Mapsize->x + 10, Mapsize->y - 6);
		printf("남은 배터리: %d", PlayerCoord.hp);//" 남은 장애물 파괴 가능 횟수 확인
		gotoxy(PlayerCoord.x, PlayerCoord.y);
		ch = _getch();

		if (ch == 224) // 방향키 처리, 맵 뚫고 나가는 버그 있으면 여기 부분 값 수정해주면 됨
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
		else if (ch == 101) // 키보드 상에서 E키를 누르면 주변 4방향의 장애물이 사라짐
		{
			if (PlayerCoord.limit_break != 0)
			{
				Maingame_break_obstacle(PlayerCoord.x, PlayerCoord.y);
				PlayerCoord.limit_break--;
			}
		}
		//디버깅용 함수들.
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
		else if (ch == 'h')
		{
			BoxGame_init(maingame_difficult);
		}
	}
	//성공했을 때 함수 들어갈 자리
	//실패했을 때 함수 들어갈 자리.
}


int Maingame_not_spawn_flag_on_obstacle(int x_locate, int y_locate) // 깃발이 장애물이 생성된 위치에 덮어 씌워져 생성되지 않도록 체크!
{
	for (int i = 0; i < obstacle_amount; i++)
	{
		if (ObstacleCoord[i].x == x_locate && ObstacleCoord[i].y == y_locate)
			return 1;
	}

	return 0;
}
int Maingame_check_locate_obstacle(int x, int y) // 장애물에 충돌 예정인지 확인함. 
{
	for (int i = 0; i < obstacle_amount; i++)
	{
		if (ObstacleCoord[i].x == x && ObstacleCoord[i].y == y)
			return 1;
	}
	return 0;
}
void on_flag_f() // 플레이어가 페널티 깃발에 위치할 때
{
	int size = Falseflags_amount;//패널티 깃발 전체 크기 확인
	for (int i = 0; i < size; i++) // 플레이어가 페널티 깃발에 위치하는지 확인, 위치하면 이벤트 발생
	{
		if (FalseflagCoord[i].x == PlayerCoord.x && FalseflagCoord[i].y == PlayerCoord.y)
		{
			FalseflagCoord[i].x = FalseflagCoord[i].y = -1;//-1로 바꿔서 사라진 깃발임을 명시
			minigame_acess_amount += 1;//미니게임 접근 횟수 +1.
			Maingame_start_minigame(maingame_difficult);//메인게임 난이도 받아서 미니게임 돌입
			SetTextcolor(11, 0);//색상 다시 원래대로
			Maingame_map_reprinting();//맵 다시 프린팅
		}
	}
}
int check_flag_t() // 플레이어가 일반 깃발에 위치할 때
{
	int size = flag_amount;//보상 깃발 전체 크기 확인
	for (int i = 0; i < size; i++) // 플레이어가 페널티 깃발에 위치하는지 확인, 위치하면 이벤트 발생
	{
		if (TrueflagCoord[i].x == PlayerCoord.x && TrueflagCoord[i].y == PlayerCoord.y)
		{
			PlayerCoord.flagcount += 1;
			gotoxy(TrueflagCoord[i].x, TrueflagCoord[i].y);
			printf(" ");
			TrueflagCoord[i].x = TrueflagCoord[i].y = -1;//-1로 바꿔서 사라진 깃발임을 명시.
		}
	}

	if (PlayerCoord.flagcount == size) // 모든 일반 깃발을 다 모은 경우
	{
		system("cls");
		gotoxy(17, 7);
		printf("모든 일반 깃발을 다 모았습니다!");
		return 1;
	}

	return 0;
}
void Maingame_break_obstacle(int x, int y) //" E키를 눌렀을 때 그 방향의 장애물을 파! 괴! 
{
	for (int i = 0; i < obstacle_amount; i++)
	{
		if (ObstacleCoord[i].x == (x - 1) && ObstacleCoord[i].y == y) // if - else if로 두면 1방향만 없어져서 그러면 X
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
//미니게임 실행 함수
void Maingame_start_minigame(int difficulty)//미니게임 출력시키는 함수. 여기서 버프유무/디버프 유무 결정함.
{
	int game_num = rand() % 6; //3으로 나누어서 게임 시작.
	Maingame_show_minigame_inrush_screen();//미니게임 돌입 전 UI 출력하는 함수. 
	switch (game_num) {
	case 0: GetData_show_start_screen();  GetData_game_init(difficulty); break;
	case 1: PW_show_start_screen();  PW_game_init(difficulty); break;
	case 2:
		if (quiz_work_count <= 19)//저장된 퀴즈를 다 내보냈을 경우.
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
	case 3: BoxGame_show_start_screen(); BoxGame_init(difficulty); break;
	case 4: TicTacToe_show_start_screen(); TicTacToe_init(difficulty); break;
	case 5: UpdowmGame_show_start_screen(); UpdownGame_init(difficulty); break;
	}
	if (isMinigameClear)
	{
		Maingame_get_reward();//보상함수 실행
		Sleep(2000);
		isMinigameClear = 0;
		minigame_clear_amount += 1;//클리어율을 1로 만들어버려ㅓㅓㅓ
	}
	else
	{
		Maingame_get_penalty();
		Sleep(2000);
	}
}
//

//미니게임 클리어 후 실행되는 함수
void Maingame_get_reward(void) //" 수많은 보상 중 어느 보상을 랜덤하게 지정
{
	int reward = rand() % 4; // 현재 보상은 랜덤 출력 설정
	system("cls");
	switch (reward) // 열거형으로 정의한 보상에 맞추어 함수 동작
	{
	case 0:
		// printf("바이러스에 감염된 파일을 스캔해줄게! 파일이 삼각형 모양이 될거야!");
		gotoxy(Mapsize->x, Mapsize->y + 6); printf("+----------------------------------------------------------+");
		gotoxy(Mapsize->x, Mapsize->y + 7); printf("|                                                          |");
		gotoxy(Mapsize->x, Mapsize->y + 8); printf("|                                                          |");
		gotoxy(Mapsize->x, Mapsize->y + 9); printf("|                                                          |");
		gotoxy(Mapsize->x, Mapsize->y + 10); printf("|                                                          |");
		gotoxy(Mapsize->x, Mapsize->y + 11); printf("|                                                          |");
		gotoxy(Mapsize->x, Mapsize->y + 12); printf("+----------------------------------------------------------+");

		gotoxy(Mapsize->x + 3, Mapsize->y + 8); typewriterEffect("전체 파일을 스캔 중입니다...", 20);

		gotoxy(Mapsize->x + 32, Mapsize->y + 8); spinningBarAnimation(2500);

		// printf("전체 파일을 스캔합니다.");
		gotoxy(Mapsize->x, Mapsize->y + 8); typewriterEffect("|                                                          |", 0);

		gotoxy(Mapsize->x + 3, Mapsize->y + 8); typewriterEffect("파일 스캔이 완료되었습니다!                    ", 20);
		gotoxy(Mapsize->x + 3, Mapsize->y + 10); typewriterEffect("바이러스에 감염된 파일의 위치가 느낌표로 표시됩니다.", 20);
		// printf("바이러스에 감염된 파일이 삼각형으로 표시됩니다.");
		Maingame_reward_show_event_flag();

		break;
	case 1:
		gotoxy(Mapsize->x, Mapsize->y + 6); printf("+----------------------------------------------------------+");
		gotoxy(Mapsize->x, Mapsize->y + 7); printf("|                                                          |");
		gotoxy(Mapsize->x, Mapsize->y + 8); printf("|                                                          |");
		gotoxy(Mapsize->x, Mapsize->y + 9); printf("|                                                          |");
		gotoxy(Mapsize->x, Mapsize->y + 10); printf("+----------------------------------------------------------+");

		gotoxy(Mapsize->x + 3, Mapsize->y + 8); typewriterEffect("! 위치에 있는 파일 1개를 획득합니다!", 20);
		// printf("바이러스에 감염된 데이터를 회수할게!!")
		Maingame_reward_get_flag();
		break;
	case 2:
		gotoxy(Mapsize->x, Mapsize->y + 6); printf("+----------------------------------------+");
		gotoxy(Mapsize->x, Mapsize->y + 7); printf("|                                        |");
		gotoxy(Mapsize->x, Mapsize->y + 8); printf("|                                        |");
		gotoxy(Mapsize->x, Mapsize->y + 9); printf("|                                        |");
		gotoxy(Mapsize->x, Mapsize->y + 10); printf("|                                        |");
		gotoxy(Mapsize->x, Mapsize->y + 11); printf("|                                        |");
		gotoxy(Mapsize->x, Mapsize->y + 12); printf("+----------------------------------------+");

		gotoxy(Mapsize->x + 3, Mapsize->y + 8); typewriterEffect("이동 가능 횟수가 증가합니다!", 20);
		// printf("이동 가능 횟수를 늘려줄게!\n");

		gotoxy(Mapsize->x + 3, Mapsize->y + 10); printf("이동 가능 횟수: %d -> %d", PlayerCoord.remain_move_amount, PlayerCoord.remain_move_amount + 100);

		PlayerCoord.remain_move_amount += 100;
		break;

	case 3:
		gotoxy(Mapsize->x, Mapsize->y + 6); printf("+-----------------------------------------+");
		gotoxy(Mapsize->x, Mapsize->y + 7); printf("|                                         |");
		gotoxy(Mapsize->x, Mapsize->y + 8); printf("|                                         |");
		gotoxy(Mapsize->x, Mapsize->y + 9); printf("|                                         |");
		gotoxy(Mapsize->x, Mapsize->y + 10); printf("|                                         |");
		gotoxy(Mapsize->x, Mapsize->y + 11); printf("|                                         |");
		gotoxy(Mapsize->x, Mapsize->y + 12); printf("+-----------------------------------------+");

		gotoxy(Mapsize->x + 3, Mapsize->y + 8); typewriterEffect("방화벽 파괴 가능 횟수가 증가합니다!", 20);
		// printf("장애물 파괴 가능 횟수를 늘려줄게!\n");

		gotoxy(Mapsize->x + 3, Mapsize->y + 10); printf("방화벽 파괴 가능 횟수: %d -> %d", PlayerCoord.limit_break, PlayerCoord.limit_break + 1);

		PlayerCoord.limit_break += 1; // 블록 파괴 횟수 늘려주기.
		break;
	}
}

//보상 함수들
void Maingame_reward_get_flag(void) //" 이벤트 깃발 1개를 임의로 삭제함
{
	int check_special_circumstance = 1; // 모든 이벤트 깃발을 다 모으거나 제거된 상태 등 예외 경우인가?

	for (int i = 0; i < flag_amount; i++)
	{
		if (TrueflagCoord[i].x != -1) // 회수할 깃발이 하나라도 남아 있나면 예외가 아님.
			check_special_circumstance = 0;
	}

	int selected_flag = rand() % flag_amount; // 임의의 깃발 선택

	if (!(check_special_circumstance)) // 예외 경우가 아닌 경우 깃발 제거
	{
		while (TrueflagCoord[selected_flag].x == -1 && TrueflagCoord[selected_flag].y == -1) // 얻었거나 제거된 깃발은 선택되지 않음
			selected_flag = rand() % Falseflags_amount;

		gotoxy(TrueflagCoord[selected_flag].x, TrueflagCoord[selected_flag].y);
		printf("!"); //특수문자는 ▷
		Sleep(50);
		printf(" ");
		TrueflagCoord[selected_flag].x = TrueflagCoord[selected_flag].y = -1;
		PlayerCoord.flagcount++;
	}
}

void Maingame_reward_show_event_flag(void) //" 이벤트 깃발의 위치를 보여줌
{
	//위치 보여주는 로직 : 허공에서 삼각형 깃발들이 차례대로 나타나는 방식.
	for (int i = 0; i < Falseflags_amount; i++)
	{
		if (FalseflagCoord[i].x == -1 && FalseflagCoord[i].y == -1) // 이미 얻은 이벤트 깃발의 위치는 생략
			continue;

		gotoxy(FalseflagCoord[i].x, FalseflagCoord[i].y);
		printf("!"); //특수문자는 ▶
		Sleep(500);
		printf("  ");
	}
}


//패널티
void Maingame_get_penalty()
{
	system("cls");
	int penalty = rand() % 3;
	PlayerCoord.hp--;
	switch (penalty) {
	case 0:
		gotoxy(Mapsize->x, Mapsize->y + 6); printf("+-----------------------------+");
		gotoxy(Mapsize->x, Mapsize->y + 7); printf("|                             |");
		gotoxy(Mapsize->x, Mapsize->y + 8); printf("|                             |");
		gotoxy(Mapsize->x, Mapsize->y + 9); printf("|                             |");
		gotoxy(Mapsize->x, Mapsize->y + 10); printf("+-----------------------------+");
		gotoxy(Mapsize->x + 3, Mapsize->y + 8); typewriterEffect("깃발의 위치가 뒤섞입니다!", 20);
		Maingame_penalty_change_locate();
		break;

	case 1: //" 감소하는 요소들은 밸런스 조정해야할 수도 있음
		gotoxy(Mapsize->x, Mapsize->y + 6); printf("+--------------------------------------+");
		gotoxy(Mapsize->x, Mapsize->y + 7); printf("|                                      |");
		gotoxy(Mapsize->x, Mapsize->y + 8); printf("|                                      |");
		gotoxy(Mapsize->x, Mapsize->y + 9); printf("|                                      |");
		gotoxy(Mapsize->x, Mapsize->y + 10); printf("|                                      |");
		gotoxy(Mapsize->x, Mapsize->y + 11); printf("|                                      |");
		gotoxy(Mapsize->x, Mapsize->y + 12); printf("+--------------------------------------+");

		if (PlayerCoord.remain_move_amount <= 100) //" 남은 이동횟수가 100보다 적으면 남은 수의 절반만큼 차감
		{
			gotoxy(Mapsize->x + 3, Mapsize->y + 8); typewriterEffect("이동 가능 횟수가 감소합니다!", 20);
			gotoxy(Mapsize->x + 3, Mapsize->y + 10); printf("이동 가능 횟수: %d -> %d", PlayerCoord.remain_move_amount, PlayerCoord.remain_move_amount - (PlayerCoord.remain_move_amount / 2));
			PlayerCoord.remain_move_amount -= (PlayerCoord.remain_move_amount / 2);
			break;
		}
		else {
			gotoxy(Mapsize->x + 3, Mapsize->y + 8); typewriterEffect("이동 가능 횟수가 감소합니다!", 20);
			gotoxy(Mapsize->x + 3, Mapsize->y + 10); printf("이동 가능 횟수: %d -> %d", PlayerCoord.remain_move_amount, PlayerCoord.remain_move_amount - 100);
			PlayerCoord.remain_move_amount -= 100;
		}

		break;

	case 2://" 남은 장애물 파괴 가능 횟수가 0이면 감소하지 X
		if (PlayerCoord.limit_break <= 0) {
			Maingame_get_penalty();
			break;
		}
		else {
			gotoxy(Mapsize->x, Mapsize->y + 6); printf("+---------------------------------------+");
			gotoxy(Mapsize->x, Mapsize->y + 7); printf("|                                       |");
			gotoxy(Mapsize->x, Mapsize->y + 8); printf("|                                       |");
			gotoxy(Mapsize->x, Mapsize->y + 9); printf("|                                       |");
			gotoxy(Mapsize->x, Mapsize->y + 10); printf("|                                       |");
			gotoxy(Mapsize->x, Mapsize->y + 11); printf("|                                       |");
			gotoxy(Mapsize->x, Mapsize->y + 12); printf("+---------------------------------------+");

			gotoxy(Mapsize->x + 3, Mapsize->y + 8); typewriterEffect("방화벽 파괴 가능 횟수가 감소합니다!", 20);

			gotoxy(Mapsize->x + 3, Mapsize->y + 10); printf("방화벽 파괴 가능 횟수: %d -> %d", PlayerCoord.limit_break, PlayerCoord.limit_break - 1);
			PlayerCoord.limit_break--;
			break;

		}
	}
}
void Maingame_penalty_change_locate(void) //" 일반 깃발의 위치 변경, 대부분 기존 코드 재활용
{
	int i, j;//반복문용 더비 변수.
	for (i = 0; i < (flag_amount); i++) // 진짜 깃발이 생성될 위치 결정 및 좌표 저장
	{
		int x_locate = 1 + rand() % (Mapsize->x - 5); // 깃발이 오른쪽 벽을 뚫는 오류 발생
		int y_locate = 1 + rand() % (Mapsize->y - 2);

		if (x_locate == 1 && y_locate == (Mapsize->y - 2) || Maingame_not_spawn_flag_on_obstacle(x_locate, y_locate)) // 스폰 위치에 생성되지 않게끔
		{
			i--;
			continue;
		}
		if (TrueflagCoord[i].x == -1)//이미 먹은 깃발이면
		{
			continue;
		}
		for (j = 0; j < (flag_amount); j++) {
			if (x_locate == TrueflagCoord[j].x && y_locate == TrueflagCoord[j].y)//중복 방지 알고리즘
			{
				i--;
				continue;
			}
		}
		TrueflagCoord[i].x = x_locate;
		TrueflagCoord[i].y = y_locate;
	}
	for (i = 0; i < (Falseflags_amount); i++) // 가짜깃발이 생성될 위치 결정 및 좌표 저장
	{
		int x_locate = 1 + rand() % (Mapsize->x - 5); // 깃발이 오른쪽 벽을 뚫는 오류 발생
		int y_locate = 1 + rand() % (Mapsize->y - 2);

		if (x_locate == 1 && y_locate == (Mapsize->y - 2) || Maingame_not_spawn_flag_on_obstacle(x_locate, y_locate)) // 스폰 위치에 생성되지 않게끔
		{
			i--;
			continue;
		}
		if (FalseflagCoord[i].x == -1)
		{
			continue;
		}
		for (j = 0; j < flag_amount; j++) {
			if (x_locate == TrueflagCoord[j].x && y_locate == TrueflagCoord[j].y)//중복 방지 알고리즘
			{
				i--;
				continue;
			}
		}
		for (j = 0; j < Falseflags_amount; j++) {
			if (x_locate == FalseflagCoord[j].x && y_locate == FalseflagCoord[j].y)//중복 방지 알고리즘
			{
				i--;
				continue;
			}
		}
		FalseflagCoord[i].x = x_locate;
		FalseflagCoord[i].y = y_locate;
	}
}


//메인게임을 전부 클리어했을때 실행되는 함수들. 
void Maingame_gamecomplete(void) //각 난이도를 클리어할시 출력되는 구문.
{
	system("cls");
	Sleep(500);
	int ClearTimetoStart = time(NULL) - cleartime;//클리어 시간 구하기.
	float Minigame_clear_rate = (minigame_clear_amount / (double)minigame_acess_amount) * 100;
	printf("\n\n");
	printf("      +-------------------------------+\n");
	printf("      |                               |\n");
	printf("      |  클리어 시간:          %-3d초  |\n", ClearTimetoStart);
	printf("      |  남은 이동 가능 횟수:  %-3d회  |\n", PlayerCoord.remain_move_amount);
	printf("      |  미니게임 클리어율:    %.1f%%   |\n", (minigame_acess_amount) ? Minigame_clear_rate : 0.0);
	printf("      |                               |\n");
	printf("      +-------------------------------+\n");


	if (minigame_acess_amount == 0)
	{
		Minigame_clear_rate = 0;
	}
	printf("       총 점수 : ");
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
			printf("길 찾기의 고수!");
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
			printf("길 찾기의 고수!");
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
			printf("길 찾기의 고수!");
		else
			printf("D");
		break;
	case Tutorial:
		gotoxy(8, 7);
		printf("튜토리얼을 클리어했습니다!");

		gotoxy(5, 9);
		printf("이제 난이도를 골라서 플레이하세요!");

		Sleep(2000);

		system("cls");
		SetTextcolor(15, 0);
		Game_Difficulty_Select_Screen_draw(3);
		break;
	default:
		break;
	}
	Sleep(2000);

	//동적메모리 할당 구문들
	free(FalseflagCoord); //" 동적 메모리 해제 구문들이 없어서 일단 프로그램 종료 시점이니 추가(옥준민)
	free(TrueflagCoord);//여기서 오류 뜸(왜인지는 모름)
	free(Mapsize);
	free(ObstacleCoord);
}
void Maingame_gameover(void) //" 게임 오버시 출력되는 화면
{
	Maingame_show_gameover_screen();
	free(FalseflagCoord); //" 동적 메모리 해제 구문들이 없어서 일단 프로그램 종료 시점이니 추가(옥준민)
	free(TrueflagCoord);//여기서 오류 뜸 대체 왜지감자
	free(Mapsize);
	free(ObstacleCoord);
	exit(1);//바로 강제종료해버림. 
}

// 로딩 텍스트 애니메이션 효과
void spinningBarAnimation(int duration) {
	const char spinner[] = { '|', '/', '-', '\\' };
	int spinnerSize = sizeof(spinner) / sizeof(spinner[0]);
	int delay = 50;
	int elapsed = 0;

	while (elapsed < duration) {
		printf("\b%c", spinner[(elapsed / delay) % spinnerSize]);
		fflush(stdout);
		Sleep(delay);
		elapsed += delay;
	}
	printf("\b ");
}

//그대들은어떻게플레이할것인가(플레이 정보)
void Maingame_how_to_play(void)
{
	SetTextcolor(15, 0);

	gotoxy(40, 3);
	printf("플레이어는 방향키를 통해서 움직입니다.");

	gotoxy(37, 5);
	printf("다음은 게임에 사용되는 기호와 요소들입니다.");

	gotoxy(44, 7);
	printf("#: 벽    #: 방화벽    @: 데이터");

	gotoxy(37, 8);
	printf("E를 누르면 주변 4방향의 장애물이 파괴됩니다.");

	gotoxy(40, 10);
	printf("데이터는 \'일반\'과 \'감염\' 2종류가 있습니다.");

	gotoxy(40, 11);
	printf("감염 데이터에 닿으면 미니게임이 진행됩니다.");

	gotoxy(34, 13);
	printf("성공 여부에 따라 여러 보상과 벌칙이 기다리고 있습니다.");

	Sleep(2500);

	gotoxy(38, 17);
	printf("룰을 모두 숙지하셨다면 아무 키나 눌러주세요.");

	while (1)
	{
		if (_kbhit())
			break;
	}

	system("cls");
	gotoxy(15, 5);
	printf("그럼 기능을 한 번 익혀봅시다!");

	Sleep(1500);

	system("cls");
	SetTextcolor(11, 0);
}

