#include "MinerStates.h"
#include "Miner.h"
#include "StateMachine.h"

#include <conio.h>
#include <iostream>
#include <string>

const float maxStamina = 5.0f;
const int maxLoad = 5;

/*
void main()
{

	Miner* myMiner = new Miner(maxStamina, maxLoad);

	Idle* stateIdle = new Idle();
	WalkToMine* stateWalkToMiner = new WalkToMine();
	Mining* stateMining	= new Mining();
	WalkToHome* stateWalkToHome	= new WalkToHome();
	DropLoad* stateDropLoad = new DropLoad();
	
	stateIdle->setNextState(stateWalkToMiner);
	stateWalkToMiner->setNextState(stateMining);
	stateMining->setNextState(stateWalkToHome);
	stateWalkToHome->setNextState(stateDropLoad);
	stateDropLoad->setNextState(stateIdle);

	StateMachine<Miner> myStateMachine(myMiner, stateIdle);
	myMiner->setStateMachine(myStateMachine);

	char exit;
	int iteration = 0;
	do
	{
		//DEBUG--------------------------------------------------------------------//
		system("cls");																//
		std::cout << "Iteration number : " << iteration << std::endl;				//
		std::cout << "Actual State : " << myMiner->getStateName() << std::endl;		//
		std::cout << "Stamina : " << myMiner->getStamina() << std::endl;			//
		std::cout << "Max Stamina : " << myMiner->getMaxStamina() << std::endl;		//
		std::cout << "Load : " << myMiner->getLoad() << std::endl;					//
		std::cout << "MaxLoad : " << myMiner->getMaxLoad() << std::endl;			//
		std::cout << "Position : " << myMiner->getPosition() << std::endl;			//
		std::cout << "Destination : " << myMiner->getDestination() << std::endl;	//
		//END DEBUG----------------------------------------------------------------//

		myMiner->Update();

		++iteration;
		exit = _getch();
	} while (exit != 'y');

	
}
*/

#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "The Miner");
	window.setFramerateLimit(60); // FPS Limit to 60

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
		
		// Draw Miner
		myMiner->Update();
		sf::Vector2f moving(myMiner->getPosition(), 0);
		shapeMiner.setPosition(vPositionMiner.x + myMiner->getPosition(), shapeMiner.getPosition().y);
		window.draw(shapeMiner);
		
		window.display();
	}

	return 0;
}
