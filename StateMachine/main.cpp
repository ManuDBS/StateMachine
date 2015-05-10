#include "Miner.h"
#include <iostream>

//PROVA FABIO

void main()
{
	Miner* myMiner = new Miner(5.0f, 5.0f);

	Idle* stateIdle = new Idle();
	WalkToMiner* stateWalkToMiner = new WalkToMiner();
	Mining* stateMining = new Mining();
	WalkToHome* stateWalkToHome = new WalkToHome();
	
	stateIdle->setState(stateWalkToMiner);
	stateWalkToMiner->setState(stateMining);
	stateMining->setState(stateWalkToHome);
	stateWalkToHome->setState(stateIdle);

	StateMachine<Miner> myStateMachine(myMiner, stateIdle);

	std::getchar();
}