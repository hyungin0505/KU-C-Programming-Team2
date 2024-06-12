#define _CRT_SECURE_NO_WARNINGS
#include "All_In_one_header.h"

///<PWminigame용 정의들> 

#define Password_Easy_Max_Len 4//문자열 길이는 항상 하나 더 많게 짜주기
#define Password_Easy_Max_Hint 3

#define Password_Normal_Max_Len 6
#define Password_Normal_Max_Hint 3

#define Password_Hard_Max_Len 10
#define Password_Hard_Max_Hint 5

///<GetData용 정의들>
//수정기한 없으니까 여기서 obstacle amount 이외의 것들은 건들지 마십쇼.

#define GetData_Max_X 70//GatData게임에서 x축으로 퍼지는 정도


#define GetData_Easy_MAX_target 3
#define GetData_Easy_MAX_Obstacle 5

#define GetData_Normal_MAX_target 4
#define GetData_Normal_MAX_Obstacle 7

#define GetData_Hard_MAX_target 5
#define GetData_Hard_MAX_Obstacle 10//내려올 타켓 개수, 여기서 조금만 바꿔주면 됨.

#define GetData_Easy_hp 7
#define GetData_Easy_end_time 15.0f

#define GetData_Normal_hp 6
#define GetData_Normal_end_time 12.0f

#define GetData_Hard_hp 5
#define GetData_Hard_end_time 10.0f//끝나는 시간 등등.. 

#define GetData_Distance 5//서로 떨어져있는 정도
///
/// 
/// 
///퀴즈용 정의들
/// 
#define NUM_QUESTIONS 20 // 지금까지 추가한 문제 수. 만일 문제 추가를 원한다면 초, 중, 고급에 한문제씩 다 추가해야만 함.+ indicies 하나 늘려주기. 
#define Quiz_Easy_Hp 7
#define Quiz_Easy_end_time 15.0f
#define Quiz_Normal_Hp 7
#define Quiz_Normal_end_time 15.0f
#define Quiz_Hard_Hp 7
#define Quiz_Hard_end_time 15.0f
//

//BoxGame용 정의들
#define Map_print_x 30
#define Map_print_y 4

#define Easy_BoxGame_Restart_count 7
#define Normal_BoxGame_Restart_count 6
#define Hard_BoxGame_Restart_count 5
//

//업다운 게임용 정의들. 
#define Easy_Updown_try_amount 8
#define Easy_Updown_Max_ADDRESS 64

#define Normal_Updown_try_amount 7
#define Normal_Updown_Max_ADDRESS 128

#define Hard_Updown_try_amount 8
#define Hard_Updown_Max_ADDRESS 256

//미니게임이 전체적으로 사용하는 구조체와 열거형들
typedef enum difficulty {//난이도 설정 변수. 여기서 l 하나 지웠음.
	Easy,
	Normal,
	Hard
}difficulty;//각자 0, 1, 2에 대응, Easy, Normal, Hard 쓰고 싶으면 스근하게 0, 1, 2 사용하면 됨. 
//
//전체 전역변수 선언
extern int isMinigameClear;//이게 1로 바뀌면 미니게임이 클리어된거고, 0이면 클리어 안된거임. 

//패스워드 미니게임

