#define _CRT_SECURE_NO_WARNINGS
#include "default_header.h"
#include "GameUtility.h"

//���� �޴� UI��
void Game_Start_Screen_draw();//����ȭ�� �׸��� �Լ�
void Game_Start_menu_Screen_draw(int);//��ŸƮ �޴� �׸��� �Լ�
int Game_Select_menu_control(int, void*(int));//���� UI ������ �� �ְ� ���ִ� �Լ�.
void Game_Difficulty_Select_Screen_draw(int);
void Game_Story_Select_Screen_draw();
//

//���ΰ��� ȭ�� ��ȯ ���丮
void Game_Story_Easy_to_Normal();
void Game_Story_Normal_to_Hard();
void Game_Story_Endinng();
//���ΰ��� ȭ���
// 
void Maingame_show_gameover_screen();//���ΰ��� ���ӿ��� ��ũ��
void Maingame_show_gamecomplete_screen();//���ΰ��� �������ø�Ʈ ��ũ��
void Maingame_show_minigame_inrush_screen();//���ΰ��ӿ��� �̴ϰ������� ������ �� �ߴ� ��ũ��.
//�̴ϰ��� ȭ��

//��й�ȣ ����
void PW_show_start_screen();
void PW_game_show_winsreen();//�̰��� �� UI ������
void PW_game_show_defeatscreen();//���� �� ȭ�� ������
//
//�����ϱ� ���� ȭ���
void GetData_show_start_screen();
void GetData_game_show_menu_screen(int, float, char*, int, int);//�����ϱ� �̴ϰ��� �޴� ȭ��
void GetData_game_show_Gameover_screen(int, int);//�����ϱ� �̴ϰ��� ���� ȭ��
//
void quiz_show_start_screen();
void quiz_show_screen(char*);//������� ����ȭ��. 
void quiz_Select_answer_Screen_draw(int, char**);//������� �����
int quiz_Select_menu_control(int, void* (int, char**), char**);//������� �޴� �ű�°� ����. 
void quiz_show_win_screen();//�̰����� ȭ��
void quiz_show_defeat_screen();//������ ȭ��