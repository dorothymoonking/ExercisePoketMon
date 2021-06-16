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
		strcpy(m_MonName, "������ũ");
		m_MaxHp = 50;
		m_Hp = m_MaxHp;
		m_Gold = 50;
		AttackRate = 10;
		m_MonHint = "������ ���� �Ҹ��� �鸰��.";
		m_moveStr = 15;
	}

	else if (_data == 1)
	{
		strcpy(m_MonName, "������׶�");
		m_MaxHp = 80;
		m_Hp = m_MaxHp;
		m_Gold = 100;
		AttackRate = 20;
		m_MonHint = "�״� �ڱ׶��� ���̶�� �Ҹ���...";
		m_moveStr = 12;
	}
	else if (_data == 2)
	{
		strcpy(m_MonName, "������");
		m_MaxHp = 100;
		m_Hp = m_MaxHp;
		m_Gold = 150;
		AttackRate = 30;
		m_MonHint = "���� ���մ� ������ ����� ���δ�...";
		m_moveStr = 12;
	}

	else if (_data == 3)
	{
		strcpy(m_MonName, "�������콺");
		m_MaxHp = 150;
		m_Hp = m_MaxHp;
		m_Gold = 200;
		AttackRate = 40;
		m_MonHint = "���� ���մ� Ŀ�ٶ� ���� �׸��ڰ� ���δ�.";
		m_moveStr = 9;
	}

	else if (_data == 4)
	{
		strcpy(m_MonName, "�׸��Ⱓ��");
		m_MaxHp = 250;
		m_Hp = m_MaxHp;
		m_Gold = 250;
		AttackRate = 50;
		m_MonHint = "����� �Դ���...�� ������ �̸�...";
		m_moveStr = 12;
	}
}

void Monster::PrintInfo()
{
	cout << "���� �̸�(" << m_MonName << ") " <<"ü��(" << m_MaxHp << ") " << "���ݷ�(" << AttackRate << ")" << endl;
}
