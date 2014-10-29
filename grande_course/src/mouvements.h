/*
 * mouvements.h
 *
 *  Created on: 2014-10-23
 *      Author: thor4_000
 */

#include <libarmus.h>

#ifndef MOUVEMENTS_H_
#define MOUVEMENTS_H_


typedef struct{
	int traveled ;
	int targetMove ;
	int total_traveled ;
	int targetAngle ;
	int currentAngle ;
	bool stop ;
	int toTravelAfterStop ;
	int horizontalTravel ;
}MOVE_data_t;

extern MOVE_data_t MOVE_data;

const short PAUSE = 500;
const short TIMEOUT = 25;//50;
const short SUBDIVISIONS = 20;//10;
const short TICK_PER_ROTATION = 64;
const short CM_PER_ROTATION = 24;
const float PI = 3.1415926535897932384626;
const float CM_BETWEEN = 13.8;//14.0;

enum motor_t{GAUCHE, DROIT, DEUX};

void MOTEUR_SetSpeed(motor_t motor, short speed);

void move_cm(short cm, short ticks_per_second);

void move_ticks(short ticks, short ticks_per_second);

void turn_degrees(short degrees, short speed);

void turn_ticks(short ticks, short speed);

void* TASK_mouvement (void* a);

void MOVE_Stop (void);
void MOVE_Resume (void);
void MOVE_Avance (int distance);
void MOVE_Tourner (int angle);

#endif /* MOUVEMENTS_H_ */
