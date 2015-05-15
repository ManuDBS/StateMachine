#include "MinerStates.h"
#include "Miner.h"
#include "StateMachine.h"

#include <conio.h>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

const float maxStamina = 5.0f;
const int maxLoad = 5;

// Set true for debug
const bool bDebug = true;

int main()
{
	sf::Clock myClock;
	sf::RenderWindow window(sf::VideoMode(600, 600), "The Miner");

	// Setup Home 
	sf::Vector2f vSizeHome(50.0f, 50.0f); // Size
	sf::Vector2f vPositionHome(0, 300.0f - (vSizeHome.y/2)); // Position
	sf::RectangleShape shapeHome(vSizeHome);
	shapeHome.setFillColor(sf::Color::Green);
	shapeHome.setPosition(vPositionHome);

	// Setup Mine
	sf::Vector2f vSizeMine(50.0f, 50.0f); // Size
	sf::Vector2f vPositionMine(600.0f-vSizeMine.x, 300.0f - (vSizeMine.y / 2)); // Position
	sf::RectangleShape shapeMine(vSizeMine);
	shapeMine.setFillColor(sf::Color::White);
	shapeMine.setPosition(vPositionMine);

	// Setup Miner
	sf::Vector2f vSizeMiner(25.0f, 25.0f); // Size
	sf::Vector2f vPositionMiner(vSizeHome.x, 300.0f - (vSizeMiner.y / 2)); // Position
	sf::RectangleShape shapeMiner(vSizeMiner);
	shapeMiner.setFillColor(sf::Color::Red);
	shapeMiner.setPosition(vPositionMiner);

	// Setup Text
	sf::Font myFont;
	myFont.loadFromFile("resources/myFont.ttf");
	sf::Text textState;
	textState.setFont(myFont);
	textState.setCharacterSize(30);
	textState.setColor(sf::Color::White);
	sf::Vector2f vPositionText(10, 560);
	textState.setPosition(vPositionText);

	//------ Setup State Machine 
	Miner* myMiner = new Miner(maxStamina, maxLoad);
	Idle* stateIdle = new Idle();
	float fDistance = vPositionMine.x - vPositionHome.x - vSizeHome.x - vSizeMiner.x;
	WalkToMine* stateWalkToMiner = new WalkToMine(fDistance);
	Mining* stateMining = new Mining();
	WalkToHome* stateWalkToHome = new WalkToHome(0);
	DropLoad* stateDropLoad = new DropLoad();
	// Set State
	stateIdle->setNextState(stateWalkToMiner);
	stateWalkToMiner->setNextState(stateMining);
	stateMining->setNextState(stateWalkToHome);
	stateWalkToHome->setNextState(stateDropLoad);
	stateDropLoad->setNextState(stateIdle);
	// Set State Machine
	StateMachine<Miner> myStateMachine(myMiner, stateIdle);
	myMiner->setStateMachine(myStateMachine);
	//------ End Setup State Machine 

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		// Draw Home and Mine
		window.draw(shapeHome);
		window.draw(shapeMine);
		
		if (bDebug)
		{
			// ------ Debug
			system("cls");
			std::cout << "Actual State : " << myMiner->getStateName() << std::endl;
			std::cout << "Stamina : " << myMiner->getStamina() << std::endl;
			std::cout << "Max Stamina : " << myMiner->getMaxStamina() << std::endl;
			std::cout << "Load : " << myMiner->getLoad() << std::endl;
			std::cout << "MaxLoad : " << myMiner->getMaxLoad() << std::endl;
			std::cout << "Position : " << myMiner->getPosition() << std::endl;
			std::cout << "Destination : " << myMiner->getDestination() << std::endl;
			// ------ End Debug
		}

		// Draw Miner
		sf::Time myTime = myClock.getElapsedTime();
		myMiner->Update(myTime.asSeconds());
		myClock.restart();
		
		sf::Vector2f moving(myMiner->getPosition(), 0);
		shapeMiner.setPosition(vPositionMiner.x + myMiner->getPosition(), shapeMiner.getPosition().y);
		window.draw(shapeMiner);

		// Draw Text
		textState.setString("Stato: " + myMiner->getStateName());
		window.draw(textState);

		window.display();
	}

	return 0;
}
