#include "GameManager.h"

#include <Windows.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <conio.h>
#include <thread>
#include <chrono>
#include <sstream>


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

	cout << "������ �����մϴ�!" << endl;
	this_thread::sleep_for(chrono::milliseconds(1000)); //1�� ������

	int logline = monster->getart().size() + 4; //��Ʈ���� 2�� �Ʒ�
	int battlelog = logline + 6;
	int delay = 500; //0.5��

	system("cls");
	
	while (player->getHealth() != 0 && monster->getHealth() != 0) // attack �Լ� ����?
	{
		playerUI(player);  //Ŀ�� ������ �̵� �� 1��¥�� UI ���

		drawMonsterArt(monster, 2); // 3��° �ٺ��� ��Ʈ ���

		printLog(monster->getName() + "��(��) ��Ÿ�����ϴ�!", logline);
		
		battleUI(player, monster, logline + 2);

		monster->takeDamage(player->getAttack());				//���Ͱ� ���� ���� ����
		playerUI(player);
		battleUI(player, monster, logline);
		printLog("���谡�� " + to_string(player->getAttack()) + "�� ���ظ� �������ϴ�.", battlelog);
		++battlelog;
		this_thread::sleep_for(chrono::milliseconds(delay));

		player->takeDamage(monster->getAttack());				//�÷��̾ ���� ����
		playerUI(player);
		battleUI(player, monster, logline);
		printLog("���Ͱ� " + to_string(monster->getAttack()) + "�� ���ظ� �������ϴ�.", battlelog);
		++battlelog;
		this_thread::sleep_for(chrono::milliseconds(delay));


		if (player->getHealth() < (player->getMaxHealth() / 2)) //�ִ� ü���� 50% �Ʒ��� ������ ��� �ڵ� ���
		{
			string find = "ü�� ����";

			auto it = find_if(inventory.begin(), inventory.end(), [&find](Item* item) {return item->getName() == find; }); // ü�� ������ �����ϴ��� Ȯ��

			if (it != inventory.end())
			{
				//ü�� ���� ���
				inventory[it - inventory.begin()]->use(player);
				playerUI(player);
				battleUI(player, monster, logline);
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

	player->setKillcount(player->getKillcount() + 1);  //���� ų�� +1
	player->setGold(monster->getGold() + player->getGold());

	playerUI(player);
	battleUI(player, monster, logline);
	printLog("���͸� óġ�߽��ϴ�!", logline + 10);

	//���� óġ -> ����ġ�� ��� ������ ȹ��

	//��� ȹ��
	//���͸��� ��� �ٸ��� �ϰ� dropGold ���� �Լ��� ��� ��� Ȯ��
	//�÷��̾ addGold �Լ��� ��� �߰�, ��� ȹ�� ���� ���

	cout << monster->getGold() << "��带 ȹ���߽��ϴ�." << endl;

	player->addInventory(monster->dropItem());

	//��� �������� �ִ��� Ȯ���ϰ� ������ �κ��� �߰� ������ �Ѿ��

	delete monster;
}

void GameManager::visitShop(Character* player)
{
	Shop* shop = new Shop();

	int logline = shop->getart().size() + 4; //���� ��Ʈ 4�� �Ʒ�����

	while (true)
	{
		system("cls"); //�ܼ� ȭ�� �����

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

				playerUI(player);

				drawShopArt(shop, 2);

				setCursor(0, logline);

				int choice = shop->buyLoop(player);

				if (choice == 0) break;       // �ڷΰ���
				if (choice == -1) 
				{
					printLog("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.", logline + 10);											//�α� ��� ���� ��ġ ���� �ʿ�
					this_thread::sleep_for(chrono::milliseconds(1000)); // 1�� ���
					continue;
				}

				// ������ ������ ���� ó��
				setCursor(0, logline + 10);
				shop->buyItem(choice - 1, player);
			}
		}
		else if (choice == 2) //�Ǹ�
		{
			while (true)
			{
				system("cls"); //�ܼ� ȭ�� �����

				playerUI(player);

				drawShopArt(shop, 2);

				setCursor(0, logline);

				int choice = shop->sellLoop(player);

				if (choice == 0) break;       // �ڷΰ���
				if (choice == -1)
				{
					printLog("�߸��� �����Դϴ�. �ٽ� �Է����ּ���.", logline + 10);											//�α� ��� ���� ��ġ ���� �ʿ�
					this_thread::sleep_for(chrono::milliseconds(1000)); // 1�� ���
					continue;
				}
				else if (choice == -2)
				{
					printLog("�Ǹ��� �������� �����ϴ�.", logline + 10);
					break;
				}

				// ������ �Ǹ�

				shop->sellItem(choice - 1, player);
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

void drawHealthbar(int hp, int maxHp, int barWidth = 10)
{
	UINT oldCP = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	double ratio = (double)hp / maxHp;
	int filled = (int)(ratio * barWidth);

	cout << "[";

	for (int i = 0; i < barWidth; i++)
	{
		if (i < filled) {
			SetConsoleTextAttribute(hConsole, 10); // 10 = �ʷϻ�
			cout << u8"��";
		}
		else {
			SetConsoleTextAttribute(hConsole, 7); // 12 = ������
			cout << u8"-";  // �� ĭ�� �� ��� ��ĥ�� ��� ���� ����
		}
	}

	SetConsoleTextAttribute(hConsole, 7); // �⺻ �������� ����
	cout << "] ";

	SetConsoleOutputCP(oldCP);
}

void GameManager::playerUI(Character* player) // �ܼ�â ��� ����
{
	setCursor(0, 0);
	cout << "�г���: " << player->getName() << " | ü��: ";
	drawHealthbar(player->getHealth(), player->getMaxHealth());
	cout << " " << player->getHealth() << "/" << player->getMaxHealth();
	cout << " | ����: " << player->getLevel();
	cout << " | ����ġ: " << player->getExp() << "/100";
	cout << " | ���: " << player->getGold() << " G";
	cout << " | óġ�� ���� ��: " << player->getKillcount() << "����\n" << endl;
}

void GameManager::battleUI(Character* player, Monster* monster, int line)
{
	setCursor(0, line); // Ŀ�� �̵�
	cout << "========== ���� ���� ==========\n";
	cout << "���谡 ü��: ";
	drawHealthbar(player->getHealth(), player->getMaxHealth(), 20);
	cout << "  " << player->getHealth() << "/" << player->getMaxHealth() << "  ���ݷ�: " << player->getAttack() << "\n";
	cout << "���� ü��: ";
	drawHealthbar(monster->getHealth(), monster->getMaxHealth(), 20);
	cout << "  " << monster->getHealth() << "/" << monster->getMaxHealth() << "  ���ݷ�: " << monster->getAttack() << "\n";
	cout << "===============================\n";
}

void GameManager::setCursor(int x, int y) {
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void GameManager::drawMonsterArt(Monster* monster, int line)
{
	UINT oldCP = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	string art = monster->getart();
	istringstream iss(art);
	string lineStr;
	int offset = 0;

	while (std::getline(iss, lineStr)) {
		setCursor(0, line + offset);
		cout << lineStr << "                                         ";
		offset++;
	}

	SetConsoleOutputCP(oldCP);
}

void GameManager::drawShopArt(Shop* shop, int line)
{
	UINT oldCP = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	string art = shop->getart();
	istringstream iss(art);
	string lineStr;
	int offset = 0;

	while (std::getline(iss, lineStr)) {
		setCursor(0, line + offset);
		cout << lineStr << "                                         ";
		offset++;
	}

	SetConsoleOutputCP(oldCP);
}

void GameManager::drawDefeat(Character* player, int line)
{
	UINT oldCP = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	string art = player->getart();
	istringstream iss(art);
	string lineStr;
	int offset = 0;

	while (std::getline(iss, lineStr)) {
		setCursor(0, line + offset);
		cout << lineStr << "                                         ";
		offset++;
	}

	SetConsoleOutputCP(oldCP);
}

void GameManager::drawMainArt(MainArt* mainart, int line)
{
	UINT oldCP = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	string art = mainart->getart();
	istringstream iss(art);
	string lineStr;
	int offset = 0;

	while (std::getline(iss, lineStr)) {
		setCursor(0, line + offset);
		cout << lineStr << "                                         ";
		offset++;
	}

	SetConsoleOutputCP(oldCP);
}

void GameManager::printLog(const string& msg, int line)
{
	setCursor(0, line);
	cout << msg << "                         \n"; // �������� ���� �ؽ�Ʈ �����
}
