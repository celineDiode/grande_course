/*
 * contourne_obstacle.cpp
 *
 *  Created on: 2014-10-28
 *      Author: thor4_000
 */
#include "sensors.cpp"
#include "Math.cpp"
#include "mouvements.h"

float distanceCritique=15.0;
float variationMouvement=3.5;

void Contourne_Obstacle (int direction)
{
	bool obstacleMouvant=0;
	do{
		float distanceInitiale=capteur.distance.distance1;
		THREAD_MSleep(550);//temps d'attente
		float variation=capteur.distance.distance1-distanceInitiale;
		if (absf(variation)>variationMouvement)
			obstacleMouvant=1;
		else
			obstacleMouvant=0;
	}while(obstacleMouvant||capteur.distance.distance1<distanceCritique);

	//Si l'obstacle n'est plus là, on continue
	if (capteur.distance.distance1>distanceCritique){
		MOVE_Resume();
		return;
	}

	//L'obstacle est fixe, on l'évite!
	MOVE_Tourner(45);
	THREAD_MSleep(550);
	if (capteur.distance.distance1>distanceCritique){
		MOVE_Avance(20);
		MOVE_Tourner(-45);
		MOVE_Resume();
		return;
	}
	else{
		MOVE_Tourner(-90);
		MOVE_Avance(20);
		MOVE_Tourner(45);
		MOVE_Resume();
		return;
	}
}





