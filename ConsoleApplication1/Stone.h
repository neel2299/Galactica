#pragma once
#include <SFML/Graphics.hpp>
class Stone
{
private:
	sf::CircleShape shape;
	int hp;
	int hpMax;
	float speed;
	int damage;
	unsigned pointCount;
	int points;
	void initVariables();
	void initShape();
public:
	Stone(float pos_x,float pos_y);
	virtual ~Stone();

	//accessor
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	//functions
	void update();
	void render(sf:: RenderTarget* target);

};

