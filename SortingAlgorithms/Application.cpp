#include "Application.h"


void Application::Init()
{
	// INITIALISE UI
	resetButton = std::make_unique<Button>("res/ResetButton.png", sf::Vector2f(40.0f, 40.0f));
	bubbleButton = std::make_unique<Button>("res/BubbleButton.png", sf::Vector2f(160.0f, 40.0f));
	insertionButton = std::make_unique<Button>("res/InsertionButton.png", sf::Vector2f(280.0f, 40.0f));
	quickSortButton = std::make_unique<Button>("res/QuickSortButton.png", sf::Vector2f(400.0f, 40.0f));

	// CREATE SORTER POINTERS
	bubbleSorter = std::make_shared<BubbleSorter>();
	insertionSorter = std::make_shared<InsertionSorter>();
	quickSorter = std::make_shared<QuickSorter>();

	// INIT CAMERA
	camera.reset(sf::FloatRect(window.getSize().x, window.getSize().y, window.getSize().x, window.getSize().y));
	camera.setCenter(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

	
	// GIVE POSITIONS TO POSITION ARRAY
	for (int i = 0; i < NUM_OF_LINES; i++)
	{
		positions[i] = i * LINE_WIDTH;
	}

	// CREATE LINE SHAPES AND PUT INTO ARRAY
	for (int i = 0; i < NUM_OF_LINES; i++)
	{
		line[i] = sf::RectangleShape(sf::Vector2f(LINE_WIDTH, i));
	}
	
	// INITIALISE LINE POSITIONS
	for (int i = 0; i < NUM_OF_LINES; i++)
	{
		line[i].setPosition(sf::Vector2f(i * LINE_WIDTH, (window.getSize().y / 2) - i / 2));
	}

	// FIRST SHUFFLE
	ShuffleArray();

	// INITIALISE STATE MACHINE
	currentSortState = NONE;
}


void Application::Update()
{
	//Sleep(500);

	// STATE MACHINE
	if (currentSortState == BUBBLE)
	{
		// SORT ARRAY
		// IF SORTED, CHANGE STATE TO IDLE
		if (bubbleSorter->Sort(line))
		{
			currentSortState = NONE;
		}		
	}
	else if(currentSortState == INSERTION)
	{
		// SORT ARRAY
		// IF SORTED, CHANGE STATE TO IDLE
		if (insertionSorter->Sort(line))
		{
			currentSortState = NONE;
		}
	}
	else if (currentSortState == QUICKSORT)
	{
		if (quickSorter->Sort(line, NUM_OF_LINES))
		{
			currentSortState = NONE;
		}
	}
	
	// HANDLE ALL INPUT IN FUNCTION
	HandleInput();
	// RENDER UI
	Render();
}

void Application::ShuffleArray()
{
	// SHUFFLE ARRAY OF LINES
	std::random_shuffle(std::begin(line), std::end(line));
	// UPDATE POSITIONS ON SCREEN
	UpdatePositions();
}

void Application::UpdatePositions()
{
	// RESET UI POSITIONS
	for (int i = 0; i < NUM_OF_LINES; i++)
	{
		line[i].setPosition(sf::Vector2f(i * LINE_WIDTH, line[i].getPosition().y));
	}
}

void Application::Render()
{
	// CLEAR SCREEN
	window.clear();
	
	// DRAW ALL LINES
	for (int i = 0; i < NUM_OF_LINES; i++)
	{
		window.draw(line[i]);
	}

	// DRAW UI
	window.draw(*resetButton);
	window.draw(*bubbleButton);
	window.draw(*insertionButton);
	window.draw(*quickSortButton);

	
	// DISPLAY ON SCREEN
	window.display();

}

void Application::HandleInput()
{

	// IF MOUSE OVER RESET BUTTON..
	if (resetButton->Hover(window))
	{
		// IF MOUSE CLICKED,
		// SET STATE MACHINE TO IDLE
		// SHUFFLE ARRAY
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !helpers.mouseClicked)
		{
			helpers.mouseClicked = true;
			currentSortState = NONE;
			ShuffleArray();
		}
		
	}
	// IF MOUSE OVER BUBBLE BUTTON..
	else if (bubbleButton->Hover(window))
	{
		// IF MOUSE CLICKED,
		// SET STATE MACHINE TO IDLE
		// SHUFFLE ARRAY
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !helpers.mouseClicked)
		{
			helpers.mouseClicked = true;
			currentSortState = BUBBLE;
		}
	}
	// IF MOUSE OVER INSERTION BUTTON..
	else if (insertionButton->Hover(window))
	{
		// IF MOUSE CLICKED,
		// SET STATE MACHINE TO IDLE
		// SHUFFLE ARRAY
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !helpers.mouseClicked)
		{
			helpers.mouseClicked = true;
			insertionSorter->counter = 0;
			currentSortState = INSERTION;
		}
	}

	// IF MOUSE OVER QUICK SORT BUTTON..
	else if (quickSortButton->Hover(window))
	{
		// IF MOUSE CLICKED,
		// SET STATE MACHINE TO IDLE
		// SHUFFLE ARRAY
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !helpers.mouseClicked)
		{
			helpers.mouseClicked = true;
			currentSortState = QUICKSORT;
		}
	}

	// SET MOUSE UP
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		helpers.mouseClicked = false;


}