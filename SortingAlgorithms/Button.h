#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Button : public sf::Sprite
{
	
private: 


public:
	Button(std::string s, sf::Vector2f _pos)
	{
		tex.loadFromFile(s);
		setPosition(_pos);
		setTexture(tex);
		
	}

	~Button() {};
	sf::Texture tex;
	bool Hover(sf::Window &w)
	{
		float wx = sf::Mouse::getPosition(w).x;
		float wy = sf::Mouse::getPosition(w).y;

		if (wx < getPosition().x) return false;
		if (wx > (getPosition().x + getGlobalBounds().width)) return false;
		if (wy < getPosition().y) return false;
		if (wy > (getPosition().y + getGlobalBounds().height)) return false;
		return true;

	}

};