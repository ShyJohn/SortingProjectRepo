#pragma once
#include "SortAlgorithm.h"

class BubbleSorter : public SortAlgorithm
{

public:
	BubbleSorter() {}
	~BubbleSorter() {}

	bool Sort(sf::RectangleShape* line)
	{
		int numOfSwaps = 0;

		for (int i = 0; i < NUM_OF_LINES - 1; i++)
		{
			if (line[i].getSize().y > line[i + 1].getSize().y)
			{
				Swap(line, i, i + 1);
				// incremeent number of swaps
				numOfSwaps++;
			}
		}

		// return true when sorted
		if (numOfSwaps = 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};