#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include <conio.h>
#include <string.h>
#include "GameUtility.h"//���� ����µ��� �ʿ��� 

static int ch;//����ڷκ��� �Է¹޴�
static int x = 53, y = 18;//�Է���ǥ
void setcolor(int txt, int bg);//�ؽ�Ʈ�� ��� ���� �ٲٴ� �Լ� txt�� �ؽ�Ʈ ���� bg�� ������
void CursorView();//Ŀ�� ����� �Լ�
void menu();//ù��° ���ӽ��� ���丮 ���� �����ϴ� �Լ�
void draw();//�׸� ����ϴ� �Լ�
void menu1();//ù��° �޴��Լ����� �������� ����ϴ� �Լ�
void difficulty();//���̵� ������� �����ϴ� �Լ�
void menu2();//������ ���̵� ����ϴ� �Լ�

int main() {
	
	system("title �������� ã��");

	CursorView();//Ŀ�� �����
	draw();//�׸� ���
	setcolor(1, 0);//�ؽ�Ʈ �Ķ��� ��� ������
	gotoxy(54, 18); printf("���ӽ���");

	setcolor(15, 0);//�ؽ�Ʈ �Ͼ�� ��� ������
	gotoxy(55, 20);printf("���丮");

	gotoxy(56, 22);printf("����");
	menu();
	system("cls");//ȭ�� �����
	menu1();
	
	
}

void setcolor(int txt, int bg) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), txt + bg * 16);

}

void CursorView() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void draw() {
	gotoxy(45, 2);
	printf("_____    _____");
	Sleep(200);
	gotoxy(47, 3);
	printf("ll       ll");
	Sleep(200);
	gotoxy(47,4);
	printf("-       -");
	Sleep(200);
	gotoxy(49, 7);
	printf("  ��");
	Sleep(200);
	//���� ��Ŀ���� : Ŀ���� ���� ���� �׸� �׸���, ���߰�, �ٽ� �׸���, ���߰� �ݺ�
		

	}
void menu() {
	do{
		gotoxy(x, y);
		setcolor(15, 0);
		printf(">\b");
		ch = _getch();

		if (ch == 224) {

			printf(" ");
			ch = _getch();
			switch (ch) {
			case 72:
				if (y == 18) {
					y = 22;
					
					setcolor(15, 0);
					gotoxy(54, 18); printf("���ӽ���");

					setcolor(15, 0);
					gotoxy(55, 20); printf("���丮");

					setcolor(1, 0);
					gotoxy(56, 22); printf("����");
				}

				else if (y == 22) {
					y -= 2;
					setcolor(15, 0);
					gotoxy(54, 18); printf("���ӽ���");

					setcolor(1, 0);
					gotoxy(55, 20); printf("���丮");
					setcolor(15, 0);
					gotoxy(56, 22); printf("����");
				}
				else if(y==20) {
					y -= 2;
					setcolor(1, 0);
					gotoxy(54, 18); printf("���ӽ���");

					setcolor(15, 0);
					gotoxy(55, 20); printf("���丮");
					setcolor(15, 0);
					gotoxy(56, 22); printf("����");
				}
				break;
			case 80:
				if (y == 22) {
					y = 18;
					setcolor(1, 0);
					gotoxy(54, 18); printf("���ӽ���");

					setcolor(15, 0);
					gotoxy(55, 20); printf("���丮");
					setcolor(15, 0);
					gotoxy(56, 22); printf("����");
				}
				else if (y == 20) {
					y+= 2;
					setcolor(15, 0);
					gotoxy(54, 18); printf("���ӽ���");

					setcolor(15, 0);
					gotoxy(55, 20); printf("���丮");
					setcolor(1, 0);
					gotoxy(56, 22); printf("����");
				}

				else if (y == 18) {
					y += 2;
					setcolor(15, 0);
					gotoxy(54, 18); printf("���ӽ���");

					setcolor(1, 0);
					gotoxy(55, 20); printf("���丮");
					setcolor(15, 0);
					gotoxy(56, 22); printf("����");
				}
				break;
			}

		}

	} while (ch != 13);
	
}
void menu1() {
	if ( y == 18) {
		gotoxy(54, 18);
		setcolor(1, 0);
		printf("����");
		
		setcolor(15,0);
		gotoxy(54, 20);
		printf("����");

		gotoxy(54, 22);
		printf("�����");
		difficulty();
		system("cls");
		menu2();
	}
	else if (y == 22) {
		gotoxy(50, 15);
		printf("������ �����մϴ�");
		for (int i = 0; i < 13; i++)
			printf("\n");
		
	}
	else
	{
		char story[] = "������ ��ġ�� �Դ�... �߾�!!!!!";//���丮�� ������ �����
		for (int i = 0; i < 30; i++) {
			printf("%c", story[i]);
			Sleep(50);//�ѱ����ѱ��� ���
		}
	}
}
void menu2() {
	if (y == 18) {
		printf("����̵�~")

			;
	}
	else if ( y == 20) {
		printf("����~");
	}
	else if (y == 22)
		printf("�����~");
	
}
void difficulty() {
	do {
		gotoxy(x, y);
		setcolor(15, 0);
		printf(">\b");
		ch = _getch();

		if (ch == 224) {

			printf(" ");
			ch = _getch();
			switch (ch) {
			case 72:
				if (y == 18) {
					y = 22;

					setcolor(15, 0);
					gotoxy(54, 18); printf("����");

					setcolor(15, 0);
					gotoxy(54, 20); printf("����");

					setcolor(1, 0);
					gotoxy(54, 22); printf("�����");
				}

				else if (y == 22) {
					y -= 2;
					setcolor(15, 0);
					gotoxy(54, 18); printf("����");

					setcolor(1, 0);
					gotoxy(54, 20); printf("����");
					setcolor(15, 0);
					gotoxy(54, 22); printf("�����");
				}
				else if (y == 20) {
					y -= 2;
					setcolor(1, 0);
					gotoxy(54, 18); printf("����");

					setcolor(15, 0);
					gotoxy(54, 20); printf("����");
					setcolor(15, 0);
					gotoxy(54, 22); printf("�����");
				}
				break;
			case 80:
				if (y == 22) {
					y = 18;
					setcolor(1, 0);
					gotoxy(54, 18); printf("����");

					setcolor(15, 0);
					gotoxy(54, 20); printf("����");
					setcolor(15, 0);
					gotoxy(54, 22); printf("�����");
				}
				else if (y == 20) {
					y += 2;
					setcolor(15, 0);
					gotoxy(54, 18); printf("����");

					setcolor(15, 0);
					gotoxy(54, 20); printf("����");
					setcolor(1, 0);
					gotoxy(54, 22); printf("�����");
				}

				else if (y == 18) {
					y += 2;
					setcolor(15, 0);
					gotoxy(54, 18); printf("����");

					setcolor(1, 0);
					gotoxy(54, 20); printf("����");
					setcolor(15, 0);
					gotoxy(54, 22); printf("�����");
				}
				break;
			}

		}

	} while (ch != 13);


}

