#include "player.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Player::Player() {

}


void Player::initTexture(){

}


void Player::initSprite() {
	this->sprite.setTexture(this->texture);
}

Player::~Player() {
	this->initTexture();
	this->initSprite();

}


void Player::update() {

}


void Player::render(sf::RenderTarget& target) {
	
}