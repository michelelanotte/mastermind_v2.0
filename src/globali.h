/*
 * globali.h
 *
 *  Created on: 16 dic 2016
 *      Author: Michele97
 */

#ifndef GLOBALI_H_
#define GLOBALI_H_


#include<stdio.h>
#include<stdlib.h>

//-----------------------definizione delle costanti-----------------------
#define LUNGHEZZA_MAX 8
#define VALMAX 9
#define VALMIN 0
#define MAX_TENTATIVI 27
#define DIM_MAX 20


//-----------------------definizione delle strutture-----------------------

typedef struct {
  int corretti;
  int sbagliati;
  int codice_utente[LUNGHEZZA_MAX];
}supporto1;

typedef struct {
  int tentativo;
  int max_tentativi;
  int lunghezza_codice;
  int codice_generato[LUNGHEZZA_MAX];
  supporto1 info_cod_utente[MAX_TENTATIVI];
}dati_gioco;



typedef struct {
  int codice_gioco[LUNGHEZZA_MAX];
  int lunghezza_codice;
}codice;

typedef struct {
	int numero_tentativi;
	int lunghezza;
	int doppioni;
}settings;

#endif /* GLOBALI_H_ */
