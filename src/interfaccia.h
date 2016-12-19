#ifndef INTERFACCIA_H_
#define INTERFACCIA_H_

#include <windows.h>
#include <unistd.h>
#include <string.h>
#include "globali.h"
#include "lettura_scrittura.h"
#include "operazioni.h"

#define DIM_PERCORSO 300

void Pagina_principale(int *numero_tentativi, int *lunghezza, int *doppioni);
void gotoxy(int x, int y);
void Stampare_titolo();
void Stampare_menu();
void Stampare_risultati_precedenti(dati_gioco info_partita, int tentativo, int y);
void Acquisire_parola_utente(dati_gioco *info_partita, int riga, int tentativo);
void Pulire_riga(int y);
void Cancellare_errore(int x, int y);
void Stampare_esito(dati_gioco info_partita, int esito_parole_uguali, int tentativo_ultimo);

void Stampare_livelli_difficolta();

void Aiuto(int *numero_tentativi, int *doppioni, int *lunghezza);

#define N_COLONNE_DISPLAY 80

#endif /* INTERFACCIA_H_ */
