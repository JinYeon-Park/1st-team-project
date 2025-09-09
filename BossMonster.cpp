#include <iostream>
#include <string>
#include "BossMonster.h"
#include <random>
#include "HealthPotion.h"
#include "AttackBoost.h"

using namespace std;

BossMonster::BossMonster(int level)
{
	name = "BossMonster";

	art = {};

	//���� ������ �� �ڵ� chat Gpt�� ������ �޾Ƽ� �ۼ��߽��ϴ�.
	random_device rd;	 //�õ� ���� (���� �õ带 ����� ��ġ)
	mt19937 gen(rd());	 //���� �ʱ�ȭ (Mersenne Twister 19937 �˰��� ����� ���� ������)

	uniform_int_distribution<int> healthDist(level * 30, level * 45);	//���� ���� (level * 30 ~ level * 45)
	uniform_int_distribution<int> attackDist(level * 10, level * 15);	//���� ���� (level * 10 ~ level * 15)

	health = healthDist(gen);

	maxHealth = health;

	attack = attackDist(gen);
}

string BossMonster::getName() const
{
	return name;
}
int BossMonster::getHealth() const
{
	return health;
}
int BossMonster::getAttack() const
{
	return attack;
}
int BossMonster::getMaxHealth() const
{
	return maxHealth;
}
string BossMonster::getart() const
{
	return art;
}


//���� �ǰ�
void BossMonster::takeDamage(int damage)
{
	health -= damage;
	if (health < 0) health = 0;  // 0�� �Ǹ� �׾���ϴ� �������� ������ �� 0���� ����
}


//���������Լ��� ����ؼ� �ϴ� ������ �صξ����ϴ�. ��x
Item* BossMonster::dropItem() {
	return nullptr;
}

int BossMonster::getExp() const {
	return 0;
}

int BossMonster::getGold() const {
	return 0;
}