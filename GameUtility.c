#include "GameUtility.h"
void gotoxy(int x, int y)//�̵� �Լ�, Minigame���� ����� xy�� ������ƿ��Ƽ.h���� �޾Ƽ� �����Ѵ�. 
{
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}