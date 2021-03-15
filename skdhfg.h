#ifndef ROOM_H
#define ROOM_H
#include "Object.h"

class Room
{
private:
	Object items[5][10];
public:
	void loadRoom(ifstream& fin);
	void saveRoom(ofstream& fout);
	Object& getObjectAt(int i, int j);
	void displayLine(int l, int rX, int rY, bool displayFull);
};

#endif