#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <stdlib.h>
using namespace std;
#include "Inventory.h"

void Inventory::loadInventory(ifstream& fin)
{
	int count;
	fin >> count;
	for(int i = 0; i<count; i++)
	{
		Object t;
		t.loadItem(fin);
		itemList.push_back(t);
	}
}
void Inventory::saveInventory(ofstream& fout)
{
	fout << itemList.size() << "\n";
	for(int i = 0; i<itemList.size(); i++)
		itemList[i].saveItem(fout);
}
bool Inventory::isKeyExist(Object t)
{
	for(int i = 0; i<itemList.size(); i++)
		if(itemList[i].matchKey(t))
			return true;
	return false;
}
void Inventory::addItem(Object t)
{
    if(t.getType() != EMPTY)
        itemList.push_back(t);
}
void Inventory::display()
{
    cout <<"\n\t\t--- Inventory List ---\n\n";
    if(itemList.size() == 0)
        cout << "\n\t\tInventory is empty\n";
	for(int i = 0; i<itemList.size(); i++)
		cout << i+1 << "  " << itemList[i].getName() << "\n";
	system("pause");
}
int Inventory::count(Items t)
{
    int counter  = 0;
    for(int i = 0; i<itemList.size(); i++)
        if(itemList[i].getType() == t)
            counter++;
    return counter;
}
