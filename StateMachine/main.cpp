#include "MinerStates.h"
#include "Miner.h"
#include "StateMachine.h"

#include <conio.h>
#include <iostream>
#include <string>

const float stamina = 4.0f;
const float maxLoad = 5;

void main()
{

	Miner* myMiner = new Miner(stamina, maxLoad);

	Idle*		stateIdle			= new Idle();
	WalkToMine* stateWalkToMiner	= new WalkToMine();
	Mining*		stateMining			= new Mining();
	WalkToHome* stateWalkToHome		= new WalkToHome();
	DropLoad*	stateDropLoad		= new DropLoad();
	
	stateIdle			->		setNextState(stateWalkToMiner);
	stateWalkToMiner	->		setNextState(stateMining);
	stateMining			->		setNextState(stateWalkToHome);
	stateWalkToHome		->		setNextState(stateDropLoad);
	stateDropLoad		->		setNextState(stateIdle);

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