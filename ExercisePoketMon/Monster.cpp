#include "Monster.h"
#include<iostream>

#pragma warning(disable:4996)

Monster::Monster()
{
	m_MonName[0] = '\0';
	m_MaxHp = 0;
	m_Hp = 0;
	m_Gold = 0;
	AttackRate = 0;
	m_MonHint = "";
	m_moveStr = 0;
}

Monster::Monster(const char* _Name, int _Maxhp, int _Hp, int _Gold, int Att)
{
	strcpy(m_MonName, _Name);
	m_MaxHp = _Maxhp;
	m_Hp = _Hp;
	m_Gold = _Gold;
	AttackRate = Att;
	m_MonHint = "";
	m_moveStr = 0;
}

Monster::~Monster()
{
}

void Monster::newMonster(int _data)
{
	if (_data == 0)
	{
		strcpy(m_MonName, "쿠쿠르야크");
		m_MaxHp = 50;
		m_Hp = m_MaxHp;
		m_Gold = 50;
		AttackRate = 10;
		m_MonHint = "소조의 울음 소리가 들린다.";
		m_moveStr = 15;
	}

	else if (_data == 1)
	{
		strcpy(m_MonName, "도스쟈그라스");
		m_MaxHp = 80;
		m_Hp = m_MaxHp;
		m_Gold = 100;
		AttackRate = 20;
		m_MonHint = "그는 자그라스의 왕이라고 불리는...";
		m_moveStr = 12;
	}
	else if (_data == 2)
	{
		strcpy(m_MonName, "안쟈나프");
		m_MaxHp = 100;
		m_Hp = m_MaxHp;
		m_Gold = 150;
		AttackRate = 30;
		m_MonHint = "불을 내뿜는 수룡의 모습이 보인다...";
		m_moveStr = 12;
	}

	else if (_data == 3)
	{
		strcpy(m_MonName, "리오레우스");
		m_MaxHp = 150;
		m_Hp = m_MaxHp;
		m_Gold = 200;
		AttackRate = 40;
		m_MonHint = "불을 내뿜는 커다란 왕의 그림자가 보인다.";
		m_moveStr = 9;
	}

	else if (_data == 4)
	{
		strcpy(m_MonName, "네르기간테");
		m_MaxHp = 250;
		m_Hp = m_MaxHp;
		m_Gold = 250;
		AttackRate = 50;
		m_MonHint = "고룡을 먹는자...그 몬스터의 이름...";
		m_moveStr = 12;
	}
}

void Monster::PrintInfo()
{
	cout << "몬스터 이름(" << m_MonName << ") " <<"체력(" << m_MaxHp << ") " << "공격력(" << AttackRate << ")" << endl;
}
