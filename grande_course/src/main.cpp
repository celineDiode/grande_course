/*
============================================================================
 Name : grande_course.cpp
 Author :
 Version :
 Description : Hello world - Exe source file
============================================================================
*/

// Include Files

#include "main.h"

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
		LCD_ClearAndPrint("R:%i  G:%i  B:%i\n",capteur.couleur.rouge,capteur.couleur.vert,capteur.couleur.bleu);
		LCD_Printf("Distance CM: %d",capteur.distance.distance1);
		THREAD_MSleep(50);
	}

	return 0;
}

