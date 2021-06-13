#include<stdio.h>
#include<iostream>
#include <cwchar>
#include <windows.h>
#include<random>
#include<vector>
#include "Hero.h"
#include "Monster.h"

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

void Save(vector<Monster>* _list)
{
	FILE* a_wFP = fopen("MySave.abc", "wb");
	if (a_wFP != NULL)
	{
		int a_StrCount = 0;		
		
		a_StrCount = strlen(g_Hero.m_Name) + 1;
		fwrite(&a_StrCount, sizeof(int), 1, a_wFP);
		if (1 < a_StrCount)
			fwrite(g_Hero.m_Name, a_StrCount, 1, a_wFP);
		fwrite(&g_Hero.m_MaxHp, sizeof(int), 1, a_wFP);
		fwrite(&g_Hero.m_Hp, sizeof(int), 1, a_wFP);
		fwrite(&g_Hero.AttackRate, sizeof(int), 1, a_wFP);
		fwrite(&g_Hero.m_Gold, sizeof(int), 1, a_wFP);

		int MonsterCount = _list->size();
		fwrite(&MonsterCount, sizeof(int), 1, a_wFP);

		if (0 < MonsterCount)
		{
			
			for (int ii = 0; ii < MonsterCount; ii++)
			{
				a_StrCount = strlen((*_list)[ii].m_MonName) + 1;
				fwrite(&a_StrCount, sizeof(int), 1, a_wFP);
				if (1 < a_StrCount)
					fwrite((*_list)[ii].m_MonName, a_StrCount, 1, a_wFP);

				fwrite(&(*_list)[ii].m_MaxHp, sizeof(int), 1, a_wFP);
				fwrite(&(*_list)[ii].m_Hp, sizeof(int), 1, a_wFP);
				fwrite(&(*_list)[ii].AttackRate, sizeof(int), 1, a_wFP);
				fwrite(&(*_list)[ii].m_Gold, sizeof(int), 1, a_wFP);

			}//for (int ii = 0; ii < StCount; ii++)
		}//if (0 < StCount)

		fclose(a_wFP);
	}//if (a_wFP != NULL)
}

