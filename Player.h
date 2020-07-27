#ifndef PLAYER_H
#define PLAYER_H
#include "Inventory.h"

enum Directions { NORTH = 'N', WEST = 'W', SOUTH = 'S', EAST = 'E' };

struct Point
{
	int x, y;
};

class Player
{
private:
	Point currentRoom;
	Point currentLocation;
	Inventory inventory;
	Directions direction;
public:
	Point loc();
	Point currRoom();
	void setRoom(int x, int y);
	void setLoc(int x, int y);
	void setInventory(Object t);
	bool isKeyExist(Object t);
	void loadPlayer(ifstream& fin);
	void savePlayer(ofstream& fout);
	void setDirection(Directions);
	Directions getDirection();
	void displayInventory();
	int gemsCount();
	int diamondsCount();
};

#endif
