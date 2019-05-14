#pragma once
#include "SortAlgorithm.h"

class InsertionSorter : public SortAlgorithm

{

public:
	InsertionSorter() {
		counter = 0;
	}
	~InsertionSorter() {}

	bool Sort(sf::RectangleShape* line)
	{
		if (++counter < NUM_OF_LINES)
		{
			Insert(line);
		}
		else
		{
			counter = 0;
			return true;
		}
		return false;
	}

	void Insert(sf::RectangleShape* line)
	{
		int j = counter;
		while (j > 0 && line[j].getSize().y < line[j - 1].getSize().y)
		{
			Swap(line, j, j-1);
			j = j - 1;
		}
	}
};