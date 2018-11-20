#pragma once
#include <algorithm>
#include "Helpers.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class SortAlgorithm
{

public:
	SortAlgorithm() {}
	~SortAlgorithm() {}
	int counter;
	virtual bool Sort() {
		return false;
	};
	void Swap(sf::RectangleShape* line, int i1, int i2)
	{
		std::swap(line[i1], line[i2]);
		float tempx = line[i1].getPosition().x;
		line[i1].setPosition(sf::Vector2f(line[i2].getPosition().x, line[i1].getPosition().y));
		line[i2].setPosition(sf::Vector2f(tempx, line[i2].getPosition().y));
	}
	
};