#include <iostream>
#include <string>
#include "Goblin.h"
#include <random>
#include "HealthPotion.h"
#include "AttackBoost.h"

using namespace std;

Goblin::Goblin(int level)
{
	name = "Goblin";

	exp = 50;

	art = {};


	//���� ������ �� �ڵ� chat Gpt�� ������ �޾Ƽ� �ۼ��߽��ϴ�.
	random_device rd;	 //�õ� ���� (���� �õ带 ����� ��ġ)
	mt19937 gen(rd());	 //���� �ʱ�ȭ (Mersenne Twister 19937 �˰��� ����� ���� ������)

	uniform_int_distribution<int> healthDist(level * 20, level * 30);	//���� ���� (level * 20 ~ level * 30)
	uniform_int_distribution<int> attackDist(level * 5, level * 10);	//���� ���� (level * 5 ~ level * 10)

	uniform_int_distribution<int> goldDist(1, 5);  // 1~5���
	gold = goldDist(gen);


	health = healthDist(gen);

	maxHealth = health;

	attack = attackDist(gen);
}

string Goblin::getName() const
{
	return name;
}
int Goblin::getHealth() const
{
	return health;
}
int Goblin::getAttack() const
{
	return attack;
}
int Goblin::getMaxHealth() const
{
	return maxHealth;
}
int Goblin::getExp() const
{
	return exp;
}
int Goblin::getGold() const
{
	return gold;
}

string Goblin::getart() const
{
	return art;
}


//���� �ǰ�
void Goblin::takeDamage(int damage)
{
	health -= damage;
	if (health < 0) health = 0;  // 0�� �Ǹ� �׾���ϴ� �������� ������ �� 0���� ����
}

//������ ���
Item* Goblin::dropItem() {

	random_device rd;
	mt19937 gen(rd());

	//FMath�� RandRange�� �𸮾� ���� ���̺귯���� ������� ���Ѵٰ� �ϳ׿�.. 
	uniform_int_distribution<int> dist(0, 99);  // 0~99 ���� ����

	int per = dist(gen);

	//Ȯ���� ���� ���������
	if (per < 40) {
		return new HealthPotion();  // 40% hp drop
	}
	else if (per < 60) {
		return new AttackBoost();  // 20% AB drop
	}
	else {
		return nullptr;  // 40% drop X
	}

}