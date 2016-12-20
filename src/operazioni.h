#ifndef OPERAZIONI_H_
#define OPERAZIONI_H_

#include <time.h>
#include <conio.h>
#include "globali.h"
#include "interfaccia.h"
#include "lettura_scrittura.h"

#define N_RIGHE_DISPLAY 25
#define DIM_NOME 15

void Nuova_partita(settings *impostazioni);
void Generare_parola(dati_gioco *info_partita, settings impostazioni);
int Simbolo_presente(int numero_generato, dati_gioco info_partita, int posizione_elemento);
void Valutazione_parola(dati_gioco *info_partita, int tentativo);
int Controllo_parole_uguali(dati_gioco info_partita, int tentativo);
void Conteggiare_valutazioni(int *conteggio_presenti, int *conteggio_corretti, char valutazione[LUNGHEZZA_MAX], int lunghezza);

void Salvataggio_partita(int y, int x, dati_gioco *info_partita, settings *impostazioni);

void Impostazioni(settings *impostazioni);
void Acquisizione_difficolta(settings *impostazioni);
void Acquisire_ammissione_doppioni(settings *impostazioni);

#endif /* OPERAZIONI_H_ */
