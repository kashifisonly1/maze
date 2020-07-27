#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <stdlib.h>
using namespace std;
#include "Driver.h"

/*
	Description: This function is the starting point of application
*/
void startApplication()
{
	MenuCommands command;
	do
	{
		displayMainMenu();
		command = (MenuCommands)inputNumber(1, 4);
		performMenuCommand(command);
	}
	while ( command != EXIT_APPLICATION);

	cout << "\n\n\t\t--- GoodBye, See you again! ---\n";
}
/*
	This function is used to input number in a range
	@param[lowerLimit] => lower limit of number
	@param[upperLimit] => upper limit of the number
	Return => it will return number in given range
*/
int inputNumber(int lowerLimit, int upperLimit)
{
	int num;
	cout << "\nEnter Number Between " << lowerLimit << " and "<<upperLimit<<": ";
	cin>>num;
	while(num < lowerLimit || num > upperLimit || !cin.good())
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout<<"\nInvalid Number, Enter Number Between " << lowerLimit << " and "<<upperLimit<<": ";
		cin>>num;
	}
	return num;
}
/*
	this function perform menu operations
	@param[command] => command to perform
*/
void performMenuCommand(MenuCommands command)
{
	switch(command)
	{
	case START_NEW_GAME:
		Maze("maze.txt");
	break;
	case LOAD_PREVIOUS_GAME:
	{
	    string fname;
		cout << "Enter Your Name: ";
		cin >> fname;
		Maze(fname + ".txt");
	}
	break;
	case GAME_DESCRIPTION:
	{
	    system("cls");
	    ifstream fin("description.txt");
		cout << fin.rdbuf() << "\n";
		system("pause");
	}
	break;
	}
}
/*
	It will display Main Menu of the application
*/
void displayMainMenu()
{
	system("cls");
	cout << "\n\t\t--- Welcome to maze adventour game ---";
	cout << "\n[1] Start New Game.";
	cout << "\n[2] Load Previous Game.";
	cout << "\n[3] View Game Description.";
	cout << "\nExit Application.\n";
}
