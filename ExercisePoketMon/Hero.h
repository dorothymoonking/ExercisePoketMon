#pragma once
class Hero
{
public:
	char m_Name[128];
	int  m_MaxHp;
	int  m_Hp;
	int AttackRate;
	int m_Gold = 0;

public:
	Hero();
	~Hero();

public:
	void NewHero(char _Name[128]);
	void PrintInfo();
	void SetHP(int _hp);
	void SetAttack(int _att);
	void LoadHero(const char* _Name, int _MaxHp, int _hp, int _Gold, int _Att);

};

