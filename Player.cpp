#include <iostream>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <fstream>
using namespace std;
#include "Player.h"

Point Player::loc()
{
	return currentLocation;
}
Point Player::currRoom()
{
	return currentRoom;
}
void Player::setRoom(int x, int y)
{
	currentRoom.x = x;
	currentRoom.y = y;
}
void Player::setLoc(int x, int y)
{
	currentLocation.x = x;
	currentLocation.y = y;
}
void Player::setInventory(Object t)
{
	inventory.addItem(t);
}
bool Player::isKeyExist(Object t)
{
	return inventory.isKeyExist(t);
}
void Player::loadPlayer(ifstream& fin)
{
	fin >> currentRoom.x;
	fin >> currentRoom.y;
	fin >> currentLocation.x;
	fin >> currentLocation.y;
	fin >> (int&)direction;
	inventory.loadInventory(fin);
}
void Player::savePlayer(ofstream& fout)
{
	fout << currentRoom.x << "\n";
	fout << currentRoom.y << "\n";
	fout << currentLocation.x << "\n";
	fout << currentLocation.y << "\n";
	fout << direction << "\n";
	inventory.saveInventory(fout);
}
Directions Player::getDirection()
{
	return direction;
}
void Player::setDirection(Directions direct)
{
	direction = direct;
}
void Player::displayInventory()
{
	inventory.display();
}
int Player::gemsCount()
{
    return inventory.count(GEM);
}
int Player::diamondsCount()
{
    return inventory.count(DIAMOND);
}
