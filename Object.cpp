#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cstring>
using namespace std;
#include "Object.h"

Items Object::getType()
{
	return type;
}
string Object::getName()
{
	switch(type)
	{
	case EMPTY: return "Empty area";
	case WALL: return "Wall";
	case OPEN_DOOR: return "Door";
	case LOCKED_DOOR: return "Locked Door";
	case BOX: return "Box";
    case PLAYER: return "People";
    case ENEMY: return "Enemy";
    case GEM: return "Gem";
    case DIAMOND: return "Diamond";
    case KEY_1: return "Key";
    case KEY_2: return "Key";
	}
}
void Object::loadItem(ifstream& fin)
{
	fin >> (int&)type;
	fin >> keyValue;
	fin.ignore();
	getline(fin, encounterText);
}
void Object::saveItem(ofstream& fout)
{
	fout << type << "\n" << keyValue << "\n" << encounterText << "\n";
}
void Object::setType(Items t)
{
	type = t;
}
bool Object::matchKey(Object t)
{
	return t.keyValue == keyValue;
}
Object Object::examine()
{
	Object n;
	if(keyValue == EMPTY || keyValue == DIAMOND || keyValue == GEM)
	{
		n.type = (Items)keyValue;
		n.keyValue = 0;
		n.encounterText = "";
	}
	else
	{
		n.type = KEY_2;
		n.keyValue = keyValue;
		n.encounterText = "";
	}
    keyValue = EMPTY;
	return n;
}
string& Object::getEncounterText()
{
	return encounterText;
}
