#ifndef OPERAZIONI_H_
#define OPERAZIONI_H_

#include <time.h>
#include <conio.h>
#include "globali.h"
#include "interfaccia.h"
#include "lettura_scrittura.h"

#define N_RIGHE_DISPLAY 25

void Nuova_partita(int *numero_tentativi, int *doppioni, int *lunghezza);
void Generare_parola(dati_gioco *info_partita, int doppioni, int lunghezza);
int Simbolo_presente(int numero_generato, dati_gioco info_partita, int posizione_elemento);
void Valutazione_parola(dati_gioco *info_partita, int tentativo);
int Controllo_parole_uguali(dati_gioco info_partita, int tentativo);
void Conteggiare_valutazioni(int *conteggio_presenti, int *conteggio_corretti, char valutazione[LUNGHEZZA_MAX], int lunghezza);

void Impostazioni(int *lunghezza, int *numero_tentativi, int *doppioni);
void Acquisizione_difficolta(int *lunghezza, int *numero_tentativi, int *doppioni);
void Acquisire_ammissione_doppioni(int *doppioni, int *lunghezza, int *numero_tentativi);

#endif /* OPERAZIONI_H_ */
