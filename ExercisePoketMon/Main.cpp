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


void LoadUI()
{
	int _Num = 0;
	system("cls");
	while (true) 
	{
		if (_Num == 0)
		{
			gotoxy(12, 0);
			cout << "    ����             ����" << endl;
			gotoxy(12, 1);
			cout << "  ������         ������" << endl;
			gotoxy(12, 2);
			cout << "��������     ��������" << endl;
			gotoxy(12, 3);
			cout << "��������     ��������" << endl;
			gotoxy(12, 4);
			cout << "  ������         ������" << endl;
			gotoxy(12, 5);
			cout << "    ����             ����" << endl;
		}
		else if (_Num == 1)
		{
			gotoxy(12, 0);
			cout << "    ����             ����" << endl;
			gotoxy(12, 1);
			cout << "  ������         ������" << endl;
			gotoxy(12, 2);
			cout << "��������     ��������" << endl;
			gotoxy(12, 3);
			cout << "��������     ��������" << endl;
			gotoxy(12, 4);
			cout << "  ������         ������" << endl;
			gotoxy(12, 5);
			cout << "    ����             ����" << endl;
		}
		else if (_Num == 2)
		{
			gotoxy(12, 0);
			cout << "    ����             ����" << endl;
			gotoxy(12, 1);
			cout << "  ������         ������" << endl;
			gotoxy(12, 2);
			cout << "��������     ��������" << endl;
			gotoxy(12, 3);
			cout << "��������     ��������" << endl;
			gotoxy(12, 4);
			cout << "  ������         ������" << endl;
			gotoxy(12, 5);
			cout << "    ����             ����" << endl;
		}
		else if (_Num == 3)
		{
			gotoxy(12, 0);
			cout << "    ����             ����" << endl;
			gotoxy(12, 1);
			cout << "  ������         ������" << endl;
			gotoxy(12, 2);
			cout << "��������     ��������" << endl;
			gotoxy(12, 3);
			cout << "��������     ��������" << endl;
			gotoxy(12, 4);
			cout << "  ������         ������" << endl;
			gotoxy(12, 5);
			cout << "    ����             ����" << endl;
		}
		else if (_Num == 4)
		{
			gotoxy(12, 0);
			cout << "    ����             ����" << endl;
			gotoxy(12, 1);
			cout << "  ������         ������" << endl;
			gotoxy(12, 2);
			cout << "��������     ��������" << endl;
			gotoxy(12, 3);
			cout << "��������     ��������" << endl;
			gotoxy(12, 4);
			cout << "  ������         ������" << endl;
			gotoxy(12, 5);
			cout << "    ����             ����" << endl;
		}
		else if (_Num == 5)
		{
			gotoxy(12, 0);
			cout << "    ����             ����" << endl;
			gotoxy(12, 1);
			cout << "  ������         ������" << endl;
			gotoxy(12, 2);
			cout << "��������     ��������" << endl;
			gotoxy(12, 3);
			cout << "��������     ��������" << endl;
			gotoxy(12, 4);
			cout << "  ������         ������" << endl;
			gotoxy(12, 5);
			cout << "    ����             ����" << endl;
		}
		else if (_Num == 6)
		{
			gotoxy(12, 0);
			cout << "    ����             ����" << endl;
			gotoxy(12, 1);
			cout << "  ������         ������" << endl;
			gotoxy(12, 2);
			cout << "��������     ��������" << endl;
			gotoxy(12, 3);
			cout << "��������     ��������" << endl;
			gotoxy(12, 4);
			cout << "  ������         ������" << endl;
			gotoxy(12, 5);
			cout << "    ����             ����" << endl;
		}
		gotoxy(22, 9);
		cout << "<�ε���...>";
		_Num++;
		Sleep(500);
		if (_Num == 7)
			break;
	}
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

bool Die(Monster* _Mon, vector<Monster>* _list)
{
	bool DieCheck = false;
	if (_Mon->m_Hp <= 0)
	{
		g_Hero.m_Gold += _Mon->m_Gold;
		cout << endl << "<���� óġ!>" << endl;
		cout << _Mon->m_Gold << " ��带 ȹ���ϼ̽��ϴ�";
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
		cout << endl << "<���� ���!>" << endl;
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

//-----�ʵ� ���� �� ��������
void Fight(vector<Monster>* _list)
{
	PrintEyes();

	gotoxy(18, 9);
	cout << "����(1) ����(2) : ";
	int FightMenuSell = 0;
	cin >> FightMenuSell;
	cin.get();

	if (FightMenuSell == 2)
	{
		int Ran = rand() % 2;
		if (Ran == 1)
		{
			cout << "���� ����!";
			return;
		}
		else
		{
			cout << "���� ����! ��������!";
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
			cout << "<" << a_Monster.m_MonName << ">�� " << g_Hero.AttackRate << "��ŭ�� ���ظ� �Ծ���.";
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
			cout << "<" << g_Hero.m_Name << ">�� " << a_Monster.AttackRate << "��ŭ�� ���ظ� �Ծ���.";
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
		cout << "ü���� �����ϴ�.";
		cout << endl << "Enter�� ������ ���� ȭ������..." << endl;
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
		Fight(_list);
	}
	else
	{
		cout << endl << endl << "���͸� �߰����� ���߽��ϴ�...";
		cout << endl << endl << "ü���� 10 �����߽��ϴ�...";
		g_Hero.m_Hp -= 10;
		if (g_Hero.m_Hp <= 0)
			g_Hero.m_Hp = 0;
		cout << endl << "Enter�� ������ ���� ȭ������..." << endl;
	}
}
//-----

void MyInfo(vector<Monster>* _list)
{
	system("cls");
	TitleUI();
	cout << endl;
	g_Hero.PrintInfo();
	cout << endl << "<���� ��� ���>" << endl;
	for (int ii = 0; ii < _list->size(); ii++)
	{
		cout << ii + 1 << "�� : ";
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
		cout << "ȸ��(1) ��ȭ(2) ������(3): ";
		int ShopMenuSell = -1;
		cin >> ShopMenuSell;
		cin.get();

		if (ShopMenuSell <= 0 || 2 <ShopMenuSell)
		{
			if (ShopMenuSell == 3)
			{
				cout << "<������ �����ϴ�!>" << endl;
				break;
			}
			continue;
		}

		if (ShopMenuSell == 1)
		{
			if (g_Hero.m_Hp == g_Hero.m_MaxHp)
			{
				cout << "�̹� ü���� Max�� �Դϴ�." << endl;
				break;
			}

			if (g_Hero.m_Gold < 20)
			{
				cout << "<������尡 �����մϴ�!>" << endl;
				break;
			}
			else
			{
				g_Hero.m_Gold -= 20;
				g_Hero.m_Hp = g_Hero.m_MaxHp;
				cout << "<ȸ���Ǿ����ϴ�!>" << endl;
				break;
			}
		}//if (ShopMenuSell == 1)

		else if (ShopMenuSell == 2)
		{
			if (g_Hero.m_Hp <= 10)
			{
				cout << "ü�º��� ȸ�����ּ���!>" << endl;
				break;
			}

			while (true) 
			{
				system("cls");
				TitleUI();
				gotoxy(20, 4);
				cout << "<��ȭ ������!>";
				gotoxy(20, 6);
				cout << "<���� ��� : " << g_Hero.m_Gold << ">" << endl;
				int UpgradeMenuSell = -1;

				gotoxy(10, 7);
				cout << "HP��ȭ(1) ���ݷ°�ȭ(2) ������(3) : ";
				cin >> UpgradeMenuSell;
				cin.get();

				if (UpgradeMenuSell <= 0 || 2 < UpgradeMenuSell)
				{
					if (UpgradeMenuSell == 3)
					{
						cout << endl << "<������ �����ϴ�!>" << endl;
						break; 
					}
					continue;
				}
				int Successrate = rand() % 10;

				if (g_Hero.m_Gold < 50)
				{
					cout << endl << "<������尡 �����մϴ�!>" << endl;
					break;
				}

				if (UpgradeMenuSell == 1)
				{
					if (Successrate < 5)
					{
						gotoxy(15, 9);
						cout << "<��ȭ ����!> ü�� + 20" << endl;
						g_Hero.m_Gold -= 50;
						g_Hero.SetHP(20);
						g_Hero.PrintInfo();
						cin.get();
						continue;
					}
					else
					{
						gotoxy(20, 9);
						cout << "<��ȭ ����!>" << endl;
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
						cout << "<��ȭ ����!> ���ݷ� + 10" << endl;
						g_Hero.m_Gold -= 50;
						g_Hero.SetAttack(10);
						g_Hero.PrintInfo();
						cin.get();
						continue;
					}
					else
					{
						gotoxy(20, 9);
						cout << "<��ȭ ����!>" << endl;
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
				cout << endl <<"�ε��� �����Ͱ� �����ϴ�!";
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
			Field(&m_MonList);
			Save(&m_MonList);
		}

		else if (m_MainMenuSell == 2)
		{
			MyInfo(&m_MonList);
			cout << endl << "Enter�� ������ ���� ȭ������..." << endl;
		}

		else if (m_MainMenuSell == 3)
		{
			Shop();
			Save(&m_MonList);
			cout << endl << "Enter�� ������ ���� ȭ������..." << endl;
		}

		else if (m_MainMenuSell == 4)
		{
			Save(&m_MonList);
			cout << endl <<  "���� �Ǿ����ϴ�!";
		}
			
		cin.get();
	}

	m_MonList.clear();
	cin.get();
}