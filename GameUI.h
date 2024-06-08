#define _CRT_SECURE_NO_WARNINGS
#include "default_header.h"
#include "GameUtility.h"

//게임 메뉴 UI들
void Game_Start_Screen_draw();//메인화면 그리는 함수
void Game_Start_menu_Screen_draw(int);//스타트 메뉴 그리는 함수
int Game_Select_menu_control(int, void*(int));//게임 UI 선택할 수 있게 해주는 함수.
void Game_Difficulty_Select_Screen_draw(int);
void Game_Story_Select_Screen_draw();
//

//메인게임 화면 전환 스토리
void Game_Story_Easy_to_Normal();
void Game_Story_Normal_to_Hard();
void Game_Story_Endinng();
//메인게임 화면들
// 
void Maingame_show_gameover_screen();//메인게임 게임오버 스크린
void Maingame_show_gamecomplete_screen();//메인게임 게임컴플리트 스크린
void Maingame_show_minigame_inrush_screen();//메인게임에서 미니게임으로 돌입할 때 뜨는 스크린.
//미니게임 화면

//비밀번호 게임
void PW_show_start_screen();
void PW_game_show_winsreen();//이겼을 때 UI 디자인
void PW_game_show_defeatscreen();//졌을 때 화면 디자인
//
//똥피하기 게임 화면들
void GetData_show_start_screen();
void GetData_game_show_menu_screen(int, float, char*, int, int);//똥피하기 미니게임 메뉴 화면
void GetData_game_show_Gameover_screen(int, int);//똥피하기 미니게임 엔딩 화면
//
void quiz_show_start_screen();
void quiz_show_screen(char*);//퀴즈게임 메인화면. 
void quiz_Select_answer_Screen_draw(int, char**);//퀴즈게임 드로잉
int quiz_Select_menu_control(int, void* (int, char**), char**);//퀴즈게임 메뉴 옮기는거 도움. 
void quiz_show_win_screen();//이겼을때 화면
void quiz_show_defeat_screen();//졌을때 화면