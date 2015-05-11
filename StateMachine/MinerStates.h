#pragma once

#include "State.h"
#include "Miner.h"

#include <string>

const float dt = 0.016f;

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
			Agent->setStamina(fStamina + (1 * dt));
		} else
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
private:
	float fDestination;

public:
	WalkToMine(float Destination)
		:
		fDestination(Destination)
	{}

	void OnEnter(Miner* Agent)
	{
		Agent->setDestination(fDestination);
	}

	void Update(Miner* Agent)
	{
		float fPosition = Agent->getPosition();

		if ( fPosition >= Agent->getDestination())
			Agent->ChangeState();
		else
			Agent->setPosition(fPosition + (50 * dt));
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
		float fLoad = Agent->getLoad();
		float fStamina = Agent->getStamina();

		if ( fStamina <= 0 || fLoad >= Agent->getMaxLoad())
			Agent->ChangeState();
		else
		{
			Agent->setStamina(fStamina - (1 * dt));
			Agent->setLoad(fLoad + (1 * dt));
		}
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
private:
	float fDestination;

public:
	WalkToHome(float Destination)
		:
		fDestination(Destination)
	{
	}

	void OnEnter(Miner* Agent)
	{
		Agent->setDestination(fDestination);
	}

	void Update(Miner* Agent)
	{
		float fPosition = Agent->getPosition();

		if (fPosition <= Agent->getDestination())
			Agent->ChangeState();
		else
			Agent->setPosition(fPosition - (50 * dt));
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
		float fLoad = Agent->getLoad();

		if (fLoad > 0)
		{
			Agent->setLoad(fLoad - (1*dt));
		} else
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