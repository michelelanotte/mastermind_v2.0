#ifndef INTERFACCIA_H_
#define INTERFACCIA_H_

#include <windows.h>
#include <unistd.h>
#include <string.h>
#include "globali.h"
#include "lettura_scrittura.h"
#include "operazioni.h"

#define DIM_PERCORSO 300
#define N_RIGHE_DISPLAY 25
#define N_COLONNE_DISPLAY 80

void Pagina_principale(settings *impostazioni);
void gotoxy(int x, int y);
void Stampare_titolo();
void Stampare_menu();
void Interfaccia_acquisizione(settings *impostazioni, dati_gioco *info_partita, int *contatore_tentativi, int *esito_parole_uguali);
void Stampare_risultati_precedenti(dati_gioco info_partita, int tentativo, int y);
void Acquisire_parola_utente(dati_gioco *info_partita, int riga, int tentativo, int spazio_libero, settings *impostazioni);
void Scrolling_tentativi_precedenti(dati_gioco info_partita, int spazio_libero, int primo_stampato);
void Pulire_riga(int y);
void Cancellare_errore(int x, int y);
void Stampare_esito(dati_gioco info_partita, int esito_parole_uguali, int tentativo_ultimo, settings *impostazioni);

void Stampare_livelli_difficolta();

void Aiuto(settings *impostazioni);


#endif /* INTERFACCIA_H_ */
