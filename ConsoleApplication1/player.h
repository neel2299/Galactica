#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
class Player
{
private:
	sf::Sprite sprite; //game assests are called sprite
	sf::Texture texture;

	void initTexture();
	void initSprite();
public:
	Player();
	virtual ~Player();


	void update();
	void render(sf::RenderTarget& target);

};

