#pragma once
class Hero
{
public:
	char m_Name[128];
	int  m_Hp;
	int  m_Gold;

public:
	Hero();
	~Hero();

public:
	void NewHero(char _Name[128]);
	void PrintInfo();
};

