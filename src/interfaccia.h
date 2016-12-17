/*
 * interfaccia.h
 *
 *  Created on: 17 dic 2016
 *      Author: Michele97
 */

#ifndef INTERFACCIA_H_
#define INTERFACCIA_H_

#include <windows.h>
#include "globali.h"
#include "lettura_scrittura.h"
#include "operazioni.h"

void Pagina_principale();
void gotoxy(int x, int y);
void Stampare_titolo();
void Stampare_menu();
void Stampare_risultati_precedenti(dati_gioco info_partita, int tentativo, int y);
void Acquisire_parola_utente(dati_gioco *info_partita, int riga, int tentativo);
void Pulire_riga(int y);
void Cancellare_errore(int x, int y);
void Stampare_esito(dati_gioco info_partita, int esito_parole_uguali, int tentativo_ultimo);

void Stampare_livelli_difficolta();

#define N_COLONNE_DISPLAY 80

#endif /* INTERFACCIA_H_ */
