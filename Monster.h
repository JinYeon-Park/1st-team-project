#pragma once
#include <string>
#include <iostream>
#include "Item.h"

using namespace std;

class Monster {
public:
	//���������Լ� �ڽ� Ŭ�������� ������ �����ؾ� ��
	virtual string getName() const = 0;
	virtual int getHealth() const = 0;
	virtual int getAttack() const = 0;
	virtual void takeDamage(int damage) = 0;
	virtual Item* dropItem();

	virtual int getMaxHealth() const = 0;
	virtual int getExp() const = 0;
	virtual int getGold() const = 0;

	virtual ~Monster() = default;
};
