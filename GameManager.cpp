#include "GameManager.h"

#include <iostream>
#include <vector>
#include <random>

using namespace std;

Monster* GameManager::generateMonster(int level)
{
	vector<Monster*> Monsterlist = { new Goblin(level), new Orc(level), new Troll(level) };
	
	random_device rand;
	mt19937 gen(rand());
	uniform_int_distribution<int> dis(0, 2);	// 0 ~ 2 ���̿��� �����ϰ� ���ڸ� �����ϰ� ���͸���Ʈ�� �ε����� ����

	return Monsterlist[dis(gen)];
}

Monster* GameManager::generateBossMonster(int level)
{
	return new BossMonster(level);
}

void GameManager::battle(Character* player, Monster* monster)  // ĳ����/���� ������ �ѹ��� �����ϰ� �� �� �ϳ��� ������ break
{
	int curAttack = player->getAttack();	//���� ���ݷ�
	int buffAttack = player->getAttack();	//���� ��� �� ���ݷ�
	if (true) // ���ݷ� ���� ������ ���� Ȯ��
	{
		string choice;
		cout << "���ݷ� ��ȭ ������ ����Ͻðڽ��ϱ�? (Y/N)" << endl;
		cin >> choice;

		if (choice == "Y" || choice == "y")
		{
			buffAttack += 10; //���ݷ� ��ȭ ��ġ
			player->setAttack(buffAttack);
		}
	}
	while (player->getHealth() != 0 && monster->getHealth != 0) // attack �Լ� ����?
	{
		cout << "������ �����մϴ�." << endl;
		
		monster->takeDamage(player->getAttack());				//���Ͱ� ���� ���� ����
		player->takeDamage(monster->getAttack());				//�÷��̾ ���� ����

		if (player->getHealth() < (player->getMaxHealth() / 2))
		{
			//ü�� ���� ���
			//ü�� ������ �ε��� �ʿ�
			int index = 0; 
			player->useItem(index);
		}
	}

	if (player->getHealth() == 0)
	{
		throw runtime_error("���谡�� ����߽��ϴ�.");
	}

	player->setAttack(curAttack); //���ݷ� ���� ����

	cout << "���͸� óġ�߽��ϴ�!" << endl;

	delete monster;
}

void GameManager::visitShop(Character* player)
{
	Shop* shop = new Shop();

	while (true)
	{
		int choice;
		//���� Ȥ�� �Ǹ� ������ ���

		cout << "==================" << endl;
		cout << "1. ����" << endl;
		cout << "2. �Ǹ�" << endl;
		cout << "3. ���� ������" << endl;
		cout << "==================" << endl;
		
		cin >> choice;

		if (choice == 1) //����
		{
			int Itemchoice;
			cout << "���� ������ ���" << endl;

			shop.displayitems(); // ���� ������ ����Ʈ ���

			cout << "� �������� �����Ͻðڽ��ϱ�?" << endl;

			cin >> Itemchoice;

			switch (Itemchoice)
			{
			case 1:
				shop->buyItem(0, player);
				break;
			case 2:
				shop->buyItem(1, player);
				break;
			case 3:
				shop->buyItem(2, player);
				break;
			default:
				break;
			}
		}
		else if (choice == 2) //�Ǹ�
		{
			int Itemchoice;

			displayInventory(player);

			cout << "� �������� �Ǹ��Ͻðڽ��ϱ�?" << endl;

			cin >> Itemchoice;  //�κ��� �ִ� ������ ������ ��� Ư���� ����

			switch (Itemchoice)
			{
			case 1:
				shop->sellItem(0, player);
				break;
			case 2:
				shop->sellItem(1, player);
				break;
			default:
				break;
			}
		}
		else if (choice == 3)
		{
			string answer;

			cout << "������ �����ðڽ��ϱ�? (Y/N)" << endl;
			cin >> answer;

			if (answer == "Y" || answer == "y")
			{
				break;
			}
			else
			{
				continue;
			}
		}
		else
		{
			cout << "�߸��� �Է��Դϴ�." << endl;
			continue;
		}
	}

	delete shop;
}

void GameManager::displayInventory(Character* player)
{
	//ĳ���� Ŭ�������� getInventory �Լ� �ʿ�
	// �������� ���� �Ӹ� �ƴ϶� ������ �ʿ��� -> map �ڷ��� Ȱ��

	Item* item = player->getInventory();

	for (int i = 1; i <= player->getInventory().size(); ++i)
	{
		cout << i << ". " << item->first << ": " << item->second << endl;
	}
}
