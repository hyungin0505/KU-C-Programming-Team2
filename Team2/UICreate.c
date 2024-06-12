#include "GameUI.h"



//스타트 게임 메뉴를 위한 define과 열거형들
#define Start_Menu_x 53//이거 바꾸면 startmenu가 그려지는 위치가 달라집니다
#define Start_Menu_y 18

#define diff_select_menu_x 53 //얘내를 바꾸면 난이도 선택 메뉴가 그려지는 위치가 달라집니다. 
#define diff_select_menu_y 18
//

//스토리가 그려지는 위치
#define Story_Scene_draw_x 30
#define Story_Scene_draw_y 20
//퀴즈게임 UI를 위한 define들
#define quiz_answer_select_x 5
#define quiz_answer_selcet_y 20
typedef enum CursorInput {
	Start,///각각 0, 1, 2에 대응합니다
	Story,
	Quit
}CursorInput;

typedef enum TutorialSelect {//튜토리얼용
	Yes,
	No
} TutorialSelect;
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
//메뉴 셀렉트할?? 사용되는 함수들
extern int Cursor_input;//밖에서 받아오는 매개변수임
void Game_Start_menu_Screen_draw(int Cursor_input)//스타트 메뉴 그려줌.
{
	switch (Cursor_input)//커서가 어디에 가있는지 확인받아서 입력받기 때문에, 바뀔 ??마다 바꿔줄 수 있음.
	{
	case Start://글자색깔을 바꿔줄 수 없기 때문에, 항상 지우고 다시 그려줌.
		printf(" ");
		gotoxy(Start_Menu_x, Start_Menu_y);
		printf(">\b");
		SetTextcolor(1, 0);//텍스트 파란색 배경 검은색. 커서를 바꿔줌.
		gotoxy(Start_Menu_x + 1, Start_Menu_y); printf("게임시작");
		SetTextcolor(15, 0);
		gotoxy(Start_Menu_x + 2, Start_Menu_y + 2); printf("스토리");
		gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("종료");
		gotoxy(Start_Menu_x, Start_Menu_y);
		break;
	case Story:
		printf(" ");//커서 지워주고
		gotoxy(Start_Menu_x, Start_Menu_y + 2);
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
	switch (Cursor_input)//커서가 어디에 가있는지 확인받아서 입력받기 때문에, 바뀔 ??마다 바꿔줄 수 있음.
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
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y); printf("쉬움");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 2); printf("보통");
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 4); printf("어려움");
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
void Game_Tutorial_Screen_draw(int Cursor_input)//튜토리얼용
{
	switch (Cursor_input)
	{
	case Yes:
		printf(" ");
		gotoxy(Start_Menu_x, Start_Menu_y); //
		printf(">\b");
		SetTextColor(1, 0);
		gotoxy(Start_Menu_x + 2, Start_Menu_y); printf("예");
		SetTextColor(15, 0); //
		gotoxy(Start_Menu_x + 1, Start_Menu_y + 2); printf("아니오");
		gotoxy(Start_Menu_x, Start_Menu_y);
		break;
	case No:
		printf(" ");
		gotoxy(Start_Menu_x, Start_Menu_y + 2); //
		printf(">\b");
		SetTextColor(15, 0);
		gotoxy(Start_Menu_x + 2, Start_Menu_y); printf("예");
		SetTextColor(1, 0); //
		gotoxy(Start_Menu_x + 1, Start_Menu_y + 2); printf("아니오");
		gotoxy(Start_Menu_x, Start_Menu_y + 2);
		break;
	default:
		system("cls");
		gotoxy(Start_Menu_x - 8, Start_Menu_y - 8); printf("튜토리얼을 진행할까요?");
		system("cls");
		gotoxy(Start_Menu_x - 8, Start_Menu_y - 8); printf("튜토리얼을 진행할까요?");
		gotoxy(Start_Menu_x, Start_Menu_y); //
		printf(">\b");
		SetTextColor(1, 0);
		gotoxy(Start_Menu_x + 2, Start_Menu_y); printf("예");
		SetTextColor(15, 0); //
		gotoxy(Start_Menu_x + 1, Start_Menu_y + 2); printf("아니오");
		gotoxy(Start_Menu_x, Start_Menu_y);
		break;
	}
}
//스토리 화면

void Game_Story_Select_Screen_draw()//스토리 고르는 화면.
{
	system("cls");
	char story[13][150] =
	{
		{ "....." },
		{ "저기?" },
		{ "내 말 들리나?" },
		{ "들리는 모양이군" },
		{ "여기는 컴퓨터 속 파일 정리 사무소"},
		{ "난 이곳의 총괄 청소부라네" },
		{ "바이러스에 오염된 파일도, 위치를 벗어난 파일도" },
		{ "심지어 조각조각 난 파일도 우리는 원상복구를 해주지" },
		{ "본론부터 얘기해보자고." },
		{ "날 찾아온 것은, 아마 컴퓨터 파일 정리가 필요해서겠지?" },
		{ "평소에 깔끔하게 컴퓨터를 쓰는게 최선이지만"},
		{"불가피하다면 전문가의 손을 빌리는 수밖에 없겠지." },
		{ "좋아. 무슨 일인지 알겠으니 시간 지체 말고 이동하자고." }
	};
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 13; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
		{
			break;
		}
		Sleep(1500);
		if (i != 12)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}
