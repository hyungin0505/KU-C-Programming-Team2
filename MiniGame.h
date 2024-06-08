#include "default_header.h"
#include "GameUtility.h"
#include "GameUI.h"

//���� ��ü������ ���̴� ����ü
typedef struct level_memory {//���� �ð��� hp. 
	float end_time;
	int hp;
}level_memory;
//

//�н�������ӿ� ����ü ����
typedef struct Password_inform {//�Ծ�� �ϴ� ��ǥ�� ������ ��� ��Ʈ����.. 
	size_t size;//����� ������ ���� �κ�
	char* pw;//�н����� ������ ���� �κ�
}Password_inform;
//
//�н����� �̴ϰ��ӿ� �Լ���
void PW_game_init(difficulty);
void PW_game(Password_inform*, level_memory*);//��й�ȣ ����. 
void PW_game_show_PW_screen(Password_inform*);//��Ʈ + �н����� �����ִ� ȭ��
void PW_game_show_input_screen(int, int);//��ǲȭ��
void PW_game_wIn();//�¸����� �� ����
void PW_game_defeat();//�й���� �� ����

void Test();

//GetData�� ����������
int* FindDupli;//������Ʈ ���� �ߺ� �ִ��� Ȯ�� /���� �Ҵ���. ���� �� �޸� ���� ��ٸ� �̰� �ʱ�ȭ�ߴ��� �ٽ� Ȯ���غ���
typedef struct ObjectCoord//������Ʈ ��ǥ�� �����ص� ��Ʈ����
{
	int x;//x��
	int y;//y��
	int speed;//�ӵ�
}ObjectCoord;

typedef struct target {//�Ծ�� �ϴ� ��ǥ�� ������ ��� ��Ʈ����.. 
	char* name;
	size_t n;
}target;
//�ٵ����Ϳ� �Լ���
void GetData_game_init(difficulty);//�ٵ����� ���� �ʱ�ȭ
void Getdata_Minigame(target*, level_memory*, int, int, int);//�������� �����͸� ���������� �ݴ� ����
void Control_Obst_Move(ObjectCoord*, int, ObjectCoord, int*, int, int);//�ٵ����Ϳ�, ������Ʈ���� ���� ��ġ ��Ʈ��
void Control_Target_Move(ObjectCoord*, target*, int, char*, int, ObjectCoord, char*, int, int);//���������Ʈ���� ��ġ ��Ʈ��
void Control_Player_Move(ObjectCoord*);//�÷��̾� ��ġ ��Ʈ��
void get_position(size_t, int, int);//���� ��ġ �ο�
void GetData_Gameover(int, int);//���ӿ����� ����Ǵ� �Լ�

//���� ���ӿ� ����ü ����
typedef struct {
	char question[256];
	char* choices[4];//���� ���� 4���� ������. 
	int correct_answer; // 0-3 index of the correct answer
} Question;

//���� ���ӿ� �Լ� ����
void quiz_game_init(difficulty);
void quiz_Minigame(Question*);
void shuffle(int*, int);//���� ���� ����
void quiz_win();//���� �¸�������
void quiz_defeat();//���� �й����� ��
int print_question(Question);