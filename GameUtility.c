#include "GameUtility.h"
extern int x, y;//�ܺ� �������� ����
void gotoxy(int x, int y)//�̵� �Լ�, Minigame���� ����� xy�� ������ƿ��Ƽ.h���� �޾Ƽ� �����Ѵ�. 
{
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}//Ŀ�� �̵���Ű�� �Լ�
void CursorClosing() {//Ŀ���� �� ���̰� �ϴ� �Լ�
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void CursorView() {//Ŀ���� ���̰� �ϴ� �Լ�
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = TRUE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
extern int txt, bg;//�ܺκ������� ����
void SetTextcolor(int txt, int bg) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), txt + bg * 16);//�۵� ��Ŀ����� bg�� ��� ����, txt�� �ؽ�Ʈ ������ �ǹ���
	//�ѹ� �ٲ������ �ٽ� �ٲٱ� �������� �� ������ �״�� ������. �̶� �ٲ�°� '���� �ԷµǴ� �ؽ�Ʈ�� ����' ��
	//���� �ѹ� �Ķ������� �ٲ�����, �� �ٽ� �����·� �������� ��!
}