//패스워드 게임 전역변수
Password_inform* Password;
level_memory* Password_Level;
void PW_game_init(difficulty difficult)
{
	Password = (Password_inform*)calloc(1, sizeof(Password_inform));//패스워드 저장할 포인터 선언
	Password_Level = (level_memory*)calloc(1, sizeof(level_memory));//전부 동적 할당이라서 무조건 초기화 해줘야함.
	switch (difficult) {
	case Easy://난이도 할당 작업
		Password->size = Password_Easy_Max_Len;
		(*Password).pw = (char*)calloc(Password_Easy_Max_Len, sizeof(char));
		Password_Level->hp = Password_Easy_Max_Hint;//여기선 hp가 힌트
		break;
	case Normal:
		Password->size = Password_Normal_Max_Len;
		(*Password).pw = (char*)calloc(Password_Normal_Max_Len, sizeof(char));
		Password_Level->hp = Password_Normal_Max_Hint;//여기선 hp가 힌트
		break;
	case Hard:
		Password->size = Password_Hard_Max_Len;
		(*Password).pw = (char*)calloc(Password_Hard_Max_Len, sizeof(char));
		Password_Level->hp = Password_Hard_Max_Hint;//여기선 hp가 힌트
		break;
	default:
		printf("올바른 난이도를 선택해주세요");
		return;
		break;

	}
	PW_game();//메모리 찬거 확인하는 로직 넣어주기
}
void PW_game()
{
	int i, j = 0;
	int Hint_amount = Password_Level->hp;//힌트 개수
	int end_time = (int)Password_Level->end_time; //만약 end time 사용 가능하다면 사용할 것.. 여기선 어떻게 써야 할지 모르겠다.
	int s_time;
	char* Password_pw = (*Password).pw;
	char* initialize = (char*)calloc(Password->size, sizeof(char));//초기화용 변수
	char* input = (char*)calloc(Password->size, sizeof(char));//사용자 입력 받는 변수. 둘 다 동적할당이라 free 해줘야함
	//비밀번호 설정 과정
	for (i = 0; i < (Password->size) - 1; i++)//패스워드 할당 작업
	{
		if (rand() % 2)
			Password_pw[i] = 'a' + rand() % 26;

		else
			Password_pw[i] = 'A' + rand() % 26;

	}
	Password_pw[i] = '\0';
	//
	PW_game_show_PW_screen();//게임 시작 화면 출력
	PW_game_show_input_screen(Hint_amount);//인풋 화면 출력
	s_time = time(0);
	// 
	while (1) {//입력버퍼 비워주기
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
		if (j >= Password->size - 1) {//다 입력했을 경우
			input[Password->size - 1] = '\0';
			printf("\n검사중...");
			Sleep(2000);
			if (!strcmp(Password->pw, input)) {
				PW_game_wIn();
				break;
			}
			else {
				if (Hint_amount > 0) {
					system("cls");
					Hint_amount--;
					printf("\n 틀렸습니다, 남은 힌트는 %d개입니다.", Hint_amount);
					Sleep(2000);
					j = 0;
					strcpy(input, initialize);
					PW_game_show_PW_screen();
					PW_game_show_input_screen(Hint_amount);
				}
				else {
					PW_game_defeat();
					break;
				}
			}
		}
	}
	free(Password); //동적할당 해제
	free(Password_Level);
	free(initialize);
	free(input);
}
void PW_game_show_PW_screen()//패스워드 미니게임에서 비밀번호 입력 화면 출력하는 것
{
	system("cls");
	printf("----------------------------------------------------------\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|           비밀번호: %s                           |\n", (*Password).pw);
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	Sleep(2000);
}
void PW_game_show_input_screen(int hp)//사용자 입력 받는 스크린
{
	system("cls");
	printf("----------------------------------------------------------\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|    비밀번호를 입력하세요                                |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	printf("남은 기회 : %d\n", hp);
	return;
}
void PW_game_wIn()
{
	PW_game_show_winsreen();
	isMinigameClear = 1;
}
//승리시 실행되는 함수
void PW_game_defeat()
{
	PW_game_show_defeatscreen();

}

//여기까지

///getdata 미니게임
//GetData용 전역변수
int* FindDupli;//오브젝트 값에 중복 있는지 확인
//
target* GetData_Target;//목표 데이터
level_memory* GetData_Level;//레벨 데이터.
int GetData_difficult;//게임 난이도
int Targetamount, Obstacleamount;//타겟 개수, 장애물 개수.
ObjectCoord* D;//목표물 좌표 저장되는 배열.
ObjectCoord* B;//장애물 좌표 저장되는 배열



void GetData_game_init(difficulty difficult) {//난이도에 따라 들어갈 문자들과 hp, 끝나는 시간. Easy는 0번, Normal은 1번, Hard는 2번임. 
	GetData_Target = (target*)calloc(1, sizeof(target));////동적 할당임. 
	GetData_Level = (level_memory*)calloc(1, sizeof(level_memory));////동적 할당임. 
	switch (difficult)//Ease, Normal, Hard는 각각 0,1,2에 해당하게 번역되기 ??문에 문제없음. 난이도에 따라 다른 상태 지정.
	{
	case Easy:
		GetData_Target->name = " Kimch!";
		GetData_Target->n = 6;
		FindDupli = (int*)malloc((GetData_Easy_MAX_target + GetData_Easy_MAX_Obstacle) * sizeof(int));
		GetData_Level->hp = GetData_Easy_hp;
		GetData_Level->end_time = GetData_Easy_end_time;
		Targetamount = GetData_Easy_MAX_target;
		Obstacleamount = GetData_Easy_MAX_Obstacle;
		GetData_difficult = Easy;
		break;
	case Normal:
		GetData_Target->name = " function";
		GetData_Target->n = 8;
		FindDupli = (int*)malloc((GetData_Normal_MAX_target + GetData_Normal_MAX_Obstacle) * sizeof(int));
		GetData_Level->hp = GetData_Normal_hp;
		GetData_Level->end_time = GetData_Normal_end_time;
		Targetamount = GetData_Normal_MAX_target;
		Obstacleamount = GetData_Normal_MAX_Obstacle;
		GetData_difficult = Normal;
		break;
	case Hard:
		GetData_Target->name = " HelloPlayer!";
		GetData_Target->n = 12;
		FindDupli = (int*)malloc((GetData_Hard_MAX_target + GetData_Hard_MAX_Obstacle) * sizeof(int));
		GetData_Level->hp = GetData_Hard_hp;
		GetData_Level->end_time = GetData_Hard_end_time;
		Targetamount = GetData_Hard_MAX_target;
		Obstacleamount = GetData_Hard_MAX_Obstacle;
		GetData_difficult = Hard;
		break;
	default:
		printf("올바른 난이도를 선택해주세요");
		return;
		break;
	}

	Getdata_Minigame();
	return;

}
void Getdata_Minigame()//상자 모양은 [문자], 흩어진 배열을 줍는 게임. 
{
	int GameHp = GetData_Level->hp;//게임 체력
	float GameOverCount = GetData_Level->end_time;//게임 끝나는 시간
	int string_size = (int)GetData_Target->n;//스트링 사이즈.
	char* GetData = (char*)calloc((((int)GetData_Target->n) + 1), sizeof(char));
	GetData[(GetData_Target->n) + 1] = '\0';//떨어진 문자열 저장되는 배열. 동적할당임(free를 쓰라)
	D = (ObjectCoord*)malloc(Targetamount * sizeof(ObjectCoord));//타겟 정보 저장되는 배열
	B = (ObjectCoord*)malloc(Obstacleamount * sizeof(ObjectCoord));//장애물 정보 저장되는 배열
	ObjectCoord P1 = { 0, 29, 3 };//플레이어 변수
	int IsFullCollect = 0;//전부 모았는지 확인하는 변수. 
	int i;//반복문용 변수
	int arr_size = (Obstacleamount + Targetamount);//배열 사이즈 
	for (i = 0; i < Obstacleamount; i++)//좌표값 부여해주는 과정.
	{
		get_position(arr_size, i, string_size / Targetamount);
		B[i].x = FindDupli[i];
		B[i].speed = rand() % 10 + 1;
		B[i].y = 0;
	}
	for (i = 0; i < Targetamount; i++)//보상 위치를 중복 없게끔 만들어주는 함수
	{
		get_position(arr_size, Obstacleamount + i, string_size / Targetamount);
		D[i].x = FindDupli[Obstacleamount + i];//D랑 B랑 서로 저장되는 배열 위치가 다름.
		D[i].y = 0;
		D[i].speed = rand() % 10 + 1;
	}
	while (1)
	{
		system("cls");//화면 비워줌

		if (_kbhit())//시분할로 코드를 구성함. 첫번째로는 플레이어 움직임을 컨트롤함.
		{
			Control_Player_Move(&P1);
		}
		for (i = 0; i < Obstacleamount; i++) {//오브젝트 움직여주는 과정
			Control_Obst_Move(&B[i], i, P1, &GameHp, arr_size, string_size);
		}
		for (i = 0; i < Targetamount; i++)
		{
			if (D[i].speed != -1)
			{
				Control_Target_Move(&D[i], GetData_Target, 2 * i, GetData_Target->name, arr_size, P1, GetData, arr_size, string_size);//이름이 간다.
			}
		}
		if (GameHp <= 0 || GameOverCount <= 0)//게임 종료 코드. 내려왔을 때 기준으로 한번 체크해줌. 
		{
			break;
		}
		if (_kbhit())
		{
			Control_Player_Move(&P1);
		}
		//화면 만드는 코드
		GetData_game_show_menu_screen(GameHp, GameOverCount, GetData, string_size, GetData_Max_X);
		if (strlen(GetData) >= string_size - 1)//나중에 여기서 오류 날 수도, 체크
		{
			break;
		}
		gotoxy(P1.x, P1.y);
		for (i = 0; i < 4; i++)
		{
			while (_kbhit())
			{
				Control_Player_Move(&P1);
			}
			Sleep(50);
		}
		if (_kbhit())//플레이어 위치를 계속 체크해주면서 딜레이 해소
		{
			Control_Player_Move(&P1);
		}
		GameOverCount -= 0.2f;

	}//게임 코드
	system("cls");
	IsFullCollect = 0;
	for (i = 0; i < string_size; i++)
	{
		if (GetData[i] == GetData_Target->name[i + 1])//로스트
		{
			IsFullCollect += 1;
		}
	}
	GetData_Gameover(IsFullCollect, string_size);
	//프리 액션(메모리 할당 해제)
	free(GetData_Target);
	free(GetData_Level);
	free(FindDupli);
	free(D);
	free(B);
}
void Control_Obst_Move(ObjectCoord* Obje1, int i, ObjectCoord Player, int* Hp, int Allamount, int string_size)//오브젝트 움직임을 담당
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
		get_position(Allamount, i, string_size / Targetamount);
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
void Control_Target_Move(
	ObjectCoord* Obje1, target* Target,
	int i, char* TargetText, int arr_size,
	ObjectCoord Player, char* GetText, int Targetamount, int string_size)
{
	int t = 0;//밑에.. 대충 뭔가에서 사용하는ㄱ것
	int j = 0;//여기서만 사용되는 지역변수
	if (Obje1->y >= 30)//끝까지 간 별 삭제
	{
		if (abs(Player.x - Obje1->x) < GetData_Target->n / Targetamount + 3)//닿았는지 확인하는 로직
		{
			t = i;
			for (j = 1 + i; j <= 2 + i; j++)
			{
				GetText[t] = TargetText[j];
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
		get_position(arr_size, i, ((int)Target->n / Targetamount));
		Obje1->x = FindDupli[i];
		Obje1->y = 0;
		Obje1->speed = rand() % 10 + 1;
		return;
	}
	//오브젝트 스피드가 1이 되는 것을 먹은 것의 기준으로 봄 
	gotoxy(Obje1->x, Obje1->y);
	for (j = 1 + i; j <= 2 + i; j++)
	{
		printf("%c", *(TargetText + j));
	}
	Obje1->y += Obje1->speed;
	return;
}//보상 문자열의 움직임을 제어
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
	printf("◇");
	return;
}
void get_position(size_t size, int idx, int distance) {//위치 담겨있는 변수, 장애물이 몇개인지, 오브젝트 번호, 글자 길이 받아서 위치 설정.
	int i = 0;
	int pos = rand() % GetData_Max_X;

	for (i = 0; i < size; i++) //보상 위치를 중복 없게끔 만들어주는 함수
	{
		if (abs(pos - FindDupli[i]) < distance)//만약 3칸 이내에 장애물이나 다른 보상이 있다면
		{
			pos = rand() % GetData_Max_X;//다시 설정함
			i = 0;
		}
	}
	FindDupli[idx] = pos;
}
void GetData_Gameover(int isFullCorrect, int string_size)
{
	GetData_game_show_Gameover_screen(isFullCorrect, string_size);
	if (((double)isFullCorrect / string_size) * 100 >= 100.0)
	{
		isMinigameClear = 1;//미니게임 클리어를 1로
	}
	//isfullcorrect는 모은 배열 수, string_size는 전체 배열 수. 완료율 바탕으로 다른 디버프 주도록 할 것
	//디버프 들어갈 함수.
}
//여기까지

//퀴즈 미니게임
//퀴즈 미니게임용 전역변수, 

//문제 전역변수들. 문제 수 늘릴 때마다 이 네개를 다 늘려줘야 함.
Question easy_questions[NUM_QUESTIONS] = {
		{"C 언어의 표준 라이브러리 중 하나인 `stdio.h`에 포함된 함수는 무엇인가요?", {"printf", "malloc", "strcpy", "sqrt"}, 0},
		{"C 언어에서 변수 선언의 올바른 예시는 무엇인가요?", {"int 4number;", "int number4;", "int number 4;", "int number-4;"}, 1},
		{"C 프로그램의 시작점이 되는 함수는 무엇인가요?", {"start()", "main()", "printf()", "init()"}, 1},
		{"C에서 문자를 나타내기 위해 사용하는 자료형은 무엇인가요?", {"char", "int", "float", "double"}, 0},
		{"다음 중 주석을 올바르게 사용하는 방법은 무엇인가요?", {"\\ This is a comment", "/* This is a comment */", "// This is a comment */", "/* This is a comment"}, 1},
		{"C 언어에서 배열의 인덱스는 몇부터 시작하나요?", {"1", "0", "2", "-1"}, 1},
		{"다음 중 C에서 사용하는 자료형이 아닌 것은?", {"int", "float", "real", "double"}, 2},
		{"C에서 상수를 선언하는 키워드는 무엇인가요?", {"const", "var", "let", "constant"}, 0},
		{"다음 중 C 언어의 논리 연산자가 아닌 것은?", {"&&", "||", "!", "&"}, 3},
		{"다음 중 C에서 문자열을 저장하기 위한 자료형은 무엇인가요?", {"char", "int", "float", "string"}, 0},
		{"C 언어의 표준 라이브러리 중 하나인 `stdio.h`에 포함된 함수는 무엇인가요?", {"printf", "malloc", "strcpy", "sqrt"}, 0},
		{"C 언어에서 변수 선언의 올바른 예시는 무엇인가요?", {"int 4number;", "int number4;", "int number 4;", "int number-4;"}, 1},
		{"C 프로그램의 시작점이 되는 함수는 무엇인가요?", {"start()", "main()", "printf()", "init()"}, 1},
		{"C에서 문자를 나타내기 위해 사용하는 자료형은 무엇인가요?", {"char", "int", "float", "double"}, 0},
		{"다음 중 주석을 올바르게 사용하는 방법은 무엇인가요?", {"// This is a comment", "/* This is a comment */", "// This is a comment */", "/* This is a comment"}, 1},
		{"C 언어에서 배열의 인덱스는 몇부터 시작하나요?", {"1", "0", "2", "-1"}, 1},
		{"다음 중 C에서 사용하는 자료형이 아닌 것은?", {"int", "float", "real", "double"}, 2},
		{"C에서 상수를 선언하는 키워드는 무엇인가요?", {"const", "var", "let", "constant"}, 0},
		{"다음 중 C 언어의 논리 연산자가 아닌 것은?", {"&&", "||", "!", "&"}, 3},
		{"다음 중 C에서 문자열을 저장하기 위한 자료형은 무엇인가요?", {"char", "int", "float", "string"}, 0}
};
Question medium_questions[NUM_QUESTIONS] = {
	{"다음 코드의 출력 결과는 무엇인가요? \nint a = 5;\nint b = 10;\nint c = a + b;\nprintf(\"%d\", c);", {"5", "10", "15", "20"}, 2},
	{"C 언어에서 함수를 선언하는 올바른 방법은 무엇인가요?", {"function int add(int a, int b)", "int add(int a, int b);", "int add(a, b)", "func int add(int a, int b)"}, 1},
	{"다음 중 포인터 선언이 올바른 것은 무엇인가요?", {"int p;", "int *p;", "int p*;", "int * p;"}, 1},
	{"다음 코드의 출력 결과는 무엇인가요?\nint a = 10;\nint *p = &a;\nprintf(\"%d\", *p);", {"0", "10", "쓰레기 값", "컴파일 오류"}, 1},
	{"다음 중 배열을 선언하는 올바른 방법은 무엇인가요?", {"int arr[5];", "int arr;", "int arr[];", "arr[5];"}, 0},
	{"다음 코드의 출력 결과는 무엇인가요?\nint arr[] = {1, 2, 3, 4, 5};\nprintf(\"%d\", arr[2]);", {"1", "2", "3", "4"}, 2},
	{"다음 중 변수의 값을 1 증가시키는 올바른 방법은 무엇인가요?", {"x += 1;", "x =+ 1;", "x = 1;", "x == 1;"}, 0},
	{"다음 코드의 출력 결과는 무엇인가요?\nprintf(\"%d\", sizeof(int));", {"2", "4", "8", "16"}, 1},
	{"다음 코드의 출력 결과는 무엇인가요?\nchar str[] = \"Hello\";\nprintf(\"%s\", str);", {"Hello", "H", "str", "컴파일 오류"}, 0},
	{"다음 중 함수 포인터를 사용하는 올바른 방법은 무엇인가요?", {"int (*funcPtr)(int, int) = &functionName;", "int *funcPtr(int, int) = &functionName;", "int funcPtr(int, int) = &functionName;", "int (*funcPtr)(int, int) = functionName;"}, 3},
	{"C언어에서 사용되는 키워드로 변수를 선언하는 것은 무엇인가요?", {"define", "int", "var", "let"}, 1},
	{"다음 중 C언어에서 사용되는 반복문이 아닌 것은 무엇인가요?", {"for", "while", "repeat", "do-while"}, 2},
	{"C언어에서 변수를 선언할 때, 초기화하지 않으면 해당 변수의 값은 무엇이 될까요?", {"0", "1", "무작위 값", "에러"}, 2},
	{"C언어에서 문자열을 비교하는 함수는 무엇인가요?", {"strcmp", "strcpy", "strcat", "strlen"}, 0},
	{"C언어에서 정수형 변수를 선언하는 키워드는 무엇인가요?", {"int", "float", "real", "double"}, 0},
	{"C언어에서 사용되는 비교 연산자가 아닌 것은 무엇인가요?", {"<", ">", "<=", "=="}, 3},
	{"C언어에서 실수형 데이터를 나타내는 키워드는 무엇인가요?", {"int", "float", "double", "real"}, 1},
	{"C언어에서 변수의 값을 증가시키는 방법으로 적절한 것은 무엇인가요?", {"x++", "++x", "x += 1", "모두"}, 3},
	{"C언어에서 조건문을 통해 실행할 코드 블록을 지정하는 데 사용되는 괄호는 무엇인가요?", {"()", "{}", "[]", "모두"}, 1},
	{"C언어에서 사용되는 할당 연산자가 아닌 것은 무엇인가요?", {"=", "+=", "-=", "=="}, 3}
};
Question hard_questions[NUM_QUESTIONS] = {
	{"다음 코드의 출력 결과는 무엇인가요? \nint arr[] = {1, 2, 3, 4, 5};\nint *p = arr;\nprintf(\"%d\", *(p + 3));", {"1", "2", "3", "4"}, 3},
	{"다음 코드의 출력 결과는 무엇인가요? \nint a = 5;\nint b = 10;\nint *p = &a;\nint *q = &b;\n*p = *q;\nprintf(\"%d\", a);", {"5", "10", "쓰레기 값", "0"}, 1},
	{"다음 코드의 출력 결과는 무엇인가요? \nint a = 10;\nint *p = &a;\n*p += 5;\nprintf(\"%d\", *p);", {"10", "15", "쓰레기 값", "컴파일 오류"}, 1},
	{"다음 코드의 출력 결과는 무엇인가요? \nint x = 5;\nint *p = &x;\n*p = *p + 10;\nprintf(\"%d\", x);", {"5", "10", "15", "20"}, 2},
	{"다음 중 동적 메모리 할당을 해제하는 함수는 무엇인가요?", {"malloc", "calloc", "realloc", "free"}, 3},
	{"다음 코드의 출력 결과는 무엇인가요? \nint arr[5] = {1, 2, 3, 4, 5};\nint *p = arr;\nprintf(\"%d\", p[2]);", {"1", "2", "3", "4"}, 2},
	{"다음 중 함수 포인터를 사용하는 올바른 방법은 무엇인가요?", {"int (*funcPtr)(int, int) = &functionName;", "int *funcPtr(int, int) = &functionName;", "int funcPtr(int, int) = &functionName;", "int (*funcPtr)(int, int) = functionName;"}, 3},
	{"다음 코드의 출력 결과는 무엇인가요? \nstruct Point {int x; int y;};\nstruct Point p1 = {10, 20};\nstruct Point *p2 = &p1;\nprintf(\"%d\", p2->y);", {"10", "20", "쓰레기 값", "컴파일 오류"}, 1},
	{"다음 중 메모리 할당에 실패했을 때 반환하는 값은 무엇인가요?", {"NULL", "0", "-1", "EOF"}, 0},
	{"다음 중 다음 코드를 통해 접근할 수 있는 값은 무엇인가요? \nstruct Node {int data; struct Node *next;};\nstruct Node n1 = {10, NULL};\nstruct Node n2 = {20, &n1};\nprintf(\"%d\", n2.next->data);", {"10", "20", "쓰레기 값", "컴파일 오류"}, 0},
	{"다음 코드의 출력 결과는 무엇인가요? \nint arr[] = {1, 2, 3, 4, 5};\nint *p = &arr[2];\nprintf(\"%d\", *p);", {"1", "2", "3", "4"}, 2},
	{"C언어에서 변수의 값을 감소시키는 방법으로 올바른 것은 무엇인가요?", {"x -= 1", "x =- 1", "x = 1", "x != 1"}, 0},
	{"C언어에서 사용되지 않는 예약어는 무엇인가요?", {"int", "real", "double", "char"}, 1},
	{"C언어에서 포인터를 사용할 때 발생하는 문제 중 하나는 무엇인가요?", {"댕댕이", "탈출문자", "댕글링 포인터", "버그"}, 2},
	{"C언어에서 두 변수의 값을 교환하기 위한 가장 간단한 방법은 무엇인가요?", {"temp 변수 사용", "함수 호출", "포인터 사용", "없음"}, 0},
	{"C언어에서 사용되는 두 변수의 값을 서로 비교하기 위한 연산자는 무엇인가요?", {"==", "=", "!=", "<>"}, 0},
	{"C언어에서 논리 연산자로 두 개의 조건이 모두 참일 때 결과가 참이 되는 연산자는 무엇인가요?", {"&&", "||", "!", "&"}, 0},
	{"C언어에서 문자열을 연결하는 함수는 무엇인가요?", {"strcat", "strcmp", "strlen", "strcpy"}, 0},
	{"C언어에서 포인터를 사용할 때 발생할 수 있는 문제 중 하나는 무엇인가요?", {"메모리 누수", "메모리 부족", "메모리 접근 오류", "메모리 해제 오류"}, 2},
	{"C언어에서 메모리 동적 할당에 실패했을 때 반환되는 값은 무엇인가요?", {"NULL", "0", "-1", "EOF"}, 0}
};
//
level_memory quiz_level;//퀴즈 틀리는 횟수랑 엔드타임 정의해놓은 구조체. 
int question_indices[NUM_QUESTIONS] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };//문제선수 셔플
int quiz_work_count = 0;//퀴즈가 몇번 작동했는지 체크. 
int quiz_difficult;//난이도 책정

void quiz_game_init(difficulty difficult)
{
	if (quiz_work_count == 0)//한번도 작동되지 않았다면
	{
		shuffle(question_indices, NUM_QUESTIONS);//문제 나오는 순서 셔플. 
	}
	switch (difficult)//난이도에 따라 다른 문제 할당. 
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
	quiz_show_screen(question[question_indices[quiz_work_count]].question);//화면 출력. 
	quiz_Select_answer_Screen_draw(4, question[question_indices[quiz_work_count]].choices);
	if (quiz_Select_menu_control(4, quiz_Select_answer_Screen_draw, question[question_indices[quiz_work_count]].choices) == question[question_indices[quiz_work_count]].correct_answer)
	{
		//맞췄을 ??
		system("cls");
		quiz_win();//맞췄을때 함수 작동
	}
	else
	{
		//틀렸을 때
		system("cls");
		quiz_defeat();//틀렸을때 함수 작동
	}
}
void quiz_win()//맞췄을때 함수
{
	quiz_work_count++;
	quiz_show_win_screen();
	isMinigameClear = 1;
}
void quiz_defeat()//틀렸을때 함수
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


//


int BoxGame_Restart_count = 0;
BoxController_map BoxGameMap[2] =
{
   {
		{"################",
		 "#*#            #",
		 "#      0#*     #",
		 "# S          * #",
		 "#  #####  ######",
		 "#   0          #",
		 "#   0  ##      #",
		 "#              #",
		 "################" },
		{3, 2}
   },
   {

		{"################",
		 "#         #  *##",
		 "#    0         #",
		 "#         # *  #",
		 "#  0      ######",
		 "#              #",
		 "#   0        ###",
		 "#S        # *###",
		 "################" },
		{7, 1}
   }
};
char BoxGame_Map[9][17];//맵이 저장될 변수.
Player_inform BoxGame_Player;//플레이어 위치가 저장될 변수. 
int Rad;//지금 이 게임이 어떤 맵을 골랐는지 테스트.
void BoxGame_show_title_screen() {//옆에 뜨는 화면을 출력해줌. 
	gotoxy(50, 5);
	printf("데이터 헤더를 밀어서 데이터를 결합시키세요!");
	gotoxy(50, 7);
	printf("P : 플레이어, * : 데이터, O : 데이터 헤더. ");
	gotoxy(50, 9);
	printf("데이터 헤더를 데이터가 있는 쪽까지 밀고 가면 점수를 얻을 수 있습니다.");
	gotoxy(50, 11);
	printf("esc : 게임 포기, r : 재시작");
	gotoxy(50, 13);
	printf("남은 재시작 횟수 : %d", BoxGame_Restart_count);



}
void BoxGame_init(int difficult)
{
	system("cls");
	srand((unsigned int)time(NULL));
	switch (difficult)
	{
	case Easy:
		BoxGame_Restart_count = Easy_BoxGame_Restart_count;
		break;
	case Normal:
		BoxGame_Restart_count = Normal_BoxGame_Restart_count;
		break;
	case Hard:
		BoxGame_Restart_count = Hard_BoxGame_Restart_count;
		break;
	}
	Rad = rand() % 2;//랜덤으로 정해셔 BoxGameMap과 플레이어 x,y좌표를 바꿔줌.
	//플레이어 x, y좌표는 이차원 배열 내부인걸로 판정함. 
	for (int i = 0; i < 9; i++)///포인터를 이어주는 방식으로 하면 원본 맵 자체가 바뀌어버림
	{
		for (int j = 0; j < 17; j++)
		{
			BoxGame_Map[i][j] = BoxGameMap[Rad].Map_inform[i][j];
		}
	}
	BoxGame_Player.x = BoxGameMap[Rad].PlayerCoord.x;
	BoxGame_Player.y = BoxGameMap[Rad].PlayerCoord.y;
	BoxGame_Start();
}
void BoxGame_Start()
{
	CursorView();
	BoxGame_show_title_screen();
	CursorView();
	int x = BoxGame_Player.x;
	int y = BoxGame_Player.y;
	int ch;
	int cnt = 0;//몇개를 모았는지
	gotoxy(Map_print_x, Map_print_y);
	for (int i = 0; i < 9; i++) {
		puts(BoxGame_Map[i]);
		gotoxy(Map_print_x, Map_print_y + i + 1);
	}
	while (1) {
		ch = _getch();
		if (ch == 27) {
			gotoxy(50, 8);
			printf("실패");
			break;
		}
		if (ch == 'r')
		{
			if (BoxGame_Restart_count == 0)
			{
				BoxGame_defeat();
				CursorClosing();
				break;
			}
			system("cls");
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 17; j++)
				{
					BoxGame_Map[i][j] = BoxGameMap[Rad].Map_inform[i][j];
				}
			}
			BoxGame_Restart_count--;
			BoxGame_Start();
		}
		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 80:

				if (BoxGame_Map[x + 1][y] == ' ')
				{
					BoxGame_Map[x][y] = ' ';
					x++;

					BoxGame_Map[x][y] = 'S';
				}
				else if (BoxGame_Map[x + 1][y] == '0')
				{
					if (BoxGame_Map[x + 2][y] == ' ')
					{
						BoxGame_Map[x][y] = ' ';
						x++;
						BoxGame_Map[x][y] = 'S';
						BoxGame_Map[x + 1][y] = '0';
					}
					else if (BoxGame_Map[x + 2][y] == '*') {
						BoxGame_Map[x][y] = ' ';
						x++;
						BoxGame_Map[x][y] = 'S';
						BoxGame_Map[x + 1][y] = ' ';
						cnt++;
					}

				}
				break;
			case 72:

				if (BoxGame_Map[x - 1][y] == ' ') {
					BoxGame_Map[x][y] = ' ';
					x--;
					BoxGame_Map[x][y] = 'S';
				}
				else if (BoxGame_Map[x - 1][y] == '0') {
					if (BoxGame_Map[x - 2][y] == ' ') {
						BoxGame_Map[x][y] = ' ';
						x--;
						BoxGame_Map[x][y] = 'S';
						BoxGame_Map[x - 1][y] = '0';
					}
					else if (BoxGame_Map[x - 2][y] == '*') {
						BoxGame_Map[x][y] = ' ';
						x--;
						BoxGame_Map[x][y] = 'S';
						BoxGame_Map[x - 1][y] = ' ';
						cnt++;
					}
				}

				break;
			case 75:
				if (BoxGame_Map[x][y - 1] == ' ') {
					BoxGame_Map[x][y] = ' ';
					y--;
					BoxGame_Map[x][y] = 'S';
				}
				else if (BoxGame_Map[x][y - 1] == '0') {
					if (BoxGame_Map[x][y - 2] == ' ') {
						BoxGame_Map[x][y] = ' ';
						y--;
						BoxGame_Map[x][y] = 'S';
						BoxGame_Map[x][y - 1] = '0';
					}
					else if (BoxGame_Map[x][y - 2] == '*') {
						BoxGame_Map[x][y] = ' ';
						x--;
						BoxGame_Map[x][y] = 'S';
						BoxGame_Map[x][y - 2] = ' ';
						cnt++;
					}
				}
				break;
			case 77:
				if (BoxGame_Map[x][y + 1] == ' ') {
					BoxGame_Map[x][y] = ' ';
					y++;
					BoxGame_Map[x][y] = 'S';
				}
				else if (BoxGame_Map[x][y + 1] == '0') {
					if (BoxGame_Map[x][y + 2] == ' ') {
						BoxGame_Map[x][y] = ' ';
						y++;
						BoxGame_Map[x][y] = 'S';
						BoxGame_Map[x][y + 1] = '0';
					}
					else if (BoxGame_Map[x][y + 2] == '*') {
						BoxGame_Map[x][y] = ' ';
						y++;
						BoxGame_Map[x][y] = 'S';
						BoxGame_Map[x][y + 1] = ' ';
						cnt++;


					}
				}

			}
			CursorCoordclear();

			gotoxy(Map_print_x, Map_print_y);
			for (int i = 0; i < 9; i++) {
				puts(BoxGame_Map[i]);
				gotoxy(Map_print_x, Map_print_y + i + 1);
			}
			if (cnt == 3) {
				BoxGame_win();
				CursorClosing();
				break;
			}

		}


	}

}
void BoxGame_win()
{
	BoxGame_show_win_screen();
	isMinigameClear = 1;
}
void BoxGame_defeat()
{
	BoxGame_show_defeat_screen();
}

