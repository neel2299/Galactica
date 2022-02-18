// Application1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Game.h"
#include<time.h>

int main()
{
    //init game engine
    srand(time(0));

    Game game;

    game.run();

     return 0;
    }