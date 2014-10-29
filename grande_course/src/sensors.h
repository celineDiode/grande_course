/*
 * sensors.h
 *
 *  Created on: 2014-10-28
 *      Author: thor4_000
 */

#ifndef SENSORS_H_
#define SENSORS_H_

const int frequenceAcquisition=1000;
const int IDcouleurRouge=1;
const int IDcouleurVert=2;
const int IDcouleurBleu=3;
const int IDligneGauche=4;
const int IDligneCentre=5;
const int IDligneDroite=6;
const int IDdistanceIR=4;
const int IDdetecteur5kHz=8;

const int IDpowerCouleur=9;
const int IDpowerDistanceIR=10;
const int IDpowerDetecteur5khz=16;

typedef struct{
	bool gauche;
	bool centre;
	bool droite;
}Ligne;
typedef struct {
	int rouge;
	int vert;
	int bleu;
}Couleur;

typedef struct{
	int distance1;
}Distance;

typedef struct{
	bool avant;
	bool arriere;
	bool gauche;
	bool droit;
}Bumper;

typedef struct{
	int droit;
	int gauche;
}Encodeurs;

typedef struct{
	Ligne ligne;
	Couleur couleur;
	Bumper bumper;
	Distance distance;
	Encodeurs encodeurs;
}Capteur;

extern Capteur capteur;;

void getCouleurs(void);
void getLignes();
float getDistanceGP2D12cm();
void attendreSignalDepart();
void* lireCapteurs(void* a);
void fermerCapteurs();
int test();

#endif /* SENSORS_H_ */