//틱텍토 게임
//전역변수.
char TicTacToe_Map_Preset[3][4] = { "...",
									"...",
									"..." };
char TicTacToe_Map[3][4];

void TicTacToe_init() {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			TicTacToe_Map[i][j] = TicTacToe_Map_Preset[i][j];
		}
	}
	TicTacToe_Map_Printing();
	TicTacToe_Start();
}
void TicTacToe_Map_Printing() {
	system("cls");
	puts(TicTacToe_Map[0]);
	puts(TicTacToe_Map[1]);
	puts(TicTacToe_Map[2]);
}
void TicTacToe_Start()
{
	srand(time(NULL)); // 난수 생성을 위한 시드 초기화
	int x, y;//사용자에게 입력받기 위한 x, y
	while (1) {
		// 사용자 입력
		while (1) {
			printf("수를 둘 좌표를 입력 (1-3 범위): ");
			scanf("%d %d", &x, &y);

			if ((x >= 1 && x <= 3) && (y >= 1 && y <= 3)) {
				if (TicTacToe_Map[y - 1][x - 1] == '.') {
					break;//비어있으면 빠진다.
				}
			}
			printf("잘못된 입력입니다. 다시 입력하세요.\n");
		}
		TicTacToe_Map[y - 1][x - 1] = '0';
		TicTacToe_Map_Printing();
		if (TicTacToe_isWin() == 1) {
			TicTacToe_win();
			break;
		}
		// 무승부 확인
		int isDraw = 1;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (TicTacToe_Map[i][j] == '.') {
					isDraw = 0;
					break;
				}
			}
			if (!isDraw) break;
		}
		if (isDraw) {
			printf("무승부입니다. 하지만 그 사이 ai가 데이터를 가져갑니다..");
			Sleep(2000);
			TicTacToe_defeat();//패배했음을 확인.
			break;
		}

		// 컴퓨터 입력
		while (1) {
			x = rand() % 3 + 1;
			y = rand() % 3 + 1;

			if (TicTacToe_Map[y - 1][x - 1] == '.') {
				break;
			}
		}
		TicTacToe_Map[y - 1][x - 1] = 'x';
		printf("컴퓨터가 x,y를 입력: %d %d\n", x, y);
		TicTacToe_Map_Printing();
		if (TicTacToe_isWin() == 1) {
			printf("Ai가 승리했습니다. 패배입니다..");
			Sleep(2000);
			TicTacToe_defeat();
			break;
		}

		// 무승부 확인
		isDraw = 1;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (TicTacToe_Map[i][j] == '.') {
					isDraw = 0;
					break;
				}
			}
			if (!isDraw) break;
		}
		if (isDraw) {
			printf("무승부입니다. 하지만 그 사이 ai가 데이터를 가져갑니다..");
			Sleep(2000);
			TicTacToe_defeat();//패배했음을 확인.
			break;
		}
	}
}
int TicTacToe_isWin() {//일일히 검사
	int x1 = TicTacToe_Map[0][0] + TicTacToe_Map[0][1] + TicTacToe_Map[0][2];
	int x2 = TicTacToe_Map[1][0] + TicTacToe_Map[1][1] + TicTacToe_Map[1][2];
	int x3 = TicTacToe_Map[2][0] + TicTacToe_Map[2][1] + TicTacToe_Map[2][2];
	int x4 = TicTacToe_Map[0][0] + TicTacToe_Map[1][0] + TicTacToe_Map[2][0];
	int x5 = TicTacToe_Map[0][1] + TicTacToe_Map[1][1] + TicTacToe_Map[2][1];
	int x6 = TicTacToe_Map[0][2] + TicTacToe_Map[1][2] + TicTacToe_Map[2][2];
	int x7 = TicTacToe_Map[0][0] + TicTacToe_Map[1][1] + TicTacToe_Map[2][2];
	int x8 = TicTacToe_Map[0][2] + TicTacToe_Map[1][1] + TicTacToe_Map[2][0];
	if (x1 == ('0' + '0' + '0')) return 1;
	if (x2 == ('0' + '0' + '0')) return 1;
	if (x3 == ('0' + '0' + '0')) return 1;
	if (x4 == ('0' + '0' + '0')) return 1;
	if (x5 == ('0' + '0' + '0')) return 1;
	if (x6 == ('0' + '0' + '0')) return 1;
	if (x7 == ('0' + '0' + '0')) return 1;
	if (x8 == ('0' + '0' + '0')) return 1;
	if (x1 == ('x' + 'x' + 'x')) return 1;
	if (x2 == ('x' + 'x' + 'x')) return 1;
	if (x3 == ('x' + 'x' + 'x')) return 1;
	if (x4 == ('x' + 'x' + 'x')) return 1;
	if (x5 == ('x' + 'x' + 'x')) return 1;
	if (x6 == ('x' + 'x' + 'x')) return 1;
	if (x7 == ('x' + 'x' + 'x')) return 1;
	if (x8 == ('x' + 'x' + 'x')) return 1;
	return 0;
}
void TicTacToe_win()
{
	TicTacToe_show_win_screen();
	isMinigameClear = 1;
}
void TicTacToe_defeat()
{
	TicTacToe_show_defeat_screen();

}

