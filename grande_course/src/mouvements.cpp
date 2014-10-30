// Include Files

#include "mouvements.h"
#include <math.h>
#define USE_SERVO 1

MOVE_data_t MOVE_data;


void MOTEUR_SetSpeed(motor_t motor, short speed)
{
#ifdef USE_SERVO
	//Oui, oui, 45 degres corresponds a une vitesse nulle, c'est la librairie qui suit pas la convention
	//de controle des servo moteurs

	if(speed >= -100 || speed <= 100)
	{
		switch(motor)
		{
		case DROIT:
			{
				SERVO_SetAngle(SERVO1, 45 + speed);
				MOVE_data.speed_right = speed;
			}
		break;

		case GAUCHE:
			{
				SERVO_SetAngle(SERVO2, 45 - speed);
				MOVE_data.speed_left = speed;
			}
		break;

		case DEUX:
			{
				MOTEUR_SetSpeed(DROIT, speed);
				MOTEUR_SetSpeed(GAUCHE, speed);
			}
		break;

		default:
			{
				LCD_Printf("ERREUR: MAUVAISE COMMANDE MOTEUR");
			}
			break;
		}
	}

	else
	{
		LCD_Printf("ERREUR: MAUVAISE VITESSE MOTEUR");
	}
#else
	MOTOR_SetSpeed(motor, speed);
#endif
}

void MOVE_Stop(void)
{
	MOVE_data.stop = true;
	if(MOVE_data.currentAngle != 0)
	{
		MOVE_data.total_traveled += MOVE_data.traveled*sin(MOVE_data.currentAngle);
	}
	else
	{
		MOVE_data.total_traveled += MOVE_data.traveled;
	}
	MOVE_data.toTravelAfterStop = (MOVE_data.traveled - MOVE_data.targetMove); //this might go unused
}

void MOVE_Resume(void)
{
	MOVE_data.stop = false;
	MOVE_data.targetMove = 0;
}

void MOVE_Avance(int ticks_per_second)
{
	MOVE_data.speed_move = ticks_per_second;

	MOVE_data.stop = 0;

	capteur.encodeurs.gauche = 0;
	capteur.encodeurs.droit  = 0;

	MOVE_data.distance_left  = 0;
	MOVE_data.distance_right = 0;

	MOVE_data.speed_left  = 50;
	MOVE_data.speed_right = 50;

	MOVE_data.ticks_per_second_wanted = (MOVE_data.speed_move * TIMEOUT) / 1000;
}

void MOVE_Tourner(int angle)
{
	MOVE_data.targetAngle = angle;
}

void* TASK_mouvement(void* a __attribute__((unused)))
{
	LCD_Printf("Mouvements : PRET\n");

	MOVE_Avance(40);

	while(1)
	{
		//on avance et on comptabilise notre distance
		if(MOVE_data.speed_rotate)
		{
			LCD_Printf("TOURNER");
			THREAD_MSleep(50);
			//MOTEUR_SetSpeed(GAUCHE, 50);
			//MOTEUR_SetSpeed(DROIT, -50);
		}
		else if(MOVE_data.speed_move)
		{
			MOTEUR_SetSpeed(GAUCHE, MOVE_data.speed_left);
			MOTEUR_SetSpeed(DROIT,  MOVE_data.speed_right);

			THREAD_MSleep(TIMEOUT);

			LCD_ClearAndPrint("%d += (%d + %d - %d)\n", MOVE_data.speed_left, MOVE_data.ticks_per_second_wanted, MOVE_data.distance_left, capteur.encodeurs.gauche);
			LCD_Printf("%d += (%d + %d - %d)\n", MOVE_data.speed_right, MOVE_data.ticks_per_second_wanted, MOVE_data.distance_right, capteur.encodeurs.droit);

			MOVE_data.speed_left  += (MOVE_data.ticks_per_second_wanted + MOVE_data.distance_left  - capteur.encodeurs.gauche);
			MOVE_data.speed_right += (MOVE_data.ticks_per_second_wanted + MOVE_data.distance_right - capteur.encodeurs.droit);

			MOVE_data.distance_left  = capteur.encodeurs.gauche;
			MOVE_data.distance_right = capteur.encodeurs.droit;
		}
		else
		{
			MOTEUR_SetSpeed(DEUX, 0);
			THREAD_MSleep(50);
		}
		//THREAD_MSleep(50);
	}
	return NULL;
}
