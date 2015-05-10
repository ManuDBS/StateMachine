#pragma once

#include "State.h"

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
			ActualState = ActualState->OnExit(Agent);
			ActualState->OnEnter(Agent);
		}
		
		void Update()
		{
			ActualState->Update(Agent);
		}
};