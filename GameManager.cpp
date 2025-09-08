#include "GameManager.h"

#include <Windows.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <conio.h>
#include <thread>
#include <chrono>

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

	auto it = find_if(inventory.begin(), inventory.end(), [&find](Item* item) {return item->getName() == find; }); // ���ݷ� ���� ������ �����ϴ��� Ȯ��

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

	cout << "������ �����մϴ�." << endl;
	this_thread::sleep_for(chrono::milliseconds(800)); //0.8�� ������

	int logline = monster->art().size() + 4; //��Ʈ���� 2�� �Ʒ�
	int battlelog = logline + 6;
	int delay = 500; //0.5��

	system("cls");
	
	while (player->getHealth() != 0 && monster->getHealth() != 0) // attack �Լ� ����?
	{
		setCursor(0, 0);
		playerUI(player);  //Ŀ�� ������ �̵� �� 1��¥�� UI ���

		drawMonsterArt(monster, 2); // 3��° �ٺ��� ��Ʈ ���

		battelUI(player, monster, logline);

		monster->takeDamage(player->getAttack());				//���Ͱ� ���� ���� ����
		setCursor(0, 0);
		playerUI(player);
		battelUI(player, monster, logline);
		printLog("���谡�� " + to_string(player->getAttack()) + "�� ���ظ� �������ϴ�.", battlelog);
		++battlelog;
		this_thread::sleep_for(chrono::milliseconds(delay));

		player->takeDamage(monster->getAttack());				//�÷��̾ ���� ����
		setCursor(0, 0);
		playerUI(player);
		battelUI(player, monster, logline);
		printLog("���Ͱ� " + to_string(monster->getAttack()) + "�� ���ظ� �������ϴ�.", battlelog);
		++battlelog;
		this_thread::sleep_for(chrono::milliseconds(delay));


		if (player->getHealth() < (player->getMaxHealth() / 2)) //�ִ� ü���� 50% �Ʒ��� ������ ��� �ڵ� ���
		{
			string find = "HealthPotion";

			auto it = find_if(inventory.begin(), inventory.end(), [&find](Item* item) {return item->getName() == find; }); // ü�� ������ �����ϴ��� Ȯ��

			if (it != inventory.end())
			{
				//ü�� ���� ���
				inventory[it - inventory.begin()]->useItem(player);
				setCursor(0, 0);
				playerUI(player);
				battelUI(player, monster, logline);
				printLog("ü�� ������ ����Ͽ� 50�� ü���� ȸ���߽��ϴ�!", battlelog);
				++battlelog;
				this_thread::sleep_for(chrono::milliseconds(delay));
			}
		}
		++battlelog;
	}

	if (player->getHealth() == 0)
	{
		throw runtime_error("���谡�� ����߽��ϴ�.");
	}

	player->setAttack(curAttack); //���ݷ� ���� ����

	int dropGold = monster->dropGold(); //��� ��� ����ϱ�

	player->setkillmonster(player->getkillmonster + 1);  //���� ų�� +1
	player->setGold(dropGold + player->getGold());

	setCursor(0, 0);
	playerUI(player);
	battelUI(player, monster, logline);
	printLog("���͸� óġ�߽��ϴ�!", logline + 10);

	//���� óġ -> ����ġ�� ��� ������ ȹ��

	//��� ȹ��
	//���͸��� ��� �ٸ��� �ϰ� dropGold ���� �Լ��� ��� ��� Ȯ��
	//�÷��̾ addGold �Լ��� ��� �߰�, ��� ȹ�� ���� ���

	cout << monster->dropGold() << "��带 ȹ���߽��ϴ�." << endl;

	player->addInventory(monster->dropItem());

	//��� �������� �ִ��� Ȯ���ϰ� ������ �κ��� �߰� ������ �Ѿ��

	delete monster;
}

