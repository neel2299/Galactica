#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
class Bullet
{private:
	sf::Sprite shape;
	sf::Texture* texture;
	sf::Vector2f direction;
	float movement_Speed=0;
public:
	Bullet();
	Bullet(sf::Texture *texture,float pos_x,float pos_y, float dirX, float dirY, float movement_Speed ); //pointer texture
	virtual ~Bullet();
	//accessor
	const sf::FloatRect getBounds() const;
	void update();
	void render(sf::RenderTarget* target);
};

