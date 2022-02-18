#include "Ship.h"

void Ship::initTexture()
{
	//load texture from file here
	if (!this->texture.loadFromFile("Textures/PngItem_188897.png"))
	{
		std::cout << "Error::player::could not load texture file";
	}
}

void Ship::initVariables()
{
	this->movementSpeed = 4.f;
	this->attackCooldownMax = 12.f;
	this->attackCooldown = this->attackCooldownMax;
	this->hpMax = 100;
	this->hp = this->hpMax;

}

void Ship::initsprite()
{//set texture to sprite
	this->sprite.setTexture(this->texture);
	//Resize the sprit
	this->sprite.scale(0.06f, 0.06f);

}
Ship::Ship()
{
	this->initVariables();
	this->initTexture();
	this->initsprite();
}

Ship::~Ship()
{
}

//functions

const sf::Vector2f& Ship::getpos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Ship::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Ship::getHp() const
{
	return this->hp;
}

const int& Ship::getHpMax() const
{
	return this->hpMax;
}

void Ship::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}
void Ship::setPosition(const float x, const float y) {
	this->sprite.setPosition(x, y);
}

void Ship::setHp(const int Hp)
{
	this->hp = Hp;
}

void Ship::loosehp(const int value)
{
	this->hp -= value;
	if (this->hp < 0) {
		this->hp = 0;
	}
}

void Ship::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed*dirX , this->movementSpeed*dirY);
}

const bool Ship::canAttack()
{
	if (this->attackCooldown>= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
     }
	return false;
}

void Ship::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

void Ship::update()
{
	this->updateAttack();

}

void Ship::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