//업다운 게임

int UpdownGame_Max_ADDRESS;
int UpdownGame_try_amount;
int UpdownGame_data_location;
int ud_count = 0;//플레이어에게 입력받은 횟수.

void UpdownGame_init(int difficulty) {
	system("cls");
	switch (difficulty) {
	case Easy:
		UpdownGame_try_amount = Easy_Updown_try_amount;
		UpdownGame_Max_ADDRESS = Easy_Updown_Max_ADDRESS;
		break;
	case Normal:
		UpdownGame_try_amount = Normal_Updown_try_amount;
		UpdownGame_Max_ADDRESS = Normal_Updown_Max_ADDRESS;
		break;
	case Hard:
		UpdownGame_try_amount = Hard_Updown_try_amount;
		UpdownGame_Max_ADDRESS = Hard_Updown_Max_ADDRESS;
		break;
	}
	ud_count = 0;
	srand(time(NULL));
	UpdownGame_data_location = rand() % (UpdownGame_Max_ADDRESS + 1);//주소 설정
	UpdownGame_Start();

}
void UpdownGame_Start() {
	printf("0 ~ %d까지 주소를 입력하게! 업 혹은 다운으로 주소값을 판별하겠네!\n\n", UpdownGame_Max_ADDRESS);
	Sleep(2000);
	int guess;//플레이어 추측값 저장하는 변수
	while (ud_count <= UpdownGame_try_amount) {
		printf("주소를 입력하게! : ");
		scanf("%d", &guess);
		if (guess < 0 || guess > UpdownGame_Max_ADDRESS) {
			printf("유효한 주소값을 입력하게 (00 ~ %d)\n\n", UpdownGame_Max_ADDRESS);
			continue;
		}

		if (guess < UpdownGame_data_location) {
			printf("업!, 남은 접근 가능 횟수 = %d\n\n", UpdownGame_try_amount - ud_count);
			ud_count++;
		}
		else if (guess > UpdownGame_data_location) {
			printf("다운!, 남은 접근 가능 횟수  = %d\n\n", UpdownGame_try_amount - ud_count);
			ud_count++;
		}
		else {
			printf("좋아, 주소를 찾았네! 0x%d\n\n", UpdownGame_data_location);
			Sleep(2000);
			break;
		}
	}
	if (ud_count > UpdownGame_try_amount) {
		UpdownGame_defeat();
	}
	else {
		UpdownGame_win();//승리
	}
}

void UpdownGame_win()
{
	system("cls");
	UpdownGame_show_win_screen();
	isMinigameClear = 1;
}
void UpdownGame_defeat()
{
	system("cls");
	UpdownGame_show_defeat_screen();
}
