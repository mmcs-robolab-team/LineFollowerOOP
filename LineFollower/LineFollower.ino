#include "Car.h"

#define initSpeed 2

#define MOTOR_1_PWM 3
#define MOTOR_1_1 11
#define MOTOR_1_2 10

#define MOTOR_2_PWM 5
#define MOTOR_2_1 9
#define MOTOR_2_2 8

#define IR_1 6
#define IR_2 4
#define IR_3 7

Car car(initSpeed);

///////// Главная часть программы //////// 
void setup()
{
	Serial.begin(9600);
	car.AddEngine(Engine::LEFT, MOTOR_1_PWM, MOTOR_1_1, MOTOR_1_2, 125);
	car.AddEngine(Engine::RIGHT, MOTOR_2_PWM, MOTOR_2_1, MOTOR_2_2, 125);
	car.AddIR(IR::LEFT, IR_1);
	car.AddIR(IR::MIDDLE, IR_2);
	car.AddIR(IR::RIGHT, IR_3);
	car.Forward();
	delay(2000);
}

void loop()
{
	car.TrackLine();
	//delay(1);
}