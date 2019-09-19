/***********************************************
 *  Module:OS
 *
 *  File Name:main.c
 *
 *  Description: OS application
 *
 *  Created on: 2019-09-16
 *  Author: AbdElkader
 ***********************************************/
#include "OS.h"
void Task1(void)
{
	PORTB ^=(1<<4);
	//Delete_Task(Task3); /*in case you need to test Delete_Task*/

}
void Task2(void)
{
	PORTB ^=(1<<5);
}
void Task3(void)
{
	PORTB ^=(1<<6);
}

int main(void)
{
	DIO_SetPinDirection(PinB4,HIGH);
	DIO_SetPinDirection(PinB5,HIGH);
	DIO_SetPinDirection(PinB6,HIGH);
	DIO_SetPinDirection(PinB7,HIGH);
	DIO_SetPinDirection(PinA0,HIGH);
	DIO_SetPinDirection(PinA1,HIGH);
	DIO_WritePin(PinB4,LOW);
	DIO_WritePin(PinB5,LOW);
	DIO_WritePin(PinB6,LOW);
	OS_init();
	Create_Task(Task1,1,1000,1000);
	Create_Task(Task2,2,2000,2000);
	Create_Task(Task3,3,3000,3000);
	OS_Run();
	return 0;
}
