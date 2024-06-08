#define _CRT_SECURE_NO_WARNINGS
#include "All_In_one_header.h"

///<PWminigame용 정의들> 

#define Password_Easy_Max_Len 2//문자열 길이는 항상 하나 더 많게 짜주기
#define Password_Easy_Max_end_time 10.0f
#define Password_Easy_Max_Hint 3

#define Password_Normal_Max_Len 5
#define Password_Normal_Max_end_time 10.0f
#define Password_Normal_Max_Hint 3

#define Password_Hard_Max_Len 20
#define Password_Hard_Max_end_time 10.0f
#define Password_Hard_Max_Hint 5

///<GetData용 정의들>

#define GetData_Max_X 70//GatData게임에서 x축으로 퍼지는 정도


#define GetData_Easy_MAX_target 3
#define GetData_Easy_MAX_Obstacle 5

#define GetData_Normal_MAX_target 4
#define GetData_Normal_MAX_Obstacle 7

#define GetData_Hard_MAX_target 5
#define GetData_Hard_MAX_Obstacle 12//내려올 타켓 개수, 여기서 조금만 바꿔주면 됨.

#define GetData_Easy_hp 4
#define GetData_Easy_end_time 15.0f

#define GetData_Normal_hp 3
#define GetData_Normal_end_time 12.0f

#define GetData_Hard_hp 2
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


//미니게임이 전체적으로 사용하는 구조체와 열거형들
typedef enum difficulty {//난이도 설정 변수. 여기서 l 하나 지웠음.
	Easy,
	Normal,
	Hard
}difficulty;//각자 0, 1, 2에 대응, Easy, Normal, Hard 쓰고 싶으면 스근하게 0, 1, 2 사용하면 됨. 
//
//전역변수 선언
extern int isMinigameClear;//이게 1로 바뀌면 미니게임이 클리어된거고, 0이면 클리어 안된거임. 

//패스워드 미니게임
void PW_game_init(difficulty difficult)
{
	Password_inform* Password = (Password_inform*)calloc(1, sizeof(Password_inform));//패스워드 저장할 포인터 선언
	level_memory* Level = (level_memory*)calloc(1, sizeof(level_memory));//전부 동적 할당이라서 무조건 초기화 해줘야함.
	switch (difficult) {
		case Easy://난이도 할당 작업
			Password->size = Password_Easy_Max_Len;
			(*Password).pw = (char*)calloc(Password_Easy_Max_Len, sizeof(char));
			Level->end_time = Password_Easy_Max_end_time;
			Level->hp = Password_Easy_Max_Hint;//여기선 hp가 힌트
			break;
		case Normal:
			Password->size = Password_Normal_Max_Len;
			(*Password).pw = (char*)calloc(Password_Normal_Max_Len, sizeof(char));
			Level->end_time = Password_Normal_Max_end_time;
			Level->hp = Password_Normal_Max_Hint;//여기선 hp가 힌트
			break;
		case Hard:
			Password->size = Password_Hard_Max_Len;
			(*Password).pw = (char*)calloc(Password_Hard_Max_Len, sizeof(char));
			Level->end_time = Password_Hard_Max_end_time;
			Level->hp = Password_Hard_Max_Hint;//여기선 hp가 힌트
			break;
		default: 
			printf("올바른 난이도를 선택해주세요");
			return;
			break;

	}
	PW_game(Password, Level);//메모리 찬거 확인하는 로직 넣어주기
}
void PW_game(Password_inform* Password, level_memory* Level)
{
	int i, j = 0;
	int Hint_amount = Level->hp;//힌트 개수
	int end_time = (int)Level->end_time; //만약 end time 사용 가능하다면 사용할 것.. 여기선 어떻게 써야 할지 모르겠다.
	int s_time;
	char* Password_pw = (*Password).pw;
	char* initialize = (char*)calloc(Password->size, sizeof(char));//초기화용 변수
	char* input = (char*)calloc(Password->size, sizeof(char));//사용자 입력 받는 변수. 둘 다 동적할당이라 free 해줘야함
	//비밀번호 설정 과정
	for (i = 0; i < (Password->size)-1; i++)//패스워드 할당 작업
	{
		if (rand() % 2)
			Password_pw[i] = 'a' + rand() % 26;

		else
			Password_pw[i] = 'A' + rand() % 26;

	}
	Password_pw[i] = '\0';
	//
	PW_game_show_PW_screen(Password);//게임 시작 화면 출력
	PW_game_show_input_screen(Hint_amount, end_time);//인풋 화면 출력
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
			if (!strcmp(Password->pw, input)){
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
	free(Password); //동적할당 해제
	free(Level);
	free(initialize);
	free(input);
}
void PW_game_show_PW_screen(Password_inform* Password)//패스워드 미니게임에서 비밀번호 입력 화면 출력하는 것
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
void PW_game_show_input_screen(int hp, int end_time)//사용자 입력 받는 스크린
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
	//이후 여기에 버프 들어감
}
//승리시 실행되는 함수
void PW_game_defeat()
{
	PW_game_show_defeatscreen();
	//이후 여기에 디버프 들어감
}
//패배시 실행되는 함수
//여기까지

