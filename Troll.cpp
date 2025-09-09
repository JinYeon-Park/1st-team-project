#include <iostream>
#include <string>
#include "Troll.h"
#include <random>

using namespace std;

Troll::Troll(int level)
{
	name = "Troll";

	exp = 50;

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

string Troll::getName() const
{
	return name;
}
int Troll::getHealth() const
{
	return health;
}
int Troll::getAttack() const
{
	return attack;
}
int Troll::getMaxHealth() const
{
	return maxHealth;
}
int Troll::getExp() const
{
	return exp;
}
int Troll::getGold() const
{
	return gold;
}


//���� �ǰ�
void Troll::takeDamage(int damage)
{
	health -= damage;
	if (health < 0) health = 0;  // 0�� �Ǹ� �׾���ϴ� �������� ������ �� 0���� ����
}

//������ ���
Item* Troll::dropItem() {

	random_device rd;
	mt19937 gen(rd());

	//FMath�� RandRange�� �𸮾� ���� ���̺귯���� ������� ���Ѵٰ� �ϳ׿�.. 
	uniform_int_distribution<int> chance(0, 1);

	//50%Ȯ���� ���
	if (chance(gen) == 1) {
		return new Item("HealthPotion");
	}

	//�������
	return nullptr;
}