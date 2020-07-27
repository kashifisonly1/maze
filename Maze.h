#ifndef MAZE_H
#define MAZE_H
#include "Player.h"
#include "Room.h"

enum GameCommands { SAVE, EXIT, TALK, MOVE, 
		LOOK, OPEN, EXAMINE, INVENTORY, HELP, GET, UNLOCK, NONE };
enum GameStatus { CONTINUE, WIN, LOSE, LEFT };

class Maze
{
private:
	Room rooms[5][5]; // for storing actual maze of 5*5
	Player currentPlayer; // for dealing with player movements
	GameStatus gameStatus; // to store current game status

public:
	Maze(string fname);

	void loadFileData(ifstream& fin);
	void startGame();
	GameCommands inputCommand();
	void executeCommand(GameCommands);

	void performSaveWork();
	void performExitWork();
	void performTalkWork();
	void performMoveWork();
	void performLookWork();
	void performExamineWork();
	void performOpenWork();
	void performGetWork();
	void performUnlockWork();
	void display();
	void checkEnd();
};

#endif