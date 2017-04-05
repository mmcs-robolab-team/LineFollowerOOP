#include "Car.h"

void Car::Forward()
{
	for (size_t i = 0; i < engCount; i++)
		engines[i].Forward();
}

void Car::Backward()
{
	for (size_t i = 0; i < engCount; i++)
		engines[i].Backward();
}

void Car::Run(int curspeed)
{
	for (size_t i = 0; i < engCount; i++)
	{
		engines[i].Set_speed(curspeed);
		Serial.print("Speed ");
		Serial.print(i);
		Serial.print(" on run ");
		Serial.println(engines[i].getSpeed());
	}
}

void Car::Stop()
{
	for (size_t i = 0; i < engCount; i++)
		engines[i].Stop();
}

void Car::Turn(int angle)
{
	Engine::EngineType curtype = (angle > 0) ? Engine::LEFT : Engine::RIGHT;
	for (size_t i = 0; i < engCount; i++)
	{
		if (engines[i].GetType() == curtype)
		{
			engines[i].Set_speed(0);
			//Serial.println(engines[i].GetType());
		}
		else
			engines[i].Set_speed(speed);

		auto s = String("Speed");
		s += i;
		s += " on turn ";
		s += engines[i].getSpeed();

		//Serial.print("Speed ");
		//Serial.print(i);
		//Serial.print(" on turn ");
		//Serial.println(engines[i].getSpeed());
		Serial.println(s);
	}
	//Serial.println();
	//delayMicroseconds((int)(100 * abs(angle) / 45.0));
	//Serial.println((int)(100 * angle / 45.0));

	//for (size_t i = 0; i < engCount; i++)
	//{
	//	engines[i].Set_speed(speed);
	//	Serial.print("Speed ");
	//	Serial.print(i);
	//	Serial.print(" after turn ");
	//	Serial.println(engines[i].getSpeed());
	//}
	//Serial.println();
}

void Car::AddEngine(Engine::EngineType type, byte pin_PWM, byte pin_dir1, byte pin_dir2, int speedLowBorder)
{
	engines[engCount++] = Engine(type, pin_PWM, pin_dir1, pin_dir2, speedLowBorder);
	//engines[engCount++].Forward();
	//Serial.println(engCount);
}

void Car::AddIR(IR::IR_Type type, byte pin)
{
	IRs[irCount++] = IR(type, pin);
}

void Car::TrackLine
()
{
	bool turnDir = true;
	int absTurnValue = 10;
	byte state = getIR_Values();
	Serial.print("Cur state = ");
	Serial.println(state);
	switch (state)
	{
		case IR_NONE:
		{
			Forward();
			if (turnDir)
			{
				Turn(-5);
				Turn(5);
			}
			else
			{
				Turn(5);
				Turn(-5);
			}
			turnDir = !turnDir;

			//Run(speed);
			//Backward();
			//speed = initialSpeed;
			break;
		}
		case IR_RIGHT:
		{
			//Run(speed);
			Turn(-absTurnValue);
			break;
		}
		case IR_MIDDLE:
		{
			Forward();
			Run(speed);

			if (turnDir)
			{
				Turn(-5);
				Turn(5);
			}
			else
			{
				Turn(5);
				Turn(-5);
			}
			turnDir = !turnDir;

			//speed++;
			break;
		}
		case IR_MIDDLE_RIGHT:
		{
			Run(speed);
			//Turn(-absTurnValue/2);
			break;
		}
		case IR_LEFT:
		{
			//Run(speed);
			Turn(absTurnValue);
			break;
		}
		case IR_LEFT_RIGHT:
		{
			Stop();
			//Backward();
			break;
		}
		case IR_LEFT_MIDDLE:
		{
			Run(speed);
			//Turn(absTurnValue/2);
			break;
		}
		case IR_ALL:
		{
			Forward();
			Run(speed);
			break;
		}
	}
}

byte Car::getIR_Values()
{
	byte res = 0;
	for (int i = 0; i < irCount; i++)
		res += IRs[i].get_IR();
	return res;
}
