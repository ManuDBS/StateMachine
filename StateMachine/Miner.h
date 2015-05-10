#pragma once

#include "StateMachine.h"

// Per ogni update del framework chiamo l'update della statemachine

class Miner
{
	private:
		//Vector2 position;
		//Vector2 destination;
		float fStamina;
		float fLoad; // number of stone
		float fMaxLoad;
		float fPosition; // only for debug
		float fDestination; // only for debug
		StateMachine<Miner> myStateMachine;

	public:
		Miner(float Stamina, float MaxLoad)
			: 
			fStamina(Stamina),
			fMaxLoad(MaxLoad)
		{
			//position = Vector2(0, 0);
			//destination = Vector2(0, 0);
			this->fLoad = 0;
			this->fPosition = 0;
			this->fDestination = 0; // home
		}

		/*const Vector2& getPosition() const
		{
			return position;
		}*/

		/*const Vector2& getDestination() const
		{
			return destination;
		}*/
		
		float getStamina() const
		{
			return fStamina;
		}
		float getLoad() const
		{
			return fLoad;
		}
		float getMaxLoad() const
		{
			return fMaxLoad;
		}
		float getPosition() const
		{
			return fPosition;
		}
		float getDestination() const
		{
			return fDestination;
		}
		
		void setStateMachine(StateMachine<Miner>& StateMachine)
		{
			this->myStateMachine = StateMachine;
		}

		void setStamina(float fStamina)
		{
			this->fStamina = fStamina;
		}
		void setPosition(float fPosition)
		{
			this->setPosition = fPosition;
		}
		void setDestination(float fDestination)
		{
			this->setDestination = fDestination;
		}
		void setLoad(float fLoad)
		{
			this->fLoad = fLoad;
		}

		void ChangeState() 
		{
			myStateMachine.ChangeState();
		}

		~Miner() {}
};
