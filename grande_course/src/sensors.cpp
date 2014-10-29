/*
 * sensors.cpp
 *
 *  Created on: 2014-10-28
 *      Author: berf2308
 */

#include <libarmus.h>

int frequenceAcquisition=1000;
int IDcouleurRouge=1;
int IDcouleurVert=2;
int IDcouleurBleu=3;
int IDligneGauche=4;
int IDligneCentre=5;
int IDligneDroite=6;
int IDdistanceIR=4;
int IDdetecteur5kHz=8;

int IDpowerCouleur=9;
int IDpowerDistanceIR=10;
int IDpowerDetecteur5khz=16;

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
	Ligne ligne;
	Couleur couleur;
	Bumper bumper;
	Distance distance;
}Capteur;


Capteur capteur;

void getCouleurs(){
	DIGITALIO_Write(IDpowerCouleur,1);
	MOTOR_SetSpeed(6,100);
	THREAD_MSleep(50);
	capteur.couleur.rouge = ANALOG_Read(IDcouleurRouge);
	capteur.couleur.vert = ANALOG_Read(IDcouleurVert);
	capteur.couleur.bleu = ANALOG_Read(IDcouleurBleu);
	THREAD_MSleep(10);
	MOTOR_SetSpeed(6,0);
	DIGITALIO_Write(IDpowerCouleur,0);
}
void getLignes(){
	capteur.ligne.gauche=(ANALOG_Read(IDligneGauche)<512);
	capteur.ligne.centre=(ANALOG_Read(IDligneCentre)<512);
	capteur.ligne.droite=(ANALOG_Read(IDligneDroite)<512);
}

float getDistanceGP2D12cm(){
	DIGITALIO_Write(IDpowerDistanceIR,1);
	THREAD_MSleep(100);
	int voltageINT=ANALOG_Read(IDdistanceIR);
	float voltage=static_cast<float>(voltageINT);
	voltage*=(5.0/1023);
	float distance=23.53/(voltage-0.129)-0.42;
	if (distance>50.0 || distance <9.0)
		distance=-1.0;
	capteur.distance.distance1=distance;
	DIGITALIO_Write(IDpowerDistanceIR,0);
	return distance;
}

void attendreSignalDepart(){
	bool depart=0;
	DIGITALIO_Write(IDpowerDetecteur5khz,1);
	THREAD_MSleep(1000);
	LCD_ClearAndPrint("En attente du signal de depart...");
	while (ANALOG_Read(IDdetecteur5kHz)<512){
		THREAD_MSleep(100);
	}
	DIGITALIO_Write(IDpowerDetecteur5khz,0);
}
void lireCapteurs(){
	while(1){
	getCouleurs();
	//getLignes();
	getDistanceGP2D12cm();
	THREAD_MSleep(frequenceAcquisition);
	}
}

void fermerCapteurs(){
	DIGITALIO_Write(IDpowerCouleur,0);
	DIGITALIO_Write(IDpowerDistanceIR,0);
}
int test(){
	fermerCapteurs();
	attendreSignalDepart();
	while(1){
		getCouleurs();
		getDistanceGP2D12cm();
		LCD_ClearAndPrint("R:%i  G:%i  B:%i\n",capteur.couleur.rouge,capteur.couleur.vert,capteur.couleur.bleu);
		LCD_Printf("Distance CM: %d",capteur.distance.distance1);
		THREAD_MSleep(1000);
	}
	return 0;
}
