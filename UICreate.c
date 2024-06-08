#include "GameUI.h"



//��ŸƮ ���� �޴��� ���� define�� ��������
#define Start_Menu_x 53//�̰� �ٲٸ� startmenu�� �׷����� ��ġ�� �޶����ϴ�
#define Start_Menu_y 18

#define diff_select_menu_x 53 //�곻�� �ٲٸ� ���̵� ���� �޴��� �׷����� ��ġ�� �޶����ϴ�. 
#define diff_select_menu_y 18
//

//������� UI�� ���� define��
#define quiz_answer_select_x 5
#define quiz_answer_selcet_y 20
typedef enum CursorInput {
	Start,///���� 0, 1, 2�� �����մϴ�
	Story,
	Quit
}CursorInput;

typedef enum difficultyy {
	Easy,///���� 0, 1, 2�� �����մϴ�
	Normal,
	Hard
}Gamedifficulty;
//

void Game_Start_Screen_draw()//���� ó�� �����Ҷ� �׸� �׸��� �Լ�
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
	//���� ��Ŀ���� : Ŀ���� ���� ���� �׸� �׸���, ���߰�, �ٽ� �׸���, ���߰� �ݺ�
}
//�޴� ����Ʈ�ҋ� ���Ǵ� �Լ���
extern int Cursor_input;//�ۿ��� �޾ƿ��� �Ű�������
void Game_Start_menu_Screen_draw(int Cursor_input)//��ŸƮ �޴� �׷���.
{
	switch (Cursor_input)//Ŀ���� ��� ���ִ��� Ȯ�ι޾Ƽ� �Է¹ޱ� ������, �ٲ� ������ �ٲ��� �� ����.
	{
		case Start://���ڻ����� �ٲ��� �� ���� ������, �׻� ����� �ٽ� �׷���.
			printf(" ");
			gotoxy(Start_Menu_x, Start_Menu_y);
			printf(">\b");
			SetTextcolor(1, 0);//�ؽ�Ʈ �Ķ��� ��� ������. Ŀ���� �ٲ���.
			gotoxy(Start_Menu_x+1, Start_Menu_y); printf("���ӽ���");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 2, Start_Menu_y+2); printf("���丮");
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("����");
			gotoxy(Start_Menu_x, Start_Menu_y);
			break;
		case Story:
			printf(" ");//Ŀ�� �����ְ�
			gotoxy(Start_Menu_x, Start_Menu_y+2);
			printf(">\b");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 1, Start_Menu_y); printf("���ӽ���");
			SetTextcolor(1, 0);
			gotoxy(Start_Menu_x + 2, Start_Menu_y + 2); printf("���丮");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("����");
			gotoxy(Start_Menu_x, Start_Menu_y + 2);
			break;
		case Quit:
			printf(" ");//Ŀ�� �����ְ�
			gotoxy(Start_Menu_x, Start_Menu_y + 4);
			printf(">\b");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 1, Start_Menu_y); printf("���ӽ���");
			SetTextColor(15, 0);
			gotoxy(Start_Menu_x + 2, Start_Menu_y + 2); printf("���丮");
			SetTextcolor(1, 0);
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("����");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x, Start_Menu_y + 4);
			break;
		default://���� ó�� �ԷµǾ��� ��
			gotoxy(Start_Menu_x, Start_Menu_y);
			printf(">\b");
			SetTextcolor(1, 0);//�ؽ�Ʈ �Ķ��� ��� ������
			gotoxy(Start_Menu_x + 1, Start_Menu_y); printf("���ӽ���");
			SetTextcolor(15, 0);//�ؽ�Ʈ �Ͼ�� ��� ������
			gotoxy(Start_Menu_x + 2, Start_Menu_y + 2); printf("���丮");
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("����");
			gotoxy(Start_Menu_x, Start_Menu_y);
			break;
	}
}
void Game_Difficulty_Select_Screen_draw(int Cursor_input)
{
	switch (Cursor_input)//Ŀ���� ��� ���ִ��� Ȯ�ι޾Ƽ� �Է¹ޱ� ������, �ٲ� ������ �ٲ��� �� ����.
	{
	case Easy://���ڻ����� �ٲ��� �� ���� ������, �׻� ����� �ٽ� �׷���.
		printf(" ");
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		printf(">\b");
		SetTextcolor(1, 0);////////////////////////////////////////////////////
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y); printf("����");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 2); printf("����");
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 4); printf("�����");
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		break;
	case Normal:
		printf(" ");//Ŀ�� �����ְ�
		gotoxy(diff_select_menu_x, diff_select_menu_y + 2);
		printf(">\b");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y); printf("����");
		SetTextcolor(1, 0);//////////////////////////////////
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 2); printf("����");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 4); printf("�����");
		gotoxy(diff_select_menu_x, diff_select_menu_y + 2);
		break;
	case Hard:
		printf(" ");//Ŀ�� �����ְ�
		gotoxy(diff_select_menu_x, diff_select_menu_y + 4);
		printf(">\b");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y); printf("����");
		SetTextColor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 2); printf("����");
		SetTextcolor(1, 0);///////////////////////////////////////
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 4); printf("�����");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x, diff_select_menu_y + 4);
		break;
	default://���� ó�� �ԷµǾ��� ��
		system("cls");
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		printf(">\b");
		SetTextcolor(1, 0);///////////////////////////////////////////////////
		gotoxy(diff_select_menu_x+1, diff_select_menu_y); printf("����");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x+1, diff_select_menu_y + 2); printf("����");
		gotoxy(diff_select_menu_x+1, diff_select_menu_y + 4); printf("�����");
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		break;
	}
}
int Game_Select_menu_control(int max_menu_amount, void(*SelectFp)(int))//�޴��� �ִ� ����� Ȯ��+�Լ� ������ ���
{
	int ch;
	int Cursor_y = 0;

	while (1)//���̵� �����ϴ� ����
	{
		ch = _getch();
		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 72:
				Cursor_y = ((Cursor_y - 1) >= 0) ? Cursor_y - 1 : max_menu_amount - 1;// Ŀ���� ���� �̵�, ��ȯ�ϵ��� ����
				SelectFp(Cursor_y);
				break;
			case 80:
				Cursor_y = ((Cursor_y + 1) <= max_menu_amount - 1) ? Cursor_y + 1 : 0;// Ŀ���� �Ʒ��� �̵�, ��ȯ�ϵ��� ����
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
	return Cursor_y;//Ŀ���� ��� �־����� ����, 0, 1, 2�� ���·� ������.
}//���� �޴� ����Ʈ�� �����ִ� �ܺ� �Լ���

//���丮 ȭ��
void Game_Story_Select_Screen_draw()//���丮 ���� ȭ��.
{
	char story[] = "���� �̸��� �˷��� ���� ��ǻ�;ȿ��� ��� �ִ� ������ ���� �����ϰ� �ɽ��� ��ǻ�ͼӾּ�"
		"�����ϰ� ������ ����� ������ �ִ� ���� �ٷ� ��ǻ�;��� ��Ʈ���� ���ϵ��� ���ڸ��� �̵����ְ� ���̷����� ������ ���ϵ��� ġ�����ִ� �ϵ�����"
		"��? �̷��ϵ��� �� ��ճİ�? �װ� "
		"�ϵ��� ������ ���غ��� �׷�, �󸶳� �������� ¥���ϰ� ��մ� �ϵ��ε�...  �� ���� ���� û���Ϸ� ������?";

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

//���ΰ��� �� �̵��� ������ ���丮��. 
// 
void Game_Story_Easy_to_Normal() {//�������� �븻 �Ѿ�� ���丮
	SetTextcolor(15, 0);
	char story[] = "����� �������� �������� ��Ǯ���� �հ��� �ϳ� ��� ���Ѱ� ���������� �� ���� �� ��� ������?";

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
void Game_Story_Normal_to_Hard() {//�߰����� ����� �Ѿ�� ���丮
	SetTextcolor(15, 0);
	char story[] = "�̰� �� �����߾�...�׷��� ���� ���� ���� ���� , �ٽ� ���� ������ ����!";

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
void Game_Story_Endinng() {//���� ���丮 
	SetTextcolor(15, 0);
	char story[] = "�̹��ӹ��� �Ϻ��ϰ� �ϼ�! ��ҿ� ��ǻ�͸� �󸶳� ����� �������� �̷��� �����������! �׷��� ��մ� �ӹ����� ���� �ӹ��� �� ���� �������... ���� �� ��¥�� û�������״�"
		"���� ������ ��ǻ�Ͱ� ������ �� ������ �ð���! �׷� ���� �̸� ������ ���ư���";

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
//���ΰ��� UI
// 
void Maingame_show_gameover_screen()
{
	system("cls");
	SetTextColor(15, 0);

	gotoxy(17, 7);
	printf("GAME OVER");

	gotoxy(13, 9);
	printf("�̰͵� �� ��? ��~��");
}
void Maingame_show_gamecomplete_screen()
{
	system("cls");
	SetTextColor(15, 0);

	gotoxy(17, 7);
	printf("CONGRATULATION!");

	gotoxy(10, 9);
	printf("�� ���̵��� ��� ����� �� ��ҽ��ϴ�!");
}
void Maingame_show_minigame_inrush_screen()//�̴ϰ������� ���� �� ��µǴ� ȭ��.
{
	SetTextcolor(15, 0);//���� �Ͼ������ �ٲ���
	system("cls");
	printf("���̷����� ������ �������Դϴ�!!!");
	Sleep(500);
	printf("ġ�� ������ �����մϴ�..");
	Sleep(2000);
}


//�̴ϰ��� UI

//��й�ȣ �Է� ���ӵ�
void PW_show_start_screen()//�н����� ������ �����ϱ� �� ��µǴ� �Լ�
{
	system("cls");
	printf("�������� ������ ���Ͽ� ��й�ȣ�� �ɷȾ�. �̸� �ذ��ؾ߸� ��!");
	Sleep(2000);
}
void PW_game_show_winsreen()
{
	system("cls");
	printf("�����մϴ�! ������ Ŭ�����ϼ̽��ϴ�!");
	Sleep(2000);
}
void PW_game_show_defeatscreen()
{
	system("cls");
	printf("�� �����մϴ�! ������ �� Ŭ�����ϼ̽��ϴ�!");
	Sleep(2000);
}
//�����ϱ� ���ӵ�
void GetData_show_start_screen()//�����ϱ� ������ �����ϱ� �� ��µǴ� �Լ�.
{
	system("cls");
	printf("�迭�� �������� �����Ͱ� ������� �־�! ������ ���� ���ؼ� �����͸� �ֿ��� ��!");
	Sleep(2000);
}
void GetData_game_show_menu_screen(
	int GameHp, float GameOverCount, char* GetData, int string_size, int GetData_Max_X)
	//�̴ϰ��� hp/ ���� ���� �ð�/  ���ݱ��� ���� �迭/ ��ǥ ���ڿ� ������/  ȭ�� ����
{
	int i = 0;
	for (i = 0; i < 30; i++)
	{
		gotoxy(GetData_Max_X + 10, i);
		printf("|");//30�� �ݺ��ϸ鼭 y�� �������� �� ���� �����ִ� ���Դϴ�. 
	}
	gotoxy(GetData_Max_X + 13, 5);
	printf("�������� �����͸� �ֿ켼��!");
	gotoxy(GetData_Max_X + 13, 8);
	printf("���� ü�� : %d", GameHp);
	gotoxy(GetData_Max_X + 13, 12);
	printf("���� �ð� : %.f", GameOverCount);
	gotoxy(GetData_Max_X + 13, 15);//�������� �ܼ��� ����Ԉ�.
	printf("���ݱ��� �ֿ� �迭 : ");
	for (i = 0; i < string_size; i++)
	{
		printf("%c", GetData[i]);//���ݱ��� �ֿ� �迭�� ����մϴ�.
	}
}
void GetData_game_show_Gameover_screen(int IsFullCollect, int string_size) {
	printf("----------------------------------------------------------\n");//ȭ�� ���
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                       GameOver                          |\n");
	printf("|                      �Ϸ��� = %.lf%%                        |\n", ((float)IsFullCollect / string_size) * 100);//�Ϸ����� ������� �ؼ� ���
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	if (((double)IsFullCollect /string_size)*100 >= 60.0)
	{
		printf("�����͸� ���� ��Ҿ�! ������!");
	}
	else
	{
		printf("�����͸� �� ������ ���߾�..");
	}
	Sleep(2000);
}
//���� �̴ϰ���
void quiz_show_start_screen()
{
	system("cls");
	printf("�� �����Ͱ� � ���������� ������ Ǯ��� ��. �׷��߸� �����Ϳ� ������ �� �־�!"); 
	Sleep(2000);
}
void quiz_show_screen(char* question)
{
	system("cls");
	printf("��");
	Sleep(200);
	printf("��");
	Sleep(200); 
	printf("��"); 
	Sleep(200); 
	printf("��!!");
	Sleep(200); 
	printf("\n");
	printf("-------------------------\n");
	printf("|                        |\n");
	printf("|                        |\n");
	printf("|  ���� ������ �ذ��Ͻÿ�|\n");
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
	switch (Cursor_input)//Ŀ���� ��� ���ִ��� Ȯ�ι޾Ƽ� �Է¹ޱ� ������, �ٲ� ������ �ٲ��� �� ����.
	{
	case 0://���ڻ����� �ٲ��� �� ���� ������, �׻� ����� �ٽ� �׷���.
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
		printf(" ");//Ŀ�� �����ְ�
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
		printf(" ");//Ŀ�� �����ְ�
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
		printf(" ");//Ŀ�� �����ְ�
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

	default://���� ó�� �ԷµǾ��� ��
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
int quiz_Select_menu_control(int max_menu_amount, void(*SelectFp)(int, char**), char** choices)//�޴��� �ִ� ����� Ȯ��+�Լ� ������ ���. 
//����� �갡 üũ����.
{
	int ch;
	int Cursor_y = 0;

	while (1)//���̵� �����ϴ� ����
	{
		ch = _getch();
		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 72:
				Cursor_y = ((Cursor_y - 1) >= 0) ? Cursor_y - 1 : max_menu_amount - 1;// Ŀ���� ���� �̵�, ��ȯ�ϵ��� ����
				SelectFp(Cursor_y, choices);
				break;
			case 80:
				Cursor_y = ((Cursor_y + 1) <= max_menu_amount - 1) ? Cursor_y + 1 : 0;// Ŀ���� �Ʒ��� �̵�, ��ȯ�ϵ��� ����
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
	return Cursor_y;//Ŀ���� ��� �־����� ����, 0, 1, 2�� ���·� ������.
}//���� �޴� ����Ʈ�� �����ִ� �ܺ� �Լ���
void quiz_show_win_screen()
{
	system("cls");
	printf("�����մϴ�! ���߼̽��ϴ�!");
	Sleep(2000);
}
void quiz_show_defeat_screen()//������ ȭ��
{
	system("cls"); 
	printf("���̰�̤� Ʋ���̽��ϴ�!");
	Sleep(2000);
}