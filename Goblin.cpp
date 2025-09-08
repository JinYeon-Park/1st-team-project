#include <iostream>
#include <string>
#include <random>
#include "Goblin.h"

using namespace std;

Goblin::Goblin(int level)
{
	name = "Goblin";

	//���� ������ �� �ڵ� chat Gpt�� ������ �޾Ƽ� �ۼ��߽��ϴ�.
	random_device rd;	 //�õ� ���� (���� �õ带 ����� ��ġ)
	mt19937 gen(rd());	 //���� �ʱ�ȭ (Mersenne Twister 19937 �˰��� ����� ���� ������)

	uniform_int_distribution<int> healthDist(level * 20, level * 30);	//���� ���� (level * 20 ~ level * 30)
	uniform_int_distribution<int> attackDist(level * 5, level * 10);	//���� ���� (level * 5 ~ level * 10)

	health = healthDist(gen);
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


//���� �ǰ�
void Goblin::takeDamage(int damage)
{
	health -= damage;
	if (health < 0) health = 0;  // 0�� �Ǹ� �׾���ϴ� �������� ������ �� 0���� ����
}

//������ ���
DropItem* Goblin::dropItem()
{
	return new DropItem("sword");
}