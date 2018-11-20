#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <memory>
#include <Windows.h>
#include "Button.h"
#include "Helpers.h"
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"

enum CurrentSortState{BUBBLE, INSERTION, QUICKSORT, NONE};
class Application {

private: 
	
	// FUNCTIONS
	void Render();
	void ShuffleArray();
	void UpdatePositions();
	void HandleInput();

	// CAMERA
	sf::View camera;

	// ARRAY OF LINE SHAPES
	sf::RectangleShape line[NUM_OF_LINES];

	// ARRAY OF X POSITIONS FOR LINE SHAPES
	float positions[NUM_OF_LINES];

	// STATE MACHINE ENUM
	CurrentSortState currentSortState;

	// SORTERS
	std::shared_ptr<BubbleSorter> bubbleSorter;
	std::shared_ptr<InsertionSorter> insertionSorter;
	std::shared_ptr<QuickSorter> quickSorter;

	// UI
	std::unique_ptr<Button> resetButton;
	std::unique_ptr<Button> bubbleButton;
	std::unique_ptr<Button> insertionButton;
	std::unique_ptr<Button> quickSortButton;

	// HELPERS
	Helpers helpers;

public:
	// CONSTRUCTOR
	Application(sf::RenderWindow& windowref) : window(windowref) {}

	// SFML WINDOW
	sf::RenderWindow& window;
	
	// PUBLIC FUNCTIONS
	void Init();
	void Update();
};
#endif
