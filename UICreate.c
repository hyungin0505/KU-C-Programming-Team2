#include "GameUI.h"



//스타트 게임 메뉴를 위한 define과 열거형들
#define Start_Menu_x 53//이거 바꾸면 startmenu가 그려지는 위치가 달라집니다
#define Start_Menu_y 18

#define diff_select_menu_x 53 //얘내를 바꾸면 난이도 선택 메뉴가 그려지는 위치가 달라집니다. 
#define diff_select_menu_y 18
//

//퀴즈게임 UI를 위한 define들
#define quiz_answer_select_x 5
#define quiz_answer_selcet_y 20
typedef enum CursorInput {
	Start,///각각 0, 1, 2에 대응합니다
	Story,
	Quit
}CursorInput;

typedef enum difficultyy {
	Easy,///각각 0, 1, 2에 대응합니다
	Normal,
	Hard
}Gamedifficulty;
//

void Game_Start_Screen_draw()//게임 처음 시작할때 그림 그리는 함수
{
	gotoxy(30, 4);
	printf("######  #  #   ####     #    #  #  #    #  #####    ##     ");
	gotoxy(30, 5);
	printf("#          #  #         # #  #     # #  #     #    #  #");
	gotoxy(30, 6);
	printf("#####   #  #  #####     #  # #  #  #  # #    #    #    #       ");
	gotoxy(30, 7);
	printf("#       #  #  #         #   ##  #  #   ##   #     ######  ");
	gotoxy(30, 8);
	printf("#       #  #   ####     #    #  #  #    #  #####  #    #   ");
	gotoxy(30, 9);
	//동작 메커니즘 : 커서가 위로 가서 그림 그리고, 멈추고, 다시 그리고, 멈추고 반복
}
//메뉴 셀렉트할떄 사용되는 함수들
extern int Cursor_input;//밖에서 받아오는 매개변수임
void Game_Start_menu_Screen_draw(int Cursor_input)//스타트 메뉴 그려줌.
{
	switch (Cursor_input)//커서가 어디에 가있는지 확인받아서 입력받기 때문에, 바뀔 떄마다 바꿔줄 수 있음.
	{
		case Start://글자색깔을 바꿔줄 수 없기 때문에, 항상 지우고 다시 그려줌.
			printf(" ");
			gotoxy(Start_Menu_x, Start_Menu_y);
			printf(">\b");
			SetTextcolor(1, 0);//텍스트 파란색 배경 검은색. 커서를 바꿔줌.
			gotoxy(Start_Menu_x+1, Start_Menu_y); printf("게임시작");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 2, Start_Menu_y+2); printf("스토리");
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("종료");
			gotoxy(Start_Menu_x, Start_Menu_y);
			break;
		case Story:
			printf(" ");//커서 지워주고
			gotoxy(Start_Menu_x, Start_Menu_y+2);
			printf(">\b");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 1, Start_Menu_y); printf("게임시작");
			SetTextcolor(1, 0);
			gotoxy(Start_Menu_x + 2, Start_Menu_y + 2); printf("스토리");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("종료");
			gotoxy(Start_Menu_x, Start_Menu_y + 2);
			break;
		case Quit:
			printf(" ");//커서 지워주고
			gotoxy(Start_Menu_x, Start_Menu_y + 4);
			printf(">\b");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 1, Start_Menu_y); printf("게임시작");
			SetTextColor(15, 0);
			gotoxy(Start_Menu_x + 2, Start_Menu_y + 2); printf("스토리");
			SetTextcolor(1, 0);
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("종료");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x, Start_Menu_y + 4);
			break;
		default://가장 처음 입력되었을 때
			gotoxy(Start_Menu_x, Start_Menu_y);
			printf(">\b");
			SetTextcolor(1, 0);//텍스트 파란색 배경 검은색
			gotoxy(Start_Menu_x + 1, Start_Menu_y); printf("게임시작");
			SetTextcolor(15, 0);//텍스트 하얀색 배경 검은색
			gotoxy(Start_Menu_x + 2, Start_Menu_y + 2); printf("스토리");
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("종료");
			gotoxy(Start_Menu_x, Start_Menu_y);
			break;
	}
}
void Game_Difficulty_Select_Screen_draw(int Cursor_input)
{
	switch (Cursor_input)//커서가 어디에 가있는지 확인받아서 입력받기 때문에, 바뀔 떄마다 바꿔줄 수 있음.
	{
	case Easy://글자색깔을 바꿔줄 수 없기 때문에, 항상 지우고 다시 그려줌.
		printf(" ");
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		printf(">\b");
		SetTextcolor(1, 0);////////////////////////////////////////////////////
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y); printf("쉬움");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 2); printf("보통");
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 4); printf("어려움");
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		break;
	case Normal:
		printf(" ");//커서 지워주고
		gotoxy(diff_select_menu_x, diff_select_menu_y + 2);
		printf(">\b");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y); printf("쉬움");
		SetTextcolor(1, 0);//////////////////////////////////
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 2); printf("보통");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 4); printf("어려움");
		gotoxy(diff_select_menu_x, diff_select_menu_y + 2);
		break;
	case Hard:
		printf(" ");//커서 지워주고
		gotoxy(diff_select_menu_x, diff_select_menu_y + 4);
		printf(">\b");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y); printf("쉬움");
		SetTextColor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 2); printf("보통");
		SetTextcolor(1, 0);///////////////////////////////////////
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 4); printf("어려움");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x, diff_select_menu_y + 4);
		break;
	default://가장 처음 입력되었을 때
		system("cls");
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		printf(">\b");
		SetTextcolor(1, 0);///////////////////////////////////////////////////
		gotoxy(diff_select_menu_x+1, diff_select_menu_y); printf("쉬움");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x+1, diff_select_menu_y + 2); printf("보통");
		gotoxy(diff_select_menu_x+1, diff_select_menu_y + 4); printf("어려움");
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		break;
	}
}
int Game_Select_menu_control(int max_menu_amount, void(*SelectFp)(int))//메뉴가 최대 몇개인지 확인+함수 포인터 사용
{
	int ch;
	int Cursor_y = 0;

	while (1)//난이도 선택하는 과정
	{
		ch = _getch();
		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 72:
				Cursor_y = ((Cursor_y - 1) >= 0) ? Cursor_y - 1 : max_menu_amount - 1;// 커서를 위로 이동, 순환하도록 수정
				SelectFp(Cursor_y);
				break;
			case 80:
				Cursor_y = ((Cursor_y + 1) <= max_menu_amount - 1) ? Cursor_y + 1 : 0;// 커서를 아래로 이동, 순환하도록 수정
				SelectFp(Cursor_y);
				break;
			default:
				break;
			}
		}
		else if (ch == 13)
		{
			break;
		}
	}
	return Cursor_y;//커서가 어디에 있었는지 리턴, 0, 1, 2의 형태로 리턴함.
}//게임 메뉴 셀렉트를 도와주는 외부 함수임

