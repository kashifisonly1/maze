#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <stdlib.h>
using namespace std;
#include "Maze.h"

const string commandsList[11] = { "save", "exit", "talk",
		"move", "look", "open", "examine", "inventory", "help", "get", "unlock" };

Maze::Maze(string fname)
{
	ifstream fin(&fname[0]);
	// if failed to start game.
	if(fin.fail())
	{
		cout << "\nCould not open the file!\n\n";
		system("pause");
		return;
	}
	// loading data
	loadFileData(fin);
	fin.close();
    system("cls");
	fin.open("story.txt");
	cout << fin.rdbuf();
	cout << "\n\n\t\t";
	fin.close();
	system("pause");
 	startGame();
}
void Maze::loadFileData(ifstream& fin)
{
	currentPlayer.loadPlayer(fin);
	for(int i = 0; i<5; i++)
		for(int j = 0; j<5; j++)
			rooms[i][j].loadRoom(fin);
}
void Maze::startGame()
{
	gameStatus = CONTINUE;
	do
	{
		display();
		executeCommand( inputCommand() );
	}
	while ( gameStatus == CONTINUE);
    if(gameStatus == LEFT)
        return;
	display();
	if(gameStatus == WIN)
	{
	    cout << "\n\n\t\t--- You Won!---\n";
        cout << "\nTOTAL GEMS: " << currentPlayer.gemsCount();
        cout << "\nTOTAL DIAMONDS: " << currentPlayer.diamondsCount();
        cout<<"\n\n";
	}
	else if(gameStatus == LOSE)
		cout << "\n\n\t\t--- You Lose!---\n";
	system("pause");
}
GameCommands Maze::inputCommand()
{
	string command;
	cout << "Enter Command: ";
	cin >> command;
	int i = 0;
	while(i < 11 && command != commandsList[i])
		i++;
	return (GameCommands)i;
}
void Maze::executeCommand(GameCommands comm)
{
	switch(comm)
	{
	case SAVE: performSaveWork(); break;

	case EXIT: performExitWork(); break;

	case TALK: performTalkWork(); break;

	case MOVE: performMoveWork(); break;

	case LOOK: performLookWork(); break;

	case OPEN: performOpenWork(); break;

	case EXAMINE: performExamineWork(); break;

	case INVENTORY: system("cls"); currentPlayer.displayInventory(); break;

	case HELP: {system("cls");ifstream fin("help.txt"); cout << fin.rdbuf() <<"\n\t\t"; system("pause"); fin.close();} break;

	case GET: performGetWork(); break;

	case UNLOCK: performUnlockWork(); break;

	default: cout << "\nInvalid Command! to view commands, type: help.\n"; system("pause");
	}
	checkEnd();
}
void Maze::performSaveWork()
{
	string fname;
	cout << "Enter Your Name: ";
	cin >> fname;
	fname += ".txt";
	ofstream fout(&fname[0]);
	currentPlayer.savePlayer(fout);
	for(int i = 0; i<5; i++)
		for(int j = 0; j<5; j++)
			rooms[i][j].saveRoom(fout);
	fout.close();
	cout << "\n\t\t--- Your Game is Saved! ---\n";
	system("pause");
}
void Maze::performExitWork()
{
	string opt;
	cout << "Do you really want to exit? (Y/N): ";
	cin>>opt;
	if(opt == "y" || opt == "Y")
		gameStatus = LEFT;
}
void Maze::performTalkWork()
{
	Object* t;
	switch(currentPlayer.getDirection())
	{
	case NORTH:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x-1, currentPlayer.loc().y);
	break;
	case SOUTH:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x+1, currentPlayer.loc().y);
	break;
	case EAST:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y-1);
    break;
	case WEST:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y+1);
	break;
	}
	if(t->getType() == PLAYER)
    {
        t->setType(EMPTY);
        cout << t->getEncounterText() << "\n";
        system("pause");
    }
	else
	{
		cout << "\nTalking to " << t->getName() << " is meaningless!\n";
		system("pause");
	}
}
void Maze::performMoveWork()
{
	string loc;
	cin >> loc;
	cout << loc;
	if(loc != "N" && loc != "S" && loc != "W" && loc != "E")
	{
		cout << "\nInvalid Command! to view commands, type: help.\n";
		system("pause");
	}
	Object* t;
	switch(loc[0])
	{
	case NORTH:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x-1, currentPlayer.loc().y);
		if(t->getType() == EMPTY)
		{
			t->setType(PLAYER);
			rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y).setType(EMPTY);
			currentPlayer.setLoc(currentPlayer.loc().x-1, currentPlayer.loc().y);
		}
		currentPlayer.setDirection(NORTH);
	break;
	case SOUTH:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x+1, currentPlayer.loc().y);
		if(t->getType() == EMPTY)
		{
			t->setType(PLAYER);
			rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y).setType(EMPTY);
			currentPlayer.setLoc(currentPlayer.loc().x+1, currentPlayer.loc().y);
		}
		currentPlayer.setDirection(SOUTH);
	break;
	case EAST:
		for(int i = 0; i<2; i++){
			t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y-1);
			if(t->getType() == EMPTY)
			{
				t->setType(PLAYER);
				rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y).setType(EMPTY);
				currentPlayer.setLoc(currentPlayer.loc().x, currentPlayer.loc().y-1);
			}
		}
		currentPlayer.setDirection(EAST);
    break;
	case WEST:
       for(int i = 0; i<2; i++){
			t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y+1);
			if(t->getType() == EMPTY)
			{
			    t->setType(PLAYER);
				rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y).setType(EMPTY);
				currentPlayer.setLoc(currentPlayer.loc().x, currentPlayer.loc().y+1);
			}
		}
		currentPlayer.setDirection(WEST);
	break;
	}
}
void Maze::performLookWork()
{
	string loc;
	cin >> loc;
	if(loc != "N" && loc != "S" && loc != "W" && loc != "E")
	{
		cout << "\nInvalid Command! to view commands, type: help.\n";
		system("pause");
		return;
	}
	switch(loc[0])
	{
	case NORTH:
		currentPlayer.setDirection(NORTH);
	break;
	case SOUTH:
		currentPlayer.setDirection(SOUTH);
	break;
	case EAST:
		currentPlayer.setDirection(EAST);
	break;
	case WEST:
		currentPlayer.setDirection(WEST);
	break;
	}
}
void Maze::performExamineWork()
{
	Object* t;
	switch(currentPlayer.getDirection())
	{
	case NORTH:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x-1, currentPlayer.loc().y);
	break;
	case SOUTH:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x+1, currentPlayer.loc().y);
	break;
	case EAST:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y-1);
	break;
	case WEST:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y+1);
	break;
	}
	if(t->getType() != BOX)
	{
		cout << "\nExamine a "<<t->getName()<<" is meaningless\n";
		system("pause");
	}
	else
	{
		Object temp = t->examine();
		if(temp.getType() != EMPTY)
		{
		    cout << "\nYou Found a "<<temp.getName()<<"\n";
            currentPlayer.setInventory(temp);
		}
		else
        {
            cout<<"\nBox is Empty!\n";
        }
		system("pause");
	}
}
void Maze::performOpenWork()
{
	Object* t;
	switch(currentPlayer.getDirection())
	{
	case NORTH:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x-1, currentPlayer.loc().y);
	break;
	case SOUTH:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x+1, currentPlayer.loc().y);
	break;
	case EAST:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y-1);
	break;
	case WEST:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y+1);
	break;
	}
	if(t->getType() != OPEN_DOOR)
	{
		cout << "\nCannot Open a "<<t->getName()<<"\n";
		system("pause");
	}
	else
	{
		rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x,currentPlayer.loc().y).setType(EMPTY);
		switch(currentPlayer.getDirection())
		{
		case NORTH:
			currentPlayer.setRoom(currentPlayer.currRoom().x-1, currentPlayer.currRoom().y);
			currentPlayer.setLoc(3, currentPlayer.loc().y);
		break;
		case SOUTH:
			currentPlayer.setRoom(currentPlayer.currRoom().x+1, currentPlayer.currRoom().y);
			currentPlayer.setLoc(1, currentPlayer.loc().y);
		break;
		case EAST:
			currentPlayer.setRoom(currentPlayer.currRoom().x, currentPlayer.currRoom().y-1);
			currentPlayer.setLoc(currentPlayer.loc().x, 8);
		break;
		case WEST:
			currentPlayer.setRoom(currentPlayer.currRoom().x, currentPlayer.currRoom().y+1);
			currentPlayer.setLoc(currentPlayer.loc().x, 1);
		break;
		}
		rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x,currentPlayer.loc().y).setType(PLAYER);
	}
}
void Maze::performGetWork()
{
	Object* t;
	switch(currentPlayer.getDirection())
	{
	case NORTH:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x-1, currentPlayer.loc().y);
	break;
	case SOUTH:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x+1, currentPlayer.loc().y);
	break;
	case EAST:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y-1);
	break;
	case WEST:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y+1);
	break;
	}
	if(t->getType() != GEM && t->getType() != DIAMOND && t->getType() != KEY_1 && t->getType() != KEY_2)
	{
		cout << "\nCannot pick a "<<t->getName()<<"\n";
		system("pause");
	}
	else
	{
		currentPlayer.setInventory(*t);
		t->setType(EMPTY);
	}
}
void Maze::performUnlockWork()
{
	Object* t;
	switch(currentPlayer.getDirection())
	{
	case NORTH:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x-1, currentPlayer.loc().y);
	break;
	case SOUTH:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x+1, currentPlayer.loc().y);
	break;
	case EAST:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y-1);
	break;
	case WEST:
		t=&rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y+1);
	break;
	}
	if(t->getType() != LOCKED_DOOR)
	{
		cout << "\nUnlock a "<<t->getName()<<" is meaningless\n";
		system("pause");
	}
	else if(currentPlayer.isKeyExist(*t) == false)
	{
		cout <<"\nKey of the door does not exist in inventory\n";
		system("pause");
	}
	else
	{
		rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x,currentPlayer.loc().y).setType(EMPTY);
		switch(currentPlayer.getDirection())
		{
		case NORTH:
			currentPlayer.setRoom(currentPlayer.currRoom().x-1, currentPlayer.currRoom().y);
			currentPlayer.setLoc(3, currentPlayer.loc().y);
		break;
		case SOUTH:
			currentPlayer.setRoom(currentPlayer.currRoom().x+1, currentPlayer.currRoom().y);
			currentPlayer.setLoc(1, currentPlayer.loc().y);
		break;
		case EAST:
			currentPlayer.setRoom(currentPlayer.currRoom().x, currentPlayer.currRoom().y-1);
			currentPlayer.setLoc(currentPlayer.loc().x, 8);
		break;
		case WEST:
			currentPlayer.setRoom(currentPlayer.currRoom().x, currentPlayer.currRoom().y+1);
			currentPlayer.setLoc(currentPlayer.loc().x, 1);
		break;
		}
		rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x,currentPlayer.loc().y).setType(PLAYER);
	}
}
void Maze::display()
{
	system("cls");
	for(int row = 0; row<5; row++)
	{
		for(int line = 0; line < 5; line++)
		{
			if(line||row==0)
                cout<<"\t\t";
			for(int column = 0; column < 5; column++)
			{
				if(currentPlayer.currRoom().x == row && currentPlayer.currRoom().y == column)
					rooms[row][column].displayLine(line, row, column, true);
				else
					rooms[row][column].displayLine(line, row, column, false);
			}
			if(line||row==0)
                cout << "\n";
		}
	}
    cout << "Current Position: Room => ("<<currentPlayer.currRoom().x<<", "<<currentPlayer.currRoom().y<<")";
    cout << " | Direction: " << (char)currentPlayer.getDirection() << " | ";
    Object nextObj;
    switch(currentPlayer.getDirection())
    {
    case NORTH:
        nextObj = rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x-1, currentPlayer.loc().y);
    break;
    case SOUTH:
        nextObj = rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x+1, currentPlayer.loc().y);
    break;
    case EAST:
        nextObj = rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y-1);
    break;
    case WEST:
        nextObj = rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(currentPlayer.loc().x, currentPlayer.loc().y+1);
    break;
    }
    if(nextObj.getType() != EMPTY && nextObj.getType() != PLAYER)
        cout << nextObj.getEncounterText() << "\n";
    else if(nextObj.getType() == PLAYER)
        cout << "You are facing a person!\n";
    else
        cout <<"\n";
}
void Maze::checkEnd()
{
	if(gameStatus == LEFT)
		return;
	if(currentPlayer.currRoom().x == 4 && currentPlayer.currRoom().y == 4)
		gameStatus = WIN;
	else
	{
		for(int i = 1; i<=3; i++)
			for(int j = 1; j<=8; j++)
				if(rooms[currentPlayer.currRoom().x][currentPlayer.currRoom().y].getObjectAt(i, j).getType() == ENEMY)
					gameStatus = LOSE;
	}
}
