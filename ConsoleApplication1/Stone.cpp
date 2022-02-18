#include "Stone.h"

void Stone::initVariables()
{
	this->pointCount = rand() % 15 + 4;   //min=3, max=10
	this->damage = this->pointCount;
	this->points = this->pointCount;
	this->speed = static_cast<float>(this->pointCount/4);
	this->hp = this->hpMax;
	this->hpMax = static_cast<int>(this->pointCount);
}  

void Stone::initShape()
{
	this->shape.setRadius(this->pointCount*4);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 254 + 1, rand() % 254 + 1, rand() % 254 + 1, 255));
}



Stone::Stone(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
}

Stone::~Stone()
{

}

const sf::FloatRect Stone::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Stone::getPoints() const
{
	return this->points;
}

const int& Stone::getDamage() const
{
	return this->damage;
}

//function 
void Stone::update()
{
	this->shape.move(0.f, this->speed);
}

void Stone::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
