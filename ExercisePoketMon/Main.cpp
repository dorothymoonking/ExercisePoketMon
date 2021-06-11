#include<stdio.h>
#include<iostream>
#include <cwchar>
#include <windows.h>
#include<random>
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

Hero g_Hero;

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

void PrintEyes() //몬스터 발견시 실행할 함수
{
	system("cls");
	gotoxy(10, 0);
	cout << "    □□□             □□□" << endl;
	gotoxy(10, 1);
	cout << "  □■■■□         □■■■□" << endl;
	gotoxy(10, 2);
	cout << "□□■□■□□     □□■□■□□" << endl;
	gotoxy(10, 3);
	cout << "□□■□■□□     □□■□■□□" << endl;
	gotoxy(10, 4);
	cout << "  □■■■□         □■■■□" << endl;
	gotoxy(10, 5);
	cout << "    □□□             □□□" << endl;
	gotoxy(20, 7); 
	cout << "몬스터 발견!";
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
	gotoxy(58, 1);
	cout <<"★" << endl;
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
void MainMenu()
{
	system("cls");
	TitleUI();
	cout << endl;
	g_Hero.PrintInfo();
	cout << endl;
	cout << "필드정찰(1) 내정보(2) 상점(3) 저장(4) 종료(5) : ";
}
//-----

//-----필드 정찰 및 전투구현
void Fight()
{
	PrintEyes();
}

void Field()
{
	bool FightOnOff = false;
	bool GoldAcheive = false;
	system("cls");
	for (int i = 0; i < 10; i++)
	{
		if (i < 3)
		{
			int Ran = rand() % 10;

			if (Ran == 9)
			{
				g_Hero.m_Gold += 50;
				GoldAcheive = true;
			}

			else if (7 < Ran && Ran < 8)
			{
				FightOnOff = true;
				break;
			}
		}

		if (i % 2 == 0)
		{
			gotoxy(10, i);
			if(GoldAcheive == false)
				cout << "뚜벅... 뚜벅...";
			else
				cout << "50골드 획득!";
		}
		else
		{
			gotoxy(30, i);
			if (GoldAcheive == false)
				cout << "뚜벅... 뚜벅...";
			else
				cout << "50골드 획득!";
		}
		GoldAcheive = false;
		Sleep(1000);
	}//for (int i = 0; i < 10; i++)

	if (FightOnOff == true)
	{
		Fight();
	}
	else
	{
		cout << endl << endl << "몬스터를 발견하지 못했습니다...";
		cout << endl << "Enter를 누르면 다음 화면으로..." << endl;
	}
}
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
		NewHeroMake(&g_Hero);
		Save();
		system("cls");
		g_Hero.PrintInfo();
	}
	else
	{
		Load();
	}

	while (true)
	{
		MainMenu();
		int m_MainMenuSell = 0;
		cin >> m_MainMenuSell;
		cin.get();

		if (m_MainMenuSell == 5)
		{
			cout << endl << "게임을 종료 합니다.";
			break;
		}

		if (m_MainMenuSell <= 0 || 5 < m_MainMenuSell)
		{
			cout << endl << "잘못입력하셨습니다! 다시 입력해주세요!" << endl;
			cout << "Enter를 누르면 다음 화면으로..." << endl;
			cin.get();
			continue;
		}

		if (m_MainMenuSell == 1)
		{
			Field();
		}

		else if (m_MainMenuSell == 2)
		{

		}

		else if (m_MainMenuSell == 3)
		{

		}

		else if (m_MainMenuSell == 4)
		{
			Save();
			cout << endl <<  "저장 되었습니다!";
		}
			
		cin.get();
	}

	//while (true)
	//{
	//}
	cin.get();
}