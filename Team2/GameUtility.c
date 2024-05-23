#include "GameUtility.h"
void gotoxy(int x, int y)//이동 함수, Minigame에서 선언된 xy를 게임유틸리티.h에서 받아서 리턴한다. 
{
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}