#pragma once

#include "Character.h" //ĳ���� Ŭ����
#include "Shop.h"      //���� Ŭ����
#include "Monster.h"   //���� Ŭ����

class GameManager
{
public:
	Monster* generateMonster(int level);							//ĳ���� ������ �޾Ƽ� ������ ���� ����
	Monster* generateBossMonster();

	void battle(Character* player, Monster* monster);				//ĳ���� ����, ���� �İ����� �ѹ��� ����
	void visitShop(Character* player);								//ĳ���Ͱ� ���� �湮
	void displayInventory(Character* player);						//ĳ���� �κ��丮 Ȯ��
};

