#include "Character.h"
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
{}

void Character :: displayStatus() const
{
	cout << "������������������������������������������������������������������";
	cout << endl;
	cout << "�̸� : " << name << "\n";
	cout << "Lv : " << level << "\n";
	cout << "����ġ : " << experience << "\n";
	cout << "HP : " << health << "/"<<maxHealth<< "\n";
	cout << "���ݷ� : " << attack;
	cout << endl;
	cout << "������������������������������������������������������������������";
}

void Character :: levelUp()
{
		experience -= 100;
		cout << endl;
		cout << "������ �߽��ϴ�!" << endl;
		++level;
		maxHealth += level * 20;
		health = maxHealth;
		cout << "ü���� ��� ȸ���ƽ��ϴ�.\n";
		attack += level * 5;
		cout << "���ݷ��� ����߽��ϴ�.\n";
		cout << "���� Lv : " << level << endl;
		cout << "���� ü�� :" << health << "/" << maxHealth << endl;
		cout << "���� ���ݷ� :" << attack << endl;
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

void Character::addInventory(Item* item)
{
	inventory.push_back(item);
}
vector<Item*> Character::getInventory()
{
	return inventory;
}
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