#pragma once
#include <string>
#include <iostream>

using namespace std;

class DropItem {

private:
	string name;

public:
	//������
	DropItem(string& name) : name(name) {}

	string getName() const
	{
		return name;
	}
};

//���� óġ ���� ����
struct DropAll {
	DropItem* dropItem;
	int gold;
	int exp;

	DropAll(DropItem* dropItem, int gold, int exp)
		:dropItem(dropItem), gold(gold), exp(exp){}
};