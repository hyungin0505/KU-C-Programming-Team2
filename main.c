#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#define FLAGS_FALSE 2 // ���Ƽ ��� ����
#define FLAGS_TRUE 1 // �Ϲ� ��� ����
#define MAX_X 50 //���� x�� ���� ũ��
#define MAX_Y 15 //���� y�� ���� ũ��

int locate_flags_false[FLAGS_FALSE][2]; // ���Ƽ ����� ������ (x, y) ��ǥ�� �����ϴ� �迭
int locate_flags_true[FLAGS_TRUE][2]; // �Ϲ� ����� ������ (x, y) ��ǥ�� �����ϴ� �迭

int locate_player[1][2] = {
	{0,}
}; // �÷��̾ ��ġ�� (x, y) ��ǥ�� �����ϴ� �迭

void base_setting(void); // �ܼ�â �� ���� ���� �⺻ ��� ����
void textcolor(int color_number); //�ܼ�â �ؽ�Ʈ ���� ����
void gotoxy(int x, int y); // �ܼ�â Ŀ�� �̵�
void on_flag_false(void); // �÷��̾ ��߿� ��ġ�� ��
int check_flag_true(void); // �÷��̾ ���� �Ϲ� ������ Ȯ��
/*

1. ���� �� ������(O)
	-> �� ũ�� ���� ���̵� ���� 50 * 15(O), �� ũ��� ���� ����(Ŀ���� �۾�����)
	-> ��ֹ� ����(O)

2. ��� ��ġ ���� ���(O)
	-> �� ó�� �÷��̾��� ���� ��ġ(1, 13)������ ����� �������� X(O)

3. ��� ����(O)
	-> ��ȣ ��� ����, �ϴ��� ���� ���� 3��(O)
	-> ���Ƽ ���, �Ϲ� ��� ����, ���� ���� -> ���Ƽ : �Ϲ� = 1: 2(O)
	-> �Ϲ� ����� ��� ��ƾ� �ش� �� Ŭ����(O)

4. ��߿� ���� �� �̺�Ʈ ���(��)
	-> �� ����� x, y��ǥ�� ���� �� �÷��̾��� ��ǥ�� ��ġ�� ��� �̺�Ʈ �߻�(O)
	-> �Ϲ� ��� �� ���� ��� ���� ȭ�� ��� �� ���α׷� ����(O)

	-> ���� �̺�Ʈ�� �Ͼ�� ����(��)
	-> ���� ��� ��Ҵ� ���̵� �ߺ��� ��� ex) ��Ģ ��߰� �Ϲ� ����� �� ����
	-> ��Ģ ��� �ʿ�

5. �����̴� �׼�(��)
	-> ���� ��踦 ���� ���ϰ� ó��(O)
	-> ��ֹ��� ���� ���ϰ� ó��(X)


---------------------------------- �ڵ�� ���� ���� �н��̳� ���ͳ� ����� �� �����ϰ� ǥ���� �����ϸ� ���� ���� -------------------------------------------


���̵��: ��Ģ�� �ִ� ���, ��¥ ���, ��� ���߸� ����, Ʋ���� ��Ģ�� �ִ� ���
	
	-> ���� ��� ����:
		1. C���α׷��� �Ϲ� ����
		2. ��ǻ�Ͱ��а��� �Ϲ� ����
		3. 
		4.
		5.

	-> ��Ģ ��� ����: 
		1. �ð� ����
		2. ü�� ����
		3. ������ ��ƼƼ �߰� - ex) ���� ����Ʈ���� or ���
		4. ���� ��� ��ġ ����
		5. ���̵� ������� ��� ��Ģ X, �ٷ� Game Over(�翬�� ��Ģ�� �ִ� ��ߵ� X)

	-> ���� ��� ����:
		1. ���Ƽ ��߰� �Ϲ� ����� �� ����
		2. ���Ƽ ��� ����
		3. ���� ����
		4. �ð� ����
		5. ü�� ����
		6. ��ֹ� ����
*/

int main(void)
{
	base_setting();
	
	int x = 1, y = (MAX_Y - 2), ch;

	while (1)
	{
		gotoxy(x, y);
		printf("*\b");

		locate_player[0][0] = x;
		locate_player[0][1] = y;

		on_flag_false(); // �÷��̾ ���Ƽ ����� ������� Ȯ��

		if (check_flag_true()) // �÷��̾ �Ϲ� ����� �������, �� ��Ҵ��� Ȯ��
		{
			Sleep(1000); // �� ���� ��� ���� ȭ�� ���, 1�� �� ���α׷� ����
			break;
		}

		ch = _getch();

		if (ch == 224) // ����Ű ó��
		{
			ch = _getch();

			switch (ch) {
			
			case 72:
				if (y == 1)
					break;
				y--;
				break;
			case 80:
				if (y == (MAX_Y - 2))
					break;
				y++;
				break;
			case 75:
				if (x == 1)
					break;
				x--;
				break;
			case 77:
				if (x == (MAX_X - 2))
					break;
				x++;
				break;
			}
		}

	}
}