///getdata 미니게임
//GetData용 전역변수
int* FindDupli;//오브젝트 값에 중복 있는지 확인
//
void GetData_game_init(difficulty difficult) {//난이도에 따라 들어갈 문자들과 hp, 끝나는 시간. Easy는 0번, Normal은 1번, Hard는 2번임. 
	target* Target = (target*)calloc(1, sizeof(target));////동적 할당임. 만약 힙 메모리 부족 뜬다면 이거 초기화했는지 다시 확인해보기
	level_memory* Level = (level_memory*)calloc(1, sizeof(level_memory));////동적 할당임. 만약 힙 메모리 부족 뜬다면 이거 초기화했는지 다시 확인해보기
	int IsProperDiff = 0;//난이도가 올바른지 확인함.
	int Targetamount, Obstacleamount;
	switch(difficult)//Ease, Normal, Hard는 각각 0,1,2에 해당하게 번역되기 떄문에 문제없음. 난이도에 따라 다른 상태 지정.
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
			Getdata_Minigame(Target, Level, difficult, Targetamount, Obstacleamount);
			return;
		}
	}
}
void Getdata_Minigame(target* Target, level_memory* Stats, int difficult, int targetamount, int obstacleamount)//상자 모양은 [문자], 흩어진 배열을 줍는 게임. 
{
	int GameHp = Stats->hp;//게임 체력
	float GameOverCount = Stats->end_time;//게임 끝나는 시간
	int string_size = (int)Target->n;
	char *GetData = (char*)calloc((((int)Target->n)+1), sizeof(char));
	GetData[(Target->n)+1] = '\0';//떨어진 문자열 저장되는 배열. 동적할당임(free를 쓰라)
	ObjectCoord* D = (ObjectCoord*)malloc(targetamount * sizeof(ObjectCoord));//타겟 정보 저장되는 배열
	ObjectCoord* B = (ObjectCoord*)malloc(obstacleamount * sizeof(ObjectCoord));//장애물 정보 저장되는 배열
	ObjectCoord P1 = { 0, 29, 3 };//플레이어 변수
	int IsFullCollect = 0;//전부 모았는지 확인하는 변수. 
	int i;//반복문용 변수
	int arr_size = (obstacleamount+targetamount)/sizeof(int);//배열 사이즈 
	for (i = 0; i < obstacleamount; i++)//좌표값 부여해주는 과정.
	{
		get_position(arr_size, i, string_size/targetamount);
		B[i].x = FindDupli[i];
		B[i].speed = rand() % 10 + 1;
		B[i].y = 0;
	}
	for (i = obstacleamount; i < obstacleamount+targetamount; i++)//보상 위치를 중복 없게끔 만들어주는 함수
	{
		get_position(arr_size, i, string_size);
		D[i-obstacleamount].x = FindDupli[obstacleamount];//D랑 B랑 서로 배열이 달라요. 
		D[i-obstacleamount].y = 0;
		D[i-obstacleamount].speed = rand() % 10 + 1;
	}
	while (1)
	{
		system("cls");//화면 비워줌

		if (_kbhit())//시분할로 코드를 구성함. 첫번째로는 플레이어 움직임을 컨트롤함.
		{
			Control_Player_Move(&P1);
		}
		for (i = 0; i < obstacleamount; i++) {//오브젝트 움직여주는 과정
			Control_Obst_Move(&B[i], i, P1, &GameHp, arr_size, string_size);
		}
		for (i = 0; i < targetamount; i++)
		{
			if (D[i].speed != -1)
			{
				Control_Target_Move(&D[i], Target, 2 * i, Target->name, arr_size, P1, GetData, arr_size, string_size);//이름이 간다.
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
		if (strlen(GetData) >= string_size-1)//나중에 여기서 오류 날 수도, 체크
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
		if (GetData[i] == Target->name[i + 1])//로스트
		{
			IsFullCollect += 1;
		}
	}
	GetData_Gameover(IsFullCollect, string_size);
	//프리 액션(메모리 할당 해제)
	free(Target);
	free(Stats);
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
		if (abs(Player.x - Obje1->x) < Target->n/Targetamount)//닿았는지 확인하는 로직
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
		get_position(arr_size, i, ((int)Target->n / Targetamount + 3));
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
	int i;
	int pos = rand() % GetData_Max_X;

	for (i = 0; i < size; i++) //보상 위치를 중복 없게끔 만들어주는 함수
	{
		if (abs(pos - FindDupli[i]) < distance+3)//만약 3칸 이내에 장애물이나 다른 보상이 있다면
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
	if (((double)isFullCorrect/string_size)*100 >= 60.0)
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
		//맞췄을 떄
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
