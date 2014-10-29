/*
============================================================================
 Name : grande_course.cpp
 Author :
 Version :
 Description : Hello world - Exe source file
============================================================================
*/

// Include Files

#include "libarmus.h"
#include "stdint.h"
#include "mouvements.h"
#include "contourne_obstacle.h"
#include "sensors.h"
#include "state_machine.h"

// Global Functions
void* test (void* a);
void tata (void);

int main()
{
	LCD_ClearAndPrint("Depart\n");

	pthread_t thread_capteurs;
	pthread_create(&thread_capteurs, NULL, &lireCapteurs, NULL);

	pthread_t thread_movements;
	pthread_create(&thread_capteurs, NULL, &TASK_mouvement, NULL);

	pthread_t thread_machine_etat;
	pthread_create(&thread_capteurs, NULL, &TASK_state_machine, NULL);

	while(1)
	{
		ENCODER_Read(ENCODER_LEFT);
		ENCODER_Read(ENCODER_RIGHT);
		THREAD_MSleep(50);
	}

	return 0;
}

void tata (void)
{
	LCD_ClearAndPrint("");
		while (1)
		{
			LCD_Printf("toto");

			THREAD_MSleep(500);
		}

}

void* test (void* a)
{
	LCD_ClearAndPrint("");
	while (1)
	{
		LCD_Printf("test");

		THREAD_MSleep(500);
	}
	return NULL;
}
