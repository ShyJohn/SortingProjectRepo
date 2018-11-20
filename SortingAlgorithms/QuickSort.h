#pragma once

#include "SortAlgorithm.h"

class QuickSorter : public SortAlgorithm
{
public:

	bool Sort(sf::RectangleShape* line, int size)
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

	void Partition(sf::RectangleShape* line, int size, std::shared_ptr<int> lower, std::shared_ptr<int> upper)
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
	}
};