#include "GameManager.h"

#include <Windows.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;
using std::cout;

Monster* GameManager::generateMonster(int level)
{
	vector<Monster*> Monsterlist = { new Goblin(level), new Orc(level), new Troll(level) }; //�ѹ��� �� �޴� ���?
	
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
	vector<Item*> inventory = player->getInventory();

	string find = "AttackBoost";

	auto it = inventory.find_if(inventory.begin(), inventory.end(), [&find](Item* item) {return item->getName() == find; }); // ���ݷ� ���� ������ �����ϴ��� Ȯ��

	if (it != inventory.end()) 
	{
		string choice;

		while (true)
		{
			cout << "���ݷ� ��ȭ ������ ����Ͻðڽ��ϱ�? (Y/N)\n" << endl;
			cin >> choice;

			if (cin.fail()) //�� ���� Ÿ���� �ԷµǸ� true ��ȯ
			{
				cin.clear(); // ���� ���� �ʱ�ȭ
				cin.ignore(1000, '\n'); // �߸��� �Է� ������
				cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n" << endl;
				continue;
			}

			if (choice == "Y" || choice == "y")
			{
				inventory[it - inventory.begin()]->use(player);
				break;
			}
			else
			{
				break;
			}
		}
	}
	while (player->getHealth() != 0 && monster->getHealth != 0) // attack �Լ� ����?
	{
		cout << "������ �����մϴ�.\n" << endl;
		
		monster->takeDamage(player->getAttack());				//���Ͱ� ���� ���� ����
		player->takeDamage(monster->getAttack());				//�÷��̾ ���� ����

		string find = "HealthPotion";

		auto it = inventory.find_if(inventory.begin(), inventory.end(), [&find](Item* item) {return item->getName() == find; }); // ü�� ������ �����ϴ��� Ȯ��

		if (it != inventory.end())
		{
			if (player->getHealth() < (player->getMaxHealth() / 2)) //�ִ� ü���� 50% �Ʒ��� ������ ��� �ڵ� ���
			{
				//ü�� ���� ���
				inventory[it - inventory.begin()]->useItem(player);
			}
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
		system("clear"); //�ܼ� ȭ�� �����

		int choice;
		//���� Ȥ�� �Ǹ� ������ ���

		cout << "==================" << endl;
		cout << "1. ����" << endl;
		cout << "2. �Ǹ�" << endl;
		cout << "3. ���� ������" << endl;
		cout << "==================\n" << endl;
		
		cin >> choice;

		if (choice == 1) //����
		{
			while (true)
			{
				int Itemchoice;

				cout << "===���� ������ ���===" << endl;

				vector<Item*> shoplist = shop.displayitems(); //vector<Item*>�� �ޱ�
															  //���� â���� ���� �ʱ� ȭ������ ������ ���� 0������ �ڷΰ��� item* �߰�

				cout << "0" << ". " << shoplist[0]->getName() << endl;  //�ڷΰ��� ���

				for (int i = 1; i <= shoplist.size(); ++i)	//���� ������ ����Ʈ ���, displayitems���� �����ϴ� ���� ���ƺ���
				{
					cout << i << ". " << shoplist[i]->getName() << ": " << shoplist[i]->getPrice() << "���" << endl;
				}

				cout << "� �������� �����Ͻðڽ��ϱ�?" << endl;

				cin >> Itemchoice; //���ڷ� �ޱ� Ȥ�� string���� ������ �̸����� �ޱ�

				if (cin.fail()) //�� ���� Ÿ���� �ԷµǸ� true ��ȯ
				{
					cin.clear(); // ���� ���� �ʱ�ȭ
					cin.ignore(1000, '\n'); // �߸��� �Է� ������
					cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
					continue; 
				}

				if (Itemchoice != 0)
				{
					shop->buyItem(Itemchoice, player); //Itemchoice�� ������ �ִ� ������ vector�� �ε����� ����
					continue;
				}
				else
				{
					break; //0�� �ڷΰ��� ���ý� ���� �ʱ�ȭ������ ���ư���
				}
			}
		}
		else if (choice == 2) //�Ǹ�
		{
			while (true)
			{
				int Itemchoice;

				displayInventory(player);

				cout << "� �������� �Ǹ��Ͻðڽ��ϱ�?" << endl;

				cin >> Itemchoice;

				if (cin.fail()) //�� ���� Ÿ���� �ԷµǸ� true ��ȯ
				{
					cin.clear(); // ���� ���� �ʱ�ȭ
					cin.ignore(1000, '\n'); // �߸��� �Է� ������
					cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
					continue;
				}

				if (Itemchoice != 0)
				{
					shop->sellItem(Itemchoice, player); //Itemchoice�� �κ��� �ִ� ������ vector�� �ε����� �Ǹ�
					continue;
				}
				else
				{
					break; //0�� �ڷΰ��� ���ý� ���� �ʱ�ȭ������ ���ư���
				}
			}
		}
		else if (choice == 3)
		{
			string answer;

			cout << "������ �����ðڽ��ϱ�? (Y/N)" << endl;
			cin >> answer;

			if (cin.fail()) //�� ���� Ÿ���� �ԷµǸ� true ��ȯ
			{
				cin.clear(); // ���� ���� �ʱ�ȭ
				cin.ignore(1000, '\n'); // �߸��� �Է� ������
				cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
				continue;
			}

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
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
			continue;
		}
	}
	delete shop;
}

void GameManager::displayInventory(Character* player)
{
	//ĳ���� Ŭ�������� getInventory �Լ� �ʿ�
	// �������� ���� �Ӹ� �ƴ϶� ������ �ʿ��� -> map �ڷ��� Ȱ��

	vector<Item*> item = player->getInventory(); //ĳ���� �κ����� 0������ �ڷΰ��� �ֱ�

	cout << "0" << ". " << item[0]->getName() << endl;  //�ڷΰ��� ���
	
	for (int i = 1; i <= item.size(); ++i)
	{
		cout << i << ". " << item[i]->getName() << ": " << item[i]->getPrice() << "���" << endl; //���⼭ price�� �������� �ǸŽ� ����
	}
}

void GameManager::drawHealthbar(int hp, int maxHp, int barWidth = 10) 
{
	// ü�� ���� ���
	double ratio = (double)hp / maxHp;
	int filled = (int)(ratio * barWidth);

	cout << "[";
	for (int i = 0; i < barWidth; i++) {
		if (i < filled) cout << "*";  // ü���� �ִ� �κ�
		else cout << " ";             // ü���� ���� �κ�
	}
	cout << "] ";
}
