#include "default_header.h"
#include "GameUtility.h"

typedef struct Obje_Coord {//��ǥ���� �����ϱ� ���� ������� ����ü
	int x;
	int y;
}Obje_Coord;
//
typedef struct Player_Coord {//�÷��̾��� ������ �����ϱ� ���� ����, ��ǥ���� speed ��..
	int x;
	int y;
	int hp;//hp�� �� ���� ������ �𸣰ڴ�. 
	int flagcount;//��� �󸶳� ��ҳ�
	int remain_move_amount;//���� �̵� ������ Ƚ�� 
	int limit_break;//���� ��ֹ� �ı� Ƚ��
}Player_Coord;


void Maingame_Base_init(int); // �ܼ�â �� ���� ���� �⺻ ��� ����. ���⼭���� ���ʴ�� �ʱ�ȭ�Ǵ� ���
void Maingame_map_printing();
void Maingame_map_element_init(); // �� ���� ���(��, ���, ��ֹ�) ���� ����
void Game_start(); //���� �����ϴ� �Լ�
//init -> printing -> element_init ������ �۵���!
void on_flag_f(); // �÷��̾ ��߿� ��ġ�� ��
int check_flag_t(); // �÷��̾ ���� �Ϲ� ������ Ȯ��
void Maingame_break_obstacle(int, int);//��ֹ� �μ��� �ڵ�
//
void Maingame_start_minigame(int difficulty);//�̴ϰ��� ����
//
//�̴ϰ��� �¸�, �й�� ������ �Լ���
void Maingame_get_reward(void);
void Maingame_get_penalty();
//
//�¸��� ������ ���� �Լ��� 
void Maingame_reward_show_event_flag(void);//���̷��� ��ߵ��� ��� ��������.
void Maingame_reward_get_flag(void);//�Ϲ� ����� ��� �Ծ���.

//�̴ϰ��� �й�� ������ �г�Ƽ �Լ��� 
void Maingame_get_penalty();
void Maingame_penalty_change_locate(void);//��� ��ġ �ٲٴ� �Լ�.//���ΰ��� ���� �¸�, �й� �Լ���
void Maingame_gameover();//���ΰ��� ���ӿ����� ������ ȭ��
void Maingame_gamecomplete();//������ Ŭ���������� ������ ȭ��