bool Load(vector<Monster>* _list)
{
	bool LoadSuccese = false;

	FILE* a_rFP = fopen("MySave.abc", "rb");
	if (a_rFP != NULL)
	{
		char a_Name[120];
		int a_MaxHp;
		int a_Hp;
		int a_Gold;
		int a_Attck;
		int a_strCount = 0;

		fread(&a_strCount, sizeof(int), 1, a_rFP);
		if (1 < a_strCount)
			fread(a_Name, a_strCount, 1, a_rFP);
		fread(&a_MaxHp, sizeof(int), 1, a_rFP);
		fread(&a_Hp, sizeof(int), 1, a_rFP);
		fread(&a_Attck, sizeof(int), 1, a_rFP);
		fread(&a_Gold, sizeof(int), 1, a_rFP);

		g_Hero.LoadHero(a_Name, a_MaxHp, a_Hp, a_Gold, a_Attck);

		int MonsterCount = 0;
		fread(&MonsterCount, sizeof(int), 1, a_rFP);
		if (0 < MonsterCount)
		{
			for (int ii = 0; ii < MonsterCount; ii++)
			{
				fread(&a_strCount, sizeof(int), 1, a_rFP);
				if (1 < a_strCount)
					fread(a_Name, a_strCount, 1, a_rFP);

				fread(&a_MaxHp, sizeof(int), 1, a_rFP);
				fread(&a_Hp, sizeof(int), 1, a_rFP);
				fread(&a_Attck, sizeof(int), 1, a_rFP);
				fread(&a_Gold, sizeof(int), 1, a_rFP);

				Monster a_RdNode(a_Name, a_MaxHp, a_Hp, a_Gold, a_Attck);
				_list->push_back(a_RdNode);
			}
		}//if (0 < StCount)
		LoadSuccese = true;
		fclose(a_rFP);
	}//if (a_rFP != NULL)
	else
	{
		LoadSuccese = false;
	}

	return LoadSuccese;
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


void LoadUI()
{
	int _Num = 0;
	system("cls");
	while (true) 
	{
		if (_Num == 0)
		{
			gotoxy(12, 0);
			cout << "    ■■■             ■■■" << endl;
			gotoxy(12, 1);
			cout << "  ■■■■■         ■■■■■" << endl;
			gotoxy(12, 2);
			cout << "■■■■■■■     ■■■■■■■" << endl;
			gotoxy(12, 3);
			cout << "■■■■■■■     ■■■■■■■" << endl;
			gotoxy(12, 4);
			cout << "  ■■■■■         ■■■■■" << endl;
			gotoxy(12, 5);
			cout << "    ■■■             ■■■" << endl;
		}
		else if (_Num == 1)
		{
			gotoxy(12, 0);
			cout << "    ■■■             ■■■" << endl;
			gotoxy(12, 1);
			cout << "  ■■■■■         ■■■■■" << endl;
			gotoxy(12, 2);
			cout << "■■■■■■■     ■■■■■■■" << endl;
			gotoxy(12, 3);
			cout << "■■■■■■■     ■■■■■■■" << endl;
			gotoxy(12, 4);
			cout << "  ■■■■■         ■■■■■" << endl;
			gotoxy(12, 5);
			cout << "    □□□             □□□" << endl;
		}
		else if (_Num == 2)
		{
			gotoxy(12, 0);
			cout << "    ■■■             ■■■" << endl;
			gotoxy(12, 1);
			cout << "  ■■■■■         ■■■■■" << endl;
			gotoxy(12, 2);
			cout << "■■■■■■■     ■■■■■■■" << endl;
			gotoxy(12, 3);
			cout << "■■■■■■■     ■■■■■■■" << endl;
			gotoxy(12, 4);
			cout << "  □■■■□         □■■■□" << endl;
			gotoxy(12, 5);
			cout << "    □□□             □□□" << endl;
		}
		else if (_Num == 3)
		{
			gotoxy(12, 0);
			cout << "    ■■■             ■■■" << endl;
			gotoxy(12, 1);
			cout << "  ■■■■■         ■■■■■" << endl;
			gotoxy(12, 2);
			cout << "■■■■■■■     ■■■■■■■" << endl;
			gotoxy(12, 3);
			cout << "□□■□■□□     □□■□■□□" << endl;
			gotoxy(12, 4);
			cout << "  □■■■□         □■■■□" << endl;
			gotoxy(12, 5);
			cout << "    □□□             □□□" << endl;
		}
		else if (_Num == 4)
		{
			gotoxy(12, 0);
			cout << "    ■■■             ■■■" << endl;
			gotoxy(12, 1);
			cout << "  ■■■■■         ■■■■■" << endl;
			gotoxy(12, 2);
			cout << "□□■□■□□     □□■□■□□" << endl;
			gotoxy(12, 3);
			cout << "□□■□■□□     □□■□■□□" << endl;
			gotoxy(12, 4);
			cout << "  □■■■□         □■■■□" << endl;
			gotoxy(12, 5);
			cout << "    □□□             □□□" << endl;
		}
		else if (_Num == 5)
		{
			gotoxy(12, 0);
			cout << "    ■■■             ■■■" << endl;
			gotoxy(12, 1);
			cout << "  □■■■□         □■■■□" << endl;
			gotoxy(12, 2);
			cout << "□□■□■□□     □□■□■□□" << endl;
			gotoxy(12, 3);
			cout << "□□■□■□□     □□■□■□□" << endl;
			gotoxy(12, 4);
			cout << "  □■■■□         □■■■□" << endl;
			gotoxy(12, 5);
			cout << "    □□□             □□□" << endl;
		}
		else if (_Num == 6)
		{
			gotoxy(12, 0);
			cout << "    □□□             □□□" << endl;
			gotoxy(12, 1);
			cout << "  □■■■□         □■■■□" << endl;
			gotoxy(12, 2);
			cout << "□□■□■□□     □□■□■□□" << endl;
			gotoxy(12, 3);
			cout << "□□■□■□□     □□■□■□□" << endl;
			gotoxy(12, 4);
			cout << "  □■■■□         □■■■□" << endl;
			gotoxy(12, 5);
			cout << "    □□□             □□□" << endl;
		}
		gotoxy(22, 9);
		cout << "<로딩중...>";
		_Num++;
		Sleep(500);
		if (_Num == 7)
			break;
	}
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

bool Die(Monster* _Mon, vector<Monster>* _list)
{
	bool DieCheck = false;
	if (_Mon->m_Hp <= 0)
	{
		g_Hero.m_Gold += _Mon->m_Gold;
		cout << endl << "<몬스터 처치!>" << endl;
		cout << _Mon->m_Gold << " 골드를 획득하셨습니다";
		_list->push_back(*_Mon);
		return true;
	}

	return DieCheck;
}

bool Die()
{
	bool DieCheck = false;
	if (g_Hero.m_Hp <= 0)
	{
		cout << endl << "<유저 사망!>" << endl;
		return true;
	}

	return DieCheck;
}

int RandMonSpawn()
{
	int Spawn = rand() % 100;
	if (Spawn < 40 && 0 <= Spawn)
		Spawn = 0;

	else if (Spawn < 65 && 40 <= Spawn)
		Spawn = 1;

	else if(Spawn < 80 && 65 <= Spawn)
		Spawn = 2;

	else if(Spawn < 95 && 85 <= Spawn)
		Spawn = 3;

	else if(Spawn < 100 && 95 <= Spawn)
		Spawn = 4;

	return Spawn;
}

//-----필드 정찰 및 전투구현
void Fight(vector<Monster>* _list)
{
	PrintEyes();

	gotoxy(18, 9);
	cout << "전투(1) 도망(2) : ";
	int FightMenuSell = 0;
	cin >> FightMenuSell;
	cin.get();

	if (FightMenuSell == 2)
	{
		int Ran = rand() % 2;
		if (Ran == 1)
		{
			cout << "도망 성공!";
			return;
		}
		else
		{
			cout << "도망 실패! 전투시작!";
		}
	}
	int MonRan = RandMonSpawn();
	Monster a_Monster;
	a_Monster.newMonster(MonRan);

	system("cls");
	
	bool AttactTurn = false;
	int gotoY = 0;
	while (true)
	{
		if (AttactTurn == false)
		{
			a_Monster.m_Hp -= g_Hero.AttackRate;
			if (a_Monster.m_Hp <= 0)
				a_Monster.m_Hp = 0;
			gotoxy(5, gotoY);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			cout << "<" << a_Monster.m_MonName << ">은 " << g_Hero.AttackRate << "만큼의 피해를 입었다.";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			AttactTurn = !AttactTurn;
			if (Die(&a_Monster, _list) == true)
			{
				break;
			}
			else
				Sleep(1000);
		}
		else
		{
			g_Hero.m_Hp -= a_Monster.AttackRate;
			if (g_Hero.m_Hp <= 0)
				g_Hero.m_Hp = 0;
			gotoxy(20, gotoY);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "<" << g_Hero.m_Name << ">은 " << a_Monster.AttackRate << "만큼의 피해를 입었다.";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			AttactTurn = !AttactTurn;
			if (Die() == true)
			{
				break;
			}
			else
				Sleep(1000);
		}
		gotoY++;
	}
}

void Field(vector<Monster>* _list)
{
	if (g_Hero.m_Hp <= 10)
	{
		cout << "체력이 없습니다.";
		cout << endl << "Enter를 누르면 다음 화면으로..." << endl;
		return;
	}

	bool FightOnOff = false;
	bool GoldAcheive = false;
	system("cls");
	for (int i = 0; i < 10; i++)
	{
		if (3 < i)
		{
			int Ran = rand() % 10;

			if (Ran == 9)
			{
				g_Hero.m_Gold += 50;
				GoldAcheive = true;
			}

			else if (4 < Ran && Ran < 8)
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
		Fight(_list);
	}
	else
	{
		cout << endl << endl << "몬스터를 발견하지 못했습니다...";
		cout << endl << endl << "체력이 10 감소했습니다...";
		g_Hero.m_Hp -= 10;
		if (g_Hero.m_Hp <= 0)
			g_Hero.m_Hp = 0;
		cout << endl << "Enter를 누르면 다음 화면으로..." << endl;
	}
}
//-----

void MyInfo(vector<Monster>* _list)
{
	system("cls");
	TitleUI();
	cout << endl;
	g_Hero.PrintInfo();
	cout << endl << "<몬스터 토벌 목록>" << endl;
	for (int ii = 0; ii < _list->size(); ii++)
	{
		cout << ii + 1 << "번 : ";
		(*_list)[ii].PrintInfo();
	}
}

void Shop()
{
	system("cls");
	TitleUI();
	cout << endl;
	while (true)
	{
		cout << "회복(1) 강화(2) 나가기(3): ";
		int ShopMenuSell = -1;
		cin >> ShopMenuSell;
		cin.get();

		if (ShopMenuSell <= 0 || 2 <ShopMenuSell)
		{
			if (ShopMenuSell == 3)
			{
				cout << "<상점을 나갑니다!>" << endl;
				break;
			}
			continue;
		}

		if (ShopMenuSell == 1)
		{
			if (g_Hero.m_Hp == g_Hero.m_MaxHp)
			{
				cout << "이미 체력이 Max값 입니다." << endl;
				break;
			}

			if (g_Hero.m_Gold < 20)
			{
				cout << "<보유골드가 부족합니다!>" << endl;
				break;
			}
			else
			{
				g_Hero.m_Gold -= 20;
				g_Hero.m_Hp = g_Hero.m_MaxHp;
				cout << "<회복되었습니다!>" << endl;
				break;
			}
		}//if (ShopMenuSell == 1)

		else if (ShopMenuSell == 2)
		{
			if (g_Hero.m_Hp <= 10)
			{
				cout << "체력부터 회복해주세요!>" << endl;
				break;
			}

			while (true) 
			{
				system("cls");
				TitleUI();
				gotoxy(20, 4);
				cout << "<강화 페이지!>";
				gotoxy(20, 6);
				cout << "<유저 골드 : " << g_Hero.m_Gold << ">" << endl;
				int UpgradeMenuSell = -1;

				gotoxy(10, 7);
				cout << "HP강화(1) 공격력강화(2) 나가기(3) : ";
				cin >> UpgradeMenuSell;
				cin.get();

				if (UpgradeMenuSell <= 0 || 2 < UpgradeMenuSell)
				{
					if (UpgradeMenuSell == 3)
					{
						cout << endl << "<상점을 나갑니다!>" << endl;
						break; 
					}
					continue;
				}
				int Successrate = rand() % 10;

				if (g_Hero.m_Gold < 50)
				{
					cout << endl << "<보유골드가 부족합니다!>" << endl;
					break;
				}

				if (UpgradeMenuSell == 1)
				{
					if (Successrate < 5)
					{
						gotoxy(15, 9);
						cout << "<강화 성공!> 체력 + 20" << endl;
						g_Hero.m_Gold -= 50;
						g_Hero.SetHP(20);
						g_Hero.PrintInfo();
						cin.get();
						continue;
					}
					else
					{
						gotoxy(20, 9);
						cout << "<강화 실패!>" << endl;
						g_Hero.m_Gold -= 50;
						cin.get();
						continue;
					}
				}//if(UpgradeMenuSell == 1)

				else if (UpgradeMenuSell == 2)
				{
					if (Successrate < 5)
					{
						gotoxy(15, 9);
						cout << "<강화 성공!> 공격력 + 10" << endl;
						g_Hero.m_Gold -= 50;
						g_Hero.SetAttack(10);
						g_Hero.PrintInfo();
						cin.get();
						continue;
					}
					else
					{
						gotoxy(20, 9);
						cout << "<강화 실패!>" << endl;
						g_Hero.m_Gold -= 50;
						cin.get();
						continue;
					}
				}//else if (UpgradeMenuSell == 2)
			}//while (true) 

			break;
		}//else if (ShopMenuSell == 2)

	}//while (true)
	
}

void main()
{
	srand((unsigned)time(NULL));

	system("mode con cols=60 lines=30");

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 18;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	vector<Monster> m_MonList;
	while (true)
	{
		TitleUI();
		int m_TitleMenuNum = TitleMenuUI();
		if (m_TitleMenuNum == 1)
		{
			NewHeroMake(&g_Hero);
			Save(&m_MonList);
			system("cls");
			g_Hero.PrintInfo();
			break;
		}
		else
		{
			if (Load(&m_MonList) == false)
			{
				cout << endl <<"로드할 데이터가 없습니다!";
				cin.get();
				system("cls");
				continue;
			}
			LoadUI();
			break;
		}
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
			Field(&m_MonList);
			Save(&m_MonList);
		}

		else if (m_MainMenuSell == 2)
		{
			MyInfo(&m_MonList);
			cout << endl << "Enter를 누르면 다음 화면으로..." << endl;
		}

		else if (m_MainMenuSell == 3)
		{
			Shop();
			Save(&m_MonList);
			cout << endl << "Enter를 누르면 다음 화면으로..." << endl;
		}

		else if (m_MainMenuSell == 4)
		{
			Save(&m_MonList);
			cout << endl <<  "저장 되었습니다!";
		}
			
		cin.get();
	}

	m_MonList.clear();
	cin.get();
}