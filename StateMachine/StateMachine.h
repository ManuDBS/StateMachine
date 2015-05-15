#pragma once

#include "State.h"

#include <string>

template <typename T>
class StateMachine
{
	private:
		T* Agent;
		State<T>* actualState;
	
	public:
		StateMachine() {}
		StateMachine(T* otherAgent, State<T>* otherActualState)
			:
			Agent(otherAgent),
			actualState(otherActualState)
		{
		}

		void ChangeState()
		{
			actualState = actualState->OnExit(Agent);
			actualState->OnEnter(Agent);
		}
		
		void Update(float dt)
		{
			actualState->Update(dt, Agent);
		}

		std::string getStateName() const
		{
			return actualState->getName();
		}
};