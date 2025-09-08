#include <iostream>
#include <string>
#include "Orc.h"
#include <random>

using namespace std;

Orc::Orc(int level)
{
	name = "Orc";

	//���� ������ �� �ڵ� chat Gpt�� ������ �޾Ƽ� �ۼ��߽��ϴ�.
	random_device rd;	 //�õ� ���� (���� �õ带 ����� ��ġ)
	mt19937 gen(rd());	 //���� �ʱ�ȭ (Mersenne Twister 19937 �˰��� ����� ���� ������)

	uniform_int_distribution<int> healthDist(level * 20, level * 30);	//���� ���� (level * 20 ~ level * 30)
	uniform_int_distribution<int> attackDist(level * 5, level * 10);	//���� ���� (level * 5 ~ level * 10)

	health = healthDist(gen);
	attack = attackDist(gen);
}

string Orc::getName() const
{
	return name;
}
int Orc::getHealth() const
{
	return health;
}
int Orc::getAttack() const
{
	return attack;
}


//���� �ǰ�
void Orc::takeDamage(int damage)
{
	health -= damage;
	if (health < 0) health = 0;  // 0�� �Ǹ� �׾���ϴ� �������� ������ �� 0���� ����
}

//������ ��� + ����ġ �߰� + ��� ��� �߰�
DropAll* Orc::dropAll() {
	int exp = 50; // ����ġ�� ���������� �־����ϴ�.



	//���� ü��,���ݷ� ������ ���� ������� �������� ����ϰ� �߽��ϴ�.
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<int> goldDist(1, 5);  // 1~5���
	int gold = goldDist(gen);



	//FMath�� RandRange�� �𸮾� ���� ���̺귯���� ������� ���Ѵٰ� �ϳ׿�.. 
	uniform_int_distribution<int> chance(0, 1);
	DropItem* dropItem = nullptr;
	if (chance(gen) == 1) {
		dropItem = new DropItem("HealthPotion");
	}

	return new DropAll(dropItem, gold, exp);
}