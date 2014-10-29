/*
============================================================================
 Name : grande_course.cpp
 Author :
 Version :
 Description : Hello world - Exe source file
============================================================================
*/

// Include Files

#include <libarmus.h>
#include <stdint.h>
// Global Functions


int main()
{
	LCD_Printf("Hello World!\n");

	SERVO_Enable(SERVO1);
	SERVO_Enable(SERVO2);
	SERVO_SetAngle(SERVO1,0);
	SERVO_SetAngle(SERVO2,75);


	return 0;
}
