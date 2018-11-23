#ifndef _APPLICATION_H_
#define _APPLICATION_H_

// SFML Includes
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

// C++ includes
#include <algorithm>
#include <iostream>
#include <memory>
#include <Windows.h>
#include <thread>
#include <sstream>

// Custom includes
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
	void ToggleButton(bool &s);
	bool CheckBubbleFinished();

	LPVOID mainFiber;

	// CAMERA
	sf::View camera;

	// ARRAY OF LINE SHAPES
	sf::RectangleShape line[NUM_OF_LINES];
	sf::RectangleShape line2[NUM_OF_LINES];

	// ARRAY OF X POSITIONS FOR LINE SHAPES
	float positions[NUM_OF_LINES];
	float positions2[NUM_OF_LINES];

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
	std::unique_ptr<Button> addThreadButton;
	std::unique_ptr<Button> minusThreadButton;
	sf::Text threadNumber;
	sf::Text threadText;
	sf::Font font;

	// HELPERS
	Helpers helpers;

	// VARIABLES
	bool bubbleStarted;
	bool insertionStarted;
	int numberOfThreads;
	int numberOfThreads2;

	std::vector<std::thread> bubbleThreads;

public:
	// CONSTRUCTOR
	Application(sf::RenderWindow& windowref) : window(windowref) {}

	// SFML WINDOW
	sf::RenderWindow& window;

	// PUBLIC FUNCTIONS
	void Init();
	void Update();
	void BubbleSort(sf::RectangleShape* line, int rangeStart, int rangeEnd);
	void InsertionSort();

};
#endif
