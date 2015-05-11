#pragma once

#include "State.h"
#include "Miner.h"

#include <string>

class Idle : public State<Miner>
{

public:

	void OnEnter(Miner* Agent)
	{
	}

	void Update(Miner* Agent)
	{
		float fStamina = Agent->getStamina();

		if (fStamina < Agent->getMaxStamina())
		{
			Agent->setStamina(fStamina + 1);
		}
		else
		{
			Agent->ChangeState();
		}

	}

	State* OnExit(Miner* Agent)
	{
		return getNextState(Agent);
	}

	std::string getName() const
	{
		return std::string("Idle");
	}
};

class WalkToMine : public State<Miner>
{

public:

	void OnEnter(Miner* Agent)
	{
		Agent->setDestination(5);
	}

	void Update(Miner* Agent)
	{
		float fPosition = Agent->getPosition() + 1;
		Agent->setPosition(fPosition);

		if (fPosition >= Agent->getDestination())
			Agent->ChangeState();
	}

	State<Miner>* OnExit(Miner* Agent)
	{
		return getNextState(Agent);
	}

	std::string getName() const
	{
		return std::string("WalkToMine");
	}

};

class Mining : public State<Miner>
{

public:

	void OnEnter(Miner* Agent)
	{
	}

	void Update(Miner* Agent)
	{
		int iLoad = Agent->getLoad() + 1;
		float fStamina = Agent->getStamina() - 1;
		Agent->setStamina(fStamina);
		Agent->setLoad(iLoad);

		if (fStamina <= 0 || iLoad == Agent->getMaxLoad())
			Agent->ChangeState();
	}

	State<Miner>* OnExit(Miner* Agent)
	{
		return getNextState(Agent);
	}

	std::string getName() const
	{
		return std::string("Mining");
	}

};

class WalkToHome : public State<Miner>
{

public:

	void OnEnter(Miner* Agent)
	{
		Agent->setDestination(0);
	}

	void Update(Miner* Agent)
	{
		float fPosition = Agent->getPosition() - 1;
		Agent->setPosition(fPosition);

		if (fPosition <= Agent->getDestination())
			Agent->ChangeState();
	}

	State<Miner>* OnExit(Miner* Agent)
	{
		return this->getNextState(Agent);
	}

	std::string getName() const
	{
		return std::string("WalkToHome");
	}

};

class DropLoad : public State<Miner>
{

	void OnEnter(Miner* Agent)
	{
	}

	void Update(Miner* Agent)
	{
		int iLoad = Agent->getLoad();

		if (iLoad > 0)
		{
			Agent->setLoad(iLoad - 1);
		}
		else
		{
			Agent->ChangeState();
		}
	}

	State<Miner>* OnExit(Miner* Agent)
	{
		return this->getNextState(Agent);
	}

	std::string getName() const
	{
		return std::string("DropLoad");
	}

};