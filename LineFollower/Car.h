#pragma once

#include "Engine.h"
#include "IR.h"
#include "Arduino.h"

#define MAX_ENGINE_COUNT 2
#define MAX_IR_COUNT 3

class Car
{
public:
	Car(byte initialSpeed) { engCount = irCount = 0; this->initialSpeed = speed = initialSpeed; };

	void Forward();
	void Backward();
	void Stop();
	void Turn(int angle);
	void Run(int curspeed);


	void AddEngine(Engine::EngineType type, byte pin_PWM, byte pin_dir1, byte pin_dir2, int speedLowBorder);
	void AddIR(IR::IR_Type type, byte pin);

	void TrackLine();
private:
	byte speed, initialSpeed;
	Engine engines[MAX_ENGINE_COUNT];
	IR IRs[MAX_IR_COUNT];
	byte engCount;
	byte irCount;

	byte getIR_Values();

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
};


