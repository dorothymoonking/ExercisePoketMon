#pragma once
class Monster
{
public:
	char m_MonName[128];
	int  m_MaxHp = 0;
	int  m_Hp;
	int  m_Gold;
	int  AttackRate;

public:
	Monster();
	Monster(const char* _Name, int _Maxhp, int m_Hp, int m_Gold, int Att);
	~Monster();

public:
	void newMonster(int _data);
	void PrintInfo();
};

