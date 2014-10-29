// Include Files

#include "mouvements.h"
#include <math.h>


MOVE_data_t data;


void MOTEUR_SetSpeed(motor_t motor, short speed)
{
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
		MOTOR_SetSpeed(MOTOR_LEFT,  speed_left);
		MOTOR_SetSpeed(MOTOR_RIGHT, speed_right);

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
				MOTOR_SetSpeed(MOTOR_LEFT, 	0);
				MOTOR_SetSpeed(MOTOR_RIGHT, 0);

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

	MOTOR_SetSpeed(MOTOR_LEFT,  speed);
	MOTOR_SetSpeed(MOTOR_RIGHT, -speed);

	do
	{
		THREAD_MSleep(1);

		ticks_left  += ENCODER_Read(ENCODER_LEFT);
		ticks_right += ENCODER_Read(ENCODER_RIGHT);

		if(ticks_left >= ticks) {
			MOTOR_SetSpeed(MOTOR_LEFT, 0);
		}

		if(ticks_right >= ticks) {
			MOTOR_SetSpeed(MOTOR_RIGHT, 0);
		}

	} while(ticks_left < ticks || ticks_right < ticks);

	MOTOR_SetSpeed(MOTOR_LEFT, 	0);
	MOTOR_SetSpeed(MOTOR_RIGHT, 0);

	//LCD_Printf("%d : %d-%d\n",ticks , ticks_left, ticks_right);
}


void MOVE_Stop (void)
{
	data.stop = true;
	if(data.currentAngle != 0)
	{
		data.total_traveled += data.traveled*sin(data.currentAngle);
	}
	else
	{
		data.total_traveled += data.traveled;
	}
	data.toTravelAfterStop = (data.traveled - data.targetMove); //this might go unused
}

void MOVE_Resume (void)
{
	data.stop = false;
	data.targetMove = 0;
}

void MOVE_Avance (int distance)
{
	data.targetMove = distance;
	data.traveled = 0;
}

void MOVE_Tourner (int angle)
{
	data.targetAngle = angle;
}

void TASK_mouvement (void)
{
	while (7==7)
	{
		if(!data.stop)
		{
			//on avance et on comptabilise notre distance
			if(data.traveled < data.targetMove)
			{

			}
			else if (data.targetAngle < data.currentAngle)
			{

			}
		}
	}
}


