#include "FSM.h"

FSM::FSM(StateCallbackPtr ForwardCallback, StateCallbackPtr BackwardCallback, StateCallbackPtr TurnLeftCallback, StateCallbackPtr TurnRightCallback, StateCallbackPtr CrossroadsCallback)
{
	curState = ST_FORWARD;
	callbacks[ST_FORWARD] = ForwardCallback;
	callbacks[ST_BACKWARD] = BackwardCallback;
	callbacks[ST_TURN_LEFT] = TurnLeftCallback;
	callbacks[ST_TURN_RIGHT] = TurnRightCallback;
	callbacks[ST_CROSSROADS] = CrossroadsCallback;
}



void FSM::nextState(IR_ENABLED sig)
{
	curState = TransitionTable[curState][sig];
	callbacks[curState]();
}
