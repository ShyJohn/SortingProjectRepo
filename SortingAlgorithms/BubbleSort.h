#pragma once
#include "SortAlgorithm.h"

class BubbleSorter : public SortAlgorithm
{

public:
	BubbleSorter() {}
	~BubbleSorter() {}

	bool Sort(sf::RectangleShape* line, int rangeStart, int rangeEnd)
	{
		int numOfSwaps = 0;

		for (int i = rangeStart; i < rangeEnd - 1; i++)
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