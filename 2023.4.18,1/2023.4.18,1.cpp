// 2023.4.18,1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"

void Keyboard(bool* playing, int* x, int* y);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);

int main()
{
    HANDLE hOP; // 핸들값 가져오기
    hOP = GetStdHandle(STD_OUTPUT_HANDLE);

    // 커서 숨기기
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.bVisible = false;
    curInfo.dwSize = 1;
    SetConsoleCursorInfo(hOP, &curInfo);

    bool isPlaying = true;
    int x = 10, y = 10;

    cout << "x좌표 : " << x << endl;
    cout << "y좌표 : " << y << endl;
    Draw(hOP, x * 2, y, (char*)"A", BACKGROUND_RED);

    while (isPlaying)
    {
        if (_kbhit())    // 키 버퍼 확인 : 키 입력이 있는 경우 버퍼에 값이 생겨서 true가 변환된다.
        {
            Keyboard(&isPlaying, &x, &y); // 키보드 함수 호출

            system("cls");
            cout << "x좌표 : " << x << endl;
            cout << "y좌표 : " << y << endl;
            Draw(hOP, x * 2, y, (char*)"A", BACKGROUND_RED);
            while (_kbhit()) _getch();   // 키를 한번만 눌러도 버퍼에 값이 계속 남아있게 되서 그 값들을 getch() 함수를 이용해서 비워줌
                                        // getch() 함수는 입력된 키보드 값을 변수로 바로 저장할 때도 사용됨
        }
    }

    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

void Keyboard(bool* playing, int* x, int* y)
{
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // 오른쪽 방향키, 정의 - F12로 출처 타고 들어갈 수 있음
        (*x)++;
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 왼쪽 방향키
        (*x)--;
    else if (GetAsyncKeyState(VK_UP) & 0x8000) // 위쪽 방향키
        (*y)--;
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000) // 아래쪽 방향키
        (*y)++;
    else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) // ESC
        *playing = false;
}

void Draw(HANDLE hOP, int x, int y, char* str, WORD color)
{
    DWORD dwCharsWritten;
    COORD cdFill = { x,y };

    FillConsoleOutputAttribute(hOP, color, strlen(str), cdFill, &dwCharsWritten); // 색상을 입혀줌
    WriteConsoleOutputCharacter(hOP, str, strlen(str), cdFill, &dwCharsWritten); // 문자를 적어줌
    // str : 호환되지 않는다 뜨면 프로젝트 - 속성 - 고급 - 문자집합 - 멀티바이트 문자 집합 사용으로 변경
}
