#pragma once

#include "Character.h" //ĳ���� Ŭ����
#include "Shop.h"      //���� Ŭ����
#include "Monster.h"   //���� Ŭ����
#include "Goblin.h"
#include "BossMonster.h"
#include "Orc.h"
#include "Troll.h"
#include "MainArt.h"

class GameManager
{
public:
	Monster* generateMonster(int level);							//ĳ���� ������ �޾Ƽ� ������ ���� ����
	Monster* generateBossMonster(int level);

	void battle(Character* player, Monster* monster);				//ĳ���� ����, ���� �İ����� �ѹ��� ����
	void visitShop(Character* player);								//ĳ���Ͱ� ���� �湮
	void displayInventory(Character* player);						//ĳ���� �κ��丮 Ȯ��
	void drawHealthbar(int hp, int maxHp, int barWidth = 20);

	void playerUI(Character* player);
	void battleUI(Character* player, Monster* monster, int line);
	void setCursor(int x, int y);
	void drawMonsterArt(Monster* monster, int line);
	void drawShopArt(Shop* shop, int line);
	void drawDefeat(Character* player, int line);
	void drawMainArt(MainArt* mainart, int line);
	void printLog(const string& msg, int line);
};

