#pragma once

#include "StateMachine.h"

#include <string>

// Per ogni update del framework chiamo l'update della statemachine

class Miner
{
	private:
		//Vector2 position;
		//Vector2 destination;
		float fStamina;
		const float fMaxStamina;
		float iLoad; // number of stone
		const int iMaxLoad;
		float fPosition; // only for debug
		float fDestination; // only for debug
		StateMachine<Miner> myStateMachine;

	public:
		Miner(float MaxStamina, int MaxLoad)
			: 
			fMaxStamina(MaxStamina),
			iMaxLoad(MaxLoad)
		{
			//position = Vector2(0, 0);
			//destination = Vector2(0, 0);
			this->fStamina = 0;
			this->iLoad = 0;
			this->fPosition = 0;
			this->fDestination = 0; // home
		}
		
		float getStamina() const
		{
			return fStamina;
		}
		float getMaxStamina() const
		{
			return fMaxStamina;
		}
		float getLoad() const
		{
			return iLoad;
		}
		int getMaxLoad() const
		{
			return iMaxLoad;
		}
		float getPosition() const
		{
			return fPosition;
		}
		float getDestination() const
		{
			return fDestination;
		}
		void setStateMachine(const StateMachine<Miner>& StateMachine)
		{
			this->myStateMachine = StateMachine;
		}
		void setStamina(float fStamina)
		{
			this->fStamina = fStamina;
		}
		void setPosition(float fPosition)
		{
			this->fPosition = fPosition;
		}
		void setDestination(float fDestination)
		{
			this->fDestination = fDestination;
		}
		void setLoad(float iLoad)
		{
			this->iLoad = iLoad;
		}

		void Update(float dt)
		{
			myStateMachine.Update(dt);
		}
		void ChangeState() 
		{
			myStateMachine.ChangeState();
		}

		std::string getStateName() const
		{
			return myStateMachine.getStateName();
		}

		~Miner() {}
};
