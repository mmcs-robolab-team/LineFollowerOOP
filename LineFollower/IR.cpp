#include "IR.h"

IR::IR(IR_Type type, byte pin)
{
	this->pin = pin;
	this->type = type;

	pinMode(pin, INPUT);
}

byte IR::get_IR()
{
	return digitalRead(pin) * type;
}