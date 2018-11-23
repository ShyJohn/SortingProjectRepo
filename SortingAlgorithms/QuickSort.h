#pragma once

#include "SortAlgorithm.h"
#include <functional>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class QuickSorter : public SortAlgorithm
{
//public:
//
//	int lower;
//	int upper;
//	int pi;
//
//	LPVOID sortFiber;
//
//	QuickSorter()
//	{
//		lower = 0;
//		upper = NUM_OF_LINES-1;
//		sortFiber = CreateFiber(0, &QuickSorter::RunFiber, this);
//	}
//
//	~QuickSorter() {}
//
//	sf::RectangleShape* line;
//	int lower, upper;
//
//	void RunForRect(sf::RectangleShape* line, int lower, int upper)
//	{
//		this->line = line;
//		this->lower = lower;
//		this->upper = upper;
//		SwitchToFiber(sortFiber);
//	}
//
//	static VOID WINAPI RunFiber(LPVOID quickSort)
//	{
//		auto sort = reinterpret_cast<QuickSorter*>(quickSort);
//		sort->Sort(sort->line, sort->lower, sort->upper);
//	}
//
//	bool Sort(sf::RectangleShape* line, int lower, int upper, std::function<void()> render, std::function<void()> handleInput)
//	{
//		std::cout << "lower: " << lower << std::endl;
//		std::cout << "upper: " << upper << std::endl;
//
//		if (lower < upper)
//		{
//			pi = Partition(line, lower, upper, render, handleInput);
//
//			Sort(line, lower, pi - 1, render, handleInput);
//			SwitchToFiber(mainFiber);
//			Sort(line, pi + 1, upper, render, handleInput);
//		}
//		
//		if (lower == 0 && upper == NUM_OF_LINES - 1)
//			return true;
//		return false;
//
//		
//	}
//
//	int Partition(sf::RectangleShape* line, int lower, int upper, std::function<void()> render, std::function<void()> handleInput)
//	{
//		float pivot = line[upper].getSize().y;
//
//		int i = (lower - 1);
//
//		for (int j = lower; j <= upper - 1; j++)
//		{
//			if (line[j].getSize().y <= pivot)
//			{
//				i++;
//				Swap(line, i, j);
//				render();
//				handleInput();
//			}
//		}
//
//		Swap(line, i + 1, upper);
//		return (i + 1);
//	}
};