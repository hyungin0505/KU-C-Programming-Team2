#define _CRT_SECURE_NO_WARNINGS
#include "All_In_one_header.h"

//��� ������ ������ ����
typedef enum CursorInput {
    Start,///���� 0, 1, 2�� �����մϴ�
    Story,
    Quit
}CursorInput;//Ŀ���� ��� �ִ��� ȣ�����ϴ� ���� �������ֱ� ����.

typedef enum difficultyy {
    Easy,///���� 0, 1, 2�� �����մϴ�
    Normal,
    Hard,
    End
}Gamedifficulty;
//
int main()
{
    SetTextcolor(15, 0);
    srand((unsigned int)time(NULL));
    CursorClosing(); // Ŀ���� ����������
    Game_Start_Screen_draw(); // ���� ȭ�� �׸�
    Game_Start_menu_Screen_draw(3); // �⺻ ���� �׸���
    switch(Game_Select_menu_control(3, Game_Start_menu_Screen_draw))//���� �޴� ������ �޴��� 3���̹Ƿ� 3�� ��
    {
        case Start:
            Game_Difficulty_Select_Screen_draw(3);
            break;

        case Story:
            Game_Story_Select_Screen_draw(3);//���丮�� �� ������ �ٷ� ���̵� ���� ȭ������ �Ѿ.
            system("cls");//ȭ�� �ʱ�ȭ
            Game_Difficulty_Select_Screen_draw(3);
            break;
        case Quit:
            system("cls");
            printf("������ �����մϴ�");//���� ���� ��ũ��, ����� ���� �Լ��� ���� ���� �Ҹ�Ȯ��.
            return 0;
            break;
    }
    //���̵� ���� ȭ��
    switch (Game_Select_menu_control(3, Game_Difficulty_Select_Screen_draw))//���� �޴� ������ �޴��� 3���̹Ƿ� 3�� ��
    {
    case Easy:
        Maingame_Base_init(Easy);
        Sleep(2000);
        //�Ѿ�� ���丮 �ƾ� �߰�. ����������ŷ���� ��� �ѱ�. 
    case Normal:
        Game_Story_Easy_to_Normal();
        Sleep(2000);
        Maingame_Base_init(Normal);
        system("cls");
        printf("�ϵ�� �Ѿ�ϴ�!");
        //�Ѿ�� ���丮 �ƾ� �߰�
    case Hard:
        Game_Story_Normal_to_Hard();
        Sleep(2000);
        Maingame_Base_init(Hard);
    case End:
        Game_Story_Endinng();
        Sleep(2000);
        break;
    }
    return 0;
  
}
