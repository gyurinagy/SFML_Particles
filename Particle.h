#pragma once

#include <SFML/Graphics.hpp>


class Particle {

	sf::CircleShape* _cShape;
	sf::Vector2f _pos;
	sf::Vector2f _vel;
	sf::Vector2f _acc;

public:
	
	Particle(sf::Vector2f pos, float r = 1.f);
	~Particle();

	void drawTo(sf::RenderWindow& window);
	void move(sf::Vector2f distance);
	void moveTo(sf::Vector2f newPos);

	void step(sf::Vector2i mouse, float grav, float resistance);

	void explode(sf::Vector2i mouse, float expF);

};