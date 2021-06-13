#include "Hero.h"
#include<iostream>
#include<string.h>

#pragma warning(disable:4996)
using namespace std;

Hero::Hero()
{
	m_Name[0] = '\0';
	m_MaxHp = 100;
	m_Hp = m_MaxHp;
	AttackRate = 20;
	m_Gold = 0;
}

Hero::~Hero()
{
}

void Hero::NewHero(char _Name[128])
{
	strcpy(m_Name, _Name);
	m_Hp = 100;
	AttackRate = 20;
}

void Hero::PrintInfo()
{
	cout << "이름 : " << m_Name << endl;
	cout << "체력 : " << m_Hp << "/" << m_MaxHp << endl;
	cout << "골드 : " << m_Gold << endl;
}

void Hero::SetAttack(int _att)
{
	AttackRate += _att;
}

void Hero::SetHP(int _hp)
{
	m_MaxHp += _hp;
}

void Hero::LoadHero(const char* _Name, int _MaxHp, int _hp, int _Gold, int _Att)
{
	strcpy(m_Name, _Name);
	m_MaxHp = _MaxHp;
	m_Hp = _hp;
	m_Gold = _Gold;
	AttackRate = _Att;
}