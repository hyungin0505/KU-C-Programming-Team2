#include "default_header.h"
#include "GameUtility.h"
#include "GameUI.h"

//게임 전체적으로 쓰이는 구조체
typedef struct level_memory {//종료 시간과 hp. 
	float end_time;
	int hp;
}level_memory;
//

//패스워드게임용 구조체 정의
typedef struct Password_inform {//먹어야 하는 목표의 정보가 담긴 스트럭쳐.. 
	size_t size;//사이즈가 실제로 들어가는 부분
	char* pw;//패스워드 실제로 들어가는 부분
}Password_inform;
//
//패스워드 미니게임용 함수들
void PW_game_init(difficulty);
void PW_game(Password_inform*, level_memory*);//비밀번호 게임. 
void PW_game_show_PW_screen(Password_inform*);//힌트 + 패스워드 보여주는 화면
void PW_game_show_input_screen(int, int);//인풋화면
void PW_game_wIn();//승리했을 때 동작
void PW_game_defeat();//패배앴을 때 동작

void Test();

//GetData용 전역변수들
int* FindDupli;//오브젝트 값에 중복 있는지 확인 /동적 할당임. 만약 힙 메모리 부족 뜬다면 이거 초기화했는지 다시 확인해보기
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
//겟데이터용 함수들
void GetData_game_init(difficulty);//겟데이터 게임 초기화
void Getdata_Minigame(target*, level_memory*, int, int, int);//떨어지는 데이터를 성공적으로 줍는 게임
void Control_Obst_Move(ObjectCoord*, int, ObjectCoord, int*, int, int);//겟데이터용, 오브젝트들의 현재 위치 컨트롤
void Control_Target_Move(ObjectCoord*, target*, int, char*, int, ObjectCoord, char*, int, int);//보상오브젝트들의 위치 컨트롤
void Control_Player_Move(ObjectCoord*);//플레이어 위치 컨트롤
void get_position(size_t, int, int);//랜덤 위치 부여
void GetData_Gameover(int, int);//게임오버시 실행되는 함수

//퀴즈 게임용 구조체 정의
typedef struct {
	char question[256];
	char* choices[4];//선지 수는 4개로 고정함. 
	int correct_answer; // 0-3 index of the correct answer
} Question;

//퀴즈 게임용 함수 정의
void quiz_game_init(difficulty);
void quiz_Minigame(Question*);
void shuffle(int*, int);//문제 순서 섞기
void quiz_win();//퀴즈 승리했을때
void quiz_defeat();//퀴즈 패배했을 때
int print_question(Question);