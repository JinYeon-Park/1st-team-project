#pragma once
#include <string>
#include <iostream>

using namespace std;

class DropItem {

private:
	string name;

public:
	//������
	DropItem(const string& name) : name(name) {}

	string getName() const
	{
		return name;
	}
};

