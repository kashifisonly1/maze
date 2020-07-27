#ifndef OBJECT_H
#define OBJECT_H

enum Items {EMPTY = 32, WALL = 219, OPEN_DOOR = 176, LOCKED_DOOR = 178, BOX = 177,
            PLAYER = 2, ENEMY = 1, GEM = 6, DIAMOND = 4, KEY_1 = 11, KEY_2 = 12};

class Object
{
private:
	Items type;
	int keyValue;
	string encounterText;
public:
	Items getType();
	string getName();
	void loadItem(ifstream& fin);
	void saveItem(ofstream& fout);
	void setType(Items);
	bool matchKey(Object);
	Object examine();
	string& getEncounterText();
};

#endif