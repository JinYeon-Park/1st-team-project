#pragma once
#include <string>
#include <iostream>
#include "DropItem.h"

using namespace std;

class Monster {
public:
	//���������Լ� �ڽ� Ŭ�������� ������ �����ؾ� ��
	virtual string getName() const = 0;
	virtual int getHealth() const = 0;
	virtual int getAttack() const = 0;
	virtual void takeDamage(int damage) = 0;
	virtual DropAll* dropAll() = 0;

	virtual ~Monster() = default;
};