//스토리 화면
void Game_Story_Select_Screen_draw()//스토리 고르는 화면.
{
	char story[] = "나의 이름은 알렉스 나는 컴퓨터안에서 살고 있는 포인터 매일 지루하고 심심한 컴퓨터속애서"
		"유일하게 나에게 쾌락을 가져다 주는 일은 바로 컴퓨터안의 흐트러진 파일들을 원자리로 이동해주고 바이러스에 감염된 파일들을 치료해주는 일들이지"
		"뭐? 이런일들이 왜 재밌냐고? 그건 "
		"니들이 경험을 못해봐서 그래, 얼마나 생각보다 짜맀하고 재밌는 일들인데...  자 이제 슬슬 청소하러 가볼까?";

	system("cls");
	int length = strlen(story);
	int i = 0;

	while (i < length) {
		printf("%c", story[i]);
		Sleep(20);
		i++;

		if (_kbhit()) {
			char input = _getch();
			if (input == '\r') {
				while (i < length) {
					printf("%c", story[i]);
					i++;
				}
				Sleep(2000);
			}
		}
	}
}
//

//메인게임 맵 이동시 나오는 스토리들. 
// 
void Game_Story_Easy_to_Normal() {//이지에서 노말 넘어가는 스토리
	SetTextcolor(15, 0);
	char story[] = "어우어우 이지이지 이정도는 몸풀기지 손가락 하나 까닥 안한거 같은데ㅋㅋ 자 슬슬 더 깊게 들어가볼까?";

	system("cls");
	int length = strlen(story);
	int i = 0;

	while (i < length) {
		printf("%c", story[i]);
		Sleep(20);
		i++;

		if (_kbhit()) {
			char input = _getch();
			if (input == '\r') {
				while (i < length) {
					printf("%c", story[i]);
					i++;
				}
			}

		}

	}

}
void Game_Story_Normal_to_Hard() {//중간에서 어려움 넘어가는 스토리
	SetTextcolor(15, 0);
	char story[] = "이건 좀 위험했어...그래도 이제 드디어 끝을 보네 , 다시 정신 차리고 들어간다!";

	system("cls");
	int length = strlen(story);
	int i = 0;

	while (i < length) {
		printf("%c", story[i]);
		Sleep(20);
		i++;

		if (_kbhit()) {
			char input = _getch();
			if (input == '\r') {
				while (i < length) {
					printf("%c", story[i]);
					i++;
				}
			}

		}

	}

}
void Game_Story_Endinng() {//엔딜 스토리 
	SetTextcolor(15, 0);
	char story[] = "이번임무도 완벽하게 완성! 평소에 컴퓨터를 얼마나 못살게 굴었는지 이렇게 어지러울수가! 그래도 재밌는 임무였어 다음 임무는 또 언제 생기려나... 내가 다 공짜로 청소해줄테니"
		"만약 감염된 컴퓨터가 있으면 다 나한테 맡겨줘! 그럼 나는 이만 집으로 돌아갈께";

	system("cls");
	int length = strlen(story);
	int i = 0;

	while (i < length) {
		printf("%c", story[i]);
		Sleep(20);
		i++;

		if (_kbhit()) {
			char input = _getch();
			if (input == '\r') {
				while (i < length) {
					printf("%c", story[i]);
					i++;
				}
			}

		}

	}
}
//메인게임 UI
// 
void Maingame_show_gameover_screen()
{
	system("cls");
	SetTextColor(15, 0);

	gotoxy(17, 7);
	printf("GAME OVER");

	gotoxy(13, 9);
	printf("이것도 못 깨? 허~접");
}
void Maingame_show_gamecomplete_screen()
{
	system("cls");
	SetTextColor(15, 0);

	gotoxy(17, 7);
	printf("CONGRATULATION!");

	gotoxy(10, 9);
	printf("이 난이도의 모든 깃발을 다 모았습니다!");
}
void Maingame_show_minigame_inrush_screen()//미니게임으로 들어가기 전 출력되는 화면.
{
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	printf("바이러스에 감염된 데이터입니다!!!");
	Sleep(500);
	printf("치료 과정을 진행합니다..");
	Sleep(2000);
}


