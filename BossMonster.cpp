#include <iostream>
#include <string>
#include "BossMonster.h"
#include <random>

using namespace std;

BossMonster::BossMonster(int level)
{
	name = "BossMonster";

	//���� ������ �� �ڵ� chat Gpt�� ������ �޾Ƽ� �ۼ��߽��ϴ�.
	random_device rd;	 //�õ� ���� (���� �õ带 ����� ��ġ)
	mt19937 gen(rd());	 //���� �ʱ�ȭ (Mersenne Twister 19937 �˰��� ����� ���� ������)

	uniform_int_distribution<int> healthDist(level * 30, level * 45);	//���� ���� (level * 30 ~ level * 45)
	uniform_int_distribution<int> attackDist(level * 10, level * 15);	//���� ���� (level * 10 ~ level * 15)

	health = healthDist(gen);
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


//���� �ǰ�
void BossMonster::takeDamage(int damage)
{
	health -= damage;
	if (health < 0) health = 0;  // 0�� �Ǹ� �׾���ϴ� �������� ������ �� 0���� ����
}

//������ ��� + ����ġ �߰� + ��� ��� �߰�
DropAll* BossMonster::dropAll() {
	int exp = 100; // ����ġ�� ���������� �־����ϴ�.



	//���� ü��,���ݷ� ������ ���� ������� �������� ����ϰ� �߽��ϴ�.
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<int> goldDist(10, 15);  // 10~15���
	int gold = goldDist(gen);



	//FMath�� RandRange�� �𸮾� ���� ���̺귯���� ������� ���Ѵٰ� �ϳ׿�.. 
	uniform_int_distribution<int> chance(0, 1);
	DropItem* dropItem = nullptr;
	if (chance(gen) == 1) {
		dropItem = new DropItem("HealthPotion");
	}

	return new DropAll(dropItem, gold, exp);
}