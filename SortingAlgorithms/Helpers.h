#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define NUM_OF_LINES 400
#define LINE_WIDTH 3

class Helpers
{

public:

	bool mouseClicked;

	sf::Texture LoadTexture(const std::string filename)
	{
		sf::Texture tex;
		tex.loadFromFile(filename);
		return tex;
	}
	
};