#pragma once

#include "IR.h"
#include "Car.h"

using StateCallbackPtr = void (Car::*)();

class FSM
{
public:
	enum IR_ENABLED
	{
		IR_NONE = 0,
		IR_RIGHT = IR::RIGHT,
		IR_MIDDLE = IR::MIDDLE,
		IR_MIDDLE_RIGHT = IR::MIDDLE + IR::RIGHT,
		IR_LEFT = IR::LEFT,
		IR_LEFT_RIGHT = IR::LEFT + IR::RIGHT,
		IR_LEFT_MIDDLE = IR::LEFT + IR::MIDDLE,
		IR_ALL = IR::LEFT + IR::MIDDLE + IR::RIGHT
	};
	static const size_t signalCount = 8;

	enum State
	{
		ST_FORWARD,
		ST_BACKWARD,
		ST_TURN_LEFT,
		ST_TURN_RIGHT,
		ST_CROSSROADS
	};
	static const size_t stateCount = 5;

	enum State TransitionTable[stateCount][signalCount] = 
	{
		TransitionTable[ST_FORWARD][IR_LEFT] = ST_TURN_LEFT,
		TransitionTable[ST_FORWARD][IR_RIGHT] = ST_TURN_RIGHT,
		TransitionTable[ST_FORWARD][IR_NONE] = ST_BACKWARD,
		TransitionTable[ST_FORWARD][IR_MIDDLE] = ST_FORWARD,

	};

	FSM(StateCallbackPtr ForwardCallback, StateCallbackPtr BackwardCallback, StateCallbackPtr TurnLeftCallback, StateCallbackPtr TurnRightCallback, StateCallbackPtr CrossroadsCallback);
	void nextState(IR_ENABLED sig);
private:
	State curState;
	StateCallbackPtr callbacks[stateCount];
};