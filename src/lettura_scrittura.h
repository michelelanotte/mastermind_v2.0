/*
 * lettura_scrittura.h
 *
 *  Created on: 17 dic 2016
 *      Author: Michele97
 */

#ifndef LETTURA_SCRITTURA_H_
#define LETTURA_SCRITTURA_H_

#include "globali.h"

void Scrivere_max_tentativi(settings *impostazioni, int valore);
void Scrivere_lunghezza(settings *impostazioni, int valore);
void Scrivere_doppioni(settings *impostazioni, int valore);
void Scrivere_info_partita(dati_gioco *info_partita, settings impostazioni);
void Scrivere_elemento_generato(int numero_generato, dati_gioco *info_partita, int posizione);
void Scrivere_tentativo_corrente(dati_gioco *info_partita, int tentativo);
void Scrivere_elemento_utente(int numero, dati_gioco *info_partita, int posizione, int tentativo);
void Scrivere_elemento_temp(int valore, codice *codice_temp, int posizione);
void Inizializzare_valutazione(char valutazione[LUNGHEZZA_MAX], int lunghezza);
void Scrivere_valutazione(char carattere, char valutazione[], int posizione);

int Leggere_max_tentativi(settings impostazioni);
int Leggere_lunghezza(settings impostazioni);
int Leggere_doppioni(settings impostazioni);
int Leggere_difficolta(dati_gioco info_partita);
int Leggere_elemento_generato(dati_gioco info_partita, int posizione);
int Leggere_elemento_utente(dati_gioco info_partita, int posizione, int tentativo);
int Leggere_corretti(dati_gioco info_partita, int tentativo);
int Leggere_presenti(dati_gioco info_partita, int tentativo);
int Leggere_elemento_temp(codice codice_temp, int posizione);
int Leggere_tentativo(dati_gioco info_partita);

#endif /* LETTURA_SCRITTURA_H_ */
