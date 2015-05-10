#pragma once

#include "Miner.h"

template<typename T>
class State
{
	protected:
		virtual State<T>* OnExit(T*) = 0;
		virtual void setState(State*) = 0;
		virtual void Update(T*) = 0;
		virtual void OnEnter(T*) = 0;
		virtual ~State() {}
};

class Idle : public State<Miner>
{
	State *nextState;

	public:
		void setState(State *nextState) 
		{ 
			this->nextState = nextState;
		}
		
		State* OnExit(Miner* Agent)
		{
			return this->nextState;
		}
		
		void Update(Miner* Agent)
		{
			float fStamina = Agent->getStamina() + 1;
			Agent->setStamina(fStamina);

			if ( fStamina > 0 )
				Agent->ChangeState();
		}
		
		void OnEnter(Miner* Agent)
		{
		}
};

class WalkToMiner : public State<Miner>
{
	private:
		State *nextState;
		//Vector2 Destination;
	
	public:
		void setState(State *nextState)
		{
			this->nextState = nextState;
		}

		State* OnExit(Miner* Agent)
		{
			return this->nextState;
		}

		void Update(Miner* Agent)
		{
			float fPosition = Agent->getPosition() + 1;
			Agent->setPosition(fPosition);

			if (Agent->getPosition == Agent->getDestination)
				Agent->ChangeState();
		}

		void OnEnter(Miner* Agent)
		{
			Agent->setDestination(5);
		}
};

class Mining : public State<Miner>
{
private:
	State *nextState;
	float maxLoad;

public:
	void setState(State *nextState)
	{
		this->nextState = nextState;
	}

	State* OnExit(Miner* Agent)
	{
		return this->nextState;
	}

	void Update(Miner* Agent)
	{
		float fLoad = Agent->getLoad() + 1;
		float fStamina = Agent->getStamina() - 1;
		Agent->setStamina(fStamina);
		Agent->setLoad(fLoad);

		if ( fStamina <= 0 || fLoad == Agent->getMaxLoad() )
			Agent->ChangeState();
	}

	void OnEnter(Miner* Agent)
	{
	}
};

class WalkToHome : public State<Miner>
{
private:
	State *nextState;
	//Vector2 Destination;

public:
	void setState(State *nextState)
	{
		this->nextState = nextState;
	}

	State* OnExit(Miner* Agent)
	{
		return this->nextState;
	}

	void Update(Miner* Agent)
	{
		float fPosition = Agent->getPosition() - 1;
		Agent->setPosition(fPosition);

		if (fPosition == Agent->getDestination)
			Agent->ChangeState();
	}

	void OnEnter(Miner* Agent)
	{
		Agent->setDestination(0);
	}
};

