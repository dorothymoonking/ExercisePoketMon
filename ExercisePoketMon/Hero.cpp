#include "Hero.h"
#include<iostream>
#include<string.h>

#pragma warning(disable:4996)
using namespace std;

Hero::Hero()
{
	m_Name[0] = '\0';
	m_Hp = 100;
	m_Gold = 0;
}

Hero::~Hero()
{
}

void Hero::NewHero(char _Name[128])
{
	strcpy(m_Name, _Name);
	m_Hp = 100;
	m_Gold = 0;
}

void Hero::PrintInfo()
{
	cout << "�̸� : " << m_Name << endl;
	cout << "ü�� : " << m_Hp << endl;
	cout << "��� : " << m_Gold << endl;
}
