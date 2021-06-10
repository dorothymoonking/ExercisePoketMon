#include<stdio.h>
#include<iostream>
#include <cwchar>
#include <windows.h>

#include "Hero.h"

#pragma warning(disable:4996)
using namespace std;

//1. 필드 정찰하기
// 필드를 돌아다니면서 골드를 획득가능하다
//         =           몬스터를 만나서 전투를 할수있다.(도망가능(도망 실패시 강제 전투))
//         =           몬스터를 만나지 못해도 체력을 잃는다.

//2. 내정보
// 이름(Lv) HP 골드
// 보유 포켓몬 리스트

//3. 상점
// 골드량
// 1. 레벨업
// 2. 부활
// 3. 나가기

//4. 저장

//5. 끝내기

//<몬스터 정보>
// 몬스터 번호, 몬스터이름(Lv) HP 상황

void Save()
{

}

void Load()
{

}

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//----- 타이틀
void TitleUI()
{
	//빈공간 22칸
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★" << endl;
	cout << "☆";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(24, 1);
	cout << "몬스터 헌터";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout <<"                       ★" << endl;
	cout << "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int TitleMenuUI()
{
	cout << endl << "                   새로시작(1) 로딩(2) : ";
	int m_UserSel = 0;
	cin >> m_UserSel;
	cin.get();

	return m_UserSel;
}

void NewHeroMake(Hero* _Hero)
{
	cout << endl;
	char a_Name[128] = { '\0' };
	cout << "유저의 이름을 입력해주세요 : ";
	cin >> a_Name;
	cin.get();
	_Hero->NewHero(a_Name);
}
//-----

//----- 메인메뉴
 
//-----

void main()
{
	system("mode con cols=60 lines=30");

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 18;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	TitleUI();
	int m_TitleMenuNum = TitleMenuUI();
	if (m_TitleMenuNum == 1)
	{
		Hero m_Hero;
		NewHeroMake(&m_Hero);
		Save();
		system("cls");
		m_Hero.PrintInfo();
	}
	else
	{
		Load();
	}

	//while (true)
	//{
	//}
	cin.get();
}