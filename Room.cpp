#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stdlib.h>
using namespace std;
#include "Room.h"

void Room::loadRoom(ifstream& fin)
{
	for(int i= 0; i<5; i++)
		for(int j = 0; j<10; j++)
			items[i][j].loadItem(fin);
}
void Room::saveRoom(ofstream& fout)
{
	for(int i= 0; i<5; i++)
		for(int j = 0; j<10; j++)
			items[i][j].saveItem(fout);
}
Object& Room::getObjectAt(int i, int j)
{
	return items[i][j];
}
void Room::displayLine(int l, int rX, int rY, bool displayFull)
{
    if(l==0&&rX)
        return;
	if(rY == 0)
		cout << (char)items[l][0].getType();

	for(int i = 1; i<=8; i++)
		if(displayFull&&l!=0 || l == 4 || l==0&&rX==0)
			cout << (char)items[l][i].getType();
		else
			cout << (char)EMPTY;

	cout << (char)items[l][9].getType();
}