void base_setting(void) // �ܼ�â �� ���� ���� �⺻ ��� ����
{
	srand((unsigned)time(NULL));

	system("mode con: cols=200 lines=15"); // �ܼ�â�� ũ�� ����, cols = ��, lines = ��
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = FALSE; // ���콺 Ŀ���� ������ �ʰ� ����, �ٸ�, ���κҸ����� Ŀ���� ����
	ConsoleCursor.dwSize = 1; // Ŀ���� ������
	textcolor(11); // ��µ� �ؽ�Ʈ�� ����

	for (int i = 0; i < MAX_Y; i++) // �⺻ �� ���, ��� ��� ������ �ʿ��� ���� ����
	{
		if (i == 0)
			printf("����������������������������������������������������������������������������������������������������");

		
		else if (i == (MAX_Y - 1))
			printf("����������������������������������������������������������������������������������������������������");

		else
			printf("��                                                ��");

		printf("\n");
	}

	for (int i = 2; i < MAX_Y - 2; i++) // ��ֹ��� ������ ��ġ ����(�� ù �ٰ� �� �Ʒ� �� ����)
	{
		for (int j = 1; j < rand() % 30; j++) // x�࿡�� ������ ��ֹ� ���� ���� ����
		{
			gotoxy(2 + rand() % (MAX_X - 4), i); // ��ֹ� ��ġ
			printf("��");
		}
	}

	for (int i = 0; i < (FLAGS_TRUE + FLAGS_FALSE); i++) // ����� ������ ��ġ ���� �� ��ǥ ����
	{
		int x_locate = 1 + rand() % (MAX_X - 3); // ����� ������ ���� �մ� ���� �߻�
		int y_locate = 1 + rand() % (MAX_Y - 2);

		if (x_locate == 1 && y_locate == (MAX_Y - 2)) // ���� ��ġ�� �������� ����
		{
			i--;
			continue;
		}

		if (i < FLAGS_TRUE) // ��¥ ����� ��ġ ����
		{
			gotoxy(x_locate, y_locate);
			printf("��"); // ��� ������ �ĺ��� �̡ڡ�ǢȢ���

			locate_flags_true[i][0] = x_locate;
			locate_flags_true[i][1] = y_locate;
		}

		else // ��¥ ����� ��ġ ����
		{
			gotoxy(x_locate, y_locate);
			printf("��"); // ��� ������ �ĺ��� �̡ڡ�ǢȢ���

			locate_flags_false[i - FLAGS_TRUE][0] = x_locate;
			locate_flags_false[i - FLAGS_TRUE][1] = y_locate;
		}

	}
}

void textcolor(int color_number) // �ܼ�â �ؽ�Ʈ ���� ����
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number); // color_number�� 11�̶� 11�� ���� ���
}

void gotoxy(int x, int y) // �ܼ�â Ŀ�� �̵�
{
	COORD Cur = { x, y };
	printf(" ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void on_flag_false(void) // �÷��̾ ���Ƽ ��߿� ��ġ�� ��
{
	for (int i = 0; i < FLAGS_FALSE; i++) // �÷��̾ ���Ƽ ��߿� ��ġ�ϴ��� Ȯ��, ��ġ�ϸ� �̺�Ʈ �߻�
	{
		if (locate_flags_false[i][0] == locate_player[0][0] && locate_flags_false[i][1] == locate_player[0][1])
		{
			gotoxy(70, 2);
			printf("���Ƽ ����Դϴ�!");
			Sleep(3000);

			gotoxy(70, 4);
			printf("������ Ǫ�ž� ���� �� �ֽ��ϴ�.");
			
			gotoxy(70, 5);
			printf("����Ű�� ������ �ٽ� ������ ���ư��ϴ�."); // ����� ������ ������ ��� �ٷ� �Ѿ��
		}
	}
}

int check_flag_true(void) // �÷��̾ �Ϲ� ��߿� ��ġ�� ��
{
	static int count = 0;
	
	for (int i = 0; i < FLAGS_TRUE; i++) // �÷��̾ �Ϲ� ��߿� ��ġ�ϴ��� Ȯ��, ��ġ�ϸ� �̺�Ʈ �߻�
	{
		if (locate_flags_true[i][0] == locate_player[0][0] && locate_flags_true[i][1] == locate_player[0][1])
			count++;
	}

	if (count == FLAGS_TRUE) // ��� �Ϲ� ����� �� ���� ���
	{
		system("cls");

		gotoxy(17, 7);
		printf("��� �Ϲ� ����� �� ��ҽ��ϴ�!");

		return 1;
	}

	return 0;
}