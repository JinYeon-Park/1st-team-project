﻿#include "Character.h"
#include <iostream>
#include <string>

using namespace std;

Character* Character::instance = nullptr;

Character::Character(string name) :
	name(name),
	level(1),
	health(100),
	maxHealth(100),
	attack(5),
	experience(0),
	gold(0),
	killcount(0)

{
	inventory = new Inventory();
}

Character::~Character()
{
	delete inventory;
	inventory = nullptr;
}

void Character :: displayStatus() const
{
	cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
	cout << endl;
	cout << "이름 : " << name << "\n";
	cout << "Lv : " << level << "\n";
	cout << "경험치 : " << experience << "\n";
	cout << "HP : " << health << "/"<<maxHealth<< "\n";
	cout << "공격력 : " << attack;
	cout << endl;
	cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
}

void Character :: levelUp()
{
		experience -= 100;
		cout << endl;
		cout << "레벨업 했습니다!" << endl;
		++level;
		maxHealth += level * 20;
		health = maxHealth;
		cout << "체력이 모두 회복됐습니다.\n";
		attack += level * 5;
		cout << "공격력이 상승했습니다.\n";
		cout << "현재 Lv : " << level << endl;
		cout << "현재 체력 :" << health << "/" << maxHealth << endl;
		cout << "현재 공격력 :" << attack << endl;
}

int Character::getAttack()
{
	return attack;
}

void Character::setAttack(int buffAttack)
{
	attack = buffAttack;
	return ;
}

int Character::getHealth()
{
	return health;
}

void Character::setHealth(int a)
{
	health = a;
	return ;
}

int Character::getMaxHealth()
{
	return maxHealth;
}

void Character::setGold(int a)
{
	gold = a;
	return;
}

int Character::getExp()
{
	return experience;
}

void Character::setExp(int a)
{
	experience = a;
	return;
}

//void Character::addInventory(Item* item)
//{
//	inventory.push_back(item);
//}
//vector<Item*> Character::getInventory()
//{
//	return inventory;
//}
void Character::useItem(int index)
{

	return;
}

void Character::takeDamage(int a)
{
	health -= a;
	return;
}

int Character::getGold()
{
	return gold;
}

int Character::getLevel()
{
	return level;
}

string Character::getName()
{
	return name;
}

int Character :: getKillcount()
{
	return killcount;
}

void Character::setKillcount(int a)
{
	killcount = a;
	return ;
}

string Character::getart() { return art; }

