#pragma once

#include "SortAlgorithm.h"

class QuickSorter : public SortAlgorithm
{
public:

	int lower;
	int upper;
	int pi;

	QuickSorter()
	{
		lower = 0;
		upper = NUM_OF_LINES-1;
	}
	bool Sort(sf::RectangleShape* line, int lower, int upper)
	{

		if (lower < upper)
		{
			pi = Partition(line, lower, upper);

			Sort(line, lower, pi - 1);
			Sort(line, pi + 1, upper);
		}
		else
			return true;
		return false;
	}

	/*bool Sort(sf::RectangleShape* line, int size)
	{
		std::shared_ptr<int> lower = std::make_shared<int>(0);
		std::shared_ptr<int> upper = std::make_shared<int>(size - 1);

		if (*lower < *upper)
		{
			Partition(line, size, lower, upper);
			return false;
		}

		return true;
	}
	*/

	int Partition(sf::RectangleShape* line, int lower, int upper)
	{
		float pivot = line[upper].getSize().y;

		int i = (lower - 1);

		for (int j = lower; j < upper - 1; j++)
		{
			if (line[j].getSize().y <= pivot)
			{
				i++;
				Swap(line, i, j);
			}
		}

		Swap(line, i + 1, upper);
		return (i + 1);
	}
	/*void Partition(sf::RectangleShape* line, int size, std::shared_ptr<int> lower, std::shared_ptr<int> upper)
	{
		if (size < 2)
			return;

		float pivot = line[rand() % size-1].getSize().y;

		while (*lower < *upper)
		{
			while (line[*lower].getSize().y < pivot)
			{
				*lower = *lower + 1;
			}
			while (line[*upper].getSize().y > pivot)
			{
				*upper = *upper - 1;
			}
			Swap(line, *lower, *upper);
			Partition(line, *lower, lower, upper);
			std::cout << "OIOIOI" << std::endl;
			Partition(&line[*lower + 1], size - *lower - 1, lower, upper);
		}
	}*/
};