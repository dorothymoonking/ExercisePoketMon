#include<stdio.h>
#include<iostream>
#include <cwchar>
#include <windows.h>

#include "Hero.h"

#pragma warning(disable:4996)
using namespace std;

//1. �ʵ� �����ϱ�
// �ʵ带 ���ƴٴϸ鼭 ��带 ȹ�氡���ϴ�
//         =           ���͸� ������ ������ �Ҽ��ִ�.(��������(���� ���н� ���� ����))
//         =           ���͸� ������ ���ص� ü���� �Ҵ´�.

//2. ������
// �̸�(Lv) HP ���
// ���� ���ϸ� ����Ʈ

//3. ����
// ��差
// 1. ������
// 2. ��Ȱ
// 3. ������

//4. ����

//5. ������

//<���� ����>
// ���� ��ȣ, �����̸�(Lv) HP ��Ȳ

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

//----- Ÿ��Ʋ
void TitleUI()
{
	//����� 22ĭ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�" << endl;
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(24, 1);
	cout << "���� ����";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout <<"                       ��" << endl;
	cout << "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int TitleMenuUI()
{
	cout << endl << "                   ���ν���(1) �ε�(2) : ";
	int m_UserSel = 0;
	cin >> m_UserSel;
	cin.get();

	return m_UserSel;
}

void NewHeroMake(Hero* _Hero)
{
	cout << endl;
	char a_Name[128] = { '\0' };
	cout << "������ �̸��� �Է����ּ��� : ";
	cin >> a_Name;
	cin.get();
	_Hero->NewHero(a_Name);
}
//-----

//----- ���θ޴�
 
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