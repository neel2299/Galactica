#pragma once
#include "Ship.h"
#include "Bullet.h"
#include "Stone.h"
#include<string>
#include<sstream>
#include<map>
/*class that acts as game engine
*/
class Game
{
private:
	//variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	//resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	//gui
	sf::Font font;
	sf::Text pointtext;
	sf::Text gameOverText;
	//world
	sf::Texture worldBackgroungTex;
	sf::Texture worldBackgroungTex2;
	sf::Sprite worldBackground;
	//system
	unsigned points;
	//ship object initialization
	Ship* ship;
	//ship healthbar
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;
	//Stones
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Stone*> stones;
	

	//functions
	void initVariables();
	void initWindow();
	void initTextures();
	void initGUI();
	void initSystems();
	void initWorld();
	void initShip();
	void initStones();

public:

	Game();
	virtual ~Game();
	//fumctions
	void run();
	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void updateWorld();
	void updateCollision();

	void update();
	void renderWorld();
	void renderGUI();
	void render();
	/*
		void Game::update() {
		this->updateInput(); //makes inppu to sjiop 
		this->updateBullets();
		this->ship->update();
		this->updateCollision();
		this->updateEnemies();
		this->updateCombat();
		this->updateWorld();
		this->updateGUI();
	*/


};

