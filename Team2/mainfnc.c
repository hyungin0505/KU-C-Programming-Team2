#define _CRT_SECURE_NO_WARNINGS
#include "All_In_one_header.h"

//사용 가능한 열거형 정의
typedef enum CursorInput {
    Start,///각각 0, 1, 2에 대응합니다
    Story,
    Quit
}CursorInput;//커서가 어디에 있는지 호강니하는 것을 통일해주기 위함.

typedef enum TutorialSelect {
    Yes,
    No
} TutorialSelect;

typedef enum difficultyy {
    Easy,///각각 0, 1, 2에 대응합니다
    Normal,
    Hard,
    End,
    Tutorial
}Gamedifficulty;
//
int main()
{
    SetTextcolor(15, 0);
    srand((unsigned int)time(NULL));
    CursorClosing(); // 커서를 지워버리고
    Game_Start_Screen_draw(); // 시작 화면 그림
    Game_Start_menu_Screen_draw(3); // 기본 세팅 그리기
    switch (Game_Select_menu_control(3, Game_Start_menu_Screen_draw))//게임 메뉴 셀렉팅 메뉴가 3개이므로 3개 씀
    {
    case Start:
        Game_Tutorial_Screen_draw(2);
        break;

    case Story:
        Game_Story_Select_Screen_draw();//스토리를 본 다음엔 바로 난이도 선택 화면으로 넘어감.
        system("cls");//화면 초기화
        Game_Tutorial_Screen_draw(2); //투토리얼로 가는 마법의 문
        break;
    case Quit:
        system("cls");
        printf("게임을 종료합니다");//게임 종료 스크린, 여기는 따로 함수로 ?壺?할지 불명확함.
        return 0;
        break;
    }

    switch (Game_Select_menu_control(2, Game_Tutorial_Screen_draw))
    {
    case Yes:
        Maingame_Base_init(Tutorial);//만약 튜토리얼 선택하면 튜토리얼을 하게 해드려야지(3이 감)
        break;
    case No:
        Game_Difficulty_Select_Screen_draw(3);
        break;
    }

    //난이도 선택 화면
    switch (Game_Select_menu_control(3, Game_Difficulty_Select_Screen_draw))//게임 메뉴 셀렉팅 메뉴가 3개이므로 3개 씀
    {
    case Easy:
        Maingame_Base_init(Easy);
        Sleep(2000);
        //넘어가는 스토리 컷씬 추가. 뭐?慧囑澯뵀쩨렝막?계속 넘김. 
    case Normal:
        Game_Story_Easy_to_Normal();
        Maingame_Base_init(Normal);
        system("cls");
        printf("하드로 넘어갑니다!");
        //넘어가는 스토리 컷씬 추가
    case Hard:
        Game_Story_Normal_to_Hard();
        Maingame_Base_init(Hard);
    case End:
        Game_Story_Endinng();
        break;
    case Tutorial:
        break;
    }
    return 0;

}
