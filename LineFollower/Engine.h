#pragma once

#include "Arduino.h"

class Engine
{
public: 
	enum EngineType
	{
		RIGHT = -1, 
		MIDDLE = 0,
		LEFT = 1
	};
	
	Engine() {};
	Engine(EngineType type, byte pin_PWM, byte pin_dir1, byte pin_dir2, int speedLowBorder);
	
	void Set_speed(int spd_in_percent);
	void Forward();
	void Backward();
	void Stop();

	int getSpeed() { return spd; }

	EngineType GetType() { return type; };
private:
	int speedLowBorder, spd;
	int pin_PWM, pin_dir1, pin_dir2;
	EngineType type;

	void Analog_speed(int spd);
};







