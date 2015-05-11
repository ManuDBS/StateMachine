#pragma once

#include <string>

template<typename T>
class State
{
	public:

		void setNextState(State<T>* nextState)
		{
			this->nextState = nextState;
		}

		State<T>* getNextState(T*)
		{
			return this->nextState;
		}

		virtual ~State() {}

		virtual void OnEnter(T*) = 0;
		virtual void Update(T*) = 0;
		virtual State<T>* OnExit(T*) = 0;
		virtual std::string getName() const = 0;

	private:

		State<T>* nextState;
};

