#include<stdio.h>
#include<iostream>
#include <cwchar>
#include <windows.h>
#include<random>
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

void PrintEyes() //���� �߽߰� ������ �Լ�
{
	system("cls");
	gotoxy(10, 0);
	cout << "    ����             ����" << endl;
	gotoxy(10, 1);
	cout << "  ������         ������" << endl;
	gotoxy(10, 2);
	cout << "��������     ��������" << endl;
	gotoxy(10, 3);
	cout << "��������     ��������" << endl;
	gotoxy(10, 4);
	cout << "  ������         ������" << endl;
	gotoxy(10, 5);
	cout << "    ����             ����" << endl;
	gotoxy(20, 7); 
	cout << "���� �߰�!";
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
	gotoxy(58, 1);
	cout <<"��" << endl;
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
void MainMenu()
{
	system("cls");
	TitleUI();
	cout << endl;
	g_Hero.PrintInfo();
	cout << endl;
	cout << "�ʵ�����(1) ������(2) ����(3) ����(4) ����(5) : ";
}
//-----

//-----�ʵ� ���� �� ��������
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
				cout << "�ѹ�... �ѹ�...";
			else
				cout << "50��� ȹ��!";
		}
		else
		{
			gotoxy(30, i);
			if (GoldAcheive == false)
				cout << "�ѹ�... �ѹ�...";
			else
				cout << "50��� ȹ��!";
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
		cout << endl << endl << "���͸� �߰����� ���߽��ϴ�...";
		cout << endl << "Enter�� ������ ���� ȭ������..." << endl;
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
			cout << endl << "������ ���� �մϴ�.";
			break;
		}

		if (m_MainMenuSell <= 0 || 5 < m_MainMenuSell)
		{
			cout << endl << "�߸��Է��ϼ̽��ϴ�! �ٽ� �Է����ּ���!" << endl;
			cout << "Enter�� ������ ���� ȭ������..." << endl;
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
			cout << endl <<  "���� �Ǿ����ϴ�!";
		}
			
		cin.get();
	}

	//while (true)
	//{
	//}
	cin.get();
}