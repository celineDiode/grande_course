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
				SERVO_SetAngle(SERVO1, speed+45);
			}
		break;

		case GAUCHE:
			{
				SERVO_SetAngle(SERVO2, speed+45);
			}
		break;

		case DEUX:
			{
				SERVO_SetAngle(SERVO1, speed+45);
				SERVO_SetAngle(SERVO2, speed+45);
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

void move_cm(short cm, short ticks_per_second)
{
	move_ticks((cm * TICK_PER_ROTATION) / CM_PER_ROTATION, ticks_per_second);
}

void move_ticks(short ticks, short ticks_per_second)
{
	short ticks_per_second_wanted = (ticks_per_second * TIMEOUT * SUBDIVISIONS) / 1000;

	short ticks_left = 0;
	short ticks_right = 0;

	short speed_left = 50;//ticks_per_second;
	short speed_right = 50;//ticks_per_second;

	ENCODER_Read(ENCODER_LEFT);
	ENCODER_Read(ENCODER_RIGHT);

	while(1)
	{
		MOTEUR_SetSpeed(GAUCHE,  speed_left);
		MOTEUR_SetSpeed(DROIT, speed_right);

		short progression_left = 0;
		short progression_right = 0;

		for(short i = 0; i < SUBDIVISIONS; i++)
		{
			THREAD_MSleep(TIMEOUT);

			int temp_left  = ENCODER_Read(ENCODER_LEFT);
			int temp_right = ENCODER_Read(ENCODER_RIGHT);

			progression_left  += temp_left;
			progression_right += temp_right;

			ticks_left  += temp_left;
			ticks_right += temp_right;

			if(ticks_left >= ticks || ticks_right >= ticks)
			{
				MOTEUR_SetSpeed(GAUCHE, 	0);
				MOTEUR_SetSpeed(DROIT, 0);

				//LCD_Printf("%d : %d-%d | ",ticks , ticks_left, ticks_right);

				return;
			}
		}

		speed_left  += (ticks_per_second_wanted - progression_left);
		speed_right += (ticks_per_second_wanted - progression_right);

		LCD_ClearAndPrint("%d_%d", speed_left, speed_right);
	}
}

void turn_degrees(short degrees, short speed)
{
	turn_ticks((degrees * CM_BETWEEN * PI * TICK_PER_ROTATION) / (CM_PER_ROTATION * 360), speed);
}

void turn_ticks(short ticks, short speed)
{
	short ticks_left = 0;
	short ticks_right = 0;

	ENCODER_Read(ENCODER_LEFT);
	ENCODER_Read(ENCODER_RIGHT);

	MOTEUR_SetSpeed(GAUCHE,  speed);
	MOTEUR_SetSpeed(DROIT, -speed);

	do
	{
		THREAD_MSleep(1);

		ticks_left  += ENCODER_Read(ENCODER_LEFT);
		ticks_right += ENCODER_Read(ENCODER_RIGHT);

		if(ticks_left >= ticks) {
			MOTEUR_SetSpeed(GAUCHE, 0);
		}

		if(ticks_right >= ticks) {
			MOTEUR_SetSpeed(DROIT, 0);
		}

	} while(ticks_left < ticks || ticks_right < ticks);

	MOTEUR_SetSpeed(GAUCHE, 	0);
	MOTEUR_SetSpeed(DROIT, 0);

	//LCD_Printf("%d : %d-%d\n",ticks , ticks_left, ticks_right);
}


void MOVE_Stop (void)
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

void MOVE_Resume (void)
{
	MOVE_data.stop = false;
	MOVE_data.targetMove = 0;
}

void MOVE_Avance (int distance)
{
	MOVE_data.targetMove = distance;
	MOVE_data.traveled = 0;
}

void MOVE_Tourner (int angle)
{
	MOVE_data.targetAngle = angle;
}

void* TASK_mouvement (void* a __attribute__((unused)))
{
	LCD_Printf("Mouvements : PRET\n");
	while (7==7)
	{
		if(!MOVE_data.stop)
		{
			//on avance et on comptabilise notre distance
			if(MOVE_data.traveled < MOVE_data.targetMove)
			{

			}
			else if (MOVE_data.targetAngle < MOVE_data.currentAngle)
			{

			}
		}
		THREAD_MSleep(50);
	}
	return NULL;
}