//

//메인게임 맵 이동시 나오는 스토리들. 
// 
void Game_Story_Easy_to_Normal() {//이지에서 노말 넘어가는 스토리
	system("cls");
	SetTextcolor(15, 0);
	char story[3][60] = { { "이 정도 파일들은 정리하기 쉽지." },
						{"정말 어려운 것은 시작도 하지 않았다네"},
						{"더 깊은 곳으로 들어가보세."} };
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 2)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}
void Game_Story_Normal_to_Hard() {//중간에서 어려움 넘어가는 스토리
	SetTextcolor(15, 0);
	char story[6][80] =
	{
			{ "역시 깊은 곳의 오염된 데이터들은 위험하군...." },
			{ "자칫하면 나도 데이터에 휩쓸려 삭제당할 뻔했어" },
			{ "그래도 이제 마지막 단계로군." },
			{ "여기까지 오느라 수고했네" },
			{ "하지만, 자금부터는 정신을 단단히 차리게. "},
			{ "이 앞의 난관은 지난 무엇보다도 더 어려울 테니.." }
	};
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 6; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 5)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}

}
void Game_Story_Endinng() {//엔딜 스토리 
	SetTextcolor(15, 0);
	char story[11][100] =
	{
		{ "이번 의뢰도 성공적으로 완수했군" },
		{"다만 자네 컴퓨터는.. 습관을 바꿀 필요가 있을 것 같더군"},
		{ "필요 없는 파일은 제때제때 지우게" },
		{ "출처가 불분명한 파일은 접근하지 말고" },
		{ "불법 프로그램보단 정품을 사용하게나" },
		{ "또 자네가 날 찾아온다면, 난 자네 컴퓨터를 청소해줄테지만.." },
		{ "...가장 좋은 약은 예방이란 것을 기억하게" },
		{ "나는 다음 의뢰를 받으러 이만 가봐야겠군.." },
		{ "다시 문제가 생긴다면 날 찾아오게나" },
		{ "물론, 웬만하면 그럴 일이 없길 바라지.." },
		{ "그럼 수고하게"}
	};
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int i = 0;
	int isBreak = 0;
	for (i = 0; i < 12; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 10)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
	system("cls");
	printf("T h e E n d");

}
//메인게임 UI
// 
void Maingame_show_gameover_screen()
{
	system("cls");
	SetTextColor(15, 0);

	gotoxy(17, 7);
	printf("GAME OVER");

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
	char story[2][60] =
	{
		{"바이러스에 감염된 데이터네!"},
		{"치료 과정을 진행하도록 하지"}
	};
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 2; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 1)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}


//미니게임 UI

//비밀번호 입력 게임들
void PW_show_start_screen()//패스워드 게임이 시작하기 전 출력되는 함수
{
	char story[2][70] =
	{
		{ "랜섬웨어 때문에 파일에 비밀번호가 걸렸네" },
		{ "비밀번호르 입력해서 이를 해결해야만 하네!" }
	};
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 2; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 1)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}
void PW_game_show_winsreen()
{
	char story[1][40] = { "잠금을 성공적으로 해제했네!" };
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 1; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 0)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}
void PW_game_show_defeatscreen()
{
	char story[1][50] = { "비밀번호 입력에 실패했네.." };
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 1; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 0)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}
//똥피하기 게임들
void GetData_show_start_screen()//똥피하기 게임이 시작하기 전 출력되는 함수.
{
	char story[2][60] = {
		{"배열이 망가져서 데이터가 쏟아지고 있네!"},
		{"쓰레기 값을 피해서 데이터를 주워야 하네!"}
	};
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 2; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 1)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
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
	gotoxy(GetData_Max_X + 13, 15);//나머지는 단순한 출력입??.
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
	if (((double)IsFullCollect / string_size) * 100 >= 100.0)
	{
		printf("데이터를 전부 모았네!");
	}
	else
	{
		printf("데이터를 다 모으지 못했네..");
	}
	Sleep(2000);
}
//퀴즈 미니게임
void quiz_show_start_screen()
{
	char story[2][76] = {
		{"이 데이터가 어떤 데이터인지 문제를 풀어야 하네."},
		{"그래야만 데이터에 접근할 수 있어!"}
	};
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 2; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 1)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}
void quiz_show_screen(char* question)
{
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(0, 3); printf("+----------------------------------------------------------+");
	gotoxy(0, 4); printf("|                                                          |");
	gotoxy(0, 5); printf("|                                                          |");
	gotoxy(0, 6); printf("|                                                          |");
	gotoxy(0, 7); printf("|                                                          |");
	gotoxy(0, 8); printf("|                                                          |");
	gotoxy(0, 9); printf("+----------------------------------------------------------+");

	gotoxy(3, 7);
	printf("다음 문제를 해결하시오!");
	int length = strlen(question);
	int i = 0;
	gotoxy(3, 12);
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
	switch (Cursor_input)//커서가 어디에 가있는지 확인받아서 입력받기 때문에, 바뀔 ??마다 바꿔줄 수 있음.
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
		gotoxy(quiz_answer_select_x, quiz_answer_selcet_y + 2);
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
		gotoxy(quiz_answer_select_x, quiz_answer_selcet_y + 4);
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
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 2); printf("%s", *(choices + 1));
		gotoxy(quiz_answer_select_x + 1, quiz_answer_selcet_y + 4); printf("%s", *(choices + 2));
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
	char story[1][40] = { "정답을 맞췄네!" };
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 1; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 0)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}
void quiz_show_defeat_screen()//졌을때 화면
{
	char story[1][40] = { "오답이네.." };
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 1; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 0)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}

