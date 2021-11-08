#include "Player.h"

Player :: Player(String file, float x, float y, float w, float h)
{
	this->file = file;
	this->hight = h;
	this->width = w;
	image.loadFromFile("gamedev\\" + this->file);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	this->x = x;
	this->y = y;
	sprite.setTextureRect(IntRect(0, 0, this->width, this->hight));
}
void Player::update(float time)
{
	switch (direction)
	{
	case 0: dx = -speed, dy = 0; break;
	case 1: dx = speed, dy = 0; break;
	case 2: dx = 0, dy = -speed; break;
	case 3: dx = 0, dy = speed; break;
	}

	x += dx * time;
	y += dy * time;

	speed = 0;
	sprite.setPosition(x, y);
}
float Player::GetPlayerCoordinateX() { return x; };
float Player::GetPlayerCoordinateY() { return y; };