//미니게임 UI

//비밀번호 입력 게임들
void PW_show_start_screen()//패스워드 게임이 시작하기 전 출력되는 함수
{
	system("cls");
	printf("랜섬웨어 때문에 파일에 비밀번호가 걸렸어. 이를 해결해야만 해!");
	Sleep(2000);
}
void PW_game_show_winsreen()
{
	system("cls");
	printf("축하합니다! 게임을 클리어하셨습니다!");
	Sleep(2000);
}
void PW_game_show_defeatscreen()
{
	system("cls");
	printf("안 축하합니다! 게임을 못 클리어하셨습니다!");
	Sleep(2000);
}
//똥피하기 게임들
void GetData_show_start_screen()//똥피하기 게임이 시작하기 전 출력되는 함수.
{
	system("cls");
	printf("배열이 망가져서 데이터가 쏟아지고 있어! 쓰레기 값을 피해서 데이터를 주워야 해!");
	Sleep(2000);
}
void GetData_game_show_menu_screen(
	int GameHp, float GameOverCount, char* GetData, int string_size, int GetData_Max_X)
	//미니게임 hp/ 게임 남은 시간/  지금까지 모은 배열/ 목표 문자열 사이즈/  화면 넓이
{
	int i = 0;
	for (i = 0; i < 30; i++)
	{
		gotoxy(GetData_Max_X + 10, i);
		printf("|");//30번 반복하면서 y축 기준으로 저 벽을 세워주는 것입니다. 
	}
	gotoxy(GetData_Max_X + 13, 5);
	printf("떨어지는 데이터를 주우세요!");
	gotoxy(GetData_Max_X + 13, 8);
	printf("남은 체력 : %d", GameHp);
	gotoxy(GetData_Max_X + 13, 12);
	printf("남은 시간 : %.f", GameOverCount);
	gotoxy(GetData_Max_X + 13, 15);//나머지는 단순한 출력입닏.
	printf("지금까지 주운 배열 : ");
	for (i = 0; i < string_size; i++)
	{
		printf("%c", GetData[i]);//지금까지 주운 배열을 출력합니다.
	}
}
void GetData_game_show_Gameover_screen(int IsFullCollect, int string_size) {
	printf("----------------------------------------------------------\n");//화면 출력
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                       GameOver                          |\n");
	printf("|                      완료율 = %.lf%%                        |\n", ((float)IsFullCollect / string_size) * 100);//완료율을 백분위로 해서 출력
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	if (((double)IsFullCollect /string_size)*100 >= 60.0)
	{
		printf("데이터를 전부 모았어! 축하해!");
	}
	else
	{
		printf("데이터를 다 모으지 못했어..");
	}
	Sleep(2000);
}
//퀴즈 미니게임
void quiz_show_start_screen()
{
	system("cls");
	printf("이 데이터가 어떤 데이터인지 문제를 풀어야 헤. 그래야만 데이터에 접근할 수 있어!"); 
	Sleep(2000);
}
void quiz_show_screen(char* question)
{
	system("cls");
	printf("문");
	Sleep(200);
	printf("제");
	Sleep(200); 
	printf("발"); 
	Sleep(200); 
	printf("생!!");
	Sleep(200); 
	printf("\n");
	printf("-------------------------\n");
	printf("|                        |\n");
	printf("|                        |\n");
	printf("|  다음 문제를 해결하시오|\n");
	printf("|                        |\n");
	printf("|                        |\n");
	printf("-------------------------\n");
	int length = strlen(question);
	int i = 0;

	while (i < length) {
		printf("%c", question[i]);
		Sleep(20);
		i++;

		if (_kbhit()) {
			char input = _getch();
			if (input == '\r') {
				while (i < length) {
					printf("%c", question[i]);
					i++;
				}
			}
		}
	}
}
void quiz_Select_answer_Screen_draw(int Cursor_input, char** choices)
{
	switch (Cursor_input)//커서가 어디에 가있는지 확인받아서 입력받기 때문에, 바뀔 떄마다 바꿔줄 수 있음.
	{
	case 0://글자색깔을 바꿔줄 수 없기 때문에, 항상 지우고 다시 그려줌.
		printf(" ");
		gotoxy(quiz_answer_select_x, quiz_answer_selcet_y);
		printf(">\b");
		SetTextcolor(1, 0);////////////////////////////////////////////////////
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y); printf("%s", *(choices));
		SetTextcolor(15, 0);
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 2); printf("%s", *(choices + 1));
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 4); printf("%s", *(choices + 2));
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 6); printf("%s", *(choices + 3));
		gotoxy(quiz_answer_select_x, quiz_answer_selcet_y);
		break;
	case 1:
		printf(" ");//커서 지워주고
		gotoxy(quiz_answer_select_x, quiz_answer_selcet_y+2);
		printf(">\b");
		SetTextcolor(15, 0);
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y); printf("%s", *(choices));
		SetTextcolor(1, 0);//////////////////////////////////
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 2); printf("%s", *(choices + 1));
		SetTextcolor(15, 0);
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 4); printf("%s", *(choices + 2));
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 6); printf("%s", *(choices + 3));
		gotoxy(quiz_answer_select_x, quiz_answer_selcet_y + 2);
		break;
	case 2:
		printf(" ");//커서 지워주고
		gotoxy(quiz_answer_select_x, quiz_answer_selcet_y+4);
		printf(">\b");
		SetTextcolor(15, 0);
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y); printf("%s", *(choices));
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 2); printf("%s", *(choices + 1));
		SetTextcolor(1, 0);///////////////////////////////////////
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 4); printf("%s", *(choices + 2));
		SetTextcolor(15, 0);
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 6); printf("%s", *(choices + 3));
		gotoxy(quiz_answer_select_x, quiz_answer_selcet_y + 4);
		break;
	case 3: 
		printf(" ");//커서 지워주고
		gotoxy(quiz_answer_select_x, quiz_answer_selcet_y + 6);
		printf(">\b");
		SetTextcolor(15, 0);
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y); printf("%s", *(choices));
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 2); printf("%s", *(choices + 1));
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 4); printf("%s", *(choices + 2));
		SetTextcolor(1, 0);///////////////////////////////////////
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 6); printf("%s", *(choices + 3));
		SetTextcolor(15, 0);
		gotoxy(quiz_answer_select_x, quiz_answer_selcet_y + 6);
		break;

	default://가장 처음 입력되었을 때
		gotoxy(quiz_answer_select_x, quiz_answer_selcet_y);
		printf(">\b");
		SetTextcolor(1, 0);///////////////////////////////////////////////////
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y); printf("%s", *(choices));
		SetTextcolor(15, 0);
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 2); printf("%s", *(choices+1));
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 4); printf("%s", *(choices+2));
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 6); printf("%s", *(choices + 3));
		gotoxy(quiz_answer_select_x, quiz_answer_selcet_y);
		break;
	}
}
int quiz_Select_menu_control(int max_menu_amount, void(*SelectFp)(int, char**), char** choices)//메뉴가 최대 몇개인지 확인+함수 포인터 사용. 
//퀴즈는 얘가 체크해줌.
{
	int ch;
	int Cursor_y = 0;

	while (1)//난이도 선택하는 과정
	{
		ch = _getch();
		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 72:
				Cursor_y = ((Cursor_y - 1) >= 0) ? Cursor_y - 1 : max_menu_amount - 1;// 커서를 위로 이동, 순환하도록 수정
				SelectFp(Cursor_y, choices);
				break;
			case 80:
				Cursor_y = ((Cursor_y + 1) <= max_menu_amount - 1) ? Cursor_y + 1 : 0;// 커서를 아래로 이동, 순환하도록 수정
				SelectFp(Cursor_y, choices);
				break;
			default:
				break;
			}
		}
		else if (ch == 13)
		{
			break;
		}
	}
	return Cursor_y;//커서가 어디에 있었는지 리턴, 0, 1, 2의 형태로 리턴함.
}//게임 메뉴 셀렉트를 도와주는 외부 함수임
void quiz_show_win_screen()
{
	system("cls");
	printf("축하합니다! 맞추셨습니다!");
	Sleep(2000);
}
void quiz_show_defeat_screen()//졌을때 화면
{
	system("cls"); 
	printf("아이고ㅜㅜ 틀리셨습니다!");
	Sleep(2000);
}