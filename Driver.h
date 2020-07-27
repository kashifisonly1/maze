#ifndef DRIVER_H
#define DRIVER_H
#include "Maze.h"

enum MenuCommands { START_NEW_GAME = 1, LOAD_PREVIOUS_GAME, GAME_DESCRIPTION, EXIT_APPLICATION };

void displayMainMenu();
void startApplication();
int inputNumber(int lowerLimit, int upperLimit);
void performMenuCommand(MenuCommands command);

#endif
