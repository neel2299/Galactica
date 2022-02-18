#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
class Ship
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	float movementSpeed;
	float attackCooldown;
	float attackCooldownMax;
	int hp;
	int hpMax;

	//function
	void initVariables();
	void initTexture();
	void initsprite();
public:
	
	Ship();
	virtual ~Ship();
	//accessor
	const sf::Vector2f& getpos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;
	//modifier
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int Hp);
	void loosehp(const int value);
	//function
	void move(const float dirX, const float dirY);
	const bool canAttack() ;
	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};

