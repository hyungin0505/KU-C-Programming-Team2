#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "GameUtility.h"//GameUtility 저장되어 있음.


///<GetData용 정의들>
#define GetData_Max_X 70//GatData게임에서 x축으로 퍼지는 정도


#define GetData_Easy_MAX_target 3
#define GetData_Easy_MAX_Obstacle 5

#define GetData_Normal_MAX_target 5
#define GetData_Normal_MAX_Obstacle 7

#define GetData_Hard_MAX_target 7
#define GetData_Hard_MAX_Obstacle 9//내려올 타켓 개수, 여기서 조금만 바꿔주면 됨.

#define GetData_Easy_hp 4
#define GetData_Easy_end_time 15.0f

#define GetData_Normal_hp 3
#define GetData_Normal_end_time 12.0f

#define GetData_Hard_hp 2
#define GetData_Hard_end_time 10.0f//끝나는 시간 등등.. 
///</여기까지>


//프로그램이 전체적으로 사용하는 구조체와 열거형들

typedef enum difficullty {//난이도 설정 변수.
	Easy,
	Normal,
	Hard
}difficulty;//각자 0, 1, 2에 대응, Easy, Normal, Hard 쓰고 싶으면 스근하게 0, 1, 2 사용하면 됨. 

typedef struct level_memory {//종료 시간과 hp. 
	float end_time;
	int hp
}level_memory;
//


//GetData용 전역변수들
typedef struct ObjectCoord//오브젝트 좌표값 저장해둘 스트럭쳐
{
	int x;//x값
	int y;//y값
	int speed;//속도
}ObjectCoord;

typedef struct target {//먹어야 하는 목표의 정보가 담긴 스트럭쳐.. 
	char* name;
	size_t n;
}target;



//함수 선언들 

void PWMiniGameLevel1(int);//비밀번호 게임. 

//겟데이터용 함수들
void GetData_game_init(int);//겟데이터 게임 초기화
void Getdata_Minigame(target*, int*, level_memory*, int, int, int);//떨어지는 데이터를 성공적으로 줍는 게임
void ControlObjMove(ObjectCoord*, int, ObjectCoord, int*);//겟데이터용, 오브젝트들의 현재 위치 컨트롤
void ControlGoldMove(ObjectCoord*, int, char*, ObjectCoord, char*);//보상오브젝트들의 위치 컨트롤
void PlayerMoveControl(ObjectCoord*);//플레이어 위치 컨트롤
//


int main()
{
	srand((unsigned)time(NULL));
	GetData_game_init(Easy);
	printf("끝");
	Sleep(2000);
	return 0;
}

void GetData_game_init(int difficult) {//난이도에 따라 들어갈 문자들과 hp, 끝나는 시간. Easy는 0번, Normal은 1번, Hard는 2번임. 
	target* Target;////동적 할당임. 만약 힙 메모리 부족 뜬다면 이거 초기화했는지 다시 확인해보기
	int* FindDupli;//동적 할당임. 만약 힙 메모리 부족 뜬다면 이거 초기화했는지 다시 확인해보기
	level_memory* Level;////동적 할당임. 만약 힙 메모리 부족 뜬다면 이거 초기화했는지 다시 확인해보기
	int IsProperDiff = 0;//난이도가 올바른지 확인함.
	int Targetamount, Obstacleamount;
	switch (difficult)//Ease, Normal, Hard는 각각 0,1,2에 해당하게 번역되기 문에 문제없음. 난이도에 따라 다른 상태 지정.
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
		printf("올바른 난이도를 선택해주세요");
		return;
		break;
	}
	if (IsProperDiff)
	{
		if (FindDupli == NULL)//동적할당 오류 체크
		{
			printf("\n\n에러 : 메모리가 부족합니다");
			return;
		}
		else
		{
			Getdata_Minigame(Target, FindDupli, Level, difficult, Targetamount, Obstacleamount);
			return;
		}
	}

}