void GameManager::visitShop(Character* player)
{
	Shop* shop = new Shop();

	int logline = shop->art().size() + 4; //���� ��Ʈ 4�� �Ʒ�����

	while (true)
	{
		system("cls"); //�ܼ� ȭ�� �����

		setCursor(0, 0);
		playerUI(player);

		drawShopArt(shop, 2);

		int choice;
		//���� Ȥ�� �Ǹ� ������ ���

		printLog("==================", logline);
		printLog("1. ����", logline + 1);
		printLog("2. �Ǹ�", logline + 2);
		printLog("3. ���� ������", logline + 3);
		printLog("==================", logline + 4);
		
		cout << "��ȣ�� �Է��ϼ���: ";

		cin >> choice;
		cin.ignore(1000, '\n');

		if (cin.fail()) //�� ���� Ÿ���� �ԷµǸ� true ��ȯ
		{
			cin.clear(); // ���� ���� �ʱ�ȭ
			cin.ignore(1000, '\n'); // �߸��� �Է� ������
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
			continue;
		}

		if (choice == 1) //����
		{
			while (true) {
				system("clear");

				setCursor(0, 0);
				playerUI(player);

				drawShopArt(shop, 2);

				setCursor(0, logline);

				int choice = shop->displayBuyMenu(player);

				if (choice == 0) break;       // �ڷΰ���
				if (choice == -1) 
				{
					printLog("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.", logline + 10);											//�α� ��� ���� ��ġ ���� �ʿ�
					this_thread::sleep_for(chrono::milliseconds(1000)); // 1�� ���
					continue;
				}

				// ������ ������ ���� ó��
				Item* selectedItem = shop->availableItems[choice];
				if (player->getGold() >= selectedItem->getPrice()) 
				{
					shop->buyItem(selectedItem);
					printLog("�������� �����߽��ϴ�.", logline + 10);
					this_thread::sleep_for(chrono::milliseconds(1000)); // 1�� ���
				}
				else 
				{
					printLog("��尡 �����մϴ�!", logline + 10);											//�α� ��� ���� ��ġ ���� �ʿ�
				}
			}
		}
		else if (choice == 2) //�Ǹ�
		{
			while (true)
			{
				system("cls"); //�ܼ� ȭ�� �����

				setCursor(0, 0);
				playerUI(player);

				drawShopArt(shop, 2);

				setCursor(0, logline);

				int choice = shop->displaySellMenu(player);

				if (choice == 0) break;       // �ڷΰ���
				if (choice == -1)
				{
					printLog("�߸��� �����Դϴ�. �ٽ� �Է����ּ���.", logline + 10);											//�α� ��� ���� ��ġ ���� �ʿ�
					this_thread::sleep_for(chrono::milliseconds(1000)); // 1�� ���
					continue;
				}

				// ������ �Ǹ�
				Item* soldItem = player->getInventory[choice];
				shop->sellItem(soldItem);
				printLog("�������� �Ǹ��߽��ϴ�.", logline + 10);
				this_thread::sleep_for(chrono::milliseconds(1000)); // 1�� ���
			}
		}
		else if (choice == 3)
		{
			string answer;

			cout << "������ �����ðڽ��ϱ�? (Y/N)" << endl;
			cin >> answer;
			cin.ignore(1000, '\n');

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
	
	vector<Item*> item = player->getInventory();
	
	for (int i = 1; i <= item.size(); ++i)
	{
		cout << i << ". " << item[i]->getName() << ": " << item[i]->getPrice()*0.8 << "���" << endl; //���⼭ price�� �������� �ǸŽ� ����
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

void GameManager::playerUI(Character* player)
{
	cout << "�г���: " << player->getName() << " | ü��: ";
	drawHealthbar(player->getHealth(), player->getMaxHealth());
	cout << " " << player->getHealth() << "/" << player->getMaxHealth();
	cout << " | ����: " << player->getLevel();
	cout << " | ����ġ: " << player->getExp() << "/100";
	cout << " | ���: " << player->getGold();
	cout << " | óġ�� ���� ��: " << player-> getkillmonster() << "����\n" << endl;
}

void GameManager::battelUI(Character* player, Monster* monster, int line)
{
	setCursor(0, line); // Ŀ�� �̵�
	cout << "========== ���� ���� ==========\n";
	cout << "���谡 ü��: ";
	drawHealthbar(player->getHealth(), player->getMaxHealth(), 20);
	cout << "  " << player->getHealth() << "/" << player->getMaxHealth() << "\n";
	cout << "���� ü��: ";
	drawHealthbar(monster->getHealth(), monster->getMaxHealth(), 20);
	cout << "  " << monster->getHealth() << "/" << monster->getMaxHealth() << "\n";
	cout << "===============================\n";
}

void GameManager::setCursor(int x, int y) {
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void GameManager::drawMonsterArt(Monster* monster, int line)
{
	vector<string> art = monster->getart();

	for (size_t i = 0; i < art.size(); ++i) 
	{
		setCursor(0, line + i);   // �� �ٸ��� ���� ��ġ ����
		cout << art[i] << "                                         "; // �������� ���� ��� ���� ����
	}
}

void GameManager::drawShopArt(Shop* shop, int line)
{
	vector<string> art = shop->getart();

	for (size_t i = 0; i < art.size(); ++i)
	{
		setCursor(0, line + i);   // �� �ٸ��� ���� ��ġ ����
		cout << art[i] << "                               "; // �������� ���� ��� ���� ����
	}
}

void GameManager::drawDefeat(Character* player, int line)
{
	vector<string> art = player->getart();

	for (size_t i = 0; i < art.size(); ++i)
	{
		setCursor(0, line + i);   // �� �ٸ��� ���� ��ġ ����
		cout << art[i] << "                               "; // �������� ���� ��� ���� ����
	}
}

void GameManager::printLog(const string& msg, int line)
{
	setCursor(0, line);
	cout << msg << "                         \n"; // �������� ���� �ؽ�Ʈ �����
}
