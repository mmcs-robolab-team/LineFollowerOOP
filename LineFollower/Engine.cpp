#include "Engine.h"

Engine::Engine(EngineType type, byte pin_PWM, byte pin_dir1, byte pin_dir2, int speedLowBorder)
{
	this->pin_PWM = pin_PWM;
	this->pin_dir1 = pin_dir1;
	this->pin_dir2 = pin_dir2;
	this->speedLowBorder = speedLowBorder;
	this->type = type;
	this->spd = 0;

	pinMode(pin_PWM, OUTPUT);
	pinMode(pin_dir1, OUTPUT);
	pinMode(pin_dir2, OUTPUT);
}

void Engine::Forward()
{
	digitalWrite(pin_dir1, LOW);
	digitalWrite(pin_dir2, HIGH);
}

void Engine::Backward()
{
	digitalWrite(pin_dir1, HIGH);
	digitalWrite(pin_dir2, LOW);
}

void Engine::Set_speed(int spd_in_percent)
{
	spd = speedLowBorder + (int)(round(spd_in_percent*(255 - speedLowBorder) / 100.0));
	if (spd_in_percent == 0)
		Analog_speed(0);
	else
		Analog_speed(speedLowBorder + (int)(round(spd_in_percent*(255-speedLowBorder)/100.0)));
}

void Engine::Analog_speed(int spd)
{
	if (spd > 255) spd = 255;
	if (spd < 0) spd = 0;
	analogWrite(pin_PWM, spd);
}

void Engine::Stop()
{
	Analog_speed(0);
}