void get_position(int* arr, size_t size, int idx, int distance) {//위치 담겨있는 변수, 장애물이 몇개인지, 오브젝트 번호, 글자 길이 
	int i;
	int pos = rand() % GetData_Max_X;

	for (i = 0; i < size; i++) //보상 위치를 중복 없게끔 만들어주는 함수
	{
		if (abs(pos - arr[i]) < distance)//만약 3칸 이내에 장애물이나 다른 보상이 있다면
		{
			pos = rand() % GetData_Max_X;//다시 설정함
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
	int TryLimit, i;//반복문 제어용 변수, TryLimit는 비밀번호 제한
	TryLimit = Difficult;
	//비밀번호 설정
	for (i = 0; i < 9; i++)
	{
		word[i] = 'a' + rand() % 25;
	}
	word[i] = '\0';
	//비밀번호 설정
	//
	for (; TryLimit > 0; TryLimit--)//난이도에 따라 주어지는 횟수만큼 만복
	{
		printf("----------------------------------------------------------\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|           비밀번호: %s                           |\n", word);
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("----------------------------------------------------------\n");
		Sleep(2000);
		system("cls");
		//
		//비밀번호 입력 받는 시퀀스
		printf("----------------------------------------------------------\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|    비밀번호를 입력하세요                                |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("----------------------------------------------------------\n");
		printf(":");
		gets_s(input, 10);//나중에 연결 리스트로 바꾸기. 
		///
		///성공, 실패 여부 판가름
		if (!(strcmp(word, input)))
		{
			printf("정답입니다.");
			//hp증가 등등의 특전 들어갈 자리
			// //성공시 종료
		}
		else
		{
			if (TryLimit - 1)//시도 횟수 남아있는지 확인
			{
				printf("틀렸습니다. 기회는 %d번입니다", TryLimit - 1);//틀리면 다시 반복
				Sleep(2000);
				system("cls");
			}
			else
			{
				printf("기회를 모두 소진하셨습니다. 디버프를 받습니다");
				//디버프 코드
			}
		}
	}
}
void Getdata_Minigame(target* Target, int* FInddupli, level_memory* Stats, int difficult, int obstacleamount, int targetamount)//상자 모양은 [문자], 흩어진 배열을 줍는 게임. 
{
	char
		int GameHp = Stats->hp;//게임 체력
	float GameOverCount = Stats->end_time;//게임 끝나는 시간
	int string_size = Target->n;
	char* GetData = (char*)malloc((Target->n + 1) * sizeof(char));//떨어진 문자열 저장되는 배열. 동적할당임(free를 쓰라)
	int* FindDupli = FInddupli;
	ObjectCoord* D = (ObjectCoord*)malloc(targetamount * sizeof(ObjectCoord));//타겟 정보 저장되는 배열
	ObjectCoord* B = (ObjectCoord*)malloc(obstacleamount * sizeof(ObjectCoord));//장애물 정보 저장되는 배열
	ObjectCoord P1 = { 0, 29, 3 };//플레이어 변수
	int IsFullCollect = 0;//전부 모았는지 확인하는 변수. 
	int i, j;//반복문용 변수
	int arr_size = sizeof(FindDupli) / sizeof(FindDupli[0]);//배열 사이즈 
	for (i = 0; i < obstacleamount; i++)//좌표값 부여해주는 과정.
	{
		get_position(FindDupli, arr_size, i, string_size);
		B[i].x = FindDupli[i];
		B[i].speed = rand() % 10 + 1;
		B[i].y = 0;
	}
	for (i = obstacleamount; i < obstacleamount + targetamount; i++)//보상 위치를 중복 없게끔 만들어주는 함수
	{
		get_position(FindDupli, arr_size, i, string_size);
		D[i - obstacleamount].x = FindDupli[obstacleamount];//D랑 B랑 서로 배열이 달라요. 
		D[i - obstacleamount].y = 0;
		D[i - obstacleamount].speed = rand() % 10 + 1;
	}
	while (1)
	{
		system("cls");//화면 비워줌

		if (_kbhit())
		{
			PlayerMoveControl(&P1);
		}
		for (i = 0; i < obstacleamount; i++) {//오브젝트 움직여주는 과정
			ControlObjMove(&B[i], i, P1, &GameHp);
		}
		for (i = 0; i < targetamount; i++)
		{
			if (D[i].speed != -1)
			{
				ControlGoldMove(&D[i], 2 * i, , P1, GetData);
			}
		}
		if (GameHp <= 0 || GameOverCount <= 0)//게임 종료 코드
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
		printf("떨어지는 데이터를 주우세요!");
		gotoxy(Max_X + 13, 8);
		printf("남은 체력 : %d", GameHp);
		gotoxy(Max_X + 13, 12);
		printf("지금까지 주운 배열 : ");
		for (i = 0; i < string_size; i++)
		{
			printf("%c", GetData[i]);
			if (GetData[i] == Target[string_random].name[i + 1])
			{
				IsFullCollect += 1;
			}
		}
		if (IsFullCollect >= string_size - 1)
		{
			break;
		}
		IsFullCollect = 0;
		gotoxy(Max_X + 13, 15);
		printf("남은 시간 : %.f", GameOverCount);
		gotoxy(P1.x, P1.y);
		for (i = 0; i < 4; i++)
		{
			if (_kbhit())
			{
				PlayerMoveControl(&P1);
			}
			Sleep(50);
		}
		if (_kbhit())//플레이어 위치를 계속 체크해주면서 딜레이 해소
		{
			PlayerMoveControl(&P1);
		}
		GameOverCount -= 0.2f;

	}//게임 코드
	system("cls");
	IsFullCollect = 0;
	for (i = 0; i < 6; i++)
	{
		if (GetData[i] == Target[string_random].name[i + 1])//로스트
		{
			IsFullCollect += 1;
		}
	}
	printf("----------------------------------------------------------\n");//화면 출력
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                       GameOver                          |\n");
	printf("|                      완료율 = %.lf%%                        |\n", (IsFullCollect / 6.0) * 100);
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	Sleep(2000);
}
//GetData 미니게임에서 쓰이는 함수들
void ControlObjMove(ObjectCoord* Obje1, int i, ObjectCoord Player, int* Hp)//오브젝트 움직임을 담당
{
	int j = 0;//여기서만 사용되는 지역변수
	if (Obje1->y >= 30)//끝까지 간 별 삭제
	{
		if (abs(Player.x - Obje1->x) < 5)//hp감소 로직
		{
			(*Hp)--;
		}
		gotoxy(Obje1->x, Obje1->y - 1);//삭제 로직
		printf(" ");
		FindDupli[i] = rand() % Max_X;
		for (j = 0; j < 5; j++)
		{
			if (FindDupli[i] == FindDupli[j])//만약 중복이 있다면 다르게 만들어버림
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
}//별 움직임 제어
void ControlGoldMove(ObjectCoord* Obje1, int i, char* GoldText, ObjectCoord Player, char* GetText)
{
	int t = 0;//밑에.. 대충 뭔가에서 사용하는ㄱ것
	int j = 0;//여기서만 사용되는 지역변수
	if (Obje1->y >= 30)//끝까지 간 별 삭제
	{
		if (abs(Player.x - Obje1->x) < 7)//닿았는지 확인하는 로직
		{
			t = i;
			for (j = 1 + i; j <= 2 + i; j++)
			{
				GetText[t] = GoldText[j];
				t++;
			}
			Obje1->speed = -1;
			gotoxy(Obje1->x, Obje1->y - 1);//삭제 로직
			printf("     ");
			Obje1->y = 0;
			return;
		}
		gotoxy(Obje1->x, Obje1->y - 1);//삭제 로직
		printf("     ");
		FindDupli[i] = rand() % Max_X;
		for (j = 0; j < 8; j++)
		{
			if (abs(FindDupli[i] - FindDupli[j]) < 3)//만약 5칸 이내에 장애물이나 다른 보상이 있다면
			{
				FindDupli[i] = rand() % Max_X;//다시 설정함
				continue;
			}
		}
		Obje1->x = FindDupli[i];
		Obje1->y = 0;
		Obje1->speed = rand() % 10 + 1;
		return;
	}
	//오브젝트 스피드가 1이 되는 것을 먹은 것의 기준으로 봄 
	gotoxy(Obje1->x, Obje1->y);
	for (j = 1 + i; j <= 2 + i; j++)
	{
		printf("%c", *(GoldText + j));
	}
	Obje1->y += Obje1->speed;
	return;
}//보상 문자열의 움직임을 제어
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
	printf("◇");
	return Obje1;
}
//여기까지