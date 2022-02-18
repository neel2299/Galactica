#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
Eclass Game
{
public:
	sf::RenderWindow* window;
public:
   Game();
	virtual ~Game();
	//Functions
	void run();