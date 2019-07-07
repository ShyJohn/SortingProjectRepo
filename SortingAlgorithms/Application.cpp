#include "Application.h"


/*void OnButtonPress(int, int)
{
	std::function<void(void* x, bool y)> onPress_;
}


void Funct(std::function<void(int x, bool y)> funct)
{
	//funct();
}
*/

void Application::Init()
{
	//Funct(std::bind(&Application::Init, this));

	//button->setOn([]() {});
	//Funct([this](int x, bool y) {
	//	quickSorter
	//});

	
	if (!font.loadFromFile("res/arial.ttf"))
	{
		// error...
		std::cout << "Error loading font" << std::endl;
	}

	// INITIALISE UI
	Button* resetButton = new Button("res/ResetButton.png", sf::Vector2f(1510.0f, 10.0f));
	Button* bubbleButton = new Button("res/BubbleButton.png", sf::Vector2f(1510.0f, 60.0f));
	Button* insertionButton = new Button("res/InsertionButton.png", sf::Vector2f(1510.0f, 110.0f));
	Button* quickSortButton = new Button("res/QuickSortButton.png", sf::Vector2f(1510.0f, 160.0f));
	Button* addThreadButton = new Button("res/AddButton.png", sf::Vector2f(1400.0f, 20.0f));
	Button* minusThreadButton = new Button("res/MinusButton.png", sf::Vector2f(1400.0f, 70.0f));
	threadText.setFont(font);
	threadText.setString("Threads:");
	threadText.setPosition(1220.0f, 40.0f);
	threadNumber.setFont(font);
	threadNumber.setPosition(1350.0f, 40.0f);

	// CREATE SORTER POINTERS
	bubbleSorter = std::make_shared<BubbleSorter>();
	insertionSorter = std::make_shared<InsertionSorter>();
	quickSorter = std::make_shared<QuickSorter>();
	
	//bubbleStarted = std::make_shared<bool>();
	//insertionStarted = std::make_shared<bool>();
	bubbleStarted = false;
	insertionStarted = false;
	numberOfThreads = 8;
	numberOfThreads2 = 1;

	// INIT CAMERA
	camera.reset(sf::FloatRect(window.getSize().x, window.getSize().y, window.getSize().x, window.getSize().y));
	camera.setCenter(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

	//mainFiber = ConvertThreadToFiber(NULL);
	
	// GIVE POSITIONS TO POSITION ARRAY
	for (int i = 0; i < NUM_OF_LINES; i++)
	{
		positions[i] = i * LINE_WIDTH;
		positions2[i] = i * LINE_WIDTH;
	}

	sf::Color colour(255, 255, 255);

	// CREATE LINE SHAPES AND PUT INTO ARRAY
	for (int i = 0; i < NUM_OF_LINES; i++)
	{
		line[i] = sf::RectangleShape(sf::Vector2f(LINE_WIDTH, i));
		line2[i] = sf::RectangleShape(sf::Vector2f(LINE_WIDTH, i));
		line[i].setOutlineColor(colour);
	}
	
	// INITIALISE LINE POSITIONS
	for (int i = 0; i < NUM_OF_LINES; i++)
	{
		line[i].setPosition(sf::Vector2f(i * LINE_WIDTH, 0.0f));
		line2[i].setPosition(sf::Vector2f(i * LINE_WIDTH, (window.getSize().y / 2)));
	}

	// FIRST SHUFFLE
	ShuffleArray();

	// INITIALISE STATE MACHINE
	currentSortState = NONE;
}


void Application::Update()
{
	// STATE MACHINE
	if (bubbleStarted)
	{
		// SORT ARRAY
		// IF SORTED, CHANGE STATE TO IDLE
		for (int i = 0; i < numberOfThreads; i++)
		{
			int difference = (NUM_OF_LINES / numberOfThreads);
			int rangeStart = i * difference;
			int rangeEnd = rangeStart + difference;

			std::thread bubbleThread(&Application::BubbleSort, this, line, 0, NUM_OF_LINES);
			bubbleThread.join();

		}

		for (int i = 0; i < numberOfThreads2; i++)
		{
			int difference = (NUM_OF_LINES / numberOfThreads);
			int rangeStart = i * difference;
			int rangeEnd = rangeStart + difference;

			std::thread bubbleThread(&Application::BubbleSort, this, line2, 0, NUM_OF_LINES);
			bubbleThread.join();
		}

	}

	if(insertionStarted)
	{
		// SORT ARRAY
		// IF SORTED, CHANGE STATE TO IDLE
		std::thread insertionThread(&Application::InsertionSort, this);
		insertionThread.join();
	}
	else if (currentSortState == QUICKSORT)
	{
		/*if (quickSorter->Sort(line, quickSorter->lower, quickSorter->upper, std::bind(&Application::Render, this), std::bind(&Application::HandleInput, this)))
		{
			std::cout << "Sorted" << std::endl;
			currentSortState = NONE;
		}*/
	}
	
	//std::stringstream s;
	//s << numberOfThreads;
	//threadNumber.setString(s.str().c_str());

	// HANDLE ALL INPUT IN FUNCTION
	HandleInput();
	// RENDER UI
	Render();
}

bool Application::CheckBubbleFinished()
{
	return true;
}
void Application::BubbleSort(sf::RectangleShape* line, int rangeStart, int rangeEnd)
{
	if (bubbleSorter->Sort(line, rangeStart, rangeEnd))
	{
		//currentSortState = NONE;
		bubbleStarted = false;
	}
}
void Application::InsertionSort()
{
	if (insertionSorter->Sort(line2))
	{
		currentSortState = NONE;
	}
}

void Application::ToggleButton(bool &s)
{
	if (s)
		s = false;
	else
		s = true;
}
void Application::ShuffleArray()
{
	// SHUFFLE ARRAY OF LINES
	std::random_shuffle(std::begin(line), std::end(line));
	std::random_shuffle(std::begin(line2), std::end(line2));

	// UPDATE POSITIONS ON SCREEN
	UpdatePositions();
}

void Application::UpdatePositions()
{
	// RESET UI POSITIONS
	for (int i = 0; i < NUM_OF_LINES; i++)
	{
		line[i].setPosition(sf::Vector2f(i * LINE_WIDTH, line[i].getPosition().y));
		line2[i].setPosition(sf::Vector2f(i * LINE_WIDTH, line2[i].getPosition().y));
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
		window.draw(line2[i]);
	}

	// DRAW UI
	window.draw(*resetButton);
	window.draw(*bubbleButton);
	window.draw(*insertionButton);
	window.draw(*quickSortButton);
	window.draw(*addThreadButton);
	window.draw(*minusThreadButton);
	window.draw(threadNumber);
	window.draw(threadText);

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
			bubbleStarted = false;
			insertionStarted = false;
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
			ToggleButton(bubbleStarted);
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
			ToggleButton(insertionStarted);
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
	// IF MOUSE OVER QUICK SORT BUTTON..
	else if (addThreadButton->Hover(window))
	{
		// IF MOUSE CLICKED,
		// SET STATE MACHINE TO IDLE
		// SHUFFLE ARRAY
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !helpers.mouseClicked)
		{
			helpers.mouseClicked = true;
			if(numberOfThreads < 8)
				numberOfThreads++;
		}
	}
	else if (minusThreadButton->Hover(window))
	{
		// IF MOUSE CLICKED,
		// SET STATE MACHINE TO IDLE
		// SHUFFLE ARRAY
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !helpers.mouseClicked)
		{
			helpers.mouseClicked = true;
			if(numberOfThreads > 1)
				numberOfThreads--;
		}
	}
	// SET MOUSE UP
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		helpers.mouseClicked = false;


}