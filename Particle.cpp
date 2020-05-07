#pragma once

#include "Particle.h"

Particle::Particle(sf::Vector2f pos, float r ) :
	_cShape(new sf::CircleShape(r)), _pos(pos), _vel({ 0.f,0.f }), _acc({ 0.f,0.f })
{
	_cShape->setPosition(_pos);
}
Particle::~Particle() {
	delete _cShape;
}

void Particle::drawTo(sf::RenderWindow& window) {
	window.draw(*_cShape);
}

void Particle::move(sf::Vector2f distance) {
	_cShape->move(distance);
}
void Particle::moveTo(sf::Vector2f target) {
	_pos = target;
	_cShape->setPosition(_pos);
}


void Particle::step(sf::Vector2i mouse, float grav, float resistance)
{
	float r = sqrt(pow(mouse.x - _pos.x, 2) + pow(mouse.y - _pos.y, 2));

	_acc.x = ((mouse.x - _pos.x) /r) * grav;
	_acc.y = ((mouse.y - _pos.y) /r) * grav;

	_vel.x += _acc.x;
	_vel.y += _acc.y;

	if (_vel.x > 0) _vel.x -= pow(_vel.x, 2) * resistance;
	else if (_vel.x < 0)_vel.x += pow(_vel.x, 2) * resistance;

	if (_vel.y > 0) _vel.y -= pow(_vel.y, 2) * resistance;
	else if (_vel.y < 0)_vel.y += pow(_vel.y, 2) * resistance;

	_pos.x += _vel.x;
	_pos.y += _vel.y;

	moveTo(_pos);
}

void Particle::explode(sf::Vector2i mouse, float expF)
{
	float r = sqrt(pow(mouse.x - _pos.x, 2) + pow(mouse.y - _pos.y, 2));

	if (r != 0) {
		sf::Vector2i exp;
		exp.x = -((mouse.x - _pos.x) / r) * expF;
		exp.y = -((mouse.y - _pos.y) / r) * expF;

		_vel.x += exp.x;
		_vel.y += exp.y;
	}
}

