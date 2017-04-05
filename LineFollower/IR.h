#pragma once

#include "Arduino.h"

class IR
{
public:
	enum IR_Type
	{
		RIGHT = 1,
		MIDDLE = 2, 
		LEFT = 4
	};

	IR() {};
	IR(IR_Type type, byte pin);

	byte get_IR();

private:
	byte pin;
	IR_Type type;
};


