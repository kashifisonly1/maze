#ifndef INVENTORY_H
#define INVENTORY_H
#include "Object.h"

class Inventory
{
private:
	vector<Object> itemList;
public:
	void loadInventory(ifstream& fin);
	void saveInventory(ofstream& fout);
	bool isKeyExist(Object t);
	void addItem(Object t);
	void display();
	int count(Items);
};

#endif
