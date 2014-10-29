/*
 * state_machine.cpp
 *
 *  Created on: 2014-10-28
 *      Author: thor4_000
 */

#include "state_machine.h"


void* TASK_state_machine (void* a)
{
	states_t etat = DEPART;
	LCD_Printf("Machine a etat : PRET\n");

	while(1)
	{
		switch(etat)
		{
		case DEPART:
			{

			}
			break;

		case ATTEINDRE_LIGNE_ROUGE:
			{
				if(capteur.couleur.rouge > 4545)//TODO mettre une vraie valeur
				{
					etat = SUIVRE_LIGNE_ROUGE;
				}
			}
			break;

		case SUIVRE_LIGNE_ROUGE:
			{
				if(MOVE_data.total_traveled >= 34534) //TODO mettre une vrai valeur
				{
					etat = ALLER_CENTRE;
				}
			}
			break;

		case ALLER_CENTRE:
			{
				if(capteur.couleur.bleu > 2342)//TOOD mettre une vraie valeur
				{
					etat = GARDER_CENTRE;
				}
			}
			break;

		case GARDER_CENTRE:
			{
				//tout faire pour garder le centre.
			}
			break;

		default:// well, we're fucked..
			break;//#yolo
		}

		THREAD_MSleep(200);
	}

	return 0;
}
