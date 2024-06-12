#include "default_header.h"
#include "GameUtility.h"

typedef struct Obje_Coord {//좌표값을 저장하기 위해 만들어준 구조체
	int x;
	int y;
}Obje_Coord;
//
typedef struct Player_Coord {//플레이어의 정보를 저장하기 위한 공간, 좌표값과 speed 등..
	int x;
	int y;
	int hp;//hp는 쓸 일이 있을진 모르겠다. 
	int flagcount;//깃발 얼마나 모았나
	int remain_move_amount;//남은 이동 가능한 횟수 
	int limit_break;//남은 장애물 파괴 횟수
}Player_Coord;


void Maingame_Base_init(int); // 콘솔창 및 난수 등의 기본 요소 설정. 여기서부터 차례대로 초기화되는 방식
void Maingame_map_printing();
void Maingame_map_element_init(); // 맵 구성 요소(벽, 깃발, 장애물) 관련 설정
void Game_start(); //게임 시작하는 함수
//init -> printing -> element_init 순서로 작동함!
void on_flag_f(); // 플레이어가 깃발에 위치할 때
int check_flag_t(); // 플레이어가 모은 일반 갯발을 확인
void Maingame_break_obstacle(int, int);//장애물 부수는 코드
//
void Maingame_start_minigame(int difficulty);//미니게임 시작
//
//미니게임 승리, 패배시 나오는 함수들
void Maingame_get_reward(void);
void Maingame_get_penalty();
//
//승리시 나오는 보상 함수들 
void Maingame_reward_show_event_flag(void);//바이러스 깃발들을 모두 ㅍ기해줌.
void Maingame_reward_get_flag(void);//일반 깃발을 대신 먹어줌.

//미니게임 패배시 나오는 패널티 함수들 
void Maingame_get_penalty();
void Maingame_penalty_change_locate(void);//깃발 위치 바꾸는 함수.//메인게임 최종 승리, 패배 함수들
void Maingame_gameover();//메인게임 게임오버시 나오는 화면
void Maingame_gamecomplete();//게임을 클리어했을때 나오는 화면

void spinningBarAnimation(int);//로딩 애니메이션
void Maingame_how_to_play(void);//그대들은어떻게플레이할것인가