//박스게임 화면들
void BoxGame_show_start_screen()
{
	char story[2][80] = {
		{"헤더가 분리된 데이터들이 있네."},
		{"이들을 다시 합쳐야 데이터를 정상적으로 쓸 수 있다네!"}
	};
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 2; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 1)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}
void BoxGame_show_win_screen()
{
	system("cls");
	char story[1][50] = { "성공적으로 데이터와 헤더를 합쳤네!" };
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 1; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 0)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}
void BoxGame_show_defeat_screen()
{
	system("cls");
	char story[1][50] = { "데이터와 헤더를 합치지 못했네..!" };
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 1; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 0)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}

//틱택토 게임 화면들
void TicTacToe_show_start_screen()
{
	char story[4][80] = {
		{"이게 무슨? Chatgpt가 갑자기 말을 걸어온다.."},
		{"chargpt : 데이터 청소부, 데이터 나에게 있다."},
		{"chatgpt : 나와 틱택토 한다. 이기면 데이터 준다."},
		{"그렇다고 한다. 틱택토를 하자"}
	};
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 4; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 3)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}

}
void TicTacToe_show_win_screen()
{
	system("cls");

	char story[2][80] =
	{
		{ "Ai와의 틱택토에서 승리했다." },
		{ "ai는 데이터를 내놓고 홀연히 사라진다.." }
	};

	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 2; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 1)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}
void TicTacToe_show_defeat_screen()
{
	system("cls");

	char story[2][80] =
	{
		{ "Ai와의 틱택토에서 패배했다.." },
		{ "ai는 데이터를 가지고 홀연히 떠난다.." }
	};

	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 2; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 1)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}
//업다운 게임 화면

void UpdowmGame_show_start_screen() {
	char story[3][80] = {
		{"데이터 주소가 담긴 포인터가 뒷부분이 소실되어 있군.."},
		{"다행히 주변 데이터를 근거로 주소를 추론해볼 수 있네"},
		{"접근 횟수가 한정되어 있으니, 신중하게 주소를 입력하게!"},
	};
	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 2)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}
void UpdownGame_show_win_screen()
{
	char story[1][80] =
	{
		{ "성공적으로 데이터의 주소를 찾았네!" },
	};

	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 1; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 0)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}
void UpdownGame_show_defeat_screen()
{
	char story[1][80] =
	{
		{ "데이터의 주소를 찾지 못했네..!" },
	};

	SetTextcolor(15, 0);//색상 하얀색으로 바꿔줌
	system("cls");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
	gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

	gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
	int isBreak = 0;
	int i = 0;
	for (i = 0; i < 1; i++)
	{
		int length = strlen(story[i]);
		int j = 0;
		while (j < length) {
			printf("%c", story[i][j]);
			Sleep(20);
			j++;

			if (_kbhit()) {
				char input = _getch();
				if (input == '\r') {
					while (j < length) {
						printf("%c", story[i][j]);
						j++;
					}
				}
				if (input == 27)
				{
					isBreak = 1;
					break;
				}

			}

		}
		if (isBreak)
			break;
		Sleep(1500);
		if (i != 0)
		{
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 6); printf("+----------------------------------------------------------+");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 7); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 8); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 9); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 10); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 11); printf("|                                                          |");
			gotoxy(Story_Scene_draw_x, Story_Scene_draw_y + 12); printf("+----------------------------------------------------------+");

			gotoxy(Story_Scene_draw_x + 3, Story_Scene_draw_y + 8);
		}
	}
}